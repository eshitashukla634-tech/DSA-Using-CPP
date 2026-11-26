class Solution {
public:
    vector<vector<int>> adj;
    vector<int> tin, low;
    vector<vector<int>> ans;
    int timer = 0;

    void dfs(int node, int parent) {
        tin[node] = low[node] = timer++;

        for (int neighbor : adj[node]) {

            if (neighbor == parent)
                continue;

            if (tin[neighbor] != -1) {
                low[node] = min(low[node], tin[neighbor]);
            }
            else {
                dfs(neighbor, node);

                low[node] = min(low[node], low[neighbor]);

                if (low[neighbor] > tin[node]) {
                    ans.push_back({node, neighbor});
                }
            }
        }
    }

    vector<vector<int>> criticalConnections(
        int n, vector<vector<int>>& connections) {

        adj.resize(n);
        tin.assign(n, -1);
        low.assign(n, -1);

        for (auto& edge : connections) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(0, -1);

        return ans;
    }
};