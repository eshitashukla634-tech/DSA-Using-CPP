class Solution {
public:
    unordered_map<string, vector<string>> adj;
    vector<string> ans;

    void dfs(string airport) {
        while (!adj[airport].empty()) {
            string next = adj[airport].back();
            adj[airport].pop_back();

            dfs(next);
        }

        ans.push_back(airport);
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {

        for (auto& ticket : tickets) {
            adj[ticket[0]].push_back(ticket[1]);
        }

        // Sort destinations in reverse alphabetical order
        for (auto& entry : adj) {
            sort(entry.second.rbegin(), entry.second.rend());
        }

        dfs("JFK");

        reverse(ans.begin(), ans.end());

        return ans;
    }
};