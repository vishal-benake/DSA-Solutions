class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;

        auto isNonDecreasing = [&](const vector<int>& arr) {
            for (int i = 1; i < arr.size(); i++) {
                if (arr[i] < arr[i - 1]) return false;
            }
            return true;
        };

        while (!isNonDecreasing(nums)) {
            int minSum = INT_MAX;
            int idx = 0;

            // Find leftmost adjacent pair with minimum sum
            for (int i = 0; i + 1 < nums.size(); i++) {
                int s = nums[i] + nums[i + 1];
                if (s < minSum) {
                    minSum = s;
                    idx = i;
                }
            }

            // Replace the pair with their sum
            nums[idx] = minSum;
            nums.erase(nums.begin() + idx + 1);
            operations++;
        }

        return operations;
    }
};
