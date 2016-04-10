#include "common/common.h"
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) {
        val = v;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

bool comp(const ListNode* l, const ListNode* r) {
    return l->val >= r->val;
}

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<ListNode*> helper;
        helper.reserve(lists.size());
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i] != NULL) {
                helper.push_back(lists[i]);
            }
        }
        make_heap(helper.begin(), helper.end(), comp);
        ListNode* before_head = new ListNode(0);
        ListNode* prev = before_head;
        while (!helper.empty()) {
            pop_heap(helper.begin(), helper.end(), comp);
            ListNode*& tmp = helper.back();
            prev->next = new ListNode(tmp->val);
            prev = prev->next;
            if (tmp->next == NULL) {
                helper.pop_back();
            } else {
                tmp = tmp->next;
                push_heap(helper.begin(), helper.end(), comp);
            }
        }
        return before_head->next;
    }
};

int main() {
    ListNode* l1 = new ListNode(1);
    ListNode* l2 = new ListNode(2);
    ListNode* l3 = new ListNode(2);
    l1->next = l2;
    l2->next = l3;

    ListNode* l4 = new ListNode(1);
    ListNode* l5 = new ListNode(1);
    ListNode* l6 = new ListNode(2);
    l4->next = l5;
    l5->next = l6;

    vector<ListNode*> lists;
    lists.push_back(l1);
    lists.push_back(l2);
    
    Solution sol;
    sol.mergeKLists(lists);
}
