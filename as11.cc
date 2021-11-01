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

//Matriz Global
//tabuleiro[Linhas][Colunas]
char** tabuleiro;

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
        //alocar espaço para o tabuleiro
        tabuleiro = new char*[linhas];
        for(int i=0; i<linhas; i++){
            tabuleiro[i] =  new char[colunas];
            for(int j=0; j<colunas; j++){
                char buffer;
                cin >> buffer;
                tabuleiro[i][j] = buffer;
            }
        }

        for(int i=0; i<linhas; i++){
            for(int j=0; j<colunas; j++){
                cout << tabuleiro[i][j];
            }
            cout << endl;
        }
        cout << endl;

        //delete
        for(int i=0; i<linhas; i++){
            delete[] tabuleiro[i];
        }
        delete[] tabuleiro;

        //ler próxima quantidade de linhas, colunas e peoes
        cin >> linhas >> colunas >> peoes;
    }

    //return
    return 0;   
}  
