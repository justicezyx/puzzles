#include "common.h"

struct iterator {
    bool terminal;
    int data;
    iterator* next;
    iterator* deeper;

    iterator() {
        terminal = false;
    }
};
        
class recursive_iterator {
    private:
        std::stack<iterator> h;

    public:
        int next() {
            while (!h.top().terminal) {
                h.push(h.top().deeper);
            }
            iterator i = h.top();
            h.pop();
            int data = i.data;
            h.push(i.next);
            return data;
        }
}
