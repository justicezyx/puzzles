/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL) {
            return NULL;
        }
        if (head->next == NULL) {
            return new TreeNode(head->val);
        }
        
        std::vector<ListNode*> h;
        while (head != NULL) {
            h.push_back(head);
            head = head->next;
        }
        return helper(h, 0, h.size());
    }
    
    TreeNode* helper(const std::vector<ListNode*>& nodes, int begin, int end) {
        if (begin >= end) {
            return NULL;
        }
        int mid = begin + (end - begin) / 2;
        
        TreeNode* root = new TreeNode(nodes[mid]->val);
        TreeNode* left = helper(nodes, begin, mid);
        TreeNode* right = helper(nodes, mid + 1, end);
        
        root->left = left;
        root->right = right;
        
        return root;
    }
};
