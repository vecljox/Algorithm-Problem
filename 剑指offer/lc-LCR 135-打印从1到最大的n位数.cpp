class Solution {
public:
    vector<int> countNumbers(int cnt) {
        vector<int> res{};
        res.reserve(pow(10,cnt));

        for(int i =1;i<pow(10,cnt);++i)
        {
            res.push_back(i);
        }

        return res;
    }
};
