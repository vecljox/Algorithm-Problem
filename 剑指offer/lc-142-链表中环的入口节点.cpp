class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        auto slow = head, fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                while (head != fast) {
                    head = head->next;
                    fast = fast->next;
                }
                return fast;
            }
        }
        return nullptr;
    }
};
