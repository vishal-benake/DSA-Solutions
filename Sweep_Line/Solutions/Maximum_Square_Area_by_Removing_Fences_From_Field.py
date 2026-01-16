class Solution:
    def maxSquareArea(self, m: int, n: int, hFences: list[int], vFences: list[int]) -> int:
        MOD = 10**9 + 7

        # Add boundary fences
        hFences.append(1)
        hFences.append(m)
        vFences.append(1)
        vFences.append(n)

        # Sort fence positions
        hFences.sort()
        vFences.sort()

        # Collect all possible horizontal distances
        horizontal_distances = set()
        H = len(hFences)
        for i in range(H):
            for j in range(i + 1, H):
                horizontal_distances.add(hFences[j] - hFences[i])

        max_side = 0

        # Check vertical distances
        V = len(vFences)
        for i in range(V):
            for j in range(i + 1, V):
                width = vFences[j] - vFences[i]
                if width in horizontal_distances:
                    max_side = max(max_side, width)

        if max_side == 0:
            return -1

        return (max_side * max_side) % MOD
