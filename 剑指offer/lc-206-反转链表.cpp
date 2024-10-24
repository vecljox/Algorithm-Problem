/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // if(head==nullptr||head->next==nullptr)
        //     return head;

        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur!=nullptr)
        {
            ListNode* tmp =cur->next;
            cur->next = pre;
            pre=cur;
            cur=tmp;
        }

        return pre;
    }
};


class SolutionB {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr||head->next==nullptr)
            return head;

        ListNode* temp = reverseList(head->next);

        head->next->next=head;
        head->next=nullptr;

        return temp;
    }
};
