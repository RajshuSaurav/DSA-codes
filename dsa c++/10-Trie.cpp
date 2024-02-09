#include<bits/stdc++.h>

using namespace std;

class TrieNode{
    public:
        char data ;
        TrieNode* children[ 26 ] ;
        bool isTerminal;
    
    TrieNode( char ch ) {
        data = ch;
        for( int i = 0 ; i < 26 ; i++ ){
            children[ i ] = NULL ;
        }
        isTerminal = false ;
    }
};

class Trie {
    public:
        TrieNode* root ;
    Trie(){
        root = new TrieNode('\0');
    }

    void insertUtil( TrieNode* root , string Word ){
        if( Word.length() == 0 ) {
            root -> isTerminal = true;
            return;
        }
        int index = Word[ 0 ] - 'A';
        TrieNode* child;
        if( root -> children[ index ] != NULL ){
            child = root -> children[index];
        }
        else{
            child = new TrieNode( Word[0] );
            root -> children[ index ] = child;
        }
        insertUtil( child , Word.substr(1));
    }   

    void insertWord( string word ){
        insertUtil( root , word );
    }

    bool searchUtil( TrieNode* root , string Word ){
        if( Word.length() == 0 ) return root -> isTerminal;
        TrieNode* child;
        int index = Word[ 0 ] - 'A';
        if( root -> children [ index ] != NULL )child = root -> children[ index ] ;
        else return false;
        return searchUtil( child , Word.substr(1));
    }

    bool searchWord( string word ){
        return searchUtil( root , word );
    }

    bool prefixUtil( TrieNode* root , string Word ){
        if( Word.length() == 0 ){
            return true;
        }
        int index = Word[ 0 ] - 'a';
        TrieNode* child;
        if( root -> children [ index ] )child = root -> children[ index ];
        else return false;
        return prefixUtil( child , Word.substr(1) );
    }

    bool startsWith(string prefix) {
        return prefixUtil( root , prefix );
    }
        void printSuggestions( TrieNode* current , vector<string> & temp , string prefix ){
        if( current -> isTerminal ) {
            temp.push_back( prefix ) ;
        }
        for( char ch = 'a' ; ch <= 'z'; ch++ ){
            TrieNode* next = current -> children [ ch - 'a' ];
            if( next ){
                prefix.push_back(ch);
                printSuggestions(next, temp ,  prefix);
                prefix.pop_back();
            }
        }
    }

    vector<vector<string>> getsuggestions( string str ){
        TrieNode* previous = root;
        vector<vector<string>> output;
        string prefix = "" ;
        for( int i = 0 ; i < str.length() ; i++ ){
            char lastch = str[ i ];
            prefix.push_back( lastch ) ;
            TrieNode* current = (previous -> children[ lastch - 'a']);
            if( current == NULL) break;
            vector<string>temp;
            printSuggestions( current , temp , prefix );
            output.push_back(temp);
            temp.clear();
            previous = current;
        }
        return output;
        
    }
};

vector<vector<string>> phoneDirectory(vector<string>&contactList, string &queryStr){
   Trie* t = new Trie();
   for( int i = 0 ; i < contactList.size() ; i++ ){
       t -> insertWord( contactList[ i ] );
   }
   return  t -> getsuggestions(queryStr);
}

int main(){
    Trie* t = new Trie();
    t -> insertWord("ABCD");
    cout << t ->searchWord("ABCD");
    return 0;
}