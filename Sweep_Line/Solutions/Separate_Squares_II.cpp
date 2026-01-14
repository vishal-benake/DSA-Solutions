class Solution {
public:
    struct Event {
        long long y, type, x1, x2;
        bool operator<(const Event& other) const {
            return y < other.y;
        }
    };

    vector<long long> xs;
    vector<int> cover;
    vector<double> length;

    // Push-up to maintain union length
    void pushUp(int node, int l, int r) {
        if (cover[node] > 0) {
            length[node] = xs[r] - xs[l];
        } else if (l + 1 == r) {
            length[node] = 0.0;
        } else {
            length[node] = length[node * 2] + length[node * 2 + 1];
        }
    }

    void update(int ql, int qr, int val, int node, int l, int r) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            cover[node] += val;
            pushUp(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(ql, qr, val, node * 2, l, mid);
        update(ql, qr, val, node * 2 + 1, mid, r);
        pushUp(node, l, r);
    }

    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;
        xs.clear();

        // ------------------------------------------------------------
        // STEP 1: Build sweep events
        // ------------------------------------------------------------
        for (auto& s : squares) {
            long long x = s[0], y = s[1], l = s[2];
            events.push_back({y, 1, x, x + l});
            events.push_back({y + l, -1, x, x + l});
            xs.push_back(x);
            xs.push_back(x + l);
        }

        // ------------------------------------------------------------
        // STEP 2: Coordinate compression on X-axis
        // ------------------------------------------------------------
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        int n = xs.size() - 1;
        cover.assign(4 * n, 0);
        length.assign(4 * n, 0.0);

        sort(events.begin(), events.end());

        // ------------------------------------------------------------
        // STEP 3: Sweep line on Y-axis
        // ------------------------------------------------------------
        vector<tuple<double, double, double>> slabs;
        long long prevY = events[0].y;

        for (auto& e : events) {
            double currWidth = length[1];
            if (e.y > prevY && currWidth > 0) {
                slabs.push_back({(double)prevY, (double)e.y, currWidth});
            }

            int l = lower_bound(xs.begin(), xs.end(), e.x1) - xs.begin();
            int r = lower_bound(xs.begin(), xs.end(), e.x2) - xs.begin();
            update(l, r, e.type, 1, 0, n);
            prevY = e.y;
        }

        // ------------------------------------------------------------
        // STEP 4: Find minimal Y where area below equals half
        // ------------------------------------------------------------
        double totalArea = 0.0;
        for (auto& s : slabs)
            totalArea += (get<1>(s) - get<0>(s)) * get<2>(s);

        double half = totalArea / 2.0;
        double acc = 0.0;

        for (auto& s : slabs) {
            double y1 = get<0>(s), y2 = get<1>(s), w = get<2>(s);
            double area = (y2 - y1) * w;
            if (acc + area >= half) {
                return y1 + (half - acc) / w;
            }
            acc += area;
        }

        return 0.0;
    }
};
