#include<bits/stdc++.h>

using namespace std;

class Node {

    public :
        int data;
        Node* next;
        Node* arb;

    Node( int data ){
        this -> data = data;
        this -> next = NULL;
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

void print ( Node* &head ) {
    if( head == NULL ) {
        cout << "List is empty "<< endl;
        return ;
    }
    Node* temp = head;
    while( temp ) {
        cout << temp -> data << "\t";
        temp = temp -> next;
    }
}

void insertAtHead ( Node* &head , int element ) {
    Node* temp = new Node ( element );
    if ( head == NULL )head = temp;    
    else {
        temp -> next = head;
        head = temp;
    }
}

void insertAtEnd ( Node* &head , int element ) {
    Node* temp=new Node( element );
    if ( head == NULL )head = temp;    
    Node* trvs = head;
    while ( trvs -> next ) trvs = trvs -> next;
    trvs -> next= temp;
}

void InsertAtPosition ( Node* &head , int position , int element ) {
    Node* trvs = head;
    if ( position == 1 ) {
        insertAtHead( head , element );
        return;
    }
    for ( int i = 1 ; i < position - 1 ; i++ ) trvs = trvs -> next;
    Node* temp = new Node ( element ) ;
    temp -> next = trvs -> next;
    trvs -> next = temp;
}

void deleteHead ( Node* &head ) {
    Node* temp = head;
    head = head -> next;
    temp -> next = NULL;
    delete temp;
}

void deleteAtPosition ( Node* &head , int position ) {
    Node* trvs = head; 
    if ( position == 1 ) {
        deleteHead( head ) ;
        return;
    }
    for ( int i = 1 ; i < position - 1 ; i++ ) trvs=trvs->next;
    Node* temp = trvs -> next;
    trvs -> next = temp -> next;
    temp -> next = NULL;
    delete temp;
}

Node* iterativeReverse( Node* &head ){
    if( head == NULL || head -> next == NULL ) return head;
    Node* P = NULL;
    Node* Q = NULL;
    Node* R = head;
    while ( R ){
        P = Q;
        Q = R;
        R = R -> next;
        Q -> next = P;
    }
    return Q;
}

Node* recursiveReverse( Node* &head ){
    if( head == NULL || head-> next == NULL ){
        return head;
    }
    Node* Head2 = recursiveReverse ( head -> next );
    head -> next -> next = head;
    head -> next = NULL;
    return Head2;
}

bool checkLoop ( Node* &head ) {
    Node* p ; Node* q;
    p = q = head;
    do{ p = p -> next;
        q = q -> next;
        q = q ? q -> next : q ;
    }while( p && q && p != q ) ;
    if( p == q ) return true;
    else return false;
}

Node *removeLoop( Node *head ) {
    Node* p ; Node* q;
    p = q = head;
    do{ p = p -> next;
        q = q -> next;
        q = q ? q -> next : q ;
    } while( p && q && p != q ) ;
    if( p != q ) return head;
    if( p == NULL ) return NULL;
    p=head;
    while( p != q ){  //from this while statement we will get the starting Node of Loop. 
        p = p -> next;
        q = q -> next;
    }
    while( p -> next != q)p = p -> next;
    p -> next = NULL;
    return head;
}

int length(Node* head){
    int count = 0; Node* temp = head;
    while ( temp ){
        count++;
        temp= temp->next;
    }
    return count;
}

Node* reverseInKgroups( Node* head, int k ) {
   if(head == NULL) return NULL ;
    int size = length( head ) ;
    if ( size < k )return head ;
    Node* q = NULL ;
    Node* p = NULL ;
    Node* r = head ;
    int count= 0 ;
    while( r && count < k ) {
        p = q;
        q = r;
        r = r -> next;
        q -> next = p;   
        count++ ;
    }  
    if ( r ) head -> next = reverseInKgroups( r , k );
    return q ;
}

int getMiddle( Node* &head ) {
    Node* p = head;
    Node* q = head;
    while ( q ) {
        q = q -> next;
        if ( q ) q = q -> next;
        if( q ) p = p -> next;
    }
    return p -> data;
}

Node* deleteDuplicatesInSortedLinkedList( Node* head ) {
        if(head == NULL || head -> next == NULL) return head;
        Node* temp = head;
        while( temp -> next ){
            if( temp -> data == temp -> next -> data ){
                Node* temp2 = temp -> next;
                temp -> next = temp -> next -> next;
                temp2 -> next = NULL;
                delete temp2;
            }
            else{
                temp = temp -> next;
            }
        }
        return head;
}

Node *removeDuplicatesUnsortedLL( Node *head ) {
    if( head == NULL || head-> next == NULL )return head;
    Node* temp = head;
    while( temp ){
        Node* temp4 = temp;
        Node* temp2 = temp->next;
        while( temp2 ){
                if( temp2 -> data == temp -> data ){
                    temp4 -> next = temp2 -> next;
                    temp2 = temp2 -> next;
                }
                else{
                    temp4 = temp2;
                    temp2 = temp2->next;
                }
        }
        temp = temp -> next;
    }
    return head;
}

Node * removeDuplicatesUnsortedLinkedList( Node *head) {   
    if( head == NULL || head -> next == NULL )return head;
    set<int> uniqueElements;
    Node* curr = head;
    Node* prev = nullptr;
    while (curr != nullptr) {
        if (uniqueElements.count(curr->data) > 0) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            uniqueElements.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

Node* findMid( Node* head) {   //how merge sort is performed on linked list
    Node* p = head;
    Node* q = head;
    while(p) {
        p = p -> next;
        if( p ) p = p -> next; 
        if( p ) q = q -> next;
    }
    return q;
}

Node* merge( Node* left,  Node* right) {
    if( !left ) return right;
    if( !right ) return left;
    Node* ans = new  Node(-1);
    Node* temp = ans;
    while( left != NULL && right != NULL) {
        if( left -> data < right -> data ) {
            temp -> next = left;
            temp = left;
            left = left -> next;
        }
        else{
            temp -> next = right;
            temp = right;
            right = right -> next;
        }
    }
    while( left ) {
        temp -> next = left;
        temp = left;
        left = left -> next;
    }
    while( right ) {
        temp -> next = right;
        temp = right;
        right = right -> next;
    }
    ans = ans -> next;
    return ans;
}

Node* mergeSort( Node *head ) {
    if( head == NULL || head -> next == NULL ) return head;
    Node* mid = findMid(head);
    Node* left = head;
    Node* right = mid->next;
    mid -> next = NULL;
    left = mergeSort(left);
    right = mergeSort(right);
    Node* result = merge(left, right);
    return result;
}

Node *cloneLindkedList(Node *head) {   
        Node* temp2=head;
        Node* cloneHead = new Node(-1);
        Node* temp = cloneHead;
        while ( temp2 ){
            temp->next=new Node(temp2->data);
            temp=temp->next;
            temp2=temp2->next;
        }
        cloneHead=cloneHead->next;
        temp2=head;
        temp=cloneHead;
        unordered_map<Node* , Node*> cloner;
        while(temp2){
            cloner[temp2]=temp; 
            temp2=temp2->next;
            temp=temp->next;
        }
        temp2=head;
        temp=cloneHead;
        while(temp2){
            temp->arb=cloner[temp2->arb];
            temp=temp->next;
            temp2=temp2->next;
        }
        return cloneHead;
    }

class cmp{
    public:
    bool operator() (Node* a, Node* b){
        return (a->data > b->data);
    }
};

Node* mergeKLists(vector<Node*> &listArray) {
        priority_queue <Node*, vector<Node*>, cmp> minHeap;
        Node* dummy = new Node(-1);
        Node* tail = dummy;

        for(Node* i:listArray){
            if(i != NULL) minHeap.push(i);
        }

        while(!minHeap.empty()){
            Node* temp = minHeap.top();
            minHeap.pop();
            if(temp->next != NULL) minHeap.push(temp->next);
            tail->next = temp;
            tail = tail->next;
        }

        return dummy->next;
}

int main(){
    Node* head = new Node(5);
    print(head);
    return 0;
}

