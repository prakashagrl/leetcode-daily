class Solution
{
public:
       vector<long long> resultArray(vector<int> &nums, int k)
       {
              vector<long long> ans(k, 0);
              vector<long long> prev(k, 0);

              for (int num : nums)
              {
                     vector<long long> cur(k, 0);

                     int val = num % k;

                     // Start a new subarray
                     cur[val]++;

                     // Extend previous subarrays
                     for (int r = 0; r < k; r++)
                     {
                            if (prev[r] == 0)
                                   continue;

                            int newRem = (long long)r * val % k;
                            cur[newRem] += prev[r];
                     }

                     // Add all subarrays ending here
                     for (int r = 0; r < k; r++)
                     {
                            ans[r] += cur[r];
                     }

                     prev.swap(cur);
              }

              return ans;
       }
};