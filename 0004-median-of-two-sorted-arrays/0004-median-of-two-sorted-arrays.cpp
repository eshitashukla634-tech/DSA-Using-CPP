class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> arr;

    // Put all the elements of nums1
    for(int x : nums1){
        arr.push_back(x);
    }
    // Put all the elemenst of nums2
    for(int x : nums2){
        arr.push_back(x);
    }
    // Sort the combined array
    sort(arr.begin(),arr.end());
        


    int n = arr.size();
    if(n % 2 == 1) {
        return arr[n/2];
    }
    else {
        return (arr[n/2-1] + arr[n/2]) / 2.0;
    }
    }
};