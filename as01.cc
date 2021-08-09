/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS01

Analise:

    Como os valores das entradas sao limitadas de 0 a 20, e' mais eficiente calcular todos
    os fatoriais de uma vez, em um arranjo, aproveitando o resultado do fatorial ja calculado 
    de n-1 para calcular o fatorial de n.

    Assim, sao feitas apenas 19 multiplicacoes. Ou seja, obtem-se um mapeamento direto entre
    um numero e seu fatorial praticamente pelo custo de um unico calculo do fatorial da maior
    entrada possivel. 
    
    O calculo dos fatoriais tem custo fixo, independente do numero de entradas
    Apenas o numero de adicoes estaria dependente do numero de entradas.
    Assim, sendo n o numero de entradas, o algoritmo seria da ordem O(n).

*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;

/*
Main
*/
int main(){
    //Declaracoes
    long long int a, b;
    long long int factorial[21];

    //Calculo de todos fatoriais 0-20 um unica vez
    factorial[0] = factorial[1] = 1;
    for (long long int i=2; i<21; i++){
        factorial[i]=i*factorial[i-1];
    }
    
    //leitura das entradas, soma dos fatoriais, resposta
    while(cin >>a){
        cin >> b;
        cout << (factorial[a]+factorial[b]) << endl;
    }

    return 1;   
}  
