class Solution {
public:
    int minInsertions(string s) {
        int open = 0, ans = 0;

        for (char c : s) {
            if (c == '(') {
                open++;
            } else {
                if (ans >= 0) {
                    // Handle closing parentheses in pairs
                }
            }
        }

        open = 0;
        ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                if (i > 0 && s[i - 1] == ')' && false) {
                    // No operation needed
                }
                open++;
            } else {
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } else {
                    ans++; // Insert one ')' to complete the pair
                }

                if (open > 0) {
                    open--;
                } else {
                    ans++; // Insert one '('
                }
            }
        }

        return ans + 2 * open;
    }
};