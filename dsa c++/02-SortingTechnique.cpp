#include<bits/stdc++.h>

using namespace std;

void display(int a[],int length){
    for (int  i = 0; i < length ; i++){
        cout<<a[i]<<" ";
    }
}

void BubbleSort(int a[],int length){
    for (int i = 0; i < length ; i++){
        int flag=0;
        for (int j = 0; j < length ; j++)
        {
            if(a[j] > a[j+1]){
                swap(a[j],a[j+1]);
                flag = 1 ;
            }
        }
        if (flag == 0)return;
    }
}

void insertionSort ( int arr[] , int n ) {
    int a;
    int j;
    for ( int i = 1 ; i < n ; i++ ) {
        j = i - 1 ;
        a = arr [ i ] ;
        while ( j > - 1 && arr [ j ] > a ) {
            arr [ j + 1 ] = arr [ j ];
            j--;
        }
        arr [ j + 1] = a;
    }
}

void SelectionSort(int arr[],int length){
    int j,k;
    for (int  i = 0; i < length ; i++){
        for ( k = j = i; j < length ; j++){
            if ( arr[j] < arr[k]){
                k=j;
            }
        }
     swap(arr[i],arr[k]);
    }
}

int pivotIndex(int arr[],int start,int end){
    int pivotElement= arr[ start ];
    int count = 0;
    for( int i = start + 1 ; i <= end ; i++ ){
        if (arr [ i ] <= pivotElement)count++;
    }
    int PivotIndex = start + count;
    swap(arr[ start ],arr[ PivotIndex ] );
    int i = start ;
    int j = end ;
    while( i < PivotIndex && j > PivotIndex ){
        while( arr[ i ] <= pivotElement ) i++;
        while( arr[ j ] > pivotElement ) j--;
        if( i  < PivotIndex && PivotIndex <  j  ){
            swap( arr[ i ] , arr[ j ] );
        }
    }
    return PivotIndex;
}

void quickSort( int arr[] , int start , int end ){
    if( end <= start ) return ;
    int p = pivotIndex( arr , start , end );
    quickSort( arr , start , p-1 );
    quickSort( arr , p+1 , end );
}

void merge( int arr[] , int start , int end ){
    int mid = start + (( end - start)/2);
    int len1 = mid - start + 1 ;
    int len2 = end - mid ;
    int* arr1 = new int[ len1 ] ;
    int* arr2 = new int[ len2 ] ;
    int temp = start ;
    for( int i = 0 ; i < len1 ; i++ ) arr1[ i ] = arr[ temp++ ]; 
    temp = mid + 1 ;
    for( int i = 0 ; i < len2 ; i++ ) arr2[ i ] = arr[ temp++ ];
    int i = 0;
    int j = 0;
    temp = start;
    while ( i < len1 && j < len2 ){
        if( arr1[ i ] < arr2[ j ] ) arr[ temp++ ] = arr1[i++];
        else arr[ temp++ ] = arr2[ j++ ];
    }
    while ( i < len1 ) arr[ temp++ ] = arr1[i++];
    while ( j < len2 ) arr[ temp++ ] = arr2[j++];
    delete []arr1;
    delete []arr2;
}

void mergeSort( int arr[] , int start , int end ){
    if( start >= end) return;
    int mid = start + ( (end - start)/2 );
    mergeSort( arr , start , mid );
    mergeSort( arr , mid + 1 , end );
    merge( arr , start , end );
}

int main(){
    int arr[ ] = {5,8,1,6,5};
    display(arr , 5);
    cout << endl;
    mergeSort(arr, 0,4);
    cout << " after sort "<<endl; 
    display(arr,5);
}