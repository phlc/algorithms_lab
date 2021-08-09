/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS02

Análise:
    Desconsiderando o número de entradas, o código realizará uma operação de subtração (Valor ASCII -48) 
    e uma de soma (acúmulo do número de leds de cada algarimso) para cada algarismo da entrada. 
    Esse problema tem crescimento linear. Considerando n o número de algarimos da entrada, complexidade O(n).
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
    int total, saida;
    string entrada;
    int mapa[10]; //vetor de mapeamento entre numero e quantidade de leds
    
    //Inicializar vetor de mapeamento
    mapa[0] = 6; mapa[1] = 2;
    mapa[2] = 5; mapa[3] = 5;
    mapa[4] = 4; mapa[5] = 5;
    mapa[6] = 6; mapa[7] = 3;
    mapa[8] = 7; mapa[9] = 6;

     
    //Ler total de entradas
    cin >> total;

    //Repetir quantidade de entradas
    for(int i=0; i<total; i++){
        //inicializacao
        cin >> entrada;
        saida = 0;

        //Repetir quantidade de algarismos no numero
        for(int j=0; entrada[j]!='\0'; j++){
            
            //utilizando o vetor de mapeamento, soma ao valor de saida o numero de leds necessario
            //para aquele algarismo. Calculo a partir do valor ASCII do caractere - 48.
            saida += mapa[entrada[j]-48];
        }

        //Mostrar saida 
        cout << saida << " leds" << endl;
    }
    return 0;   
}  
