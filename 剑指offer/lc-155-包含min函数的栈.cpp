class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;

public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int val) {
        x_stack.push(val);
        min_stack.push(min(val,getMin()));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


//不使用辅助栈做法，通过存放差值实现。个人不推荐，栈的类型要设置为long long防止差值溢出，所以也没有节省什么内存
class MinStackB {
    stack<long long>  x_stack;
    int m_min=INT_MAX;
public:
    MinStack() {

    }
    
    void push(int val) {
        long long diff = (long long)val-m_min;

        if(diff<0)
            m_min=val;
            
        x_stack.push(diff);
    }
    
    void pop() {
        if(x_stack.top()<0)
            m_min-=x_stack.top();
            
        x_stack.pop();
    }
    
    int top() {
        return (x_stack.top()<0)?m_min:m_min+x_stack.top();
    }
    
    int getMin() {
        return m_min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
