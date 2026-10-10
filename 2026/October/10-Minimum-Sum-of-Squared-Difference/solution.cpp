class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<int> diff(n);
        int mx = 0;
        long long total = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
            total += diff[i];
        }

        if (total <= k) return 0;

        int low = 0, high = mx;

        // Find the largest level x such that reducing
        // every difference above x to x takes at most k operations.
        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid) need += d - mid;
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long used = 0, ans = 0;

        for (int d : diff) {
            if (d > level) {
                used += d - level;
                d = level;
            }
            ans += 1LL * d * d;
        }

        // Distribute leftover operations by reducing some values
        // from level to level - 1.
        long long remaining = k - used;

        for (int i = 0; i < n && remaining > 0; i++) {
            // This difference must originally have been at least level.
            if (diff[i] >= level && level > 0) {
                ans -= 2LL * level - 1;
                remaining--;
            }
        }

        return ans;
    }
};