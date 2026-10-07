class Solution {
public:
    vector<string> ans;

    void solve(string s, int start, int left, int right) {
        if (left == 0 && right == 0) {
            int balance = 0;

            for (char c : s) {
                if (c == '(')
                    balance++;
                else if (c == ')') {
                    balance--;

                    if (balance < 0)
                        return;
                }
            }

            if (balance == 0)
                ans.push_back(s);

            return;
        }

        for (int i = start; i < s.size(); i++) {

            if (i > start && s[i] == s[i - 1])
                continue;

            if (s[i] != '(' && s[i] != ')')
                continue;

            string temp = s.substr(0, i) + s.substr(i + 1);

            if (s[i] == '(' && left > 0)
                solve(temp, i, left - 1, right);

            if (s[i] == ')' && right > 0)
                solve(temp, i, left, right - 1);
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        int left = 0;
        int right = 0;

        for (char c : s) {
            if (c == '(') {
                left++;
            }
            else if (c == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }

        solve(s, 0, left, right);

        return ans;
    }
};