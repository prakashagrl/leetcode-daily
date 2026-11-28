
class Solution
{
public:
       int maximumSaleItems(vector<vector<int>> &items, int budget)
       {
              int n = items.size();

              // Step 1: Count the frequency of each factor
              vector<int> freq(n + 1, 0);
              int minPrice = INT_MAX;

              for (auto &item : items)
              {
                     freq[item[0]]++;
                     minPrice = min(minPrice, item[1]);
              }

              // Step 2: Calculate the number of free-item opportunities
              vector<int> gain(n + 1, 0);

              for (int f = 1; f <= n; f++)
              {
                     for (int j = f; j <= n; j += f)
                     {
                            gain[f] += freq[j];
                     }

                     // Exclude the item itself
                     gain[f]--;
              }

              // Step 3: Collect profitable purchases
              vector<pair<int, int>> offers;

              for (auto &item : items)
              {
                     int price = item[1];
                     int freeCount = gain[item[0]];

                     if (freeCount > 0 && 1LL * price < 2LL * minPrice)
                     {
                            offers.push_back({price, freeCount});
                     }
              }

              // Step 4: Process cheaper offers first
              sort(offers.begin(), offers.end());

              long long ans = 0;
              long long remaining = budget;

              for (auto &offer : offers)
              {
                     long long price = offer.first;
                     long long count = offer.second;

                     long long take = min(count, remaining / price);

                     ans += 2 * take;
                     remaining -= take * price;
              }

              // Step 5: Spend the remaining budget on the cheapest item
              ans += remaining / minPrice;

              return (int)ans;
       }
};
