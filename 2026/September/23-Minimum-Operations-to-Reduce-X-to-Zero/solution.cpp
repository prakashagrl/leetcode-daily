class Solution
{
public:
       int minOperations(vector<int> &nums, int x)
       {
              int n = nums.size();

              long long total = 0;
              for (int num : nums)
                     total += num;

              long long target = total - x;

              // If we need to remove the entire array
              if (target == 0)
                     return n;

              // Impossible
              if (target < 0)
                     return -1;

              int left = 0;
              long long sum = 0;
              int maxLen = -1;

              for (int right = 0; right < n; right++)
              {
                     sum += nums[right];

                     while (sum > target && left <= right)
                     {
                            sum -= nums[left];
                            left++;
                     }

                     if (sum == target)
                     {
                            maxLen = max(maxLen, right - left + 1);
                     }
              }

              if (maxLen == -1)
                     return -1;

              return n - maxLen;
       }
};