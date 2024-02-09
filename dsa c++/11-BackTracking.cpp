#include<bits/stdc++.h>

using namespace std;

bool isSafe( int n, int x, int y, vector<vector<bool>> visited ,vector<vector<int>> &arr){
    if(( x >= 0 && x < n ) && ( y >= 0 && y < n ) && arr[ x ][ y ] == 1 && visited[ x ][ y ] == 0 )return true;
    return false;
}

void solve( int newx , int newy ,string path, vector<string>&ans , vector<vector<bool>>&visited ,
                vector < vector < int >> & arr , int n ){
    if( newx == n - 1 && newy == n - 1 ){
        ans.push_back(path);
        return ;
    }
    visited[ newx ][ newy ] = 1;
    if( isSafe( n , newx + 1 , newy , visited , arr ) ){
        solve( newx+1 , newy , path + 'D' , ans , visited , arr , n );
    }
    if( isSafe( n , newx  , newy - 1 , visited , arr ) ){
        solve( newx , newy - 1  , path + 'L' , ans , visited , arr , n );
    }
    if( isSafe( n , newx , newy + 1 , visited , arr ) ){
        solve( newx , newy+1 , path + 'R' , ans , visited , arr , n );
    }
    if( isSafe( n , newx - 1 , newy , visited , arr ) ){
        solve( newx - 1 , newy , path + 'U' , ans , visited , arr , n );
    }
    visited[ newx ][ newy ] = 0;
}

vector < string > searchMaze( vector < vector < int >> & arr, int n ) {
    vector<vector<bool>>visited ( n , vector<bool>( n , 0 ));
    string path ="";
    int x = 0 ; int y = 0;
    vector< string > ans ;
    if( arr[ x ][ y ] == 0 )return ans;
    solve( x , y , path , ans , visited , arr , n);
    return ans;
}

class N_Queen_problem {
public:
   bool isSafe( int row , int col , vector< string >board , int n ){
        int r = row;
        int c = col;
        while( r >= 0 && c >= 0 ){
            if( board[ r ][ c ] == 'Q' )return false;
            r-- , c-- ;
        }
        r = row ;
        c = col ;
        while( c >= 0 ){
            if( board[ r ][ c ] == 'Q')return false;
            c --;
        }
        r=row;
        c=col;
        while( r < n && c >= 0 ){
            if(board[ r ][ c ] == 'Q' )return false;
            r++;
            c--;
        } 
        return true;
    }

    void solve( int col , vector< string > &board , vector< vector < string > > &ans,int n ){
        if( col == n ){
            ans.push_back( board );
            return;
        }
        for(int row = 0 ; row < n ; row ++ ){
            if( isSafe( row , col , board , n )){
                board[ row ][ col ] = 'Q' ;
                solve( col + 1 ,board , ans , n );
                board[ row ][ col ] = '.' ;
            }
        }
    }
    
    vector< vector< string > > solveNQueens( int n ) {
        vector< vector< string > > ans;
        vector< string > board( n );
        string s( n , '.' ) ;
        for(int i = 0 ; i < n ; i++ ){
            board[ i ] = s ;
        }

        solve( 0 , board , ans , n );
        return ans;
    }
};

class Soduko_solver {
public:
    bool possible ( int row , int col , char ch , vector<vector<char>>& board ){
        int n = board.size();
        for( int i = 0 ; i < n ; i++ ){
            if( board [ i ] [ col ] ==  ch )return false;
            if( board [ row ] [ i ] ==  ch )return false;
            if( board [ 3 * (row/3) + (i / 3) ] [ 3 * (col /3 ) + (i % 3) ] == ch )return false;
        }
        return true;
    }

    bool solve( vector<vector<char>>& board ){
        int n = board.size();
        for( int i = 0 ; i < n ; i++ ){
            for( int j = 0 ; j < n ; j++ ){
                if( board [ i ] [ j ] == '.' ){
                    for( char ch = '1' ; ch <= '9' ; ch ++ ){
                      if( possible ( i , j , ch , board )){
                          board[ i ] [ j ] = ch ;
                          bool safe = solve ( board );
                          if(safe)return true ;
                          else board[ i ] [ j ] = '.';
                      }   
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};

int main(){
    
    return 0;
}

