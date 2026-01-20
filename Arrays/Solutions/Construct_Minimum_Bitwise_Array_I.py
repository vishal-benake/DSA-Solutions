class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        ans = []

        for num in nums:
            best = -1

            # Try all possible x from 0 to num
            for x in range(num + 1):
                if (x | (x + 1)) == num:
                    best = x   # smallest valid x
                    break

            ans.append(best)

        return ans