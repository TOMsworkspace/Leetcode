/*
 * @lc app=leetcode.cn id=1422 lang=cpp
 *
 * [1422] 分割字符串的最大得分
 */

// @lc code=start
class Solution {
public:
    int maxScore(string s) {
        int n = s.size();

        int ans = 0;
        int ones = 0;
        int zeros = 0;

        for(auto c : s){
            if(c == '1')
                ones++;
        }


        for(int i = 0; i < n - 1; ++i){
            if(s[i] == '1')
                ones--;
            else
                zeros++;

            ans = max(ans, ones + zeros);
        }

        return ans;
    }
};
// @lc code=end

