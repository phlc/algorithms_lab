/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Pedro Henrique Lima Carvalho

AS01
*/

//Dependencies
#include <iostream>

using namespace std;
int main(){
    long long int a, b;
    long long int factorial[21];
    factorial[0] = factorial[1] = 1;
    for (long long int i=2; i<21; i++){
        factorial[i]=i*factorial[i-1];
    }
    
    while(cin >>a){
        cin >> b;
        cout << (factorial[a]+factorial[b]) << endl;
    }

    return 1;   
}  