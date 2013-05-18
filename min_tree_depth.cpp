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
    int depth;
    int min_depth;
public:
    Solution() {
        depth = 0;
        min_depth = std::numeric_limits<int>::max();
    }
    
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return 0;
        }
        return min_path_depth(root, 1);
    }
    
    int min_path_depth(TreeNode* root, int depth) {
        if (root->left == NULL && root->right == NULL) {
            return depth;
        }
        int min = std::numeric_limits<int>::max();
        if (root->left != NULL) {
            int min_l = min_path_depth(root->left, depth + 1);
            min = std::min(min, min_l);
        }
        if (root->right != NULL) {
            int min_r = min_path_depth(root->right, depth + 1);
            min = std::min(min, min_r);
        }
        return min;
    }
};

/**
 * This is one doing the path summation from bottom upwards.
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
    int depth;
    int min_depth;
public:
    Solution() {
        depth = 0;
        min_depth = std::numeric_limits<int>::max();
    }
    
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return 0;
        }
        return min_path_depth(root);
    }
    
    int min_path_depth(TreeNode* root) {
        if (root->left == NULL && root->right == NULL) {
            return 1;
        }
        int min = std::numeric_limits<int>::max();
        if (root->left != NULL) {
            int min_l = min_path_depth(root->left);
            min = std::min(min, min_l);
        }
        if (root->right != NULL) {
            int min_r = min_path_depth(root->right);
            min = std::min(min, min_r);
        }
        return min + 1;
    }
};
