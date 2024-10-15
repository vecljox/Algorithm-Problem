// 快速乘（14次，因为target的范围最大值为10000<2^14）
class Solution {
public:
    int mechanicalAccumulator(int target) {
        int res = 0;
        int a = target + 1;
        int b = target;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        (b & 1) && (res += a);
        a <<= 1;
        b >>= 1;

        return res >> 1;
    }
};

// 递归
class SolutionB {
public:
    int mechanicalAccumulator(int target) {
        target && (target += mechanicalAccumulator(target-1));
        return target;
    }
};
