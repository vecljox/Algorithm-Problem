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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy{0,head};

        ListNode* low = &dummy;
        ListNode* fast = &dummy;

        while(n--)
        {
            fast=fast->next;
        }

        while(fast->next)
        {
            fast=fast->next;
            low=low->next;
        }

        low->next=low->next->next;

        return dummy.next;
    }
};
