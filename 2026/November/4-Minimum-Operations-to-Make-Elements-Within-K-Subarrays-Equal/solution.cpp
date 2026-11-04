class Solution
{
public:
       long long minOperations(vector<int> &nums, int x, int k)
       {
              int n = nums.size();

              multiset<int> low, high;
              long long sumLow = 0, sumHigh = 0;

              // Insert an element into the sliding window.
              auto add = [&](int val)
              {
                     if (low.empty() || val <= *low.rbegin())
                     {
                            low.insert(val);
                            sumLow += val;
                     }
                     else
                     {
                            high.insert(val);
                            sumHigh += val;
                     }
              };

              // Remove an element from the sliding window.
              auto remove = [&](int val)
              {
                     auto it = low.find(val);

                     if (it != low.end())
                     {
                            low.erase(it);
                            sumLow -= val;
                     }
                     else
                     {
                            it = high.find(val);
                            high.erase(it);
                            sumHigh -= val;
                     }
              };

              // Balance both multisets.
              auto balance = [&]()
              {
                     while (low.size() > high.size() + 1)
                     {
                            int val = *low.rbegin();
                            low.erase(prev(low.end()));
                            sumLow -= val;

                            high.insert(val);
                            sumHigh += val;
                     }

                     while (low.size() < high.size())
                     {
                            int val = *high.begin();
                            high.erase(high.begin());
                            sumHigh -= val;

                            low.insert(val);
                            sumLow += val;
                     }
              };

              // Cost of making the current window equal.
              auto getCost = [&]() -> long long
              {
                     long long median = *low.rbegin();

                     return median * low.size() - sumLow + sumHigh - median * high.size();
              };

              // Calculate the cost of every window of size x.
              vector<long long> cost(n - x + 1);

              for (int i = 0; i < n; i++)
              {
                     add(nums[i]);

                     if (i >= x)
                     {
                            remove(nums[i - x]);
                     }

                     balance();

                     if (i >= x - 1)
                     {
                            cost[i - x + 1] = getCost();
                     }
              }

              // DP: dp[j][i] = minimum cost using first i elements
              // and selecting exactly j non-overlapping windows.
              const long long INF = LLONG_MAX / 4;

              vector<vector<long long>> dp(
                  k + 1, vector<long long>(n + 1, INF));

              dp[0][0] = 0;

              for (int i = 0; i < n; i++)
              {
                     for (int j = 0; j <= k; j++)
                     {
                            if (dp[j][i] == INF)
                                   continue;

                            // Option 1: Skip current element.
                            dp[j][i + 1] = min(
                                dp[j][i + 1],
                                dp[j][i]);

                            // Option 2: Select a window of size x.
                            if (j < k && i + x <= n)
                            {
                                   dp[j + 1][i + x] = min(
                                       dp[j + 1][i + x],
                                       dp[j][i] + cost[i]);
                            }
                     }
              }

              return dp[k][n];
       }
};