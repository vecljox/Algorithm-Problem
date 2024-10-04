class Solution {
public:
    int findNthDigit(int n) {
        int d = 1;
        long mulk = 1;
        long tmp;
        while (n > (tmp = 9 * d * mulk)) {
            n -= tmp;
            d++;
            mulk *= 10;
        }
        --n;
        int num = mulk + n / d;
        int index = d - n % d;
        while (--index) {
            num /= 10;
        }
        return num % 10;
    }
};
