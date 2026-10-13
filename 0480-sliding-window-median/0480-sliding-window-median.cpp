class Solution {
public:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
    unordered_map<int, int> delayed;
    int leftSize = 0, rightSize = 0;

    void pruneLeft() {
        while (!left.empty() && delayed[left.top()] > 0) {
            delayed[left.top()]--;
            left.pop();
        }
    }

    void pruneRight() {
        while (!right.empty() && delayed[right.top()] > 0) {
            delayed[right.top()]--;
            right.pop();
        }
    }

    void balance() {
        if (leftSize > rightSize + 1) {
            right.push(left.top());
            left.pop();
            leftSize--;
            rightSize++;
            pruneLeft();
        } else if (leftSize < rightSize) {
            left.push(right.top());
            right.pop();
            leftSize++;
            rightSize--;
            pruneRight();
        }
    }

    void addNum(int num) {
        pruneLeft();

        if (left.empty() || num <= left.top()) {
            left.push(num);
            leftSize++;
        } else {
            right.push(num);
            rightSize++;
        }

        balance();
    }

    void removeNum(int num) {
        delayed[num]++;

        if (num <= left.top()) {
            leftSize--;
            if (num == left.top()) {
                pruneLeft();
            }
        } else {
            rightSize--;
            if (!right.empty() && num == right.top()) {
                pruneRight();
            }
        }

        balance();
    }

    double getMedian(int k) {
        pruneLeft();
        pruneRight();

        if (k % 2 == 1) {
            return left.top();
        }

        return ((double)left.top() + right.top()) / 2.0;
    }

    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> ans;

        for (int i = 0; i < k; i++) {
            addNum(nums[i]);
        }

        ans.push_back(getMedian(k));

        for (int i = k; i < nums.size(); i++) {
            removeNum(nums[i - k]);
            addNum(nums[i]);
            ans.push_back(getMedian(k));
        }

        return ans;
    }
};