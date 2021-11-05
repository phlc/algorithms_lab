/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS11

Análise:
        O algoritmo cria um grafo representativo de todas as posições do tabuleiro. Assim, em um tabuleiro com "n" posições
        n = linhas x colunas. A criação do grafo custa O(n).
        Em mapaVertice ficam armazenadas as posicoes de cada peça(pela especificação do problema <=16).
        Para encontrar a menorDistancia() entre todas as peças, sao realizadas <=16 buscas em larguras no grafo de tamanho n, 
        para encontrar o menor caminho de cada peça em relação às demais. Nesse caso temos <=16 buscas a um custo O(n),
        ou seja, O(n).
        Após, percorrerEstados() executa o algoritmo de programação dinâmica do caixeiro viajante para encontrar a menor
        rota que passa por todas as peças e retorna para o cavalo. A complexidade do caixeiro viajante é O(n^2*2^n), mas por
        restrições do enunciado, nesse caso n, o número de peças, está limitado a <=16.

*/

//Dependencias
#include <iostream>
#include <iomanip>

//Namespace
using namespace std;

//Macros
#define INFINITO 1000000 // peso suficientemente grande

//Variariáveis Globais
int fim; // int que funcionará como máscara para identificar quando todos vértices forem visitados
int nVertices; // número de vértices do grafo

//Arranho 2D de controle de estados
//[16] -> número do vértice atual: número máximo de peões + posição inicial do cavalo
//[1<<16] -> representação binária dos vértices visitados. A posição do bit indica se ele foi visitado ou não
int estados[16][1<<16]; 

//vertice do cavalo [1]  e dos peoes[10-1000000000000000]
int mapaVertices[1<<16];


/*menorDistancia - Armazenda no grafo a menor distancia entre as peças por busca em largura
@param int** matriz; int tamanho -> grafo do tabuleiro, tamanho da matriz
*/
void menorDistancia(int** matriz, int tamanho){
    //comecar em todos os vértices
    for(int i=0; i<nVertices; i++){

        //declarcoes locais
        int v = mapaVertices[1<<i];
        int pecasVisitadas = 1;
        int atual = v;
        int inicioFila = 0;
        int fimFila = 0;
        int pais[tamanho];
        int fila[tamanho];
        int visitados[tamanho];

        //inicializacao
        for(int j=0; j<tamanho; j++){
            pais[j] = j;
            fila[j] = -1;
            visitados[j] = -1;
        }

        //marcar v como visitado
        visitados[v] = 0;

        //fazer busca em largura por todas as pecas
        fila[fimFila++] = atual;
        while(pecasVisitadas != nVertices && inicioFila!=fimFila){
            //retirar vertice da fila
            atual = fila[inicioFila++];

            //verificar vértices adjacentes
            for(int j=0; j<tamanho; j++){
                if(atual!=j && matriz[atual][j] == 1 && visitados[j]==-1){
                    pais[j] = atual;
                    visitados[j]=1; //atualizar com a distancia
                    fila[fimFila++] = j;
                    //Se posicao tiver uma peça
                    if(matriz[j][j]==2){
                        pecasVisitadas++;
                    }
                }
            }   
        }
        //verificar distancia de cada peca ate v
        for(int j=0; j<nVertices; j++){
            //declaracoes locais
            int filho = mapaVertices[1<<j];
            atual = filho;
            int distancia = 0;

            //subir nos pais até v
            while(atual != v){
                distancia += 1;
                atual = pais[atual];
            }
            matriz[v][filho] = matriz[filho][v] = distancia;
        }

    }
    
}

/*
percorrerEstados - utiliza o arranjo de estados para manter o histórico dos os estados
parte do estado com 1 vértice, até quando todos estão visitados. Utilizando o estado anterior para montar o próximo
@param int** matriz, int v, int visitados: ponteiro para o grafo, vértice atual, vértices visitados
*/
int percorrerEstados(int** matriz, int v, int visitados){

    //Todos os vértices já foram visitados
    if(fim == visitados){
        return matriz[mapaVertices[1<<v]][mapaVertices[1]];
    }

    //alias para o int número de movimentos até atual vértice no atual estado
    int &movimentos = estados[v][visitados]; 

    //número de movimentos do estado já calculado
    if(movimentos != -1){
        return movimentos;
    }

    //se não calculado, estabelecer infinito
    movimentos = INFINITO;

    //passar por todos os vértices
    for(int i = 0; i < nVertices; i++){
        //representação binária dos vértices já visitados, marcando o próximo vértice (i) como visitado
        int atualizado = (visitados | 1 << i); //bitwise OR -> mantém visitados e marca i como 1.

        //Se vértice i já estava em visitados, pular esse loop
        if(visitados & 1 << i) //bitwise AND -> resultado 1 se i já era 1 em visitados ou 0 se não
            continue;

        else{
            //chamada para o próximo estado 
            //n_movimentos retornado + movimentos de v-i
            int movimentosCaminho = percorrerEstados(matriz, i, atualizado)+matriz[mapaVertices[1<<v]][mapaVertices[1<<i]]; 

            //seleciona o menor núemro de movimentos entre todos os estados criados pelo for
            if(movimentos > movimentosCaminho){
                movimentos = movimentosCaminho;
            }
        }
    }

    return movimentos;
}

/*
Main
*/
int main(){
    //Declaracoes
    int linhas, colunas, peoes;

    //ler número de linhas, colunas e peoes
    cin >> linhas >> colunas >> peoes;

    //repetir até 0s
    while(linhas || colunas || peoes){
        //Grafo do tabuleiro, sendo cada posição do tabuleiro um vértice
        //Inicializada para INFINITO - A princípio de uma posição não chega a outra
        //número do vértice = (número da linha)*(número de colunas) + (número da coluna)
        int tamanho = linhas*colunas;
        int** matriz = new int*[tamanho];

        for(int i=0; i<tamanho; i++){
            matriz[i] = new int[tamanho];
            for(int j=0; j<tamanho; j++){
                matriz[i][j] = INFINITO;
            }
        }

        //indice do mapaVertices
        int indice = 1<<1;

        //preencher vértices com leitura das entradas
        for(int i=0; i<linhas; i++){
            for(int j=0; j<colunas; j++){
                char entrada;
                cin >> entrada;

                int v = i*colunas + j; //(linhas * colunas)+coluna

                //posicao tiver um peao
                if(entrada == 'P'){
                    mapaVertices[indice] = v; 
                    matriz[v][v] = 2; //peça em posicao tabuleiro valida
                    indice = indice<<1;
                }
                else if(entrada == 'C'){
                    mapaVertices[1] = v;
                    matriz[v][v] = 2; //peça em posicao tabuleiro valida  
                }
                else if(entrada == '.'){
                    matriz[v][v] = 1; //posicao tabuleiro valida  sem peça
                }
                else if(entrada == '#'){
                    matriz[v][v] = 0; //posicao tabuleiro INvalida
                }
            }
        }

        //a partir de cada posicao, marcar como distancia = 1 os vertices alcancados pelo movimento do cavalo
        for(int i=0; i<linhas; i++){
            for(int j=0; j<colunas; j++){
                int v = i*colunas + j;
                
                //verificar se posicao tabuleiro é valida
                if(matriz[v][v] != 0){

                    //vertices alcançáveis pelo movimento do cavalo
                    if(i-2>=0 && j-1>=0){
                        int v2 = (i-2)*colunas + (j-1);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i-2>=0 && j+1<colunas){
                        int v2 = (i-2)*colunas + (j+1);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i-1>=0 && j-2>=0){
                        int v2 = (i-1)*colunas + (j-2);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i-1>=0 && j+2<colunas){
                        int v2 = (i-1)*colunas + (j+2);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i+2<linhas && j-1>=0){
                        int v2 = (i+2)*colunas + (j-1);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i+2<linhas && j+1<colunas){
                        int v2 = (i+2)*colunas + (j+1);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i+1<linhas && j-2>=0){
                        int v2 = (i+1)*colunas + (j-2);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                    if(i+1<linhas && j+2<colunas){
                        int v2 = (i+1)*colunas + (j+2);
                        if(matriz[v2][v2] !=0){
                            matriz[v][v2] = 1;
                        }
                    }
                }
            }
        }
        

        //Inicialização variáveis globais para menorDistancia
        nVertices = peoes+1; //número de vértices
        fim = (1<<(peoes+1)) - 1; //máscara todos os bits 1
        
        // Obter menor distância entre as peças do tabuleiro
        menorDistancia(matriz, tamanho);

        //inicializar variáveis globais para percorrerEstados
        for(int a = 0; a < 16; a++){
            for(int b = 0; b < 1<<16; b++){
                estados[a][b] = -1;
            }
        }

        //iniciar percuso dos estados a partir do local do cavalo, vértice do cavalo como visitado.
        cout << percorrerEstados(matriz, 0, 1) << endl;

        //liberar memoria
        for(int i=0; i<tamanho; i++){
            delete[] matriz[i];
        }
        delete[] matriz;

        //ler número de linhas, colunas e peoes
        cin >> linhas >> colunas >> peoes;
    }
    return 0;
}