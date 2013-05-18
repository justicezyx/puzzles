class Solution {
public:
    public int longestValidParentheses(String s) {
        if(s == null || s.length() == 0)
            return 0;
        int count = 0;
        Stack<Integer> stack = new Stack<Integer>();  //store position
        for(int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if(!stack.isEmpty() && s.charAt(stack.peek()) == '(' && c == ')') { //if valid
                stack.pop();                                  
                int start = stack.isEmpty() ? -1 : stack.peek();   //get the valid start position
                count = Math.max(count, i - start);   //update the count
            }
            else 
                stack.push(i);
        }
        return count;
    }
};
