#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// Given a |word|, for each char, replace it with '*' and return the list of
// words.
std::vector<std::string> Morph(const std::string& word) {
  std::vector<std::string> result;
  result.reserve(word.size());
  for (int i = 0; i < word.size(); i++) {
    std::string copy = word;
    copy[i] = '*';
    result.push_back(std::move(copy));
  }
  return result;
}

void TestMorph() {
  auto result = Morph("xxx");
  std::vector<std::string> expected({"*xx", "x*x", "xx*"});
  if (result != expected) {
    std::cout<< R"(Morph("error")" << std::endl;
  }
}

// Wraps two maps:
//   morphed key : words
//   morphed key link : words
class WordGroupGraph {
  public:
    void AddWord(const std::string& word) {
      const std::vector<std::string> morphed_keys = Morph(word);
      for (int i = 0; i < morphed_keys.size(); i++) {
        for (int j = i+1; j < morphed_keys.size(); j++) {
          auto link_key = morphed_keys[i] + morphed_keys[j];
          group_links_[link_key].insert(word);
        }
      }
      for (const auto& key : morphed_keys) {
        groups_[key].insert(word);
      }
    }

    // Print the two internal data structure.
    void Print() {
      for (const auto& key_words_pair : groups_) {
        std::cout << key_words_pair.first << std::endl;
        for (const auto& word : key_words_pair.second) {
          std::cout << word << std::endl;
        }
      }

      for (const auto& linkkey_words_pair : group_links_) {
        std:: cout << linkkey_words_pair.first << std::endl;
        for (const auto& word : linkkey_words_pair.second) {
          std::cout << word <<std::endl;
        }
      }
    }

  private:
  std::map<std::string, std::set<std::string>> groups_;
  std::map<std::string, std::set<std::string>> group_links_;
};

void TestWordGroupGraph() {
  std::vector<std::string> words({"ted","tex","red","tax","tad","den","rex","pee"});
  WordGroupGraph word_graph;
  for (const auto& word : words) {
    word_graph.AddWord(word);
  }

  word_graph.Print();
}

int main() {
  TestMorph();
  TestWordGroupGraph();
}
