class Solution
{
public:
       int reverseDegree(string s)
       {
              int ans = 0;

              for (int i = 0; i < s.size(); i++)
              {
                     int reverseValue = 'z' - s[i] + 1;
                     int position = i + 1;

                     ans += reverseValue * position;
              }

              return ans;
       }
};