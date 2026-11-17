class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome.
        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute the cost of every substring.
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;

                // Try every proper divisor.
                for (int d = 1; d < len; d++) {

                    if (len % d != 0) continue;

                    int changes = 0;
                    int groupSize = len / d;

                    // Process each of the d groups.
                    for (int r = 0; r < d; r++) {

                        // Make each group a palindrome.
                        for (int t = 0; t < groupSize / 2; t++) {

                            int left = i + r + t * d;

                            int right = i + r +
                                (groupSize - 1 - t) * d;

                            if (s[left] != s[right]) {
                                changes++;
                            }
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // dp[p][i] = minimum changes to partition
        // first i characters into exactly p substrings.
        vector<vector<int>> dp(
            k + 1, vector<int>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int p = 1; p <= k; p++) {

            for (int i = 2 * p; i <= n; i++) {

                for (int j = 2 * (p - 1); j <= i - 2; j++) {

                    if (dp[p - 1][j] == INF) continue;

                    dp[p][i] = min(
                        dp[p][i],
                        dp[p - 1][j] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};