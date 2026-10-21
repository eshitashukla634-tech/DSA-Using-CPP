class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    for (int d = 0; d < 4; d++) {
                        int x = i + dx[d];
                        int y = j + dy[d];

                        if (x < 0 || x >= m ||
                            y < 0 || y >= n ||
                            grid[x][y] == 0) {
                            ans++;
                        }
                    }
                }
            }
        }

        return ans;
    }
};