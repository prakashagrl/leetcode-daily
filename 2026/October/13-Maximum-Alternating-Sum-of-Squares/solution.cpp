class Solution
{
public:
       long long maxAlternatingSum(vector<int> &nums)
       {
              sort(nums.begin(), nums.end(), [](int a, int b)
                   { return abs(a) < abs(b); });

              int n = nums.size();
              long long ans = 0;

              for (int i = 0; i < n / 2; i++)
              {
                     long long large = nums[n - 1 - i];
                     long long small = nums[i];

                     ans += large * large - small * small;
              }

              if (n % 2 == 1)
              {
                     long long mid = nums[n / 2];
                     ans += mid * mid;
              }

              return ans;
       }
};