
class Solution:
    def minTimeToVisitAllPoints(self, points: List[List[int]]) -> int:
        total_time = 0

        # Traverse all consecutive point pairs
        for i in range(1, len(points)):
            x1, y1 = points[i - 1]
            x2, y2 = points[i]

            # Distance along x and y axis
            dx = abs(x1 - x2)
            dy = abs(y1 - y2)

            """
            Since diagonal moves are allowed:
            - One diagonal move reduces both dx and dy by 1
            - Remaining distance is handled by straight moves

            Therefore, minimum time needed is:
            max(dx, dy)
            """
            total_time += max(dx, dy)

        return total_time
