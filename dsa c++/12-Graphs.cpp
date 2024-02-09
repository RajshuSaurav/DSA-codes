#include<bits/stdc++.h>
using namespace std;

/* Graph is a data structure , having combination of nodes and edges */ 

class graph{
    public:
        unordered_map<int, list<int>>adjency_list;

    void add_edges(int u , int v , bool direction ){
        adjency_list[u].push_back(v);
        if ( direction == 0)adjency_list[v].push_back( u );
    }
    
    void printGraph(){
        for( auto i : adjency_list){
            cout<< i.first << " -> ";
            for(auto m : i.second){
                cout << m << " , ";
            }
            cout << endl;
        }
    }
};

vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    map< int , bool >visited;
    queue<int>q;
    q.push(0);
    vector<int> ans;
    visited[0]=1;
    while( !q.empty() ){
        int Node = q.front();
        ans.push_back(Node);
        q.pop();
        for(auto m : adj[Node]){
            if(!visited[m]){
                q.push(m);
                visited[ m ] = 1;
            }
        }
    }
    return ans;
}

void dfs( int node , unordered_map< int , bool >&visited , vector< int > &ans, vector<int> adj[]){
    visited[ node ] = true;
    for ( auto i : adj[ node ]){
        if( !visited[i] ){
            ans.push_back( i );
            dfs( i , visited, ans  , adj );
        }
    }
}
  
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    unordered_map< int , bool >visited ;
    vector< int > ans;
    ans.push_back(0);
    for ( int i = 0 ; i < V ; i++ ){
        if( !visited[i]){
            dfs( i , visited, ans  , adj );
        }
    }
    return ans;
}

bool checker( int src , map< int , bool > &visited , vector<int> adj[] ){
    map < int , int > parent ;
    queue< int > q ;
    q.push( src ) ;
    parent [ src ] = -1 ;
    visited[ src  ] = true ;
    while ( !q.empty() ){
        int node = q.front();
        q.pop();
        for( auto i : adj[node]){
            if( visited[ i ] && parent[ node ] !=  i ) return true;
            else if( !visited[i] ){
                q.push( i );
                parent[ i ] = node;
                visited[ i ] = true;
            }
        }
    }
    return false;
}

bool isCycleUsingBFS(int V, vector<int> adj[]) {
    map< int , bool > visited ;
    for( int i = 0 ; i < V ; i++){
        if ( ! visited[ i ] ){
            if (  checker( i , visited , adj ))return true;
        }
    }
    return false;
}

bool loopChecker ( vector< int >adj[] , int node , vector<bool>&visited , vector<bool>&dfsVisited) {
    visited[ node ]=true;
    dfsVisited[ node ]=true;
    for(int x : adj[ node ]) {
        if( visited[ x ] == false && loopChecker( adj , x , visited , dfsVisited ))return true;
        else if( dfsVisited[ x ] == true ) return true;
    }
    dfsVisited[ node ] = false;
    return false;
}

bool isCyclicInDirectedGraphUsisngDFS(int V, vector< int > adj[]) {
    vector< bool > visited( V , false );
    vector< bool > dfsVisited( V, false );
    for( int i = 0 ; i < V ; i++) {
        if( visited[ i ] == false){
            if(loopChecker(adj , i , visited , dfsVisited )) return true;
        }
    }
    return false;
}

/*Topological Sort only work for directed acyclic graph and the parent of eack node 
  Occurs before their respective childs . */
  
void topologicalSort ( int node , map< int , bool >&visited , stack< int >&container , vector<int> adj[] ){
    visited[ node ] = 1;
    for( auto i : adj[ node ]){
        if( !visited[i] ){
            topologicalSort( i , visited , container , adj);   
        }
    }
    container.push(node);
}

vector<int> topoSort(int V, vector< int > adj[]) {
    stack< int >container;
    map< int , bool > visited ;
    for( int i = 0 ; i < V ; i++){
        if( !visited[i] )topologicalSort( i , visited , container , adj );
    }
    vector< int >ans;
    while( ! container.empty() ){
        ans.push_back( container.top() );
        container.pop();
    }
    return ans;
}

 vector<int> topoSortUsingKahnsAlgo(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V ; u++){
        for (int v : adj[u])indegree[v]++;
    }
    queue<int> q;
    for (int i = 0; i < V; i++){
        if (indegree[i] == 0) q.push( i );
    }
    vector<int> ans;
    while ( !q.empty() ){
        int front = q.front();
        q.pop();
        ans.push_back(front);
        for (int neighbour : adj[front]) {
            indegree[neighbour]--;
            if (indegree[neighbour] == 0) q.push(neighbour);
        }
    }
    return ans;
}

bool isCyclicUsingTopologicalSort(int V, vector<int> adj[]) {
    vector< int > indegree( V, 0 );
    for( int i = 0 ; i < V ; i++ ){
        for( auto m : adj[ i ] )indegree[ m ]++;
    }
    queue< int > container;
    for( int i = 0 ; i < V ; i++ ){
        if( indegree[ i ] == 0 )container.push( i );
    }
    int count = 0;
    while( !container.empty( ) ){
        int front = container.front( );
        container.pop();
        count++;
        for( auto m : adj[ front ] ){
            indegree[ m ]--;
            if( indegree[ m ] == 0 )container.push( m );
        }
    }
    if( count == V )return false;
    /*if number of count is equal to the total number of nodes present 
      this indicates that the graph is acyclic and valid for topoligical sort.*/  
    return true;
    
}

vector<int> shortestPathInDirectedAcyclicGraph(int N , int M , vector<vector<int>>& edges){
   vector<vector<int>> adj[N];
    for(auto e : edges)adj[e[0]].push_back( {e[1], e[2]});
    vector<int> distance(N, INT_MAX);
    distance[0] = 0;
    queue<int> q;
    q.push(0);
    while(q.size()){
        int node = q.front(); q.pop(); 
        for(auto padosi : adj[ node ]){
            int nbr = padosi[0];
            int dist = padosi[1];
            if(distance[ node ] + dist < distance[ nbr ]){
                distance[ nbr ] = distance[ node ] + dist ;
                q.push(nbr);
            }
        }
    }
    for(auto &a : distance)
        if(a==INT_MAX)a = -1;
    return distance ;
}

vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    vector < int >distance(V,INT_MAX);
    set< pair< int , int >> container;
    distance[ S ] = 0;
    container.insert(make_pair( S , 0 ));
    while( !container.empty() ){
        auto top = *( container.begin() );
        int topNode = top.first;
        int topWeight = top.second ;
        container.erase( top );
        for ( auto bagal : adj[ topNode ] ){
            if( topWeight + bagal[1] < distance[ bagal[0] ] ){
                auto past = container.find( make_pair( bagal[0] , distance[ bagal[0] ] ));
                if( past != container.end() )
                    container.erase( past );
                distance[ bagal[0] ] = topWeight + bagal[1] ;
                container.insert( make_pair( bagal[0] , distance[ bagal[0] ] ) );
            }
        }
    }
    return distance ;
}

/*Spaning Tree - when you convert a graph into a tree such that it contains
 n nodes and n-1 edges and every nodes is reacheable by every other nodes 
 then that structure is known as the spaning tree and from all the spaning tree
 the spanning tree which contains the smallest cost of weights is known as 
 the minimum spaning tree for that graph.
    the method that is used to find the minimum spaning tree :-
     prim's Algo 
     krushkal's Algorithm.*/

int PrimsAlgorithm(int V, vector<vector<int>> adj[]) {
    vector< bool > mst( V , false );
    vector< int > parent( V , -1 );
    vector< int > key (V , INT_MAX );
    key[0] = 0;
    for ( int i = 0 ; i < V ; i ++ ){
        int mini = INT_MAX;
        int node;
        for ( int j = 0 ; j < V ; j++ ){
            if( (key[ j ] < mini) && (mst[j] == false )){
                mini = key[ j ] ;
                node = j ;  
            }
        }
        mst[ node ] = true ;
        for ( auto child : adj[ node ] ){
            int kid = child[0];
            int weight = child[1] ;
            if ( (weight  < key[ kid ] ) &&  (mst[ kid ] == false )){
                key[ kid ] = weight  ;
                parent[ kid ] = node ;
            }
        }
    }
    int sum = 0 ;
    for( auto i : key )sum += i;
    return sum;
}


void dfs(int node, int parent, vector<int> &discT, vector<int> &low, 
        unordered_map< int, bool > &visited, vector<vector<int>> &result, 
        vector< int >adj[], int &timer) {
    visited[node] = true;
    discT[node] = low[node] = timer++;
    for(auto neighbour : adj[node]) {
        if(neighbour == parent) continue;
        if(!visited[neighbour]) {
            dfs(neighbour, node, discT, low, visited, result, adj, timer);
            low[node] =min(low[node], low[neighbour]);
            if(low[neighbour] > discT[node]) {
                vector<int> ans;
                ans.push_back(node);
                ans.push_back(neighbour);
                result.push_back(ans);
            }
        }
        else {
             low[node] = min(low[node], discT[neighbour]);
        }
    }
    
}

vector<vector<int>> findBridges(vector< int > adj[] , int v) {
    int timer = 0;
    vector< int > discT(v);
    vector< int > low(v);
    int parent = -1;
    unordered_map< int, bool > visited;
    for(int i = 0; i<v; i++) {
          discT[i] = -1;
          low[i] = -1;
    }
    vector< vector< int > > result;
    for(int i = 0; i < v; i++ ) {
          if( !visited[ i ] )dfs( i, parent, discT, low, visited, result, adj, timer );
        }
    return result;
}


/* Articulation point or a cut vertex is node in a graph removing which the graph is splited
    into two or more disconnected components .
*/

class ArticulationPoint  {
  public:
    
    void dfs( int node , int parent , vector< bool >&ans , vector< bool >&visited , 
        vector< int >adj[], vector<int >&discT,vector< int > &lowT , int timer ){
            lowT[ node ]= discT[ node ] = timer++;
            visited[ node ] = true ;
            int child = 0;
            for( auto nbr : adj[ node ]){
                if( nbr == parent )continue;
                if( visited[ nbr ] == false){
                    dfs( nbr , node , ans , visited , adj , discT , lowT, timer );
                    lowT[ node ] = min( lowT[ node ] , lowT[ nbr ] );
                    if( (lowT[ nbr ] >= discT[ node ]) && (parent != -1) ){
                        ans[node]=true ;
                    }
                    child++;
                }
                else {
                    lowT[ node ] = min( lowT[ node ], discT[ nbr ]);
                }
            }
            if( parent == -1 && child > 1)ans[ node ] = true ;
        }  
  
    vector<int> articulationPoints(int V, vector<int>adj[]) {
        vector< int > discT(V,-1);
        vector< int > lowT(V,-1);
        vector< bool > visited(V,false);
        vector < bool > ans(V,false);
        int parent = -1 ;
        int timer = 0 ;
        for ( int i = 0 ; i < V ; i++ ){
            if( visited[i] == false )
                dfs( i , parent , ans , visited , adj , discT , lowT, timer);
        }
        vector< int >final_ans ; 
        for ( int i = 0 ; i < V ; i++)if( ans[i] )final_ans.push_back(i);
        if( final_ans.size() )return final_ans;
        return {-1};
    }
};

/* Kosaraju's Algorithm - this algorithm is used to find the strongly connected 
    components of the graph . */

class Kosarajus_Algorithm {
	public:
	void dfs( int node , vector< bool >&visited , vector<vector<int>>& adj , stack< int > &container  ){
	    visited[ node ] = true ;
	    for( auto nbr : adj[ node ]){
	        if( visited[ nbr ] == false )dfs( nbr , visited ,adj, container );
	    }
	    container.push( node );
	}
	
	void revdfs( int node , vector< bool >&visited , vector<vector<int>>& adj ){
	    visited[ node ] = true ;
	    for( auto nbr : adj[ node ]){
	        if( visited[ nbr ] == false )revdfs( nbr , visited ,adj );
	    }
	}
	
    int kosaraju(int V, vector<vector<int>>& adj) {
        vector< bool > visited( V , false );
        stack< int >container ;
        for( int i = 0 ; i < V ; i++){
            if( visited[ i ] == false )dfs( i ,visited, adj , container );
        }
        vector< vector<int> >transpose(V) ;
        for( int i = 0 ; i < V ; i++ ){
            visited[ i ] = false;
            for( auto m : adj[ i ]){
                transpose[m].push_back( i );
            }
        }
        int count = 0;
        while( !container.empty() ){
            int node = container.top();
            container.pop();
            if( visited[ node ] == false ){
                count++;
                revdfs( node  ,visited, transpose );
            }
        }
        return count ;
    }
};

vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
    vector<int>dist(V,1e8);
    dist[S] = 0;
    for(int i=0;i<V;i++){
        for(auto it : edges) {
           int u = it[0];
           int v = it[1];
           int weight = it[2];
           if(dist[u] != 1e8 && dist[u] + weight < dist[v])
               dist[v] = dist[u] + weight;
        }
    }
    for(auto it : edges) {
           int u = it[0];
           int v = it[1];
           int weight = it[2];
           if(dist[u] != 1e8 && dist[u] + weight < dist[v]){
               return {-1};
           }
    }
     return dist;
}

int main(){
    cout<< "Enter the number of nodes " << endl;
    int nodes;
    cin>> nodes;
    int edges;
    cout<< "Enter the number of edges " << endl;
    cin>> edges;
    graph G ;
    for( int i = 0 ; i < edges ; i++ ){
        int u , v;
        cin>> u >> v;
        G.add_edges(u,v,0);
    }
    G.printGraph();
    return 0;
}