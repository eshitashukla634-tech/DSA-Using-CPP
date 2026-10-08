class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (string x : tokens) {

            if (x == "+" || x == "-" || x == "*" || x == "/") {
                int b = st.top();
                st.pop();

                int a = st.top();
                st.pop();

                if (x == "+")
                    st.push(a + b);
                else if (x == "-")
                    st.push(a - b);
                else if (x == "*")
                    st.push(a * b);
                else
                    st.push(a / b);
            }
            else {
                st.push(stoi(x));
            }
        }

        return st.top();
    }
};