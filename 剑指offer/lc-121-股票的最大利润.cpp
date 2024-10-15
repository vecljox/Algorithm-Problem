// 记录第i天之前的历史最低价格，再用当前价格-历史最低价去更新最大利润
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            minPrice = min(minPrice, prices[i]);
            res = max(res, prices[i] - minPrice);
        }
        return res;
    }
};

// 自己做的，pre表示前一天卖出的最大利润
class SolutionB {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int pre = 0;
        for (int i = 1; i < prices.size(); ++i) {
            pre = max(pre + prices[i] - prices[i - 1], 0);
            res = max(res, pre);
        }
        return res;
    }
};
