#include<bits/stdc++.h>

using namespace std;

/* D.P can be applied to a problem when it staisfied these following
    conditions :-
    (1) Optimal solution of a  bigger problem can be solved using optimal 
        solutions of its subproblems.
    (2) overlapping subproblem should be there in the big problems.  

    it has 2 approaches :- 
    (1) Top Down - Recursion + memoization( storing soluton of subproblems)
    (2) Bottom up - tabulation 
    if space optimazation can be done in the question then go for that . */
    
int fibo( int n , vector< int >&DP){
    if( n <= 1)return n ;
    if( DP[ n ] != -1 )return DP[ n ];
    DP[ n ] = fibo( n-1 , DP )  + fibo( n-2 , DP ) ;
    return DP[ n ];
}

int nthFibonacci(int n){
    vector< int >DP(n+1,-1);
    return fibo(n , DP) ;
}

int solve(vector<int>& coins, int amount , vector< int >&dp) {
    int ans ;
    int mini = INT_MAX;
    if( amount == 0 )return 0;
    if( amount < 0 )return INT_MAX;
    if(dp[ amount ] != -1 )return  dp[amount];
    for( int i = 0 ; i < coins.size() ; i++ ){
        ans = solve( coins , amount - coins[ i ] ,dp );
        if(ans != INT_MAX )mini = min( mini ,1 + ans );
    }
    dp[amount] = mini;
    return dp[amount];
}

int coinChange(vector<int>& coins, int amount) {
    vector< int >dp(amount+1 , -1 );
    dp[0] = 0 ;
    int ans = solve(coins , amount , dp );
    if(ans == INT_MAX)return -1;
    return dp[amount];
}

int HouseRob(vector<int>& nums) {
    int prev1 = nums[0];
    int prev2 = 0 ; 
    for( int i = 1 ; i < nums.size() ; i++ ){
        int incl = prev2 + nums[ i ];
        int excl = prev1 ;
        int ans = max( incl , excl );
        prev2 = prev1;
        prev1 = ans;
    }
    return prev1;
}

long long int mod = 1e9 +7 ;

long long int solve( int n , vector< long long int > &dp ) {
    if(n ==1)return 0;
    if(n ==2 )return 1;
    if(dp[n] != -1)return dp[n];
    dp[n] = ((n-1)%mod) * ((solve(n-1,dp)%mod)+(solve(n-2,dp)%mod));
    return dp[n];
}

long long int countDerangements(int n) {
    vector< long long int >dp(n+1,-1);
    dp[n] = solve(n,dp)%mod;
    return dp[n];
}

int add(int a , int b){
    return (a+ b); 
}
 
int multi(int a , int b){
    return (a * b);
}

int ninjaFenceProblem(int n , int k){
    vector<int> dp(n+1,0);
    long long int prev2 = k;
    long long int prev1 = add(k,multi(k,k-1));
    for(int i=3 ; i<=n ; i++) {
        long long int ans = add(multi(prev2,k-1),multi(prev1,k-1));
        prev2=prev1;
        prev1=ans;
    }
    return prev1;
}

int solve(vector<int> &nums, int  n , vector< int > &dp){
    if( n < 0 )return 0;
    if( n == 0 )return nums[n];
    if(dp[n] != -1)return dp[n];
    dp[n] = max( solve(nums , n-1, dp), solve(nums , n-2 , dp )+nums[n]);
    return dp[n];
}

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector< int >dp(n,-1);
    dp[n-1] = solve( nums , n-1 , dp );
    return dp[n-1];
}

class knapsack {
    public:
    int solve( int reqWt , int wt[] , int val[] , int n , vector< vector< int > >&dp){
        if( n == 0){
            if( wt[0] <= reqWt )return val[0];
            else return 0;
        }
        if( dp[ n ][ reqWt ] != -1)return dp[ n ][ reqWt ];
        int incl = 0;
        if(wt[n] <= reqWt )incl = solve( reqWt - wt[n] , wt , val , n-1 , dp) + val[n];
        int excl = solve( reqWt , wt , val, n-1,dp);
        dp[ n ][ reqWt ] = max( incl, excl);
        return dp[ n ][ reqWt ];
    }
    
    int solveTab( int reqWt , int wt[], int val[]  , int n ){
        vector<vector<int>>dp(n , vector<int>(reqWt+1 ,0 ));
        for( int w = wt[0] ; w <= reqWt ; w++) dp[ 0 ][ w ] = val[0];
        int incl = 0;
        
        for(int ind = 1; ind < n ; ind++){
            for(int W = 0; W <= reqWt; W++){
                int notTake = 0 + dp[ ind - 1 ][ W ];
                int take = 0;
                if(wt[ind] <= W) take = val[ ind ] + dp[ ind - 1 ][ W - wt[ ind ]];
                dp[ind][W] = max(take, notTake);
            }
        }
        return dp[n-1][reqWt];       
    }
    
    int solveSO( int reqWt , int wt[], int val[]  , int n ){
        vector< int >prev1( reqWt + 1 , 0 );
    
        for( int w = wt[0] ; w <= reqWt ; w++) prev1[w] = val[0];
        for(int ind=1; ind<n; ind++){
            
            for(int W = reqWt ; W >= 0 ; W-- ){
                int notTake = 0 + prev1[W];
                int take = 0;
                if(wt[ind] <= W) take = val[ind] + prev1[W-wt[ind]];
                prev1[W] = max(take, notTake);
            }
        }
        return prev1[reqWt];
    }
    
    int knapSack(int W, int wt[], int val[], int n) 
    { 
        return solveSO( W , wt , val , n);
    }
};

class maxSquare {
public:
    int solve( int i, int j, vector<vector<int>> mat , int &maxi ,vector< vector< int > >&dp){
        if( i >= mat.size() || j >= mat[0].size() )return 0 ;
        if( dp [ i ] [ j ] != -1)return dp[ i ][ j ];
        int right = solve( i , j+1 , mat , maxi ,dp);
        int diagonal = solve( i+1 , j+1 , mat , maxi , dp  );
        int down = solve( i+1 , j , mat , maxi , dp );
        if( mat[ i ] [ j ] == 1 ){
            int ans = 1 + min( right , min(diagonal , down));
            maxi = max( ans , maxi);
            return dp[ i  ] [ j ] = ans ;
        }
        else  return dp[ i ] [ j ] = 0 ; 
    }
    
    int solveTab( vector<vector<int>> mat , int &maxi ){
        int n = mat.size(); int m = mat[0].size();
        vector< vector<int> >dp( n+1 , vector< int >(m+1 , 0 ) );
        for( int i = n-1 ; i >= 0 ; i--){
            for( int j = m - 1 ; j >= 0 ; j-- ){
                
                int right = dp[ i ] [ j +1 ];
                int diagonal = dp[ i + 1 ] [ j + 1 ];
                int down = dp[ i + 1 ][ j ];
                
                if( mat[ i ] [ j ] == 1 ){
                    int ans = 1 + min( right , min(diagonal , down));
                    maxi = max( ans , maxi);
                    dp[ i  ] [ j ] = ans ;
                }
                else dp[ i ] [ j ] = 0 ; 
            }
        }
        return dp[ 0 ][ 0 ];
    }
    
    int solveSO( vector<vector<int>> mat , int &maxi ){
        int n = mat.size(); int m = mat[0].size();
        vector< int >current ( m+1 , 0 );
        vector< int >next ( m + 1 , 0 );
        for( int i = n-1 ; i >= 0 ; i--){
            for( int j = m - 1 ; j >= 0 ; j-- ){
                
                int right = current [ j +1 ];
                int diagonal = next [ j + 1 ];
                int down = next [ j ];
                
                if( mat[ i ] [ j ] == 1 ){
                    int ans = 1 + min( right , min(diagonal , down));
                    maxi = max( ans , maxi);
                    current [ j ] = ans ;
                }
                else current [ j ] = 0 ; 
            }
            next = current ; 
        }
        return current [ 0 ];
    }
    
    int maxSquareCalculation(int n, int m, vector<vector<int>> mat){
        // vector< vector<int> >dp( n , vector< int >(m , -1) );
        int maxi = 0 ;
        // solve( 0 , 0 , mat , maxi , dp );
        // solveTab( mat , maxi );
        solveSO( mat , maxi );
        return maxi;
    }
};

class Sidejumps {
public:

    int solve ( vector< int >& obstacles , int position , int lane , vector<vector<int>>&dp){
        int n = obstacles.size() - 1;
        if( position == n )return 0;
        if( dp[position][lane] != -1 )return dp[position][lane];
        if( obstacles[position + 1] != lane){
             return dp[ position ][lane ] = solve( obstacles , position + 1 , lane , dp);
        }
        else{
            int ans = INT_MAX;
            for( int i = 1 ; i <= 3 ; i++){
                if( i != lane && obstacles[position] != i){
                   ans = min(ans , 1 + solve( obstacles , position  , i  ,dp));
                }
            }
            dp[position][lane] = ans;
            return ans;
        }    
    }

    int solveTab(  vector< int >& obstacles ){
        int n = obstacles.size() - 1;
        vector<vector<int>>dp(obstacles.size() , vector<int>(4 , 1e9));
        dp[ n ][ 0 ] = 0;dp[ n ][ 1 ] = 0;dp[ n ][ 2 ] = 0;dp[ n ][ 3 ] = 0;
        for( int position = n-1 ; position >= 0 ; position-- ){
            for( int  lane = 1 ; lane <= 3 ; lane ++){
                if( obstacles[position + 1] != lane){
                    dp[ position ][lane ] = dp[position + 1][lane];
                }
                else{
                    int ans = 1e9;
                    for( int i = 1 ; i <= 3 ; i++){
                        if( i != lane && obstacles[position] != i){
                            ans = min(ans , 1 + dp[position +1] [ i ]);
                        }
                    }
                    dp[position][lane] = ans;
                }
            }
        }
        return min( dp[ 0 ][2] , min( 1+dp[0][1], 1+dp[0][3]));
    }

    int minSideJumps(vector<int>& obstacles) {
        vector<vector<int>>dp(obstacles.size() , vector<int>(4 , -1));
        return solve( obstacles , 0 , 2 ,dp);
    }
};

class BinarySearchWithDP {
    public:
    //Function to find length of longest increasing subsequence.
    int solveMem(  int n ,int a[] , int curr , int prev , vector<vector<int>>&dp ){
      if(curr==n)
            return 0;
        
        if(dp[curr][prev+1]!=-1)
            return dp[curr][prev+1];
        int include=0;
        if(prev ==-1 || a[curr] > a[prev])
            include=1+solveMem(n,a,curr+1,curr,dp);
        int exclude=solveMem(n,a,curr+1,prev,dp);
        dp[curr][prev+1]=max(include,exclude);
        return dp[curr][prev+1];
    }
    
    int solveTab(int n,int a[])
    {
        vector<vector<int>>dp(n+1,vector<int>(n+1,0));
        
        for(int curr=n-1;curr>=0;curr--)
        {
            for(int prev=curr-1;prev>=-1;prev--)
            {
                int include=0;
                if(prev ==-1 || a[curr] > a[prev])
                    include=1+dp[curr+1][curr+1];
                int exclude=dp[curr+1][prev+1];
                
                dp[curr][prev+1]=max(include,exclude);
            }
        }
        return dp[0][0];
        
    }
    
    int solveSO(int n,int a[])
    {
        vector<int> next( n+1 , 0);
        vector< int >current( n+1 , 0 );
        for(int curr=n-1;curr>=0;curr--)
        {
            for(int prev=curr-1;prev>=-1;prev--)
            {
                int include=0;
                if(prev ==-1 || a[curr] > a[prev])
                    include=1+next[curr+1];
                int exclude=next[prev+1];
                
                current[prev+1]=max(include,exclude);
            }
            next = current;
        }
        return next[0];
        
    }
    
    int solveOptimal( int n , int a[]){
        if( n == 0 )return 0;
        vector< int >ans;
        ans.push_back( a[0]);
        for( int i = 0 ; i < n ; i++){
            if( a[i] > ans.back())ans.push_back(a[i]);
            else{
                int index = lower_bound( ans.begin() , ans.end() , a[i]) - ans.begin();
                ans[index] = a[ i ];
            }
        }
        return ans.size();
    }
    
    int longestSubsequence(int n, int a[])
    {
        // vector<vector<int>>dp( n , vector<int>(n+1 , -1));
        return solveOptimal( n , a  );
    }
};

class MaximumHeights {
public:
     bool check(vector<int> base, vector<int> newBox){
        if( (newBox[0] <= base[0]) && (newBox[1] <= base[1]) && (newBox[2] <= base[2]) ){
            return true;
        }
        else
            return false;
    }

    int solveSpaceOP(int n, vector<vector<int>>& a){
        vector<int> currRow(n+1, 0);
        vector<int> nextRow(n+1, 0);
        for(int curr = n-1; curr>=0; curr--){
            for(int prev = curr-1; prev>=-1; prev--){
                // include
                int take = 0;
                if(prev == -1 || check(a[curr], a[prev]))
                    take = a[curr][2] + nextRow[curr+1];
                // exclude
                int notTake = 0 + nextRow[prev+1];   
                currRow[prev+1] = max(take, notTake);
            }   
            nextRow = currRow;
        }
        return nextRow[0];
    }

    int maxHeight(vector<vector<int>>& cuboids) {
        // STEP - 1: Sort all dimensions for every cuboid
        for(auto &a: cuboids){
            sort(a.begin(), a.end()); 
        }
        // STEP - 2: Solve all cuboid basis on w or 1
        sort(cuboids.begin(), cuboids.end());
        // STEP - 3: Use LIS Logic
        int n = cuboids.size();
        return solveSpaceOP(n, cuboids);
    }
};

class PizzaSlices {
public:
    int solve ( int index , int endIndex , vector< int >slices , 
                    int require , vector< vector< int > >&dp ){
        if( index > endIndex || require == 0 )return 0 ;
        if( dp[ index ][ require] != -1)return dp[ index ] [ require];
        int take  = slices[ index ] + solve( index + 2 , endIndex , slices , require - 1 , dp );
        int notTake  = solve( index + 1 , endIndex , slices , require , dp );
        return dp[ index ] [ require ] = max( take , notTake );
    }

    int solveTab (  vector< int >slices ){
        int n = slices.size();
        vector<vector< int > >dp( n+2 , vector< int >( n+2 , 0) );
        for( int index  = n - 1 ; index >= 1 ; index--) {
            for( int require = 1 ; require <= n/3 ; require++ ){
                int take  = slices[ index ] + dp[ index + 2 ] [require - 1];
                int notTake  = dp [index + 1 ][ require ];
                dp[ index ] [ require ] = max( take , notTake );
            }
        }
        int case1 = dp[ 1 ][ n / 3 ];
        vector<vector< int > >dp2( n+2 , vector< int >( n+2 , 0) );
        for( int index  = n - 2 ; index  >= 0 ; index --) {
            for( int require = 1 ; require <= n/3 ; require++ ){
                int take  = slices[ index ] + dp2[ index + 2 ] [require - 1];
                int notTake  =  dp2[index + 1 ][ require ];
                dp2[ index ] [ require ] = max( take , notTake );
            }
        }
        int case2 = dp2[ 0 ][ n / 3 ];
        return max( case1 , case2 );
    }
    int solveSO( vector< int >slices ){
        int n = slices.size();
        vector< int >current( n + 2 , 0 ) ;
        vector< int >previous( n + 2 , 0) ;
        vector< int >next( n + 2 , 0 );
         for( int index  = n - 1 ; index >= 1 ; index--) {
            for( int require = 1 ; require <= n/3 ; require++ ){
                int take  = slices[ index ] + next[require - 1];
                int notTake  = current[ require ];
                previous[ require ] = max( take , notTake );
            }
            next = current ;
            current = previous ;
        }
        int case1 = current[ n / 3 ];
        vector< int >current2( n + 2 , 0 ) ;
        vector< int >previous2( n + 2 , 0) ;
        vector< int >next2( n + 2 , 0 );
        for( int index  = n - 2 ; index  >= 0 ; index --) {
            for( int require = 1 ; require <= n/3 ; require++ ){
                int take  = slices[ index ] + next2[require - 1];
                int notTake  =  current2[ require ];
                previous2[ require ] = max( take , notTake );
            }
            next2 = current2 ;
            current2 = previous2 ;
        }
        int case2 = current2[ n / 3 ];
        return max( case1 , case2 );
    }

    int maxSizeSlices(vector<int>& slices) {
        // int n = slices.size();
        // vector< vector< int > >dp( n ,vector< int >( n , -1 ) );
        // int first = solve( 0 , n - 2 , slices , n/3 , dp);
        // vector< vector< int > >dp2( n ,vector< int >( n , -1 ) );
        // int second = solve ( 1 , n - 1 , slices , n/3, dp2);
        return solveSO(slices);
    }
};

class DiceRoll {
  public:
    long long solve( int dice , int faces , int target , vector< vector< long long >>&dp){
        if( target < 0 )return 0;
        if( target != 0 && dice == 0 )return 0;
        if( target == 0 && dice != 0 )return 0;
        if( target == 0 && dice == 0 )return 1;
        if( dp[ dice ][ target ] != -1 )return dp[ dice ][ target ];
        long long ans = 0 ;
        for( int i = 1 ; i <= faces ; i++)ans += solve( dice - 1 , faces , target - i , dp );
        dp[ dice ][ target ] = ans ;
        return dp[ dice ][ target ];
    }
    
    long long noOfWays(int M , int N , int X) {
        vector< vector< long long >> dp( N+1 , vector< long long >( X + 1 , -1 ));
        return solve( N , M , X , dp);
    }
};

class Partition_Equal_Subset_Sum {
public:
    bool solve( int index , vector< int >nums , int target , vector< vector< int > >&dp){
        if( index >= nums.size() )return false;
        if( target < 0 )return false;
        if( target == 0 )return true;
        if( dp[ index ][ target ] != -1 )return dp[ index ][ target ];
        bool incl = solve( index + 1 , nums , target - nums[ index ] , dp);
        bool excl = solve( index + 1 , nums , target , dp );
        dp[ index ][ target ] = ( incl or excl);
        return dp[ index ][ target ] ;
    }

    bool solveTab( vector<int>& nums , int sum ){
        int n = nums.size();
        vector< vector< int > >dp( n+1 , vector< int >( (sum/2) + 1 , 0));
        for( int i = 0 ; i < n ; i++)dp[ i ][ 0 ] = 1;
        for( int index = n-1 ; index >=0 ; index-- ){
            for( int target = 1 ; target <= (sum/2) ; target++ ){
                int incl = 0 ;
                if( target - nums[ index ] >= 0 )
                    incl = dp[ index + 1][ target - nums[ index ]];
                bool excl = dp[ index + 1][ target ];
                dp[ index ][ target ] = ( incl or excl);
            }
        }
        return dp[ 0 ][ sum / 2];
    }

    bool solveSO( vector<int>& nums , int sum ){
        int n = nums.size();
        vector< int >curr( (sum/2 ) + 1 , 0);
        vector< int >next( (sum/2 ) + 1 , 0);
        next[0] = 1;
        for( int index = n-1 ; index >=0 ; index-- ){
            for( int target = 0 ; target <= (sum/2) ; target++ ){
                int incl = 0 ;
                if( target - nums[ index ] >= 0 )
                    incl = next[ target - nums[ index ]];
                bool excl = next[ target ];
                curr[ target ] = ( incl or excl);
            }
            next = curr;
        }
        return curr[ sum / 2];
    }

    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for( auto i : nums ){
            sum += i ;
        }
        if( sum & 1 )return false;
        int target = sum/2;
        // vector< vector< int > >dp( n , vector< int >( target + 1 , -1));
        return solveSO(  nums , sum );
    }
};

class minSwaps {
public:
    int solve( vector<int>& nums1, vector<int>& nums2 ,
                 int index , bool swapped , vector< vector< int >>&dp ){
        if( index == nums1.size())return 0;
        if( dp[ index ][ swapped ] != -1 )return dp[ index ][ swapped ];
        int prev1 = nums1[ index - 1 ];
        int prev2 = nums2[ index - 1 ];
        if( swapped )swap( prev1 , prev2);
        int ans = INT_MAX;
        if( nums1[ index ] > prev1 && nums2[ index ] > prev2 )
            ans = solve( nums1 , nums2 , index + 1 , 0 ,dp);
        if( nums1[ index ] > prev2 && nums2[ index ] > prev1 )
            ans = min( ans , 1 + solve( nums1 , nums2 , index + 1 , 1 , dp));
        return dp[ index ][ swapped ] = ans;
    }

    int solveTab( vector<int>& nums1, vector<int>& nums2 ){
        int n = nums1.size();
        vector< vector< int >>dp( n+1 , vector< int >( 2 , 0 ));
        for( int index = n-1 ; index >= 1 ; index-- ){
            for( int swapped = 0 ; swapped <= 1 ; swapped++){
                int ans = INT_MAX;
                int prev1 = nums1[ index - 1 ];
                int prev2 = nums2[ index - 1 ];
                if( swapped )swap( prev1 , prev2 );
                if( nums1[ index ] > prev1 && nums2[ index ] > prev2 )
                    ans = dp[ index + 1 ][ 0 ];
                if( nums1[ index ] > prev2 && nums2[ index ] > prev1 )
                    ans = min( ans , 1 + dp[ index + 1 ][1]);
                dp[ index ][ swapped ] = ans;
            }
        }
        return dp[ 1 ][ 0 ];
    }

    int solveSO( vector<int>& nums1, vector<int>& nums2 ){
        vector< int >curr( 2 , 0);
        vector< int >prev( 2 , 0);
        int n = nums1.size();
        for( int index = n-1 ; index >= 1 ; index-- ){
            for( int swapped = 0 ; swapped <= 1 ; swapped++){
                int ans = INT_MAX;
                int prev1 = nums1[ index - 1 ];
                int prev2 = nums2[ index - 1 ];
                if( swapped )swap( prev1 , prev2 );
                if( nums1[ index ] > prev1 && nums2[ index ] > prev2 )
                    ans = curr[ 0 ];
                if( nums1[ index ] > prev2 && nums2[ index ] > prev1 )
                    ans = min( ans , 1 + curr[1]);
                prev[ swapped ] = ans;
            }
            curr=prev;
        }
        return curr[ 0 ];
    }

    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        nums1.insert( nums1.begin() , -1);
        nums2.insert( nums2.begin() , -1);
        // int n = nums1.size();
        // vector< vector< int >>dp( n , vector< int >(2 , -1 ) );
        // bool swapped = 0;
        // return solve( nums1, nums2 , 1 , swapped  , dp );
        return solveSO( nums1 , nums2 );
    }
};

int longestArithSeqLength(vector<int>& nums) {
    int n = nums.size();
    if( n <= 2)return n ;
    int ans = 0;
    unordered_map< int , int >dp[ n + 1 ];
    for( int i = 1 ; i < n ; i++){
        for( int j = 0 ; j < i ; j++ ){
            int diff = nums[ i ] - nums[ j ];
            int count = 1 ;
            if( dp[ j ].count(diff))count =  dp[ j ][diff];
            dp[ i ][ diff ]= 1+count ;
            ans = max( ans , dp[ i ][ diff ]); 
        }
    }
    return ans;
}

int longestSubsequence(vector<int>& arr, int difference) {
    unordered_map< int , int >dp;
    int ans = 0;
    for( int i = 0 ; i < arr.size() ; i++ ){
        int temp = arr[ i ] - difference ;
        int tempAns = 0 ; 
        if( dp.count(temp))tempAns = dp[ temp ];
        dp[ arr[ i ]] =  1 + tempAns;
        ans = max( ans , dp[ arr[ i ] ]);
    }
    return ans; 
}

class Buy_and_Sell_stocks {
public:
    int solve( int index , vector< int >prices , int count , int buy ,vector<vector<vector< int >>>&dp){
        if( index >= prices.size() || count > 2 )return 0 ;
        int profit = 0 ; 
        if( dp[index][ buy ][ count ] != -1 )return dp[index][ buy ][ count ]; 
        if(buy){
            int sell = -prices[index] + solve( index+1 , prices , count+1 , 0 ,dp );
            int skip = solve( index + 1 , prices , count , 1 ,dp);
            profit = max( sell , skip );
        }
        else{
            int take = prices[ index ] + solve( index + 1 , prices , count , 1 ,dp);
            int skip = solve( index + 1 , prices ,  count , 0 , dp );
            profit = max( take , skip );
        }
        return dp[index][ buy ][ count ] = profit; 
    }

    int solveTab( vector< int >prices ){
        int n = prices.size();
        vector< vector< vector< int > > >dp( n+1 , vector<vector< int >>( 2 , vector< int >( 4, 0 )));
        for( int index = n - 1 ; index >= 0 ; index-- ){
            for( int buy = 1 ; buy >= 0 ; buy-- ){
                for( int count = 2 ; count >= 0 ; count-- ){
                    int profit = 0 ;
                    if(buy){
                        int sell = -prices[index] + dp[ index+1 ][ 0 ][ count+1];
                        int skip = dp[ index + 1 ][ 1 ][ count ];
                        profit = max( sell , skip );
                    }
                    else{
                        int take = prices[ index ] + dp[ index + 1 ][ 1 ][ count ];
                        int skip = dp[ index + 1 ][ 0 ][ count ];
                        profit = max( take , skip );
                    }
                    dp[index][buy][count] = profit;
                }
            }
        }
        return dp[0][1][0];
    }
    
    int solveSO( vector< int >prices ){
        int n = prices.size();
        vector< vector< int > >next( 2 , vector< int >( 4,0));
        vector< vector< int > >curr( 2 , vector< int >( 4,0));
        for( int index = n - 1 ; index >= 0 ; index-- ){
            for( int buy = 1 ; buy >= 0 ; buy-- ){
                for( int count = 2 ; count >= 0 ; count-- ){
                    int profit = 0 ;
                    if(buy){
                        int sell = -prices[index] + next[ 0 ][ count+1];
                        int skip = next[ 1 ][ count ];
                        profit = max( sell , skip );
                    }
                    else{
                        int take = prices[ index ] + next[ 1 ][ count ];
                        int skip = next[ 0 ][ count ];
                        profit = max( take , skip );
                    }
                    curr[buy][count] = profit;
                }
            }
            next = curr;
        }
        return curr[1][0];
    }

    int maxProfit(vector<int>& prices) {
        // int n = prices.size();
        // vector< vector< vector< int > > >dp( n , vector<vector< int >>( 2 , vector< int >( 3 , -1 )));
        // return solve( 0 , prices , 0 , 1 ,dp);
        return solveSO( prices );
    }
};

int solve( int index_1 , int index_2,string text1, string text2 , vector< vector< int > >&dp){
    if( index_1 >= text1.size() || index_2 >= text2.size())return 0 ;
    if( text1.size() == 0 || text2.size() == 0)return 0;
    if( dp[ index_1 ][ index_2 ] != -1 )return dp[ index_1 ][ index_2 ];
    int ans = 0 ;
    if( text1[ index_1 ] == text2[ index_2 ])
        ans = 1 + solve( index_1 + 1 , index_2 + 1 , text1 , text2, dp );
    else 
        ans =  max( solve(index_1 + 1, index_2, text1 , text2 ,dp ),solve(index_1,index_2 + 1, text1 , text2 ,dp ) );
        return dp[ index_1 ][ index_2 ] = ans ;
}

int solveTab( string text1, string text2 ){
    vector< vector< int > >dp( text1.length()+1 , vector< int >( text2.length()+1 , 0 ));
    for( int index_1 = text1.length() - 1 ; index_1 >  -1 ; index_1-- ){
        for( int index_2 = text2.length() - 1  ; index_2 > -1 ; index_2-- ){
            int ans = 0 ;
            if( text1[ index_1 ] == text2[ index_2 ])
                ans = 1 + dp[ index_1 + 1 ][ index_2 + 1];
            else 
                ans =  max( dp[ index_1 + 1][ index_2 ] , dp[ index_1 ][ index_2 + 1 ]);
            dp[ index_1 ][ index_2 ] = ans ;
        }
    }
    return dp[ 0 ][ 0 ];
}

int solveSO( string text1, string text2 ){
    vector< int >curr( text2.size() + 1  , 0 );
    vector< int >next( text2.size() + 1  , 0 );
    for( int index_1 = text1.length() - 1 ; index_1 >  -1 ; index_1-- ){
        for( int index_2 = text2.length() - 1  ; index_2 > -1 ; index_2-- ){
            int ans = 0 ;
            if( text1[ index_1 ] == text2[ index_2 ])
                ans = 1 + next[ index_2 + 1];
            else 
                ans =  max( next[ index_2 ] , curr[ index_2 + 1 ]);
            curr[ index_2 ] = ans ;
        }
        next = curr;
    }
    return curr[ 0 ];
}

int longestCommonSubsequence(string text1, string text2) {
    // vector< vector< int > >dp( text1.size() , vector< int >( text2.size() , -1 ));
    // return solve( 0 , 0 , text1 , text2 , dp );
    return solveSO( text1 , text2 );
}

int solve( string text1 , string text2){
    vector< int >curr( text2.size() + 1  , 0 );
    vector< int >next( text2.size() + 1  , 0 );
    for( int index_1 = text1.length() - 1 ; index_1 >  -1 ; index_1-- ){
        for( int index_2 = text2.length() - 1  ; index_2 > -1 ; index_2-- ){
            int ans = 0 ;
            if( text1[ index_1 ] == text2[ index_2 ])
                ans = 1 + next[ index_2 + 1];
            else 
                ans =  max( next[ index_2 ] , curr[ index_2 + 1 ]);
            curr[ index_2 ] = ans ;
        }
        next = curr;
    }
    return curr[ 0 ];
}

int longestPalindromeSubseq(string s) {
    string rev = s;
    /*we have reverse the string "s" in order to get the palindromic subsequence
    since we know the palindrome is also same on seeing from reverse order.*/
    reverse( rev.begin() , rev.end());
    return solve( s , rev );
}

int main(){
    
    return 0;
}