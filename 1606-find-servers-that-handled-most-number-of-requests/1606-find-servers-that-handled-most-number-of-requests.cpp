class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        set<int> available;

        // Initially, all servers are available
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finishing time, server index}
        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            int time = arrival[i];

            // Release servers that have finished
            while (!busy.empty() && busy.top().first <= time) {
                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find first available server >= preferred
            auto it = available.lower_bound(preferred);

            // If not found, start from server 0
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            available.erase(it);

            count[server]++;

            // Mark server as busy
            busy.push({time + load[i], server});
        }

        // Find maximum requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};