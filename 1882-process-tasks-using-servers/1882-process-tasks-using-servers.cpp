class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> available;

        priority_queue<pair<long long, pair<int, int>>,
            vector<pair<long long, pair<int, int>>>,
            greater<pair<long long, pair<int, int>>>> busy;

        int n = servers.size();
        int m = tasks.size();

        vector<int> ans;

        // Initially, all servers are available
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long time = 0;

        for (int i = 0; i < m; i++) {

            time = max(time, (long long)i);

            // Release servers that have finished their tasks
            while (!busy.empty() && busy.top().first <= time) {

                auto p = busy.top();
                busy.pop();

                int weight = p.second.first;
                int index = p.second.second;

                available.push({weight, index});
            }

            // If no server is available, wait
            if (available.empty()) {
                time = busy.top().first;

                while (!busy.empty() && busy.top().first <= time) {

                    auto p = busy.top();
                    busy.pop();

                    int weight = p.second.first;
                    int index = p.second.second;

                    available.push({weight, index});
                }
            }

            // Select the best available server
            auto p = available.top();
            available.pop();

            int weight = p.first;
            int index = p.second;

            ans.push_back(index);

            // Server becomes busy
            busy.push({
                time + tasks[i],
                {weight, index}
            });
        }

        return ans;
    }
};