/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS11

Análise:
        .

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
    int linhas, colunas, peoes;
    
    //ler quantidade de linhas, colunas e peoes
    cin >> linhas >> colunas >> peoes;

    //repetir até EOF
    while(linhas ||  colunas || peoes){
        char buffer;

        for(int i=0; i<linhas; i++){
            for(int j=0; j<colunas; j++){
                cin >> buffer;
                cout << buffer;
            }
            cout << endl;
        }
        cout << endl;

        //ler próxima quantidade de linhas, colunas e peoes
        cin >> linhas >> colunas >> peoes;
    }

    //return
    return 0;   
}  
