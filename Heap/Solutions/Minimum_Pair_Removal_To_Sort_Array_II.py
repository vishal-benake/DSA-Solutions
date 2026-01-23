from typing import List
from itertools import pairwise
import heapq

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)

        # If already non-decreasing, no operations needed
        if all(x <= y for x, y in pairwise(nums)):
            return 0

        # rmv[i] = whether index i has been removed
        rmv = [False] * n

        # Doubly linked list using indices
        prv = [i - 1 for i in range(n)]
        nxt = [i + 1 if i + 1 < n else -1 for i in range(n)]

        # Min-heap of (adjacent_sum, left_index)
        heap = [(nums[i] + nums[i + 1], i) for i in range(n - 1)]
        heapq.heapify(heap)

        # Count of adjacent violations nums[i] > nums[i+1]
        bad = sum(nums[i] > nums[i + 1] for i in range(n - 1))

        operations = 0

        while bad > 0:
            pair_sum, i = heapq.heappop(heap)

            # Validate left index
            if rmv[i] or nxt[i] == -1:
                continue

            j = nxt[i]

            # Validate right index and stale heap entries
            if rmv[j] or nums[i] + nums[j] != pair_sum:
                continue

            pi = prv[i]
            nj = nxt[j]

            # Remove old violations
            if pi != -1 and nums[pi] > nums[i]:
                bad -= 1
            if nums[i] > nums[j]:
                bad -= 1
            if nj != -1 and nums[j] > nums[nj]:
                bad -= 1

            # Merge i and j
            nums[i] = pair_sum
            rmv[j] = True

            nxt[i] = nj
            if nj != -1:
                prv[nj] = i

            # Add new violations
            if pi != -1 and nums[pi] > nums[i]:
                bad += 1
            if nj != -1 and nums[i] > nums[nj]:
                bad += 1

            # Push updated adjacent sums
            if pi != -1:
                heapq.heappush(heap, (nums[pi] + nums[i], pi))
            if nj != -1:
                heapq.heappush(heap, (nums[i] + nums[nj], i))

            operations += 1

        return operations