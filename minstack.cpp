#include <bits/stdc++.h>
using namespace std;

class MinStack {
private:
    stack<int> st;     
    stack<int> minst;  
public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        if (minst.empty()) minst.push(val);
        else minst.push(min(val, minst.top()));
    }

    void pop() {
        if (!st.empty()) {
            st.pop();
            minst.pop();
        }
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minst.top();
    }
};

int main() {
    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    cout << "Min: " << ms.getMin() << endl;  
    ms.pop();
    cout << "Top: " << ms.top() << endl;   
    cout << "Min: " << ms.getMin() << endl;
    return 0;
}
