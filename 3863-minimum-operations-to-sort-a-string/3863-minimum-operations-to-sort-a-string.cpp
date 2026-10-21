class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Already sorted
        bool sorted = true;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted) {
            return 0;
        }

        // Cannot sort an unsorted string of length 2
        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // One operation is enough
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // Check whether the minimum or maximum is in the middle
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        // Otherwise, three operations are required
        return 3;
    }
};