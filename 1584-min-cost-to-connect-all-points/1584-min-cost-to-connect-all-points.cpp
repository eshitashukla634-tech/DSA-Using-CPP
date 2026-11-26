class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();

        vector<int> dist(n, INT_MAX);
        vector<bool> visited(n, false);

        dist[0] = 0;

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int u = -1;

            // Find the nearest unvisited point
            for (int j = 0; j < n; j++) {
                if (!visited[j] &&
                    (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            visited[u] = true;
            ans += dist[u];

            // Update distances of remaining points
            for (int v = 0; v < n; v++) {
                if (!visited[v]) {
                    int cost = abs(points[u][0] - points[v][0])
                             + abs(points[u][1] - points[v][1]);

                    dist[v] = min(dist[v], cost);
                }
            }
        }

        return ans;
    }
};