// 链表从左到右进行插入排序
// lastSorted表示排序好的部分的最后一个节点
// cur表示待插入的节点
// pre表示插入位置的前一个节点

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(-1, head);
        auto lastSorted = head;
        auto cur = head->next;
        while (cur != nullptr) {
            if (cur->val >= lastSorted->val) {
                lastSorted = lastSorted->next;
            } else {
                auto pre = &dummy;
                while (cur->val > pre->next->val) {
                    pre = pre->next;
                }
                lastSorted->next = cur->next;
                cur->next = pre->next;
                pre->next = cur;
            }
            cur = lastSorted->next;
        }
        return dummy.next;
    }
};
