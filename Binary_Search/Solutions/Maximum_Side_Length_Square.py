class Solution:
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        m, n = len(mat), len(mat[0])

        # prefix[i][j] stores sum of submatrix
        # from (0,0) to (i-1,j-1)
        prefix = [[0] * (n + 1) for _ in range(m + 1)]

        # Build 2D prefix sum
        for i in range(m):
            for j in range(n):
                prefix[i + 1][j + 1] = (
                    mat[i][j]
                    + prefix[i][j + 1]
                    + prefix[i + 1][j]
                    - prefix[i][j]
                )

        # Check if a k x k square exists with sum <= threshold
        def is_valid(k: int) -> bool:
            for i in range(m - k + 1):
                for j in range(n - k + 1):
                    total = (
                        prefix[i + k][j + k]
                        - prefix[i][j + k]
                        - prefix[i + k][j]
                        + prefix[i][j]
                    )
                    if total <= threshold:
                        return True
            return False

        # Binary search on square side length
        left, right = 1, min(m, n)
        ans = 0

        while left <= right:
            mid = (left + right) // 2
            if is_valid(mid):
                ans = mid      # mid is valid
                left = mid + 1 # try larger size
            else:
                right = mid - 1

        return ans