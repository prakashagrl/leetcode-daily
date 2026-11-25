
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rank(n), newRank(n);

        // Step 1: Initialize suffix array
        iota(sa.begin(), sa.end(), 0);

        sort(sa.begin(), sa.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        // Assign initial ranks
        for (int i = 1; i < n; i++) {
            newRank[sa[i]] = newRank[sa[i - 1]] +
                (nums[sa[i]] != nums[sa[i - 1]]);
        }

        rank = newRank;

        // Step 2: Build suffix array using doubling
        for (int len = 1; len < n; len *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int ra = (a + len < n) ? rank[a + len] : -1;
                int rb = (b + len < n) ? rank[b + len] : -1;

                return ra < rb;
            });

            newRank[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int a2 = (a + len < n) ? rank[a + len] : -1;
                int b2 = (b + len < n) ? rank[b + len] : -1;

                newRank[b] = newRank[a] +
                    (rank[a] != rank[b] || a2 != b2);
            }

            rank = newRank;
        }

        // Step 3: Build inverse suffix array
        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        // Step 4: Calculate LCP using Kasai's algorithm
        vector<int> lcp(n, 0);
        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) {
                h = 0;
                continue;
            }

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0)
                h--;
        }

        // Step 5: Find the shortest unique subarray
        int ans = n;

        for (int i = 0; i < n; i++) {
            int start = sa[i];

            int maxLCP = 0;

            if (i > 0)
                maxLCP = max(maxLCP, lcp[i]);

            if (i + 1 < n)
                maxLCP = max(maxLCP, lcp[i + 1]);

            int remaining = n - start;

            if (maxLCP < remaining) {
                ans = min(ans, maxLCP + 1);
            }
        }

        return ans;
    }
};
