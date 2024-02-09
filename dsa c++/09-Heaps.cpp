/* Heap is a complete binary tree that comes with a heap order property.
Complete Binary Tree - Every level of the Binarytree is filled except the 
                    last level nodes must be filled from left to right order. */

#include<bits/stdc++.h>

using namespace std;

class Heap{
    public: 
        int arr[100];
        int size ;

    Heap(){
        arr[ 0 ] = -1;
        size = 0;
    }
    
    void insert(int element){
        size +=1;
        int index = size;
        arr[index] = element;
        while( index > 1 ) {
            int parent = index/2;
            if( arr[index] > arr[parent] ){
                swap(arr[index],arr[parent]);
                index=parent;
            }   
            else{
                return;
            }
        }
    }

    void print(){
        for( int i = 1 ; i <= size ; i++ ){
            cout<<arr[ i ]<<" ";
        }
        cout<<endl;
    }

    void deleteFromHeap(){
        if( size == 0){
            cout << "Heap is already empty" << endl;
        }
        arr[ 1 ] = arr[ size ];
        size -- ;
        int index = 1;
        while( index <= size ){
            int leftIndex = 2 * index;
            int rightIndex = 2 * index + 1;
            if( arr [ index ] < arr [ leftIndex ] && size >= index ){
                swap( arr[ index ], arr[ leftIndex ]);
                index = leftIndex;
            }
            else if( index < size && arr[ index ] < arr[ rightIndex ] ){
                    swap( arr[ index ] , arr[ rightIndex ]);
                    index = rightIndex;
                }
            else return;
        }
    }
};

class Node {
    public:
        int data;
        Node* left;
        Node* right;

    Node(int d) {
        this -> data = d;
        this -> left = NULL;
        this -> right = NULL;
    }
};

/* Always remember that for heap of n size  there leaf nodes lies between
  ( n/2 + 1 ) to  n  index of an arrray for 1 based indexing and n/2 to n for 
  0 based indexing similarly left child index in 1 based indexing is 2*i and 
  right is  ( 2*i + 1 ) and for 0 based indexing left child index is ( 2*i + 1 )
  and right is ( 2*i + 2 ). */

void heapify( int arr [] , int n , int i ){
    int largest = i ;
    int left = 2 * i ;
    int right = 2 * i  + 1 ;
    if( left <= n && arr[ largest ] < arr[ left ] ) largest = left ;
    if( right <= n && arr [ largest ] < arr[ right ] )largest = right ;
    if( largest != i ){
        swap( arr [ largest ] , arr [ i ] );
        heapify ( arr , n , largest );
    }
} 

void HeapSort( int arr [] , int size ) {
    for( int i = size/2 ; i >= 1 ; i--){
        heapify( arr , size , i );
    }
    int length = size;
    while( length > 1 ){
        swap( arr[ length ] , arr[ 1 ] );
        length -- ;
        heapify( arr , length , 1 );
   }
}

int count_Node( Node* root ){
    if( root  == NULL)return 0;
    int ans = 1 + count_Node( root -> left ) + count_Node( root -> right );
    return ans;
}

bool isCBT( Node* tree , int index , int count_node ){
    if( !tree )return true;
    if( index >= count_node)return false;
    else{
        bool left = isCBT( tree -> left , 2*index + 1 , count_node );
        bool right = isCBT( tree -> right , 2*index + 2 , count_node );
        return left && right ;
    }
}

bool maxOrder( Node* tree ){
    if(!tree -> left && !tree -> right )return true;
    if( tree -> right == NULL )
        return maxOrder( tree -> left ) && (tree -> data >= tree -> left -> data);
    if( tree -> left == NULL )
        return maxOrder( tree -> right ) && (tree -> data >= tree -> right -> data);
    else{
        bool left = maxOrder( tree -> left );
        bool right = maxOrder( tree -> right );
        return ( left && right && tree -> data >= tree -> left -> data && tree -> data >= tree -> right -> data);
    }
}

bool isHeap( Node* tree )  {
    int count_node = count_Node( tree );
    if( isCBT( tree , 0 , count_node ) && maxOrder(tree))return true;
    return false;
}

int kthSmallest(int arr[], int l, int r, int k) {
    priority_queue<int>pq;
    for(int i = l ; i < (l+k) ; i++ ){
        pq.push(arr[i]);
    }
    for( int i = l+k ; i <= r ; i++ ){
        if( pq.top() > arr[i]){
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

int Kth_Largest_Sum_Subarray(vector<int> &arr, int k){
	priority_queue< int , vector<int> , greater<int> >maxi;
	int n = arr.size();
	int sum ;
	for ( int i = 0 ; i < n ; i++ ){
		for(int j = i , sum = 0 ; j < n ; j++ ){
			sum += arr[ j ];
			if(maxi.size() < k){
				maxi.push(sum);
			}
			else{
				if(maxi.top() < sum ){
					maxi.pop();
					maxi.push(sum);
				}
			}
		}
	}
	return maxi.top();
}

class node {
    public:
        int data;
        int row;
        int column;
    node( int a , int b , int c ){
        data = a;
        row = b;
        column = c ;
    }
};

class compare {
    public:
        bool operator()(node* a, node* b){
            return a -> data > b -> data;
        }
};

vector<int> mergeKSortedArrays( vector< vector< int > > &kArrays, int k) {
    vector< int > ans;
    priority_queue< node* , vector< node* > , compare >mini;
    for(int i = 0 ; i < k ; i++ ){
        node* temp = new node ( kArrays[i][0] , i , 0 );
        mini.push(temp);
    }

    while( mini.size() > 0 ){
        node* temp = mini.top();
        ans.push_back( temp -> data );
        mini.pop();
        int i = temp -> row ;
        int j = temp -> column ;
        if( j + 1 < kArrays[i].size() ){
            node* temp2 = new node( kArrays[ i ][ j + 1 ] , i , j + 1 );
            mini.push(temp2);
        }

    }
    return ans;
}

int Smallest_Range_From_K_Sorted_List(vector<vector<int>> &a, int k, int n) {
    priority_queue< node* , vector< node* > , compare > miniHeap;
    int maxi = INT_MIN ; int mini = INT_MAX ;
    for(  int i = 0 ; i < k ; i++ ){
        node* temp = new node( a [ i ] [ 0 ] , i , 0 );
        miniHeap.push( temp );
        mini = min ( a [ i ] [ 0 ] , mini);
        maxi = max ( a [ i ][ 0 ], maxi );
    }
    int start = mini ; int end = maxi;
    while( miniHeap.size() > 0 ){
        node* top = miniHeap.top();
        miniHeap.pop();
        mini = top -> data;
        if( maxi - mini < end - start ){
            start = mini;
            end = maxi;
        }
        if( top -> column + 1 < n ){
            maxi = max ( a[ top -> row ] [ top -> column +1 ] , maxi );
            miniHeap.push( new node( a[ top -> row ] [ top -> column +1 ], top -> row , top -> column + 1));
        }
        else break;
    }
    return (end - start) + 1;
}

void inorderGiver(Node* root , vector<int> &inorder) {
	if( !root )return ;
	inorderGiver( root -> left,inorder);
	inorder.push_back( root -> data );
	inorderGiver( root -> right,inorder );
}

void heapMaker( Node* &root, vector< int > inorder , int &index ) {
	if( !root )return ;
	root -> data = inorder[index++];
	heapMaker( root -> left , inorder , index );
	heapMaker( root -> right , inorder , index );
}

Node* convertCBSTToHeap( Node* root ) {
	vector< int > inorder;
	int index = 0 ;
	inorderGiver( root , inorder );
	heapMaker( root , inorder , index );
	return root;

}

int signum(int a,int b){
    if(a==b)
        return 0;
    else if(a>b)
        return 1;
    else
        return -1;
}

void callMedian(int element,priority_queue<int> &maxi,    
     priority_queue<int,vector<int>,greater<int> > &mini,int &median){
    switch( signum( maxi.size(),mini.size() ) ){
        case 0: if(element > median){
            mini.push(element);
            median=mini.top();
        }else{
            maxi.push(element);
            median=maxi.top();
        }
        break;
        case 1:if(element > median){
            mini.push(element);
            median=(mini.top() + maxi.top())/2;
        }else{
            mini.push(maxi.top());
            maxi.pop();
            maxi.push(element);
            median=(mini.top() + maxi.top())/2;
        }
        break;
        case -1 :if(element > median){
            maxi.push(mini.top());
            mini.pop();
            mini.push(element);
            median=(mini.top() + maxi.top())/2;
        }else{
            maxi.push(element);
            median=(mini.top() + maxi.top())/2;
         }
         break;   
    }
}

vector<int> findMedianInRuningStream(vector<int> &arr, int n){
    vector<int> ans;
    priority_queue<int> maxheap;    
    priority_queue<int,vector<int>,greater<int> > minheap;
    int median=-1;
    for(int i=0;i<n;i++){
        callMedian(arr[i],maxheap,minheap,median);
        ans.push_back(median);
    }
    return ans;
}

vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    vector < int >distance( V , INT_MAX ) ;
    set< pair< int , int >> container;
    distance[ S ] = 0;
    container.insert( make_pair( S , 0 ) );
    while( !container.empty() ){
        auto top = *( container.begin() );
        int topNode = top.first ;
        int topWeight = top.second ;
        container.erase( top );
        for ( auto bagal : adj[ topNode ] ){
            if( topWeight + bagal[ 1 ] < distance[ bagal[ 0 ] ] ){
                auto past = container.find( make_pair( bagal[ 0 ] , distance[ bagal[ 0 ] ] ));
                if( past != container.end() )
                    container.erase( past );
                distance[ bagal[ 0 ] ] = topWeight + bagal[ 1 ] ;
                container.insert( make_pair( bagal[ 0 ] , distance[ bagal[ 0 ] ] ));
            }
        }
    }
    return distance ;
}

int main(){
    Heap h ;
    h.insert(55);
    h.insert(50);
    h.insert(88);
    h.insert(60);
    h.insert(53);
    h.print();
    h.deleteFromHeap();
    h.print();
    int arr[6] = {-1,55,22,80,88,5};
    int size = 5 ;
    HeapSort(arr, 5 );
    for(int i = 1 ; i <= size ; i++)cout << arr[i]<<" ";
    cout<<endl;
    return 0;
}