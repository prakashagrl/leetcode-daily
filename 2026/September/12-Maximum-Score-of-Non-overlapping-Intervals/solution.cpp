class Solution
{
public:
       vector<int> maximumWeight(vector<vector<int>> &intervals)
       {
              int n = intervals.size();

              // {left, right, weight, original index}
              vector<array<int, 4>> a;

              for (int i = 0; i < n; i++)
              {
                     a.push_back({intervals[i][0],
                                  intervals[i][1],
                                  intervals[i][2],
                                  i});
              }

              sort(a.begin(), a.end());

              // next[i] = first interval whose left > a[i].right
              vector<int> next(n);

              for (int i = 0; i < n; i++)
              {
                     int lo = i + 1, hi = n;

                     while (lo < hi)
                     {
                            int mid = lo + (hi - lo) / 2;

                            if (a[mid][0] > a[i][1])
                                   hi = mid;
                            else
                                   lo = mid + 1;
                     }

                     next[i] = lo;
              }

              // dp[i][k] = best result using intervals from i onward,
              // choosing at most k intervals.
              vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));
              vector<vector<vector<int>>> choice(
                  n + 1, vector<vector<int>>(5));

              for (int i = n - 1; i >= 0; i--)
              {
                     for (int k = 1; k <= 4; k++)
                     {

                            // Don't take interval i
                            dp[i][k] = dp[i + 1][k];
                            choice[i][k] = choice[i + 1][k];

                            // Take interval i
                            long long takeScore =
                                a[i][2] + dp[next[i]][k - 1];

                            vector<int> takeChoice = choice[next[i]][k - 1];
                            takeChoice.push_back(a[i][3]);

                            sort(takeChoice.begin(), takeChoice.end());

                            if (takeScore > dp[i][k])
                            {
                                   dp[i][k] = takeScore;
                                   choice[i][k] = takeChoice;
                            }
                            else if (takeScore == dp[i][k] &&
                                     takeChoice < choice[i][k])
                            {
                                   choice[i][k] = takeChoice;
                            }
                     }
              }

              return choice[0][4];
       }
};