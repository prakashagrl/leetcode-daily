
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = min(n, 2);

        for (int i = 0; i < n; i++) {

            // Check whether the first two elements are coprime.
            bool valid = true;

            if (i + 1 < n) {
                valid = (gcd(nums[i], nums[i + 1]) == 1);
            }

            for (int j = i + 2; j < n && valid; j++) {

                // Check the new element against all previous elements.
                for (int k = i; k < j; k++) {
                    if (gcd(nums[k], nums[j]) != 1) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
