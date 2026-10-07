class Solution {
public:
    unordered_set<string> ans;

    void dfs(string& s, int index, int leftRem, int rightRem,
             int balance, string& cur) {

        if (index == s.size()) {
            if (leftRem == 0 && rightRem == 0 && balance == 0)
                ans.insert(cur);
            return;
        }

        char c = s[index];

        if (c == '(') {
            // Remove this '('
            if (leftRem > 0) {
                dfs(s, index + 1, leftRem - 1, rightRem,
                    balance, cur);
            }

            // Keep this '('
            cur.push_back(c);
            dfs(s, index + 1, leftRem, rightRem,
                balance + 1, cur);
            cur.pop_back();
        }
        else if (c == ')') {
            // Remove this ')'
            if (rightRem > 0) {
                dfs(s, index + 1, leftRem, rightRem - 1,
                    balance, cur);
            }

            // Keep this ')' only if it has a matching '('
            if (balance > 0) {
                cur.push_back(c);
                dfs(s, index + 1, leftRem, rightRem,
                    balance - 1, cur);
                cur.pop_back();
            }
        }
        else {
            // Letter
            cur.push_back(c);
            dfs(s, index + 1, leftRem, rightRem,
                balance, cur);
            cur.pop_back();
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        int leftRem = 0;
        int rightRem = 0;

        // Find minimum removals required
        for (char c : s) {
            if (c == '(') {
                leftRem++;
            }
            else if (c == ')') {
                if (leftRem > 0)
                    leftRem--;
                else
                    rightRem++;
            }
        }

        string cur;

        dfs(s, 0, leftRem, rightRem, 0, cur);

        return vector<string>(ans.begin(), ans.end());
    }
};