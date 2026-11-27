
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> dp(budget + 1, 0);

        int minPrice = INT_MAX;

        // Find the cheapest item.
        for (auto& item : items) {
            minPrice = min(minPrice, item[1]);
        }

        // 0/1 Knapsack: Activate each item type at most once.
        for (int i = 0; i < n; i++) {
            int factor = items[i][0];
            int price = items[i][1];

            int gain = 0;

            // Calculate first-purchase benefit.
            for (int j = 0; j < n; j++) {
                if (items[j][0] % factor == 0) {
                    gain++;
                }
            }

            // 0/1 Knapsack transition.
            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j], dp[j - price] + gain);
            }
        }

        // Use the remaining budget to buy the cheapest item.
        int ans = 0;

        for (int j = 0; j <= budget; j++) {
            int extra = (budget - j) / minPrice;

            ans = max(ans, dp[j] + extra);
        }

        return ans;
    }
};
