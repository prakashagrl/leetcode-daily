class Solution
{
public
       int minCost(vectorvectorint &grid)
       {
              int m = grid.size();
              int n = grid[0].size();

              vectorvectorunordered_setint dp(
                  m, vectorunordered_setint(n));

              dp[0][0].insert(grid[0][0]);

              for (int i = 0; i m; i++)
              {
                     for (int j = 0; j n; j++)
                     {
                            if (i == 0 && j == 0)
                                   continue;

                            if (i 0)
                            {
                                   for (int x dp[i - 1][j])
                                   {
                                          dp[i][j].insert(x ^ grid[i][j]);
                                   }
                            }

                            if (j 0)
                            {
                                   for (int x dp[i][j - 1])
                                   {
                                          dp[i][j].insert(x ^ grid[i][j]);
                                   }
                            }
                     }
              }

              return min_element(
                  dp[m - 1][n - 1].begin(),
                  dp[m - 1][n - 1].end());
       }
};