class Solution
{
public:
       int numDistinct(string s, string t)
       {
              int n = s.size();
              int m = t.size();

              vector<int> dp(m + 1, 0);
              dp[0] = 1;

              for (int i = 0; i < n; i++)
              {
                     for (int j = m; j >= 1; j--)
                     {
                            if (s[i] == t[j - 1])
                            {
                                   long long sum = (long long)dp[j] + dp[j - 1];

                                   if (sum > INT_MAX)
                                          dp[j] = INT_MAX;
                                   else
                                          dp[j] = (int)sum;
                            }
                     }
              }

              return dp[m];
       }
};