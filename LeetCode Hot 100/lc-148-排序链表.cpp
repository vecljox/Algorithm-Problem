// https://www.acwing.com/solution/content/408/

// 自底向上的归并排序

// 时间复杂度： O(nlogn)
// 空间复杂度： O(1)

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        int n = 0;
        for (auto p = head; p; p = p->next)
            ++n;
        ListNode dummy;
        dummy.next = head;

        for (int i = 1; i < n; i *= 2) {  //每次归并段的长度，每次长度依次为1,2,4,8...n/2
            auto cur = &dummy;
            for (int j = 1; j + i <= n; j += 2 * i) {  //j表示第一段的开始，j+i则是第二段的开始，如果j+i这个值越界，说明只有一段，不需要归并了。
                auto p = cur->next, q = p;  //p表示第一段的起始点，q表示第二段的起始点，之后开始归并即可
                for (int k = 0; k < i; ++k)
                    q = q->next;
                int x = 0, y = 0;  //x,y用于计数第一段和第二段归并的节点个数，由于当链表长度非2的整数倍时表长会小于i,故而需要加上p && q的边界判断
                while (x < i && y < i && p && q) {
                    if (p->val <= q->val) {
                        cur->next = p;
                        p = p->next;
                        ++x;
                    } else {
                        cur->next = q;
                        q = q->next;
                        ++y;
                    }
                    cur = cur->next;
                }
                while (x < i && p) {
                    cur->next = p;
                    p = p->next;
                    cur = cur->next;
                    ++x;
                }
                while (y < i && q) {
                    cur->next = q;
                    q = q->next;
                    cur = cur->next;
                    ++y;
                }
                cur->next = q;  //记得把排好序的链表尾链接到下一链表的表头，循环完毕后q为下一链表表头
            }
        }
        return dummy.next;
    }
};
