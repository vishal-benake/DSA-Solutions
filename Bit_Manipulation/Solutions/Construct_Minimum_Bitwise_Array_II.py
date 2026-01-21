class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        ans = []

        for N in nums:

            # Even numbers cannot be formed
            # since (x | (x + 1)) is always odd
            if N % 2 == 0:
                ans.append(-1)
                continue

            res = -1

            # Iterate from MSB to LSB for minimum x
            for bit in range(30, -1, -1):
                if N & (1 << bit):

                    # Unset this bit
                    x = N ^ (1 << bit)

                    # Validate condition
                    if (x | (x + 1)) == N:
                        res = x
                        break

            ans.append(res)

        return ans