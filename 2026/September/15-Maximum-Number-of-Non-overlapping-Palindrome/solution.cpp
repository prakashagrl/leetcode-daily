class Solution
{
public:
       int maxPalindromes(string s, int k)
       {
              int n = s.size();

              // pal[i][j] = true if s[i...j] is a palindrome
              vector<vector<bool>> pal(n, vector<bool>(n, false));

              for (int i = n - 1; i >= 0; i--)
              {
                     for (int j = i; j < n; j++)
                     {
                            if (s[i] == s[j] &&
                                (j - i <= 2 || pal[i + 1][j - 1]))
                            {
                                   pal[i][j] = true;
                            }
                     }
              }

              // dp[i] = maximum number using first i characters
              vector<int> dp(n + 1, 0);

              for (int i = 1; i <= n; i++)
              {
                     // Don't use a palindrome ending at i-1
                     dp[i] = dp[i - 1];

                     // Try every possible starting position
                     for (int j = 0; j <= i - k; j++)
                     {
                            if (pal[j][i - 1])
                            {
                                   dp[i] = max(dp[i], dp[j] + 1);
                            }
                     }
              }

              return dp[n];
       }
};