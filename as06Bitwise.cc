/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS06

Análise:
        
        
*/

//Dependencias
#include <iostream>
#include <iomanip>
#include <math.h>

//Namespace
using namespace std;

//Macros
#define INFINITO 1000000 // peso máximo da aresta válida é 30000
#define MAX 2147483647 // valor máximo

//Variariáveis Globais
int todosVerticesVisitados;
int nVertices;
int controleEntradas[16][6][1<<16]; //[numero de vertices][numero de teleportes][numero de arestas]-> 2^16  máximos das entradas 


int caixeiroViajanteDP(int** matriz, int v, int teleportes, int caminho){

    //base da recursividade
    if(todosVerticesVisitados == caminho){
        return 0;
    }

    int &valor = controleEntradas[v][teleportes][caminho]; 

    
    if(valor != -1) //vertice já visitado
        return valor;

    valor = INFINITO;

    for(int i = 0; i < nVertices; i++){
        int novoCaminho = (caminho | 1 << i); //bitwise or

        if(caminho & 1 << i) //bitwise and
            continue;

        if(matriz[v][i] == INFINITO){
            if(teleportes)
                valor = min(valor, caixeiroViajanteDP(matriz, i, teleportes-1, novoCaminho));
        }
        else{
            int pontoA = valor;
            if(teleportes)
                pontoA = caixeiroViajanteDP(matriz, i, teleportes-1, novoCaminho);

            int pontoB = caixeiroViajanteDP(matriz, i, teleportes, novoCaminho)+matriz[v][i];

            valor = min(valor, min(pontoA, pontoB));
        }
    }

    return valor;
}

/*
Main
*/
int main(){
    //Declaracoes
    int nCasos, menorTempo;

    //ler número de casos
    cin >> nCasos;
    //passar por todos os casos
    for(int i=0; i<nCasos; i++){
        //Declaracoes
        int n, m, k;

        //ler quantidade de lugares(n), quantidade de rotas(m) e máximo teletransporte(k)
        cin >> n;
        cin >> m;
        cin >> k;

        //Matriz de Incidência representativa do grafo 
        //Inicializada para INFINITO
        int** matriz = new int*[n];
        for(int j=0; j<n; j++){
            matriz[j] = new int[n];
            for(int k = 0; k<n; k++){
                matriz[j][k] = INFINITO;
            }
        }
        
        //ler arestas e valores
        for(int j=0; j<m; j++){
            //Declaracoes
            int v1, v2, valor;
            cin >> v1;
            cin >> v2;
            cin >> valor;

            //Normalização vértices
            v1--; 
            v2--;
            
            //Inserir sempre os menores valores das entradas na matriz(Grafo não direcionado)
            if(matriz[v1][v2] > valor){
                matriz[v1][v2] = valor;
                matriz[v2][v1] = valor;
            }
        }

        //Inicialização variáveis globais
        for(int a = 0; a < 16; a++){
            for(int b = 0; b < 6; b++){
                for(int c = 0; c < 1<<16; c++){
                    controleEntradas[a][b][c] = -1;
                }
            }
        }
        
        
        nVertices = n;
        todosVerticesVisitados = (1<<n) - 1; //máscara todos os bits 1
        
        //verificar o menor caminho entre quaisquer par de vértices
        // a é o vértice referencia. Primeiro loop passa por todos so vértices,
        //verifica-se se a distancia direta entre dois vértices b e c é maior que b-a a-c
        // se b-a a-c for menor, atualizar para esse valor a distancia entre b-c
        for(int a=0; a<nVertices; a++){
            for(int b=0; b<nVertices; b++){
                for(int c=0; c<nVertices; c++){
                    if(matriz[b][c] > (matriz[b][a] + matriz[a][c])){
                        matriz[b][c] = matriz[b][a] + matriz[a][c];
                    }
                }
            }
        }
    

        menorTempo = caixeiroViajanteDP(matriz, 0, k, 1);

        if(menorTempo != INFINITO){
            cout << menorTempo << endl;
        }
        else{
            cout << -1 << endl;
        }
    }
    return 0;
}