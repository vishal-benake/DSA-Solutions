class Solution:
    def specialTriplets(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums)
        
        suffix_cnt = defaultdict(int) 
        for num in nums:
            suffix_cnt[num] += 1
        
        prefix_cnt = defaultdict(int)

        total_triplets = 0

        for j in range(n):
            val = nums[j]
            target = 2 * val

            suffix_cnt[val] -= 1

            total_triplets += prefix_cnt[target] * suffix_cnt[target]
            total_triplets %= MOD

            prefix_cnt[val] += 1

        return total_triplets % MOD