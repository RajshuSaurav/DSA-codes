#include<bits/stdc++.h>

using namespace std;

class node {
    public:
        int data;
        node* left;
        node* right;

    node(int d) {
        this -> data = d;
        this -> left = NULL;
        this -> right = NULL;
    }
};

node* buildTree(node* root) {
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    root = new node(data);    
    if(data == -1) {
        return NULL;
    }
    cout << "Enter data for inserting in left of " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << endl;
    root->right = buildTree(root->right);
    return root;
}

void levelOrderTraversal(node* root) {
    queue<node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()) {
        node* temp = q.front();
        q.pop();
        if(temp == NULL) { 
            cout << endl;
            if(!q.empty()) { 
                q.push(NULL);
            }  
        }
        else{
            cout << temp -> data << " ";
            if(temp ->left) {
                q.push(temp ->left);
            }

            if(temp ->right) {
                q.push(temp ->right);
            }
        }
    }

}

void inorder(node* root) {
    if(root == NULL) {
        return ;
    }
    inorder(root->left);
    cout << root-> data << " ";
    inorder(root->right);

}

void preorder(node* root) {
    if(root == NULL) {
        return ;
    }

    cout << root-> data << " ";
    preorder(root->left);
    preorder(root->right);

}

void postorder(node* root) {
    if(root == NULL) {
        return ;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root-> data << " ";
}

vector<int> morrisTraversalInorder(node* root) {
    vector<int> ans;
     node* current = root ;
     while(current){
         if( ! current -> left ) {
             ans.push_back(current -> data );
             current = current -> right ;
         }
         else{
             node* pre = current -> left ;
             while( pre -> right && pre -> right != current ) pre = pre -> right ;
             if( !pre -> right ) {
                 pre -> right = current;
                 current = current -> left;
             }
             else {
                 ans.push_back(current -> data );
                 //replace above line for preorder traversal into previous if block
                 pre -> right = NULL; 
                 current = current -> right;
             }
         }
     }
     return ans;
}


void buildFromLevelOrder(node* &root) {
    queue<node*> q;
    cout << "Enter data for root" << endl;
    int data ;
    cin >> data;
    root = new node(data);  
    q.push(root);
    while(!q.empty()) {
        node* temp = q.front();
        q.pop();
        cout << "Enter left node for: " << temp->data << endl;
        int leftData;
        cin >> leftData;

        if(leftData != -1) {
            temp -> left = new node(leftData);
            q.push(temp->left);
        }
        cout << "Enter right node for: " << temp->data << endl;
        int rightData;
        cin >> rightData;
        if(rightData != -1) {
            temp -> right = new node(rightData);
            q.push(temp->right);
        }
    }
 }

int height(node* node){
        if(!node)return 0;
        int FirstHeight = height(node->left);
        int SecondHeight = height(node->right);
        int ans = max(FirstHeight, SecondHeight) + 1;
        return ans;
}

bool isIdentical(node *r1, node *r2) {
        if( r1 == NULL && r2 != NULL || r1 != NULL && r2 == NULL  )return false;
        if( r1 == NULL && r2==NULL )return true;
        bool left  = isIdentical(r1->left,r2->left); 
        bool right = isIdentical(r1->right,r2->right);
        bool value = ( r1->data == r2->data);
        return (left && right && value);
}

pair< int , bool > balance(node *root){
    if(!root){
        pair<int , bool> p = make_pair(0,true);
        return p;
    }
    pair<int,bool> left = balance(root->left);
    pair<int,bool> right = balance(root->right);
    pair<int,bool> ans;
    ans.first=max(left.first,right.first)+1;
    if(left.second && right.second && (abs(left.first - right.first) < 2)){
        ans.second = true;
    }
    else {
        ans.second = false;
    }
    return ans;
}

bool isBalanced(node *root) {
    pair<int,bool> ans = balance(root);
    return ans.second;
}

vector <int> zigZagTraversal(node* root) {
    vector<int>finalans;
    if( !root )return finalans;
    queue< node* > container;
    container.push(root);
    bool leftToright = true;
    while( !container.empty() ){
        int size = container.size();
        vector< int >tempans( size );
        for( int i = 0; i < size ; i++ ){
            node* trvs = container.front();
            container.pop();
            int index = leftToright ? i : size - i -1;
            tempans[index] = trvs -> data;
            if( trvs -> left )container.push(trvs->left);
            if( trvs -> right )container.push(trvs->right);
            
        }
        leftToright = !leftToright;
        for ( auto i : tempans ) finalans.push_back(i); 
    }
    return finalans;
}

void treeToLinkedlist(node* &root) {
    node* current = root ;
    while( current ){
        if( current -> left ){
            node* previous = current -> left;
            while ( previous -> right )previous = previous -> right;
            previous -> right = current -> right ;
            current -> right = current -> left;
            current -> left  = NULL;
        }
        current = current -> right;
    }
}

void treetrvsleft(node *root , vector<int> &ans) {
    if( !root || (root->left == NULL && root->right == NULL))return;
    ans.push_back( root -> data );
    if ( root->left ) treetrvsleft( root->left , ans );
    else treetrvsleft( root->right , ans );
}

void treetrvsleaf (node* root , vector<int> &ans) {
    if ( !root ) return;
    if ( root->left == NULL && root->right == NULL ){
        ans.push_back( root->data );
        return;
    }
    treetrvsleaf( root->left , ans );
    treetrvsleaf( root->right , ans );
}

void treetrvsright( node *root , vector<int> &ans ){
    if( !root || (!root ->left && !root->right )) return;
    if( root -> right ) treetrvsright( root -> right , ans );
    else treetrvsright( root -> left , ans );
    ans.push_back( root -> data );
};

vector <int> boundary(node *root) {
    vector<int> ans;
    if( root == NULL ) return ans;
    ans.push_back( root -> data );
    treetrvsleft( root -> left , ans );
    treetrvsleaf( root -> left , ans );
    treetrvsleaf( root -> right , ans );
    treetrvsright( root -> right , ans);
    return ans;
}

vector<int> verticalOrder( node *root ) {
    map< int, map< int , vector< int > > > nodes;
    queue< pair < node* , pair< int , int > > > q;
    vector< int > ans;
    if(root == NULL) return ans;
    q.push( make_pair( root , make_pair( 0 , 0 )));
    while( !q.empty() ) { 
        pair< node* , pair< int , int > > temp = q.front();
        q.pop();
        node* frontNode = temp.first;
        int hd = temp.second.first;
        int lvl = temp.second.second;
        nodes[ hd ][ lvl ].push_back( frontNode->data );
        if( frontNode->left )
            q.push( make_pair( frontNode->left , make_pair( hd - 1 , lvl + 1) ));
        if( frontNode->right )
            q.push( make_pair( frontNode->right , make_pair( hd + 1 , lvl + 1 )));
    }

    for( auto i: nodes ) {
        for( auto j: i.second ) {
            for( auto k: j.second )
            {
                ans.push_back( k );
            }
        } 
    }
    return ans;
}

vector<int> topView(node *root) {
    vector< int > ans ;
    if( !root )return ans;
    map< int , int > nodes;
    queue< pair < node* , int > >q;
    q.push( make_pair( root , 0 ) );
    while( !q.empty() ){
        node* front = q.front().first;
        int Hd = q.front().second;
        q.pop();
        //In case of bottom view  we remove this condition below.
        if( nodes.find(Hd) == nodes.end() ){  
            nodes[Hd] = front -> data;
        }
        if( front -> left ) q.push( make_pair( front -> left , Hd - 1 ));
        if( front -> right ) q.push( make_pair( front -> right , Hd + 1 ));
    }
    for( auto i : nodes ){
        ans.push_back( i.second );
    }
    return ans;
}

void rightViewTrvsl( node* root , vector< int > &ans , int level ){
    if(  !root  )return;
    if( level == ans.size() )ans.push_back( root -> data );
    // from interchanging below two lines we can get left view
    rightViewTrvsl( root -> right , ans , level + 1); 
    rightViewTrvsl( root -> left , ans , level + 1);
}

vector<int> rightView(node *root){
    vector<int>ans;
    rightViewTrvsl( root , ans , 0 );
    return ans;
}

node* lowestCommonAncestor(node* root, node* p, node* q) {
        if( root == NULL )return NULL;
        if( root  ==  p || root  == q  )return root;
        node* leftAns = lowestCommonAncestor( root -> left , p , q );
        node* rightAns = lowestCommonAncestor( root ->  right , p , q);
        if( leftAns != NULL && rightAns != NULL )return root;
        else if ( leftAns != NULL && rightAns == NULL )return leftAns;
        else if ( leftAns == NULL && rightAns != NULL )return rightAns;
        else return NULL;
}

int Findposition(int in[] ,int inorderStart , int inorderEnd , int element ){
    for(int i = inorderStart ; i<=inorderEnd ;i++){
        if(in[i]==element) return i ; 
    }
    return -1 ;
}

node* solve(int in[],int pre[], int &index ,int inorderStart , int inorderEnd , int n){
    if(index>=n || inorderStart > inorderEnd)return NULL ;
    int element = pre[index++] ; 
    node* root  = new node(element); 
    int position  = Findposition(in , inorderStart , inorderEnd ,element);
    root->left = solve(in , pre , index  , inorderStart , position-1 ,n);
    root->right = solve(in , pre , index , position+1 , inorderEnd ,n);
    return root ;
}

node* buildTree(int in[],int pre[], int n) {
     int preorderindex  = 0 ;  
     node* ans = solve(in , pre , preorderindex , 0  , n-1 , n );
     return ans ;
}

int find(vector<int>& inorder , int inStart , int inEnd , int element ){
    for(int i = inStart ; i<= inEnd ; i++){
        if(inorder[i] == element )return i;
    }
    return -1;
}

node* solve(vector<int>& inorder,vector<int>& postorder , int &postIndex , int inStart , int inEnd){
    if(postIndex < 0 ||  inStart > inEnd)return NULL;
    int element = postorder[postIndex-- ];
    int pos = find(inorder,inStart,inEnd,element);
    node* root = new node(element);
    root -> right = solve(inorder ,postorder ,postIndex , pos+1,inEnd);
    root -> left  = solve(inorder , postorder , postIndex , inStart , pos - 1);
    return root;
}

node* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int postIndex = postorder.size()-1;
    node* ans = solve(inorder,postorder,postIndex,0,inorder.size()-1);
    return ans;
}

node* ParentToNode( node* root , map< node* , node* > &nodeToParent , int target ){
    node* res = NULL ;
    queue< node* >q ;
    q.push(root);
    nodeToParent[ root ] = NULL ;
    while(!q.empty()){
        node* front = q.front();
        q.pop();
        if( front -> data == target)res = front;
        if( front -> left ){
            nodeToParent[ front -> left ] = front ;
            q.push( front -> left );
        }
        if( front -> right ) {
            nodeToParent[ front -> right ] = front ;
            q.push( front -> right );
        }
    }
    return res;
}
    
int burning( node* start , map< node* , node* > &nodeToParent ){
    map< node* , bool>visited;
    queue< node* > q;
    q.push(start);
    visited[ start ] = true ;
    int ans = 0;
    while( !q.empty() ){
        int flag = 0 ;
        int size = q.size();
        for(int i = 0; i<size ; i++){
            node* temp = q.front();
            q.pop();
            if( ! visited [ temp -> left ] && temp->left){
                visited [ temp -> left ] = true ;
                q.push( temp -> left ) ;
                flag =1;
            }
            if( ! visited [temp -> right ] && temp -> right ){
                visited [ temp -> right ] = true ;
                q.push( temp -> right ) ;
                flag =1;
            }
            if( nodeToParent[ temp ] && !visited[ nodeToParent[temp] ]){
                visited [ nodeToParent[ temp ] ] = true ;
                q.push( nodeToParent[ temp ]) ;
                flag =1;
            }
        }
        if( flag == 1 ) ans ++;
    }
    return ans;
}
 
int minTime(node* root, int target) 
{
    map<node* , node* > nodeToParent ;
    node* start = ParentToNode( root , nodeToParent , target );
    int ans = burning( start , nodeToParent );
    return ans;
}



int main() {
    node* root = NULL;
    buildFromLevelOrder(root);
    levelOrderTraversal(root);
    return 0;
}