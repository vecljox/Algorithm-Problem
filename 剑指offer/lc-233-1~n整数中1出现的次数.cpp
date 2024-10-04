class Solution {
public:
    int countDigitOne(int n) {
        int ans = 0;
        for (long long mulk = 1; n >= mulk; mulk *= 10) {
            ans += n / (mulk * 10) * mulk +
                   min(max(n % (mulk * 10) - mulk + 1, 0LL), mulk);
        }
        return ans;
    }
};
