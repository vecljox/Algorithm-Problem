class Solution {
public:
    int integerBreak(int n) {

        if(n==2)
            return 1;

        if(n==3)
            return 2;

        int timesOf3 = n/3;
        
        if(n%3==1)
            --timesOf3;
        
        int timesOf2 = (n-timesOf3*3)/2;
        
        return  pow(3,timesOf3)*pow(2,timesOf2);
    }
};
