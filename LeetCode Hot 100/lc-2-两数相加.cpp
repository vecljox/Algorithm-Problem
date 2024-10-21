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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto dummy = new ListNode();
        auto pre = dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int sum = 0;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            auto node = new ListNode(sum % 10);
            pre->next = node;
            pre = node;
        }
        return dummy->next;
    }
};

//不确定这种做法是不是更适合面试，但是空间复杂度更低，思想是直接在原链表中修改
class SolutionB {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto dummy = new ListNode();
        auto pre = dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int sum = 0;
            ListNode* node = nullptr;
            if (l1) {
                node = l1;
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                node = l2;
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            if (node)
                node->val = sum % 10;
            else
                node = new ListNode(sum % 10);
            pre->next = node;
            pre = node;
        }
        return dummy->next;
    }
};
