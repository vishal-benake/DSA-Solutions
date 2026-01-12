class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)

        # output[i] will store product of all elements to the LEFT of i
        output = [0] * n

        # For index 0, there are no elements to the left
        output[0] = 1

        # First pass: build prefix products
        for i in range(1, n):
            output[i] = output[i - 1] * nums[i - 1]

        # right will store product of all elements to the RIGHT of i
        right = 1

        # Second pass (from right to left): multiply suffix products
        for i in range(n - 1, -1, -1):
            output[i] *= right
            right *= nums[i]

        return output
