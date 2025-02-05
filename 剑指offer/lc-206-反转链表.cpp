class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy;
        dummy.next = nullptr;
        while (head) {
            auto tmp = head->next;
            head->next = dummy.next;
            dummy.next = head;
            head = tmp;
        }

        return dummy.next;
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
