/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS06

Análise:
        Algoritmo aprendido e compreendido a partir dos seguintes links:
        https://www.youtube.com/watch?v=cY4HiiFHO1o
        https://youtu.be/udEe7Cv3DqU       
        https://ideone.com/Kaewyv 
        https://www.baeldung.com/cs/tsp-dynamic-programming
        Segundo o vídeo, a do caixeiro viajante é O(n^2*2^n), sendo n o número de vértices. 
        Faz sentido, vez que o número de estados possíveis é n * 2^n e cada estado custa O(n).
        Contando o número de teletransportes, k, vez que gera sempre estados usando e não usando
        os teletransportes, o algoritmo seria O(n^2 * k * 2^n).
        Obs: fiz duas usando uma abordagem gulosa não ótima e uma adaptação de Djisktra para caminhos. 
        A primeira deu 59% e a segunda timeout antes mesmo de debugar.
*/

//Dependencias
#include <iostream>
#include <iomanip>

//Namespace
using namespace std;

//Macros
#define INFINITO 1000000 // peso máximo da aresta válida é 30000
#define MAX 2147483647 // valor máximo

//Variariáveis Globais
int fim; // int que funcionará como máscara para identificar quando todos vértices forem visitados
int nVertices; // número de vértices do grafo

//Arranho 3D de controle do tempo de estados
//[16] -> número do vértice atual
//[6] -> número de teletransportes
//[1<<16] -> representação binária dos vértices visitados. A posição do bit indica se ele foi visitado ou não
// Ex: [3][1][1 000000000001101]:
// Estado onde o vértice atual é o 3. Ainda tem teletransporte. Vértices 0, 2, 3 foram visitados (1<<0)(1<<2)(1<<3)
// O tempo dessse estado fica armazenado nessa posição do arranjo 3D.
int estados[16][6][1<<16]; 

/*
percorrerEstados - utiliza o arranho estados para manter o histórico de dos os estados
parte do estado com 1 vértice, até quando todos estão visitados. Utilizando o estado anterior para montar o próximo
@param int** matriz, int v, int k, int caminho:
             ponteiro para o grafo, vértice atual, número teletransportes, representação binária vértices visitados
*/
int percorrerEstados(int** matriz, int v, int k, int visitados){

    //Todos os vértices já foram visitados
    if(fim == visitados){
        return 0;
    }

    //alias para o int tempo do atual vértice no atual estado
    int &tempo = estados[v][k][visitados]; 

    //tempo do estado já calculado
    if(tempo != -1){
        return tempo;
    }

    //se não calculado, estabelecer infinito
    tempo = INFINITO;

    //passar por todos os vértices
    for(int i = 0; i < nVertices; i++){
        //representação binária dos vértices já visitados, marcando o próximo vértice (i) como visitado
        int atualizado = (visitados | 1 << i); //bitwise OR -> mantém visitados e marca i como 1.

        //Se vértice i já estava em visitados, pular esse loop
        if(visitados & 1 << i) //bitwise AND -> resultado 1 se i já era 1 em visitados ou 0 se não
            continue;

        //Se o tempo do vértice atual para o próximo (i) == INFINITO. só pode se tive teletransporte
        if(matriz[v][i] == INFINITO){
            //Se tiver teletransporte
            if(k!=0){
                //Chamada para próximo estado com i sendo o vértice atual e teletransportes-1
                //tempo do v-i = 0, uso de teletransporte -> apenas o tempo acumulado dos próximos estados
                tempo = min(tempo, percorrerEstados(matriz, i, k-1, atualizado));
            }
        }
        //Se tempo não é infinito
        else{
            //retorno da opção 1 de próximo estado
            int tempoCaminho1 = tempo; //será infinito se não houver teletransporte
            
            //havendo teletransporte
            if(k!=0){
                //chamada para o próximo estado usando teletransporte - tempo v-i = 0
                tempoCaminho1 = percorrerEstados(matriz, i, k-1, atualizado);
            }
            //chamada para o próximo estado sem usar teletransporte
            int tempoCaminho2 = percorrerEstados(matriz, i, k, atualizado)+matriz[v][i]; //tempo retornado + tempo de v-i

            //seleciona o menor tempo entre as opções com e sem teletransporte
            if(tempoCaminho1 > tempoCaminho2){
                tempoCaminho1 = tempoCaminho2;
            }
            //seleciona o menor tempo entre todos os estados criados pelo for
            if(tempo > tempoCaminho1){
                tempo = tempoCaminho1;
            }
        }
    }

    return tempo;
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
                    estados[a][b][c] = -1;
                }
            }
        }
        
        
        nVertices = n; //número de vértices
        fim = (1<<n) - 1; //máscara todos os bits 1
        
        // verificar o menor caminho entre quaisquer par de vértices
        // a é o vértice referencia. Primeiro loop passa por todos so vértices,
        // verifica-se se a distancia direta entre dois vértices b e c é maior que b-a a-c
        // se b-a a-c for menor, atualizar para esse valor a distancia entre b-c
        // Assim a aresta b-c sempre terá o menor caminho, mesmo que no grafo original passasse por mais arestas.
        for(int a=0; a<nVertices; a++){
            for(int b=0; b<nVertices; b++){
                for(int c=0; c<nVertices; c++){
                    if(matriz[b][c] > (matriz[b][a] + matriz[a][c])){
                        matriz[b][c] = matriz[b][a] + matriz[a][c];
                    }
                }
            }
        }
    
        //iniciar percuso dos estados a partir do vértice 0, com k teletransportes e vértice 0 como visitado.
        menorTempo = percorrerEstados(matriz, 0, k, 1);

        //mostrar tempo
        if(menorTempo != INFINITO){
            cout << menorTempo << endl;
        }
        //Tempo == INFINITO -> não foi possível percorre
        else{
            cout << -1 << endl;
        }
    }
    return 0;
}