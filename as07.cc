/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS07

Análise:
        O algoritmo calcula todas as distâncias entre todos os pontos e depois mostra a menor.
        O cálculo é feito a partir de dois "for", em dentro do outro, sendo que cada um repete n, vezes,
        sendo n o número de pontos.
        Assim, a ordem de complexidade do algoritmo é O(n^2). 
        
*/

//Dependencias
#include <iostream>
#include <iomanip>
#include <math.h>

//Macros
#define INFINITO 10000.0

//Namespace
using namespace std;

/*
Main
*/
int main(){
    //Declaracoes
    int nEntradas;

    //ler número de casos
    cin >> nEntradas;

    //ler até entradas == 0
    while(nEntradas){
        //Declarações
        double menorDistancia;
        double eixoX[nEntradas];
        double eixoY[nEntradas];

        //ler todos os pontos
        for(int i=0; i<nEntradas; i++){
            cin >> eixoX[i];
            cin >> eixoY[i];
        }

        //inicializar menorDistancia
        menorDistancia = INFINITO;

        //verificar todos dois pares
        for(int i=0; i<nEntradas; i++){
            for(int j=0; j<nEntradas; j++){
                if(i!=j){
                    //buffer local
                    double buffer;

                    //cálculo distancia (eixoX[i], eixoY[i]) - (eixoX[j], eixoY[j])
                    buffer =  sqrt( pow((eixoX[i]-eixoX[j]), 2) + pow((eixoY[i]-eixoY[j]), 2) );

                    //armazenar menor número
                    if(menorDistancia > buffer){
                        menorDistancia = buffer;
                    }
                }
            }
        }


        if(menorDistancia < INFINITO){
            cout << fixed << setprecision(4) << menorDistancia << endl;
        }
        else{
            cout << "INFINITY" << endl;
        }
        //ler próxima etapa
        cin >> nEntradas;
    }

    //return
    return 0;   
}  
