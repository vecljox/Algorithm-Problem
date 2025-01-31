class Solution {
public:
    bool hasCycle(ListNode* head) {
        auto slow = head;
        auto fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;       // 慢指针每次移动一步
            fast = fast->next->next; // 快指针每次移动两步

            if (slow == fast) { // 如果两者相遇，说明有环
                return true;
            }
        }

        return false; // 如果快指针到达链表末尾，说明无环
    }
};
