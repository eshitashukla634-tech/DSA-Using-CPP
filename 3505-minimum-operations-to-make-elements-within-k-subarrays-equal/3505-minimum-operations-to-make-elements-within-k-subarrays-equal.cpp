class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> left, right;
        long long sumLeft = 0, sumRight = 0;

        // Balance the two multisets
        auto balance = [&]() {
            int need = (x + 1) / 2;

            while (left.size() > need) {
                int val = *left.rbegin();
                left.erase(left.find(val));
                sumLeft -= val;

                right.insert(val);
                sumRight += val;
            }

            while (left.size() < need && !right.empty()) {
                int val = *right.begin();
                right.erase(right.find(val));
                sumRight -= val;

                left.insert(val);
                sumLeft += val;
            }
        };

        // Insert an element
        auto add = [&](int val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sumLeft += val;
            } else {
                right.insert(val);
                sumRight += val;
            }

            balance();
        };

        // Remove an element
        auto remove = [&](int val) {
            auto it = left.find(val);

            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }

            balance();
        };

        // Calculate cost of every window
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        for (int i = 0; i <= n - x; i++) {
            long long median = *left.rbegin();

            cost[i] = median * left.size() - sumLeft
                    + sumRight - median * right.size();

            if (i + x < n) {
                remove(nums[i]);
                add(nums[i + x]);
            }
        }

        // Dynamic Programming
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {

                // Skip current position
                dp[j][i] = dp[j][i - 1];

                // Select a window of length x
                if (i >= x && dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};