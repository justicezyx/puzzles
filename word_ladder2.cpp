#include "common.h"

std::vector<std::vector<std::string>> 
min_dist(std::string start, std::string end, std::set<std::string>& dict);

std::vector<std::vector<std::string>> 
findLadders(std::string start, std::string end, std::set<std::string>& dict) {
    std::vector<std::vector<std::string>> res;
    if (start == end) {
        std::vector<std::string> t;
        t.push_back(start);
        res.push_back(t);
        return res;
    }
    
    return min_dist(start, end, dict);
}
    
std::vector<std::vector<std::string>> 
min_dist(std::string start,
         std::string end,
         std::set<std::string>& dict) {
    
    std::set<std::string> cur;
    cur.insert(start);
    std::set<std::string> next;
    
    std::map<std::string, std::vector<std::vector<std::string>>> path_list;
    path_list[start].push_back(std::vector<std::string>(1, start));
    std::vector<std::vector<std::string>> res;
    
    bool found = false;
    for (int i = 2; !found; ++i) {
        if (cur.empty()) {
            // No candidate to explore.
            break;
        }
        next.clear();
        std::set<std::string>::iterator cur_itor = cur.begin();
        std::set<std::string>::iterator cur_end = cur.end();
        
        for (; cur_itor != cur_end; ++cur_itor) {
            std::string word = *cur_itor;
            std::string tmp = *cur_itor;
            std::cout<<"word: "<<word<<std::endl;
            
            for (int j = 0; j < word.size(); ++j) {
                char pc = word[j];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == pc) { continue; }
                    word[j] = c;
                    if (word == end) {
                        found = true;

                        std::vector<std::vector<std::string>>::iterator itor
                            = path_list[tmp].begin();
                        std::vector<std::vector<std::string>>::iterator last
                            = path_list[tmp].end();
                        std::cout<<"word equals end, path num:"<<path_list[tmp].size()<<std::endl;
                        std::cout<<"original word:"<<tmp<<std::endl;
                        for (; itor != last; ++itor) {
                            std::vector<std::string> path = *itor;
                            path.push_back(end);
                            puzzles::print(path.begin(), path.end());
                            res.push_back(path);
                        }
                    }
                    if (dict.find(word) != dict.end()) {
                        next.insert(word);
                        std::vector<std::vector<std::string>> paths
                            = path_list[tmp];
                        
                        std::cout<<"Insert path to: "<<word<<" path number:"<<paths.size()<<std::endl;
                        for (int k = 0; k < paths.size(); ++k) {
                            paths[k].push_back(word);
                            path_list[word].push_back(paths[k]);
                        }
                    }
                }
                word[j] = pc;
            }
        }
        for (std::set<std::string>::iterator itor = next.begin();
             itor != next.end(); ++itor) {
            dict.erase(*itor);
        }
        cur = next;
    }
    return res;
}

void test() {
    std::string A[] = {"ted","tex","red","tax","tad","den","rex","pee"};
    int len = sizeof(A) / sizeof(std::string);
    std::set<std::string> dict(A, A + len);
    std::string start = "red";
    std::string end = "tax";
    std::vector<std::vector<std::string>> res = findLadders(start, end, dict);
    std::cout<<"res size:"<<res.size()<<std::endl;
    for (int i = 0; i < res.size(); ++i) {
      puzzles::print(res[i].begin(), res[i].end());
    }
}

int main() {
    test();
}

