class Solution:
    def maximizeSquareHoleArea(
        self,
        n: int,
        m: int,
        hBars: list[int],
        vBars: list[int]
    ) -> int:

        # Helper to find longest consecutive streak
        def longest_consecutive_streak(bars: list[int]) -> int:
            bars.sort()

            max_streak = 1
            curr_streak = 1

            for i in range(1, len(bars)):
                # If bars are consecutive, extend streak
                if bars[i] == bars[i - 1] + 1:
                    curr_streak += 1
                else:
                    curr_streak = 1

                max_streak = max(max_streak, curr_streak)

            return max_streak

        # Compute max gaps in both directions
        max_height = longest_consecutive_streak(hBars) + 1
        max_width = longest_consecutive_streak(vBars) + 1

        # Largest square side
        side = min(max_height, max_width)

        return side * side
