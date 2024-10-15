class Solution {
public:
    int iceBreakingGame(int num, int target) {
        int f = 0;
        for (int n = 2; n <= num; ++n) {
            f = (target + f) % n;
        }
        return f;
    }
};
