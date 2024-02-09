#include<bits/stdc++.h>

using namespace std;

/*Greedy Algorithm is a programming technique in which we find the 
optimal solution for the particular moment.*/

class Maximum_Meeting_Selection{
    public:
    static bool compare( pair< int , int >a , pair< int , int>b ){
        return a.second < b.second ;
    }
    int maxMeetings(int start[], int end[], int n) {   
        vector < pair< int , int > >container ;
        for( int i = 0 ; i < n ; i++ )container.push_back(make_pair(start[ i ] , end[ i ]));
        sort( container.begin() , container.end() , compare);
        int count = 1 ;
        int Ending = container[0].second ;
        for( int i = 1 ; i < n ; i++){
            if( container[i].first > Ending ){
                Ending = container[ i ].second;
                count++ ;
            }
        }
        return count ;
        
    }
};

string reverseWords(string S) { 
  string ans = "";
  string temp = "" ;
  for( int i = S.length() - 1 ; i >=0 ; i--){
        if(S[i] == '.'){
            reverse(temp.begin(),temp.end());
            ans= ans + temp;
            ans.push_back('.');
            temp = "";
        }
        else{
            temp.push_back(S[i]);
        }  
    }
    reverse(temp.begin(),temp.end());
    ans= ans + temp;
    return ans;    
} 

long long findMinDiff(vector<long long> a, long long n, long long m){
    int i = 0 ;
    int j = m-1;
    sort( a.begin() , a.end() );
    int mini = INT_MAX;
    while( j < a.size()){
        int diff = a[j] - a[i];
        mini = min( mini , diff);
        i++;
        j++;
    }
    return mini;
}   

long long minCostRopeCutting(long long arr[], long long n) {
    priority_queue < long long, vector< long long >, greater<long long >> container;
    for( int i = 0; i < n ; i++)container.push( arr[i] );
    long long cost = 0 ;
    while( container.size() > 1){
        long long first = container.top();
        container.pop();
        long long second = container.top();
        container.pop();
        long long merge = first + second ;
        cost += merge;
        container.push(merge);
    }
    return cost ;
}

class Node{
    public : 
    int data;
    Node* left;
    Node* right;
    
    Node( int d ){
        data = d;
        left = NULL;
        right = NULL;
    }
};

class cmp {
    public :
    bool operator()( Node* a , Node* b){
        return a->data > b->data;
    }
};

class huffmanCode{
	public:
	    void traverse( vector< string >& ans , string temp , Node* node){
	        if( node -> left == NULL || node -> right == NULL  ){
	            ans.push_back(temp);
	            return;
	        }
	        traverse( ans , temp + "0" , node -> left );
	        traverse( ans , temp + "1" , node -> right );
	    }

		vector<string> huffmanCodes(string S,vector<int> f,int N) {
		    priority_queue< Node* , vector< Node* > , cmp >container;
		    for( auto i : f ){
		        Node* temp = new Node( i );
		        container.push( temp );
		    }
		    while( container.size() > 1 ){
		        Node* left = container.top();
		        container.pop();
		        Node* right = container.top();
		        container.pop();
		        Node* newNode = new Node( left->data + right->data);
		        newNode->left = left ;
		        newNode->right = right ;
		        container.push(newNode);
		    }
		    Node* root = container.top();
		    vector< string > ans;
		    string temp ="";
		    traverse(ans, temp,root);
		    return ans;
		}
};

struct Item{
    int value;
    int weight;
};

class FractionalKnapsack{
    public:
    static bool cmp( pair< double , Item >a , pair< double , Item > b){
        return a.first > b.first;
    }
    double fractionalKnapsack(int W, Item arr[], int n) {
        vector<pair< double , Item > >container;
        for( int i = 0 ; i < n ; i++){
            double priority = arr[i].value*(1.0)/arr[i].weight;
            container.push_back(make_pair(priority,arr[i]));
        }
        sort( container.begin() , container.end() , cmp );
        double totalvalue = 0 ;
        for( auto element : container){
            if( element.second.weight > W){
                totalvalue += W*element.first;
                W = 0 ;
            }
            else{
                totalvalue += element.second.value;
                W -= element.second.weight;
            }
        }
        return totalvalue;
    }
};

struct Job { 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};

class JobSchedulingProblem {
    public:
    //Function to find the maximum profit and the number of jobs done.
    static bool cmp( Job a , Job b){
        return a.profit > b.profit;
    }
    
    vector<int> JobScheduling(Job arr[], int n){ 
        sort( arr , arr+n , cmp );
        int maxiDeadLine = INT_MIN;
        for( int i = 0 ; i < n ; i++){
            maxiDeadLine = max( maxiDeadLine , arr[i].dead );
        }
        vector<int>container( maxiDeadLine + 1 , -1 );
        int totalJobs = 0 ; int totalProfit = 0;
        for( int i = 0 ; i < n ; i++ ){
            int currID = arr[i].id;
            int currProfit = arr[i].profit;
            int currDead = arr[i].dead;
            for( int k = currDead ; k > 0 ; k-- ){
                if( container[k] == -1 ){
                    container[k] = currID ;
                    totalJobs++;
                    totalProfit += currProfit;
                    break;
                }
            }
        }
        vector<int>ans;
        ans.push_back(totalJobs);
        ans.push_back(totalProfit);
        return ans;
    } 
};

int main(){
    
    return 0;
}