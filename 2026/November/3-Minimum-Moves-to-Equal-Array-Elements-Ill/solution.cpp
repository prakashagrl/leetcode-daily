class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        long long moves = 0;

        for (int x : nums) {
            moves += mx - x;
        }

        return moves;
    }
};