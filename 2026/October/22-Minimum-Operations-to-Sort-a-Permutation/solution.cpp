class Solution
{
public:
       int minOperations(vector<int> &nums)
       {
              int n = nums.size();
              int zero = 0;

              for (int i = 0; i < n; i++)
              {
                     if (nums[i] == 0)
                     {
                            zero = i;
                            break;
                     }
              }

              bool increasing = true;
              bool decreasing = true;

              for (int i = 0; i < n; i++)
              {
                     if (nums[i] != (nums[0] + i) % n)
                     {
                            increasing = false;
                     }

                     if (nums[i] != (nums[0] - i + n) % n)
                     {
                            decreasing = false;
                     }
              }

              int ans = INT_MAX;

              if (increasing)
              {
                     ans = min(zero, n - zero + 2);
              }

              if (decreasing)
              {
                     ans = min(ans, min(zero + 2, n - zero));
              }

              return ans == INT_MAX ? -1 : ans;
       }
};