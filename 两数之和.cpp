#include <iostream>
#include <vector>
#include 
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 1; j < nums.size() - i; j++) {
                if (nums[i + j] + nums[i] == target) {
                    return vector<int>{i, i + j};
                }
            }
        }
        return vector<int>{-1};
    }
};