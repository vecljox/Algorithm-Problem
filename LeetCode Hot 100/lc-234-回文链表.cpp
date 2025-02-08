// 栈

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> stk;
        auto cur = head;
        while (cur) {
            stk.push(cur->val);
            cur = cur->next;
        }
        cur = head;
        while (cur) {
            if (cur->val != stk.top())
                return false;
            stk.pop();
            cur = cur->next;
        }
        return true;
    }
};
