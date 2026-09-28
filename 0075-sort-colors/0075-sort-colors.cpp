class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zeros = 0, ones = 0;

        for (int x : nums) {
            if (x == 0) zeros++;
            else if (x == 1) ones++;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i < zeros)
                nums[i] = 0;
            else if (i < zeros + ones)
                nums[i] = 1;
            else
                nums[i] = 2;
        }
    }
};