class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;
        int minLen = INT_MAX;
        string ans = "";

        for (int right = 0; right < n; right++) {

            if (s[right] == '1') {
                ones++;
            }

            // More than k ones -> shrink window
            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            // Exactly k ones
            if (ones == k) {

                // Remove unnecessary leading zeros
                while (s[left] == '0') {
                    left++;
                }

                int len = right - left + 1;
                string current = s.substr(left, len);

                // Shorter substring is better
                if (len < minLen) {
                    minLen = len;
                    ans = current;
                }
                // Same length -> lexicographically smaller is better
                else if (len == minLen && current < ans) {
                    ans = current;
                }
            }
        }

        return ans;
    }
};