/**
 * Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the two partitions.
 *
 * For example:noh
 * Given 1->4->3->2->5->2 and x = 3
 * return 1->2->2->4->3->5.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* first_half_before_head = new ListNode(0);
        ListNode* second_half_before_head = new ListNode(0);
        
        ListNode* prev_1 = first_half_before_head;
        ListNode* prev_2 = second_half_before_head;
        
        while (head) {
            if (head->val < x) {
                prev_1->next = head;
                prev_1 = head;
            } else {
                prev_2->next = head;
                prev_2 = head;
            }
            head = head->next;
        }
        prev_1->next = second_half_before_head->next;
        prev_2->next = NULL;
        
        ListNode* res = first_half_before_head->next;
        delete first_half_before_head;
        delete second_half_before_head;
        return res;
    }
};

