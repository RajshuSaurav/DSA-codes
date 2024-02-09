#include<iostream>
using namespace std;

/*for below function the exp expansion is = 1+(x/1)+(x^2/2!)+(x^3/3!).....n for e^x */

double exp(int x,int n){
    static double p=1,f=1;
    if (n==1)return 1;
    double s=exp(x,n-1);
    p*=x; f*=(n-1);
    return (s+p/f);
}

double expHornerMethod(int x,int y){
    static double s=1;
    if (y==0)return s;
    s=(1+(x/y))*s;
    return expHornerMethod(x,y-1);
}

/* horner method basically reduce the number of multiplication in the operation
so that the time to excute the operation decrease */

double pow(int x,int y){
    int res = 1;
    while(y){
        if(y&1)res*=x;
        x*=x; y>>=1; }
    return res;
}

int fibonacci(int term){
    if (term==1 || term==0)return term;
    return fibonacci(term-1)+fibonacci(term-2);  
}

double combination(int n,int r ){
    if(r==0)return 1;
    return combination(n-1,r-1)+combination(n-1,r);
}

void towerOfHanoi(int number,char A,char B,char C){
    if (number > 0){
        towerOfHanoi(number-1,A,C,B);
        cout<<"moving disk from"<< A <<"to"<< C <<"using"<< B <<endl;
        towerOfHanoi(number-1,B,A,C);
    }
}

int  main(){
    cout<<"the exponential of 2 to  term is : "<<exp(2,3);
    cout<<"applying horner method exp of 2 to 1 :"<<expHornerMethod(2,1)<<endl;
    cout<<"the power of 2 to the 4 is : " <<pow(2,4)<<endl;
    cout<<"third term of fibonacci is "<<fibonacci(3)<<endl;
    cout<<"the value of 2C1 is : "<<combination(2,1);   
}