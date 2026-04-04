#include <vector>
#include <algorithm> // Required for std::reverse

class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return;
        
        // Handle cases where k is larger than array length
        k = k % n;
        if (k == 0) return;

        // 1. Reverse the entire array
        std::reverse(nums.begin(), nums.end());

        // 2. Reverse the first k elements
        std::reverse(nums.begin(), nums.begin() + k);

        // 3. Reverse the remaining n - k elements
        std::reverse(nums.begin() + k, nums.end());
    }
};
