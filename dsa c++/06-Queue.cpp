#include<bits/stdc++.h>

using namespace std;

class Queue {
    
    int* arr;
    int qfront;
    int rear; 
    int size;
    
public:
    Queue() {
        size = 100001;
        arr = new int[size];
        qfront = 0;
        rear = 0;
    }

    bool isEmpty() {
        if(qfront == rear) {
            return true;
        }
        else
        {
            return false;
        }
    }

    void enqueue(int data) {
        if(rear == size)
            cout << "Queue is Full" << endl;
        else
        {
            arr[rear] = data;
            rear++;
        }
    }

    int dequeue() {
        if(qfront == rear) {
            return -1;
        }
        else
        {	int ans = arr[qfront];
            arr[qfront] = -1;
            qfront++;
            if(qfront==rear){
                qfront = 0;
                rear = 0;
            }
         return ans;
        }
    }

    int front() {
        if(qfront == rear) {
            return -1;
        }
        else
        {
            return arr[qfront];
        }
    }
};


class CircularQueue{
    int *arr;
    int front;
    int rear;
    int size;
    
    public:

    CircularQueue(int n){
        size = n;
        arr = new int[size];
        front = rear = -1;
    }

    
    bool enqueue(int value){
        if( (front == 0 && rear == size-1) || (rear == (front-1)%(size-1) ) ) {
            return false;
        }
        else if(front == -1) {
			front = rear = 0;
            
        }
        else if(rear == size-1 && front != 0) {
            rear = 0;
        }
        else {
            rear++;
        }
        arr[rear] = value;
        return true;
    }

    int dequeue(){
        if(front == -1){
            return -1;
        }
        int ans = arr[front];
        arr[front] = -1;
        if(front == rear) {
            front = rear = -1;
        }
        else if(front == size - 1) {
            front = 0; 
        }
        else
        {
            front++;
        }
        return ans;
    }
};

// DOUBLY ENDED QUEUE
class Deque
{	
    int *arr;
    int front;
    int rear;
    int size;
public:

    Deque(int n) {
        size = n;
        arr = new int[n];
        front = -1;
        rear = -1;
    }


    bool pushFront(int x) {
        if( isFull() ) {
            return false;
        }
        else if(isEmpty()) {
            front  = rear = 0;
        }
        else if(front == 0 && rear != size-1) {
            front = size-1;
        } 
        else {
            front--;
        }
        arr[front] = x;
        return true;
    }

    bool pushRear(int x)
    {
        if( isFull() ) {
            return false;
        }
        else if(isEmpty()) {
            front  = rear = 0;
        }
        else if(rear == size-1 && front != 0) {
            rear = 0;
        } 
        else
        {
             rear++;
        }
        arr[rear] = x;
        return true;
    }

    int popFront()
    {
        if(isEmpty()){
            return -1;
        }
        int ans = arr[front];
        arr[front] = -1;
        
        if(front == rear) { 
            front = rear = -1;
        }
        else if(front == size - 1) {
            front = 0; 
        }
        else{
            front++;
        }
        return ans;
    }

    int popRear()
    {
         if(isEmpty()){
            return -1;
        }
        
        int ans = arr[rear];
        arr[rear] = -1;
        
        if(front == rear) {
            front = rear = -1;
        }
        else if(rear == 0) {
            rear = size-1; 
        }
        else{
            rear--;
        }
        return ans;
    }

    int getFront() {
        if(isEmpty()){
            return -1;
        }
        return arr[front];
    }

    int getRear() {
       if(isEmpty()){
            return -1;
        }
        return arr[rear];
    }

    bool isEmpty() {
        if(front == -1)
            return true;
        else
            return false;
    }

    bool isFull() {
		if( (front == 0 && rear == size-1) || (front != 0 && rear == (front-1)%(size-1) ) ) return true;
        else
            return false;
    }
};

class kQueue {

    public:
        int n;
        int k;
        int *front;
        int *rear;
        int *arr;
        int freeSpot;
        int *next;

    public:
        kQueue(int n, int k) {
            this -> n = n;
            this -> k = k;
            front = new int[k];
            rear = new int[k];
            for(int i=0; i<k; i++) {
                front[i] = -1;
                rear[i] = -1;
            }

            next = new int[n];
            for(int i=0; i<n; i++) {
                next[i] = i+1;
            }
            next[n-1] = -1;
            arr = new int[n];
            freeSpot = 0;
        }    

        void enqueue(int data, int qn) {
            if( freeSpot == -1) {
                cout << "No Empty space is present" << endl;
                return;
            }
            int index = freeSpot;
            freeSpot = next[index];
            if(front[qn-1] == -1){
                front[qn-1] = index;
            }
            else{
                next[rear[qn-1]] = index;
            }
            next[index] = -1;
            rear[qn-1] = index;
            arr[index] = data;
        }

        int dequeue(int qn) {
            if(front[qn-1] == -1)  {
                cout << "Queue UnderFlow " << endl;
                return -1;
            }
            int index = front[qn-1];
            front[qn-1] = next[index];
            next[index] = freeSpot;
            freeSpot = index;
            return arr[index];
        }

};

queue<int> reverse(queue<int> q)
    {
        stack< int > reverser;
        while(!q.empty()){
            reverser.push(q.front());
            q.pop();
        }
        while(!reverser.empty()){
            q.push(reverser.top());
            reverser.pop();
        }
        return q;
    }

vector<long long> printFirstNegativeInteger(long long int A[],
                                              long long int N, long long int K) {
    deque<long long int> dq;
    vector<long long> ans;
    for(int i = 0 ; i < K ;i++){
        if(A[i] < 0)dq.push_back(i);
    }
    if( dq.size() > 0 ) ans.push_back(A[dq.front()]);           
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
 
int main(){
    
    return 0;
}

