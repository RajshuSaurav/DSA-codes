#include<iostream>
using namespace std;

void display(int a[],int &length){
    for (int  i = 0; i < length ; i++){
        cout<<a[i]<<" ";
    }
}

void insert(int a[],int &length,int position,int element ){
    for(int i = length ; i >=  position ; i--)a[i]=a[i-1];
    a[position-1] = element ;
    length++;
}

void deletion(int a[],int &length,int position){
    for(int i = position-1; i < length-1; i++){
        a[i]=a[i+1];
    }
    length--;
}

void linearSearch(int a[],int length,int target){
    for(int i = 0;i < length; i++){
        if(a[i] == target){
            cout<<"found at position "<<i+1<<endl;
            return;
        }
    }
    cout<<"no such element found in the given array "<<endl ; 
}

void binarySearch(int a[] , int length , int target ){
    int i=0 ;int j = length-1;
    int mid = i + ((j-i)/2);
    while (i<j){
        if( target == a[mid] ){
            cout<<"element is found at position "<< mid+1<<endl;
            return; }
        if( a[mid] > target )j=mid-1;
        else i=mid+1;
    }
    cout<<"element is not found "<<endl;
}

void reverse( int a[], int length ){
    int i=0 ; int j= length-1;
    while (i<=j){
        int temp=a[i];
        a[i]=a[j];
        a[j]=temp;
        i++;j--;
    }
}

int main(){
    int a[10]={1,3,4,5,6};
    int length = 5;
    reverse(a,length);
    display(a,length);
    return 0;
}