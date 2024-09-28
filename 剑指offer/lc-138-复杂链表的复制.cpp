/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==nullptr)   return nullptr;
        Node* cur = head;

        for(Node* node = head; node!=nullptr; node = node->next->next)
        {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next=nodeNew;
        }

        for(Node* node = head; node!=nullptr; node = node->next->next)
        {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random!=nullptr)?node->random->next:nullptr;
        }

        Node* headNew = head->next;

        for(Node* node = head; node!=nullptr; node = node->next)
        {
            Node* nodeNew = node->next;
            node->next = node->next->next;
            nodeNew->next = (nodeNew->next!=nullptr)?nodeNew->next->next:nullptr;
        }

        return headNew;
    }
};

//循环
class SolutionB {
public:
    Node* copyRandomList(Node* head) {
        if(head==nullptr)   return  nullptr;
        
        unordered_map<Node*, Node*> cachedNode;
        for(Node* node = head; node!=nullptr; node=node->next)
        {
            cachedNode[node] = new Node(node->val);
        }

        for(Node* node = head; node!=nullptr; node=node->next)
        {
            cachedNode[node]->next = cachedNode[node->next];
            cachedNode[node]->random = cachedNode[node->random];
        }
        
        return cachedNode[head];
    }
};

//递归
class SolutionC {
public:
    unordered_map<Node*, Node*> cachedNode;

    Node* copyRandomList(Node* head) {
        if (head == nullptr)    return nullptr;
        
        if(!cachedNode.count(head))
        {
            Node* headNew = new Node(head->val);
            cachedNode[head] = headNew;
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }

        return cachedNode[head];
    }
};

