class Solution:
    def separateSquares(self, squares: List[List[int]]) -> float:
        # ------------------------------------------------------------
        # STEP 1: Create sweep events along Y-axis
        # ------------------------------------------------------------
        # Each square contributes:
        #   - entering event at y
        #   - leaving event at y + side_length
        # Each event carries an x-interval [x, x + side)
        events = []
        xs = set()

        for x, y, l in squares:
            events.append((y, 1, x, x + l))        # square enters
            events.append((y + l, -1, x, x + l))   # square leaves
            xs.add(x)
            xs.add(x + l)

        # ------------------------------------------------------------
        # STEP 2: Coordinate compression on X-axis
        # ------------------------------------------------------------
        xs = sorted(xs)
        x_index = {x: i for i, x in enumerate(xs)}

        # Number of elementary x-intervals
        n = len(xs) - 1

        # Segment tree arrays
        cover = [0] * (4 * n)       # coverage count
        length = [0.0] * (4 * n)    # union length

        # ------------------------------------------------------------
        # STEP 3: Segment Tree Helpers
        # ------------------------------------------------------------
        def push_up(node: int, l: int, r: int):
            # If segment is covered by >=1 interval, take full length
            if cover[node] > 0:
                length[node] = xs[r] - xs[l]
            elif l + 1 == r:
                # Leaf interval not covered
                length[node] = 0.0
            else:
                # Merge children
                length[node] = length[node * 2] + length[node * 2 + 1]

        def update(ql: int, qr: int, val: int, node: int = 1, l: int = 0, r: int = n):
            # No overlap
            if qr <= l or r <= ql:
                return
            # Fully covered
            if ql <= l and r <= qr:
                cover[node] += val
                push_up(node, l, r)
                return
            # Partial overlap
            mid = (l + r) // 2
            update(ql, qr, val, node * 2, l, mid)
            update(ql, qr, val, node * 2 + 1, mid, r)
            push_up(node, l, r)

        # ------------------------------------------------------------
        # STEP 4: Sweep line on Y-axis
        # ------------------------------------------------------------
        events.sort()
        slabs = []  # (y_start, y_end, active_union_width)

        prev_y = events[0][0]

        for y, typ, x1, x2 in events:
            current_width = length[1]
            if y > prev_y and current_width > 0:
                slabs.append((prev_y, y, current_width))

            update(x_index[x1], x_index[x2], typ)
            prev_y = y

        # ------------------------------------------------------------
        # STEP 5: Find Y where area below equals half of total area
        # ------------------------------------------------------------
        total_area = sum((y2 - y1) * w for y1, y2, w in slabs)
        half_area = total_area / 2.0

        accumulated = 0.0
        for y1, y2, w in slabs:
            area = (y2 - y1) * w
            if accumulated + area >= half_area:
                return y1 + (half_area - accumulated) / w
            accumulated += area

        return 0.0
