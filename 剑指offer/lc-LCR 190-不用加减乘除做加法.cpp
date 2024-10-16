// 把dataA看做异或和，dataB看作进位
class Solution {
public:
    int encryptionCalculate(int dataA, int dataB) {
        while (dataB) {
            int c = (dataA & dataB) << 1;
            dataA ^= dataB;
            dataB = c;
        }
        return dataA;
    }
};
