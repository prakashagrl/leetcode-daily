class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        // dp[i] = number of distinct subsequences
        // using the first i characters, including empty subsequence
        vector<long long> dp(s.size() + 1, 0);

        dp[0] = 1;

        // Last occurrence of each character
        vector<int> last(26, -1);

        for (int i = 1; i <= s.size(); i++) {
            int c = s[i - 1] - 'a';

            // Add all subsequences formed by appending s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;

            // If this character appeared before,
            // remove duplicate subsequences.
            if (last[c] != -1) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }

            last[c] = i;
        }

        // Remove the empty subsequence
        return (dp[s.size()] - 1 + MOD) % MOD;
    }
};