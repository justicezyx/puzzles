#include <cassert>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

// Implements a class that does the assignment of IP addresses to mac address.
// Use integer to represent IP address [0, ), and string to represent mac
// address.
//
// Each assigned IP address has a lease time. After lease expired, the address
// is free and can be assigned to another mac address.
//
// The assignment needs to meet these rules:
// 1. If a new mac address is given, it will be assigned the IP address that is
// the least recently used. In case all previously assigned IPs are still in
// use, assign a new one with smallest integer value.
// 2. If a mac address has been assigned to an IP before, the assignment rule
// will prefer to assign the same address last time it was assigned. If this
// cannot be done, follow rule #1.
// 3. If a mac address still has an assigned IP, extend the lease term for the
// IP address.
class IPAssigner {
  public:
    // Assign an IP to the input |mac|.
    int Assign(const std::string& mac);

    std::string Dump() const;

  private:
    // Returns an IP that can be assigned to |mac|.
    int FindIP(const std::string& mac);

    // Returns the least recently used IP and its original lease term.
    std::pair<int, int> FindTheLeastRecentlyUsedIP();

    // Update internal data structure when assign |ip| to |mac|.
    void AssignIP(const std::string& mac, const int ip);

    // Map between the IP address to its latest user, i.e., the mac address.
    std::unordered_map<int, std::string> ip_lastest_user_map_;

    // Map between IP and its latest expiration time stamp.
    std::map<int, clock_t> ip_term_;
    std::unordered_map<std::string, int> ip_table_;

    int next_available_ip_ = 1;
};

const clock_t LEASE_TERM = 1;

// Returns the current time in millisecond.
clock_t Now() {
  return clock();
}

int IPAssigner::Assign(const std::string& mac) {
  auto ip = FindIP(mac);
  AssignIP(mac, ip);
  return ip;
}

std::string IPAssigner::Dump() const {
  std::ostringstream oss;
  oss << std::endl;
  oss << ">>> now: " << Now() << " <<<" << std::endl;
  for (const auto& ipterm : ip_term_) {
    oss << ipterm.first << " : " << ipterm.second << std::endl;
  }
  oss << "<<< now: " << Now() << " >>>" << std::endl;
  return oss.str();
}

// The data structure used for storing
// [IP:latest expiration (latest used time stamp)]
// is std::map. In this way, if two different IPs that have the same latest used
// time stamp, the IP that is smaller is picked.
//
// This is because the iteration sequence is ordered on the IP address, which is
// represented as int.
std::pair<int, int> IPAssigner::FindTheLeastRecentlyUsedIP() {
  std::pair<int, int> least_recently_used_ipterm = *ip_term_.begin();
  for (const auto& ipterm : ip_term_) {
    if (ipterm.second < least_recently_used_ipterm.second) {
      least_recently_used_ipterm = ipterm;
    }
  }
  return least_recently_used_ipterm;
}

void IPAssigner::AssignIP(const std::string& mac, const int ip) {
  clock_t expiration = Now() + LEASE_TERM;
  ip_term_[ip] = expiration;
  ip_table_[mac] = ip;
  ip_lastest_user_map_[ip] = mac;
}

int IPAssigner::FindIP(const std::string& mac) {
  if (ip_table_.empty()) {
    return next_available_ip_++;
  }

  if (ip_table_.find(mac) == ip_table_.end()) {
    auto tmp = FindTheLeastRecentlyUsedIP();
    if (tmp.second < Now()) {
      return tmp.first;
    } else {
      return next_available_ip_++;
    }
  } else {
    const auto ip = ip_table_[mac];
    const auto term = ip_term_[ip];

    if (term > Now() || ip_lastest_user_map_[ip] == mac) {
      // The IP is still in lease or has not been assigned.
      return ip;
    } else {
      auto tmp = FindTheLeastRecentlyUsedIP();
      if (tmp.second < Now()) {
        return tmp.first;
      } else {
        return next_available_ip_++;
      }
    }
  }
}

int main() {
  IPAssigner ip_assigner;
  std::cout << "a: " << ip_assigner.Assign("a") << std::endl;
  std::cout << "a: " << ip_assigner.Assign("a") << std::endl;
  std::cout << ip_assigner.Dump();
  std::cout << "a: " << ip_assigner.Assign("a") << std::endl;
  std::cout << ip_assigner.Dump();
  std::cout << "b: " << ip_assigner.Assign("b") << std::endl;
  std::cout << ip_assigner.Dump();
}
