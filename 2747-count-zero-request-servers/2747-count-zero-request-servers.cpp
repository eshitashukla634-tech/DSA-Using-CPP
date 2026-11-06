class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        int m = queries.size();

        // Sort logs by request time
        sort(logs.begin(), logs.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        unordered_map<int, int> mp;
        vector<int> ans(m);

        int left = 0, right = 0;
        int active = 0;

        for (auto [time, index] : q) {

            // Add logs inside the current window
            while (right < logs.size() && logs[right][1] <= time) {
                int id = logs[right][0];

                mp[id]++;

                if (mp[id] == 1)
                    active++;

                right++;
            }

            // Remove logs outside the current window
            while (left < right && logs[left][1] < time - x) {
                int id = logs[left][0];

                mp[id]--;

                if (mp[id] == 0)
                    active--;

                left++;
            }

            ans[index] = n - active;
        }

        return ans;
    }
};