#include<bits/stdc++.h>
#include<iostream>

using namespace std;

class Node {

    public :
        int data;
        Node* next;
        Node* arb;

    Node( int data ){
        this -> data = data;
        this -> next = NULL;
        this -> arb = NULL;
    }
    
    ~Node(){
        int value = this -> data;
        if( this -> next != NULL ) {
            delete next;
            this -> next = NULL;
        }
        cout << " memory is cleared of node with data " << value << endl;
    }
};

/****************************** Sieve of Eratosthenes *********************************/
 
 int countPrimes ( int n) { 
        vector< bool >tester( n+1 ,false ); int count =0;
        int m = sqrt( n );
        for( int i = 2 ; i <= m ; i++ ) {
            if( tester[ i ] == false ){
                for( int j = i*i ; j < n ; j += i){
                    tester[ j ] = true;
                }
            }
        }
        for ( int i = 2 ; i < n ; i++ ) {
            if( tester[ i ] == false ) count++;
        }
        return count;
    }

/****************************** BOOK Alocatiion Problem  ********************************/

bool possible( vector <int>& weights , int mid , int days ){
        int sum = 0 ;
        int m = 1;
        for( int i = 0 ; i < weights.size() ; i++ ) {
            if( sum + weights[ i ] <= mid ) {
                sum = sum + weights[ i ];
            }
            else{
                m++ ;
                if( m > days || weights[ i ] > mid ) return false;
                sum = weights[ i ] ;
            }
        }
        
       return true;
    }

    int shipWithinDays( vector <int>& weights, int days) {
        int total = 0; int ans;
        for( auto a : weights ){
            total = total+a;
        }
        int i=0 ; int j = total ; int mid ;
        while ( i <= j ){
            mid=( i + j ) / 2;
            if ( possible ( weights , mid , days ) ){
                ans = mid ;
                j = mid - 1;}
            else{
                i = mid + 1;
            }
        }
    return ans;    
    }
 
/********************************* Clone a Linked List *********************************/

Node *cloneList( Node *head ) {   
        Node* temp2 = head;
        Node* cloneHead = new Node(-1);
        Node* temp = cloneHead;
        while ( temp2 ){
            temp -> next = new Node( temp2 -> data );
            temp = temp -> next;
            temp2 = temp2 -> next;
        }
        cloneHead = cloneHead -> next;
        temp2 = head;
        temp = cloneHead;
        unordered_map< Node* , Node* > cloner;
        while( temp2 ){
            cloner[ temp2 ] = temp;
            temp2 = temp2 -> next;
            temp = temp -> next;
        }
        temp2 = head;
        temp = cloneHead;
        while( temp2 ){
            temp -> arb = cloner[ temp2 -> arb ];
            temp = temp -> next;
            temp2 = temp2 -> next;
        }
        return cloneHead ;
    }

/********************************* Area of Histogram *********************************/

vector<int> nextSmallerElement(vector<int> &arr, int n){
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);
    for( int i = n-1 ; i>=0 ; i--) {
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

/****************************** The celebrity prblem  *********************************/

bool knows(vector<vector<int> >& M, int a, int b, int n) {
    if(M[a][b] == 1)
        return true;
    else
        return false;
}

int celebrity(vector<vector<int> >& M, int n) 
    {
        stack<int> s;
        for(int i=0; i<n; i++) {
            s.push(i);
        }   
        
        while(s.size() > 1) {
            
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            if(knows(M,a,b,n)){
                s.push(b);
            }
            else{
                s.push(a);
            }
        }
        int ans = s.top();
        int zeroCount = 0;
        for(int i=0; i<n; i++) {
            if(M[ans][i] == 0)
                zeroCount++;
        }
        if(zeroCount != n)
            return -1;
        int oneCount = 0;
        for(int i=0; i<n; i++) {
            if(M[i][ans] == 1)
                oneCount++;
        }
        if(oneCount != n-1)
            return -1;
        return ans;
}

/********************************* Max rectangle  *********************************/


int maxArea(int M[][], int n, int m) {
        //compute area for first row
        int area = largestRectangleArea(M[0], m);
        for(int i = 1; i<n; i++) {
            for(int j = 0; j<m; j++) {   
                //row udpate: by adding previous row's value
                if(M[i][j] != 0)
                    M[i][j] = M[i][j] + M[i-1][j];
                else
                    M[i][j] = 0;
            }
            //entire row is updated now
            area = max(area, largestRectangleArea(M[i],m));
        }
        return area;
}

/********************************* circular tour  *********************************/

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int loss = 0;
    int balance = 0;
    int start = 0;
    for(int i = 0; i< gas.size() ; i++){
        balance += gas[i] - cost[i];
        if(balance < 0 ){
            loss += balance ;
            start = i+1;
            balance = 0;
        }
        
    }
    if((loss + balance)>=0)return start;
    else return -1;
    }

/********************************* Sliding Window  *********************************/

vector<long long> printFirstNegativeInteger(long long int A[],
                                                    long long int N, long long int K) {
    deque<long long int> dq;
    vector<long long> ans;
    for(int i = 0 ; i < K ;i++){
        if(A[i] < 0)dq.push_back(i);
    }
    if(dq.size() > 0) {
        ans.push_back(A[dq.front()]);
    }            
    else ans.push_back(0);
    for(int i = K ; i < N ;i++ ){
        if( !dq.empty() && i-dq.front() >= K )dq.pop_front();
        if(A[i] < 0)dq.push_back(i);
        if(dq.size() > 0) {
        ans.push_back(A[dq.front()]);
        }            
        else ans.push_back(0);
    }
    return ans;
 }

/********************************* Power calculation  *********************************/

double myPow(double x, int n) {
        if(n < 0) x = 1 / x;
        long num = labs(n);
        double pow = 1;
        while(num){ 
            if(num & 1) pow *= x;
            x *= x;
            num >>= 1;
        }
        return pow;
    }

/********************************* Delete Dulplicates  *********************************/

 ListNode* deleteDuplicates(ListNode* head) {
        if(head==0||head->next==0)return head;
        ListNode* Dummy= new ListNode(0,head);
        ListNode*prev = Dummy;
        while(head){
            if(head->next && head->val==head->next->val){
               while(head->next && head->val==head->next->val) head=head->next;
                prev->next=head->next;
                head=head->next;
            }
            else{
                prev=head;
                head=head->next;
            }
             
        }
        head= Dummy->next;
        Dummy->next=NULL;
        delete Dummy;
        return head;
        
    }

int main(){
    
    return 0;
}