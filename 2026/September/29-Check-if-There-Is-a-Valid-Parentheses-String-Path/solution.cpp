class Solution
{
public:
       int m, n;
       vector<vector<vector<int>>> dp;

       bool dfs(vector<vector<char>> &grid, int r, int c, int balance)
       {
              // Process current cell
              if (grid[r][c] == '(')
                     balance++;
              else
                     balance--;

              // Balance can never be negative
              if (balance < 0)
                     return false;

              // Too many '(' to close with remaining cells
              int remaining = (m - r - 1) + (n - c - 1);
              if (balance > remaining)
                     return false;

              // Destination
              if (r == m - 1 && c == n - 1)
                     return balance == 0;

              if (dp[r][c][balance] != -1)
                     return dp[r][c][balance];

              bool possible = false;

              // Move down
              if (r + 1 < m)
                     possible |= dfs(grid, r + 1, c, balance);

              // Move right
              if (c + 1 < n)
                     possible |= dfs(grid, r, c + 1, balance);

              return dp[r][c][balance] = possible;
       }

       bool hasValidPath(vector<vector<char>> &grid)
       {
              m = grid.size();
              n = grid[0].size();

              // Number of characters in the path must be even
              if ((m + n - 1) % 2 != 0)
                     return false;

              // A valid parentheses string must start with '('
              // and end with ')'
              if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
                     return false;

              dp.assign(m, vector<vector<int>>(
                               n, vector<int>(m + n, -1)));

              return dfs(grid, 0, 0, 0);
       }
};