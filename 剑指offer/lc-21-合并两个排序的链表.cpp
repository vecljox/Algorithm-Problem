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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy{0,nullptr};
        ListNode* cur = &dummy;

        while(list1&&list2)
        {
            if(list1->val<list2->val)
            {
                cur->next=list1;
                list1=list1->next;
            }
            else
            {
                cur->next=list2;
                list2=list2->next;
            }
            cur=cur->next;
        }
        
        cur->next=(list1)?list1:list2;

        return dummy.next;
    }
};


class SolutionB {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1==nullptr)
            return list2;

        if(list2==nullptr)
            return list1;

        if(list1->val<list2->val)
        {
            ListNode* temp = mergeTwoLists(list1->next,list2);
            list1->next=temp;
            
            return list1;
        }
        else
        {
            ListNode* temp = mergeTwoLists(list1,list2->next);
            list2->next=temp;

            return list2;
        }
    }
};
