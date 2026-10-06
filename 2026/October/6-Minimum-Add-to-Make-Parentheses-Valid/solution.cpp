class Solution
{
public:
       int minAddToMakeValid(string s)
       {
              int open = 0;
              int ans = 0;

              for (char c : s)
              {
                     if (c == '(')
                     {
                            open++;
                     }
                     else
                     {
                            if (open > 0)
                            {
                                   open--;
                            }
                            else
                            {
                                   // Need to insert '(' before this ')'
                                   ans++;
                            }
                     }
              }

              // Remaining '(' need closing ')'
              ans += open;

              return ans;
       }
};