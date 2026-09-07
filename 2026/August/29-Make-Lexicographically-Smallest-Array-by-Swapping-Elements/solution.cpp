class Solution
{
public:
       vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit)
       {
              int n = nums.size();

              // Store {value, original index}
              vector<pair<int, int>> arr;

              for (int i = 0; i < n; i++)
              {
                     arr.push_back({nums[i], i});
              }

              // Sort by value
              sort(arr.begin(), arr.end());

              int start = 0;

              while (start < n)
              {
                     int end = start;

                     // Find one connected component
                     while (end + 1 < n &&
                            arr[end + 1].first - arr[end].first <= limit)
                     {
                            end++;
                     }

                     // Collect original indices
                     vector<int> indices;

                     for (int i = start; i <= end; i++)
                     {
                            indices.push_back(arr[i].second);
                     }

                     // Values are already sorted because arr is sorted
                     vector<int> values;

                     for (int i = start; i <= end; i++)
                     {
                            values.push_back(arr[i].first);
                     }

                     // Smallest values should go to smallest indices
                     sort(indices.begin(), indices.end());

                     for (int i = 0; i < indices.size(); i++)
                     {
                            nums[indices[i]] = values[i];
                     }

                     start = end + 1;
              }

              return nums;
       }
};