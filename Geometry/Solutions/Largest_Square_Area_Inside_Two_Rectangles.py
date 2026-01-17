class Solution:
    def largestSquareArea(self, bottomLeft: List[List[int]], topRight: List[List[int]]) -> int:
        n = len(bottomLeft)
        max_area = 0

        # Iterate over all pairs of rectangles
        for i in range(n):
            for j in range(i + 1, n):

                # Find intersection bottom-left coordinates
                x1 = max(bottomLeft[i][0], bottomLeft[j][0])
                y1 = max(bottomLeft[i][1], bottomLeft[j][1])

                # Find intersection top-right coordinates
                x2 = min(topRight[i][0], topRight[j][0])
                y2 = min(topRight[i][1], topRight[j][1])

                # If rectangles do not overlap, skip this pair
                if x2 <= x1 or y2 <= y1:
                    continue

                # Width and height of the intersection rectangle
                width = x2 - x1
                height = y2 - y1

                # Largest square side that can fit in the intersection
                side = min(width, height)

                # Update maximum square area
                max_area = max(max_area, side * side)

        return max_area