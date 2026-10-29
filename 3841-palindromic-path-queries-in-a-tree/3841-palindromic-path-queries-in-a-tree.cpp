class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(n, vector<int>(17));
        vector<int> mask(n);
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[u][0] = p;

            for (int j = 1; j < 17; j++)
                up[u][j] = up[up[u][j - 1]][j - 1];

            mask[u] = 1 << (s[u] - 'a');

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer - 1;
        };

        dfs(0, 0);

        vector<int> bit(n + 1);

        auto update = [&](int i, int val) {
            for (i++; i <= n; i += i & -i)
                bit[i] ^= val;
        };

        auto query = [&](int i) {
            int res = 0;
            for (i++; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        vector<int> base(n);
        function<void(int, int, int)> build = [&](int u, int p, int cur) {
            cur ^= 1 << (s[u] - 'a');
            base[tin[u]] = cur;

            for (int v : adj[u]) {
                if (v != p)
                    build(v, u, cur);
            }
        };

        build(0, -1, 0);

        auto rangeUpdate = [&](int l, int r, int val) {
            update(l, val);
            if (r + 1 < n) update(r + 1, val);
        };

        auto getMask = [&](int u) {
            return base[tin[u]] ^ query(tin[u]);
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < 17; j++)
                if (diff & (1 << j))
                    u = up[u][j];

            if (u == v) return u;

            for (int j = 16; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    u = up[u][j];
                    v = up[v][j];
                }
            }

            return up[u][0];
        };

        vector<bool> ans;

        for (string q : queries) {
            stringstream ss(q);
            string op;
            int u;
            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;

                int change = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                rangeUpdate(tin[u], tout[u], change);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);
                int m = getMask(u) ^ getMask(v) ^ (1 << (s[w] - 'a'));

                ans.push_back((m & (m - 1)) == 0);
            }
        }

        return ans;
    }
};