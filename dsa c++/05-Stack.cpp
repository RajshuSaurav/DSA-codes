 #include<bits/stdc++.h>

using namespace std;

class Stack {
    public:

        int *arr;
        int top;
        int size;

    Stack(int size) {
        this -> size = size;
        arr = new int[size];
        top = -1;
    }

    void push( int element) {
        if(size - top > 1) arr[++top] = element;
        else cout << "Stack OverFlow" << endl;
    }

    void pop() {
        if(top >=0 ) top--;
        else cout << "Stack UnderFlow" << endl;   
    }

    int peek() {
        if(top >=0 ) return arr[top];
        else {
            cout << "Stack is Empty" << endl;
            return -1;
        }
    }

    bool isEmpty() {
        if( top == -1) {
            return true;
        }
        else{
            return false;
        }
    }

};

class NStack {

private: 

    int *arr;
    int *top;
    int *next;
    int n;
    int s;
    int freespot;

public:

    NStack(int N, int S)
    {
        n=N;
        s=S;
        top = new int[ N ];
        next = new int[ s ];
        arr = new int[ s ];
        for( int i = 0; i < n; i++ )top[i] =  -1;
        for( int i = 0; i < s; i++ )next[i] = i+1;
        next[s-1] = -1;
        freespot = 0;
    }

    bool push(int x, int m)
    {
        if( freespot == -1 )return false;
        int index = freespot;
        arr[index] = x;
        freespot = next[ index ];
        next[index] = top[m-1];
        top[m-1] = index;
        return true;
    }

    int pop(int m)
    {
        if( top[m-1] == -1 )return -1;
        int index = top[m-1];
        top[m-1] = next[index];
        next[index]=freespot;
        freespot = index;
        return arr[index];
    }
};

void InsertAtBottom( stack < int > & myStack, int x ){
    if( myStack.empty() ){ 
        myStack.push(x);
        return ;
    }
    else{
        int y = myStack.top();
        myStack.pop();
        InsertAtBottom( myStack ,  x );
        myStack.push( y );
    }
}

void Reverse( stack<int> &St ) {

    if( St.empty() )return;
    int x = St.top();
    St.pop();
    Reverse( St );
    InsertAtBottom( St , x );
    
}

bool isValidParenthesis(string expression){   
    stack < char > st;
    for(int i=0 ; i < expression.length() ; i++){
        char ch = expression[i];
    if (ch=='[' || ch=='{' || ch=='(')  st.push(ch);
    else{ 
        if(!st.empty()){
        char top=st.top();
        if ((ch == ')' && top == '(') || (ch == '}' && top == '{') ||
            (ch == ']' && top == '['))
            st.pop();
        else
            return false;
        } else
        return false;
    }
    }
    if(st.empty())return true;
    else return false;
}

void sortedInsert(stack<int> &stack, int num) {
    if(stack.empty() || (!stack.empty() && stack.top() < num) ) {
        stack.push(num);
        return;
    }
    int n = stack.top();
    stack.pop();
    sortedInsert(stack, num);
    stack.push(n);
}

void sortStack(stack<int> &stack) {
    	if(stack.empty()) return ;
    	int num = stack.top();
    	stack.pop();
    	sortStack(stack);    
    	sortedInsert(stack, num);
}

class largestRectangleAreaInHistogram {
public:
 
    vector<int> nextSmallerElement(vector<int> &arr, int n){
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);
        for(int i=n-1 ; i>=0 ; i--) {
            int curr = arr[i];
            while( s.top()!= (-1) && arr[s.top()] >= curr ){
                s.pop();
            }
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }

    vector<int> prevSmallerElement(vector<int> &arr, int n){
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);
        for(int i=0 ; i<n ; i++) {
            int curr = arr[i];
            while( s.top()!= -1 && arr[s.top()] >= curr ){
                s.pop();
            }
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }
  
    int largestRectangleArea(vector<int>& heights) {
        int n= heights.size(); 
        vector<int> next(n);
        next = nextSmallerElement(heights, n);
        vector<int> prev(n);
        prev = prevSmallerElement(heights, n);
        int area = INT_MIN;
        for(int i=0; i<n; i++) {
            int l = heights[i];
            if(next[i] == -1) next[i] = n;
            int b = next[i] - prev[i] - 1;
            int newArea = l*b;
            area = max(area, newArea);
        }
        return area;
    }   
};

int main() {
    
    return 0;
}