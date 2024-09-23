class Solution {
public:
    bool isNumber(string s) {

        int len = s.size();

        auto isNum = [&](int i)
        {
            return s[i]>='0'&&s[i]<='9';
        };

        auto isSign = [&](int i)
        {
            return s[i]=='+'||s[i]=='-';
        };

        auto isE = [&](int i)
        {
            return s[i]=='e'||s[i]=='E';
        };

        bool hasNum = false;
        bool hasDot = false;
        bool hasE = false;


        for(int i =0;i<len;++i)
        {
            if(isNum(i))
            {
                hasNum= true;
            }
            else if(isSign(i))
            {
                if((i!=0)&&(!isE(i-1)))
                    return false;
            }
            else if(s[i]=='.')
            {
                if(hasDot|hasE)
                    return false;

                hasDot = true;
            }
            else if(isE(i))
            {
                if(hasE||!hasNum)
                    return false;

                hasE = true;
                hasNum=false;
            }
            else
                return false;
        }

        return hasNum;
    }
};
