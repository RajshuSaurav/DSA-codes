#include<bits/stdc++.h>

using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int x){
        this -> data = x;
        this -> left = NULL;
        this -> right = NULL;
    }

};

class LargestBST{
    public:
    int mini ;
    int maxi ;
    bool isBST;
    int size;

    LargestBST solve( node*root , int & ans){
        if( !root )return {INT_MAX , INT_MIN , true , 0};
        LargestBST left = solve(root -> left , ans);
        LargestBST right = solve ( root -> right , ans);
        LargestBST CurrentNode ;
        CurrentNode.mini = min( root -> data , left.mini);
        CurrentNode.maxi = max( root -> data , right.maxi);
        CurrentNode.size = left.size + right.size + 1;
        if( left.isBST && right.isBST && root -> data > left.maxi 
                                        && root -> data < right.mini ){
            CurrentNode.isBST = true;
        }
        else CurrentNode.isBST = false;
        if(CurrentNode.isBST)ans = max ( ans , CurrentNode.size );
        return CurrentNode;
    }
    
    int largestBst(node *root)
    {
    	int maxSize = 0;
    	LargestBST answer = solve(root,maxSize);
    	return maxSize;
    }
};

node* insertIntoBST( node* root , int data ){
    if( root == NULL ){
        root = new node(data);
        return root;
    }
    if( data > root -> data) root -> right = insertIntoBST( root -> right , data );
    else root -> left = insertIntoBST( root -> left , data );
    return root ;
}

void takeInput( node* &root ){
    int data ;
    cin >> data ;
    while( data != -1 ){
        root = insertIntoBST(root , data );
        cin >> data;
    }
}

node* minValue( node* root ){
    node* temp = root;
    while(temp -> left)temp = temp -> left;
    return temp ;
}

node* maxValue( node* root ){
    node* temp = root;
    while( temp -> right) temp = temp ->right;
    return temp;
}

bool recursiveSearchInBST(node* root, int x) {
    if( !root ) return false ;
    if( x == root -> data )return true ;
    if( x > root -> data )recursiveSearchInBST( root -> right , x );
    else recursiveSearchInBST(root -> left , x);
}

node* iterativeSearchInBST(node* root, int val) {
    node *temp = root ; 
    while(temp != NULL) {
        if (temp -> data == val) return temp ; 
        if (temp -> data > val) temp = temp -> left; 
        else temp = temp -> right ; 
    }
    return NULL ; 
}

void inOrder( node* root ){
    if( !root )return ;
    inOrder( root -> left );
    cout<< root ->data << " ";
    inOrder( root -> right);
}

// always keep in mind that inOrder traversal always element in sorted way.

node* DeleteNode(node* &root , int x){
    if( root -> data == x){
        if( !root -> left  &&  !root -> right ){
            delete root;
            return NULL;
        }
        if( !root -> left && root -> right ){
            node* temp2 = root -> right;
            delete root ;
            return temp2;
        }
        if( !root -> right && root -> left ){
            node* temp2 = root -> left;
            delete root ;
            return temp2;
        }
        if( !root -> left && !root -> right ){
            node* temp2 = minValue( root -> right );
            root -> data = temp2 -> data;
            root -> right = DeleteNode( root -> right , temp2->data );
            return root;
        }
    }
    if( root -> data < x ){
        root -> right = DeleteNode( root -> right, x );
        return root;    
    }
    if( root -> data > x ){
        root -> left = DeleteNode( root -> left , x);
        return root;
    }
}

bool validate( node* root , int min , int max ){
    if( !root )return true ;
    if( root -> data >= min && root -> data <= max ){
        bool left = validate( root -> left , min ,root -> data );
        bool right = validate( root -> right , root -> data , max );
        return left && right;
    }
    else return false;
}

node* lowestCommonAncestor( node* root, node* p, node* q) {
    node* temp = root;
    if(temp -> data > p -> data && temp -> data > q -> data )
        return lowestCommonAncestor( temp -> left ,p ,q);
    if( temp -> data < p -> data && temp -> data < q -> data )
        return lowestCommonAncestor( temp -> right ,p ,q); ;
    return temp ;
}

void inorder(node* root , vector<int> &ans ){
    if(root == NULL)return;
    inorder ( root -> left , ans );
    ans.push_back( root -> data  );
    inorder( root -> right , ans );
}

node* BSTmakerFromInorder(vector<int>ans ,int i, int j){
    if(i > j)return NULL;
    int mid = j - ((j-i)/2);
    node* root = new node( ans [ mid ]);
    root -> left = BSTmakerFromInorder(ans, i , mid - 1 );
    root -> right = BSTmakerFromInorder(ans , mid+1 , j);
    return root;
}

node* balanceBST( node* root ) {
    vector<int>ans;
    inorder( root , ans );
    int n = ans.size() - 1;
    node* root2 = BSTmakerFromInorder( ans , 0 , n );
    return root2;
}

node* BSTfrompreorder(vector<int>& preorder , int min , int max , int &i){
    if( i >= preorder.size() ) return NULL;
    if( preorder [ i ] < min || preorder [ i ] > max )return NULL;
    node* root = new node(preorder[ i++ ]);
    root -> left = BSTfrompreorder( preorder , min , root -> data , i );
    root -> right = BSTfrompreorder( preorder , root -> data , max , i );
    return root ;
}

void inorder( node *root , vector<int> &ans ){
    if(!root )return;
    inorder(root -> left , ans );
    ans.push_back(root -> data);
    inorder(root -> right , ans );
}

vector<int> merge(vector<int>inorder1,vector<int>inorder2){
    int n = inorder1.size();
    int m = inorder2.size();
    int i = 0;
    int j = 0;
    vector<int>ans;
    while( i < n && j < m){
        if( inorder1[i] < inorder2[j]){
            ans.push_back(inorder1[i]);
            i++;
        } else {
          ans.push_back(inorder2[j]);
          j++;
        }
    } 
    while(i<n){
        ans.push_back(inorder1[i]);
        i++;
    }
    while(j<m){
        ans.push_back(inorder2[j]);
        j++;
    }
    return ans;
}

node* makeBST(vector<int>inorder,int start,int end ){
    if(start > end)return NULL;
    int mid = end - (( end - start )/2);
    node* root = new node(inorder[mid]);
    root -> left  = makeBST(inorder, start  , mid - 1 );
    root -> right = makeBST(inorder, mid + 1, end );
    return root ;
}

node *mergeBST(node *root1, node *root2){
    vector<int>inorder1;
    vector<int>inorder2;
    inorder(root1,inorder1);
    inorder(root2,inorder2);
    vector<int>finalInorder = merge(inorder1,inorder2);
    int start = 0;
    int end = finalInorder.size() - 1;
    node* finalroot = makeBST(finalInorder, start, end);
    return finalroot;
}

int main(){
    
    return 0;
}