#include <bits/stdc++.h>
using namespace std;

class MinStack {
private:
    stack<int> st;     
    stack<int> maxst;  
public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        if (maxst.empty()) maxst.push(val);
        else maxst.push(max(val, maxst.top()));
    }

    void pop() {
        if (!st.empty()) {
            st.pop();
            maxst.pop();
        }
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return maxst.top();
    }
};

int main() {
    MinStack ms;
    ms.push(6);
    ms.push(0);
    ms.push(-3);
    ms.push(7);
    cout << "Max: " << ms.getMin() << endl;  
    ms.pop();
    cout << "Top: " << ms.top() << endl;   
    cout << "Max: " << ms.getMin() << endl;
    return 0;
}
