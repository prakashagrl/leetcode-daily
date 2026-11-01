class Solution
{
public:
       int uniquePaths(vector<vector<int>> &grid)
       {
              const int MOD = 1e9 + 7;

              int m = grid.size();
              int n = grid[0].size();

              // dp[i][j][0] = ways entering (i,j) from the left (rightward)
              // dp[i][j][1] = ways entering (i,j) from above (downward)
              vector<vector<vector<int>>> dp(
                  m, vector<vector<int>>(n, vector<int>(2, 0)));

              dp[0][0][0] = 1;

              for (int i = 0; i < m; i++)
              {
                     for (int j = 0; j < n; j++)
                     {

                            int right = dp[i][j][0];
                            int down = dp[i][j][1];

                            if (grid[i][j] == 0)
                            {
                                   // Empty cell: robot can move either right or down
                                   int ways = (right + down) % MOD;

                                   if (j + 1 < n)
                                   {
                                          dp[i][j + 1][0] =
                                              (dp[i][j + 1][0] + ways) % MOD;
                                   }

                                   if (i + 1 < m)
                                   {
                                          dp[i + 1][j][1] =
                                              (dp[i + 1][j][1] + ways) % MOD;
                                   }
                            }
                            else
                            {
                                   // Mirror cell: reflect according to entry direction

                                   // Entered while moving right -> redirected down
                                   if (i + 1 < m)
                                   {
                                          dp[i + 1][j][1] =
                                              (dp[i + 1][j][1] + right) % MOD;
                                   }

                                   // Entered while moving down -> redirected right
                                   if (j + 1 < n)
                                   {
                                          dp[i][j + 1][0] =
                                              (dp[i][j + 1][0] + down) % MOD;
                                   }
                            }
                     }
              }

              return (dp[m - 1][n - 1][0] +
                      dp[m - 1][n - 1][1]) %
                     MOD;
       }
};