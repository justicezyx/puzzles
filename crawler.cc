#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

using namespace std;

// crawl(url)
// The crawler should start at the root page of a domain, e.g. "https://www.test.com" and print out all unique urls under the domain reachable from the root

// get_hyperlinks("https://www.test.com") => ["/", "/progress/", "https://twitter.com/elon-musk"]

std::vector<std::string> get_hyperlinks(const std::string& url) {
    if (url == "https://www.test.com") {
        return {"https://www.test.com/progress/", "https://twitter.com/elonmusk"};
    } else if (url == "https://www.test.com/progress/") {
        return {"https://www.test.com", "https://www.test.com/jobs/", "https://twitter.com/elonmusk"};
    } else if (url == "https://www.test.com/jobs/") {
        return {};
    }
    throw std::invalid_argument( "invalid url" );
}

void craw(const std::string& root_url, const std::string& initial_root_url, std::unordered_set<std::string>& known_urls) {
  if (known_urls.find(root_url) != known_urls.end()) {
    // Already visited this url.
    return;
  }
  known_urls.insert(root_url);
  std::cout << "visited: " << root_url << std::endl;
  for (const auto& url : get_hyperlinks(root_url)) {
    if (url.size() < initial_root_url.size() || url.substr(0, initial_root_url.size()) != initial_root_url) {
      continue;
    }
    craw(url, initial_root_url, known_urls);
  }
}

void parallel_craw(const std::string& root_url, const std::string& initial_root_url, std::unordered_set<std::string>& known_urls, std::mutex& mutex) {
  {
  std::lock_guard lk(mutex);
  if (known_urls.find(root_url) != known_urls.end()) {
    // Already visited this url.
    return;
  }
  known_urls.insert(root_url);
  }

  std::cout << "visited: " << root_url << std::endl;

  std::vector<std::thread> sub_threads;
  for (const auto& url : get_hyperlinks(root_url)) {
    if (url.size() < initial_root_url.size() || url.substr(0, initial_root_url.size()) != initial_root_url) {
      continue;
    }

    sub_threads.push_back(
      std::thread(parallel_craw, url, std::ref(initial_root_url),
                  std::ref(known_urls), std::ref(mutex)));
  }
  for (auto& t : sub_threads) {
    if (t.joinable()) {
      t.join();
    }
  }
}

std::queue<std::string> g_urls;
std::mutex g_urls_mutex;
std::atomic<int> discovered_urls_count;
std::atomic<int> processed_urls_count;

void craw_bounded_thread(const std::string& initial_root_url, std::unordered_set<std::string>& known_urls, std::mutex& mutex, std::atomic<int>& new_urls_count) {
  while (discovered_urls_count.load() > processed_urls_count.load()) {
  std::string url;
  {
    std::lock_guard lk(g_urls_mutex);
    if (!g_urls.empty()) {
      url = g_urls.front();
      g_urls.pop();
    } else {
      continue;
    }
  }
  {
  std::lock_guard lk(mutex);
  if (known_urls.find(url) != known_urls.end()) {
    ++processed_urls_count;
    // Already visited this url.
    return;
  }
  known_urls.insert(url);
  }

  std::cout << "my thread_id: " << std::this_thread::get_id() << " visited: " << url << std::endl;

  const auto new_urls = get_hyperlinks(url);
  int tmp = 0;
  {
    std::lock_guard lk(g_urls_mutex);
    for (const auto& url : new_urls) {
      if (url.size() < initial_root_url.size() || url.substr(0, initial_root_url.size()) != initial_root_url) {
        continue;
      }
      g_urls.push(url);
      ++tmp;
    }
  }
  discovered_urls_count += tmp;
  ++processed_urls_count;
  }
}

// To execute C++, please define "int main()"
int main() {
  std::unordered_set<std::string> known_urls;
  const std::string root_url = "https://www.test.com";
  std::mutex mutex;
  // craw(root_url, root_url, known_urls);
  // parallel_craw(root_url, root_url, known_urls, mutex);

  g_urls.push(root_url);
  ++discovered_urls_count;

  const int kThreadCount = 2;
  std::vector<std::thread> sub_threads;
  std::vector<atomic<int>> new_urls_counts;

  for (int i = 0; i < kThreadCount; i++) {
    sub_threads.push_back(std::thread(craw_bounded_thread, std::ref(root_url), std::ref(known_urls), std::ref(mutex), std::ref(new_urls_counts.back())));
  }

  for (auto& t : sub_threads) {
    if (t.joinable()) { t.join(); }
  }
  std::cout << "finished" << std::endl;
  return 0;
}
