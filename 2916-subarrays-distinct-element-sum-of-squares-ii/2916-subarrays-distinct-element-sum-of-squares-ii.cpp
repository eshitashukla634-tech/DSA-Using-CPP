class Solution {
public:
    const long long MOD = 1000000007;

    vector<long long> sum, sq, lazy;

    void push(int node, int l, int r) {
        if (lazy[node] == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        long long v = lazy[node];

        apply(node * 2, l, mid, v);
        apply(node * 2 + 1, mid + 1, r, v);

        lazy[node] = 0;
    }

    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;

        sq[node] = (sq[node] + 2 * v % MOD * sum[node] % MOD
                    + v * v % MOD * len % MOD) % MOD;

        sum[node] = (sum[node] + v * len) % MOD;
        lazy[node] = (lazy[node] + v) % MOD;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
        sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;

        if (ql <= l && r <= qr)
            return sq[node];

        push(node, l, r);

        int mid = (l + r) / 2;

        return (query(node * 2, l, mid, ql, qr)
              + query(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        sum.assign(4 * n + 5, 0);
        sq.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = -1;

            if (last.count(nums[i]))
                prev = last[nums[i]];

            update(1, 0, n - 1, prev + 1, i);

            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};