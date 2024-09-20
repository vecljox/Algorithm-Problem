class Solution {
public:
    double myPow(double x, int n) {
        if(n==1)
            return x;

        if(x==0)
            return 0;

        if(n==0||x==1)
            return 1;

        if(x==-1)
            return (n&1)?-1:1;
        
        if(n<0)
        {
            if(n==1<<31)
                return 1/(myPow(x,-(n+1))*x);

            return 1/myPow(x,-n);
        }

        double res = myPow(x,n>>1);
        res*=res;

        if(n&1)
            res *= x;

        return res;
    }
};

class SolutionB {
public:
    double myPow(double x, int n) {
        if(x==0)
            return 0;

        if(n==0||x==1)
            return 1;

        if(x==-1)
            return (n&1)?-1:1;

        if(n<0)
        {
            if(n==1<<31)
                return 1/(myPow(x,-(n+1))*x);

            return 1/myPow(x,-n);
        }
            
        double res = 1;

        while(n)
        {
            if(n&1)
                res*=x;

            x*=x;
            n>>=1;
        }

        return res;
    }
};
