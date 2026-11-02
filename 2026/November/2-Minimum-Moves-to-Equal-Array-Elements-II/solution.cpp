class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int median = nums[nums.size() / 2];
        int moves = 0;

        for (int x : nums) {
            moves += abs(x - median);
        }

        return moves;
    }
};