class Solution
{
public:
       int digitSum(int x)
       {
              int sum = 0;
              while (x > 0)
              {
                     sum += x % 10;
                     x /= 10;
              }
              return sum;
       }

       int minSwaps(vector<int> &nums)
       {
              int n = nums.size();

              vector<pair<int, int>> arr;

              for (int x : nums)
              {
                     arr.push_back({x, digitSum(x)});
              }

              sort(arr.begin(), arr.end(), [](auto &a, auto &b)
                   {
            if (a.second != b.second)
                return a.second < b.second;
            return a.first < b.first; });

              unordered_map<int, int> targetIndex;
              for (int i = 0; i < n; i++)
              {
                     targetIndex[arr[i].first] = i;
              }

              vector<bool> visited(n, false);
              int swaps = 0;

              for (int i = 0; i < n; i++)
              {
                     if (visited[i] || targetIndex[nums[i]] == i)
                            continue;

                     int j = i;
                     int cycleSize = 0;

                     while (!visited[j])
                     {
                            visited[j] = true;
                            j = targetIndex[nums[j]];
                            cycleSize++;
                     }

                     if (cycleSize > 1)
                            swaps += cycleSize - 1;
              }

              return swaps;
       }
};