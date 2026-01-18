class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        """
        Returns the size (side length) of the largest magic square in the grid.
        A magic square has:
        - All row sums equal
        - All column sums equal
        - Both diagonal sums equal
        """

        m, n = len(grid), len(grid[0])

        # Row prefix sum:
        # rowPrefix[r][c] = sum of elements from grid[r][0] to grid[r][c-1]
        rowPrefix = [[0] * (n + 1) for _ in range(m)]

        # Column prefix sum:
        # colPrefix[r][c] = sum of elements from grid[0][c] to grid[r-1][c]
        colPrefix = [[0] * n for _ in range(m + 1)]

        # Build prefix sums
        for i in range(m):
            for j in range(n):
                rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j]
                colPrefix[i + 1][j] = colPrefix[i][j] + grid[i][j]

        # Helper to get row sum in O(1)
        def row_sum(r, c1, c2):
            return rowPrefix[r][c2] - rowPrefix[r][c1]

        # Helper to get column sum in O(1)
        def col_sum(c, r1, r2):
            return colPrefix[r2][c] - colPrefix[r1][c]

        # Maximum possible square size
        max_k = min(m, n)

        # Try larger squares first (early exit optimization)
        for k in range(max_k, 1, -1):
            for r in range(m - k + 1):
                for c in range(n - k + 1):

                    # Target sum = first row of the square
                    target = row_sum(r, c, c + k)
                    valid = True

                    # Check all rows
                    for i in range(r, r + k):
                        if row_sum(i, c, c + k) != target:
                            valid = False
                            break

                    if not valid:
                        continue

                    # Check all columns
                    for j in range(c, c + k):
                        if col_sum(j, r, r + k) != target:
                            valid = False
                            break

                    if not valid:
                        continue

                    # Check main diagonal
                    diag1 = sum(grid[r + i][c + i] for i in range(k))
                    if diag1 != target:
                        continue

                    # Check anti-diagonal
                    diag2 = sum(grid[r + i][c + k - 1 - i] for i in range(k))
                    if diag2 != target:
                        continue

                    return k

        # Every single cell is a magic square
        return 1