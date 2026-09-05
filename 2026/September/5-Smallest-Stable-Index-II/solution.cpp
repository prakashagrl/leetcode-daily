class Solution
{
public:
       int firstStableIndex(vector<int> &nums, int k)
       {
              int n = nums.size();

              // suffixMin[i] = minimum value from i to n-1
              vector<int> suffixMin(n);

              suffixMin[n - 1] = nums[n - 1];

              for (int i = n - 2; i >= 0; i--)
              {
                     suffixMin[i] = min(nums[i], suffixMin[i + 1]);
              }

              // Maximum value from 0 to i
              int prefixMax = nums[0];

              // Check from left to right
              for (int i = 0; i < n; i++)
              {
                     prefixMax = max(prefixMax, nums[i]);

                     int score = prefixMax - suffixMin[i];

                     if (score <= k)
                     {
                            return i;
                     }
              }

              return -1;
       }
};