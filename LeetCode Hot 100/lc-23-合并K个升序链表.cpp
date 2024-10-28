// https://www.acwing.com/activity/content/code/content/347836/

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

// N: 所有链表中节点的总数
// K: 链表的数量
// 优先队列法: 时间 O(N * logk), 空间 O(k)
class Solution {
public:
    struct Cmp {
        bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Cmp> heap;
        ListNode dummy;
        auto tail = &dummy;
        for (auto l : lists)
            if (l)
                heap.push(l);
        while (heap.size()) {
            auto t = heap.top();
            heap.pop();
            tail = tail->next = t;
            if (t->next)
                heap.push(t->next);
        }
        return dummy.next;
    }
};

// 分治合并：时间 O(N * logk), 递归栈空间 O(logk)
// 空间复杂度上这种方法比优先队列更好，但个人感觉代码上不如优先队列简洁
class SolutionB {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0)
            return nullptr;
        return merge(lists, 0, n - 1);
    }

    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        if (l == r)
            return lists[l];
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy, *tail = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

//分支方法的迭代版本，空间复杂度为O(1)，代码也比较简洁，可以试试这个方法
class SolutionC {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0)
            return nullptr;
        for (int sz = 1; sz < n; sz <<= 1)  //sz代表了步长
            for (int i = 0; i + sz < n; i += 2 * sz)
                lists[i] = mergeTwoLists(lists[i], lists[i + sz]);

        return lists[0];
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy, *tail = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
