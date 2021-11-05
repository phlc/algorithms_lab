/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS11

Análise:
        O algoritmo cria um arranjo representativo de todas as posições do tabuleiro. Assim, em um tabuleiro com "n" posições
        n = linhas x colunas. A criação do tabuleiro custa O(n).
        Para encontrar a menorDistancia() entre todas as peças, sao realizadas <=16 buscas em larguras no tabuleiro de tamanho n, 
        para encontrar o menor caminho de cada peça em relação às demais. Nesse caso temos <=16 buscas a um custo cada O(n).
        Após, percorrerEstados() executa o algoritmo de programação dinâmica do caixeiro viajante para encontrar a menor
        rota que passa por todas as peças e retorna para o cavalo. A complexidade do caixeiro viajante é O(n^2*2^n), mas por
        restrições do enunciado, nesse caso n, o número de peças, está limitado a <=16.

*/

//Dependencias
#include <iostream>
#include <iomanip>

//Namespace
using namespace std;

//Variariáveis Globais
int fim; // int que funcionará como máscara para identificar quando todos vértices forem visitados
int pecas; // número de pecas no tabuleiro
int linhas; // número de linhas
int colunas; // número colunas

//Arranho 2D de controle de estados
//[16] -> número do vértice atual: número máximo de peões + posição inicial do cavalo
//[1<<16] -> representação binária dos vértices visitados. A posição do bit indica se ele foi visitado ou não
int estados[16][1<<16]; 


//Macros
#define INFINITO 1000000 // peso suficientemente grande
#define X(p) p/colunas // posicao x (2D) a partir da posicao no arranjo
#define Y(p) p%colunas // posicao y (2D) a partir da posicao no arranjo
#define P(x, y) x*colunas+y //posicao no arranjo a partir da posicao x y (2D)


/*menorDistancia - Cria um grafo com as pecas sendo vertices e arestas sendo a distancia entre as peças.
@param char tabuleiro[], int** matriz  -> arranjo representativo do tabuleiro, grafo das pecas
*/
void menorDistancia(char tabuleiro[], int** matriz){
    //Declaracoes
    int tamanho = linhas*colunas;
    //Fazer busca em largura começando em todos os vértices
    for(int i=0; i<pecas; i++){

        //declarcoes locais
        int v, pecasVisitadas, atual, inicioFila, fimFila;
        int pais[tamanho];
        int fila[tamanho];
        int visitados[tamanho];

        //inicializacao
        v = matriz[i][i];
        pecasVisitadas = 1;
        atual = v;
        inicioFila = 0;
        fimFila = 0;
        for(int j=0; j<tamanho; j++){
            pais[j] = j;
            fila[j] = -1;
            visitados[j] = -1;
        }

        //marcar atual como visitado
        visitados[atual] = 1;

        //colocar atual na fila
        fila[fimFila++] = atual;
        //busca em largura por todas as peças
        while(pecasVisitadas != pecas && inicioFila!=fimFila){

            //retirar posicao da fila
            atual = fila[inicioFila++];

            //calcular posicao 2D de atual
            int l = X(atual);
            int c = Y(atual);

            //vertices alcançáveis pelo movimento do cavalo
            if(l-2>=0 && c-1>=0){
                int v2 = P((l-2),(c-1));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l-2>=0 && c+1<colunas){
                int v2 = P((l-2),(c+1));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l-1>=0 && c-2>=0){
                int v2 = P((l-1),(c-2));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l-1>=0 && c+2<colunas){
                int v2 = P((l-1),(c+2));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l+2<linhas && c-1>=0){
                int v2 = P((l+2),(c-1));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l+2<linhas && c+1<colunas){
                int v2 = P((l+2),(c+1));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l+1<linhas && c-2>=0){
                int v2 = P((l+1),(c-2));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }
            if(l+1<linhas && c+2<colunas){
                int v2 = P((l+1),(c+2));
                if(visitados[v2]!=1 && tabuleiro[v2] != '#'){
                    pais[v2] = atual;
                    fila[fimFila++] = v2;
                    if(tabuleiro[v2]=='C' || tabuleiro[v2]=='P'){
                        pecasVisitadas++;
                    }
                }
                visitados[v2] = 1;
            }  
        }

        //verificar distancia de cada peca ate v
        for(int j=0; j<pecas; j++){
            //declaracoes locais
            int filho = matriz[j][j];
            int distancia = 0;

            //subir nos pais até v
            while(filho != v){
                distancia += 1;
                filho = pais[filho];
            }
            if(i!=j){
                matriz[i][j] = matriz[j][i] = distancia;
            }
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
        return matriz[v][0];
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
    for(int i = 0; i < pecas; i++){
        //representação binária dos vértices já visitados, marcando o próximo vértice (i) como visitado
        int atualizado = (visitados | 1 << i); //bitwise OR -> mantém visitados e marca i como 1.

        //Se vértice i já estava em visitados, pular esse loop
        if(visitados & 1 << i) //bitwise AND -> resultado 1 se i já era 1 em visitados ou 0 se não
            continue;

        else{
            //chamada para o próximo estado 
            //n_movimentos retornado + movimentos de v-i
            int movimentosCaminho = percorrerEstados(matriz, i, atualizado)+matriz[v][i]; 

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
    int peoes;
    
    //ler número de linhas, colunas e peoes
    cin >> linhas >> colunas >> peoes;

    //repetir até 0s
    while(linhas || colunas || peoes){
        //Inicialização variáveis globais para menorDistancia
        pecas = peoes+1; //número de vértices
        fim = (1<<(peoes+1)) - 1; //máscara todos os bits 1
        for(int a = 0; a < 16; a++){
            for(int b = 0; b < 1<<16; b++){
                estados[a][b] = -1;
            }
        }

        //Declaracoes locais
        int contador = 1;
        int** matriz = new int*[pecas];
        for(int i=0; i<pecas; i++){
            matriz[i] = new int[pecas];
            for(int j=0; j<pecas; j++){
                matriz[i][j] = INFINITO;
            }
        }

        //Arranjo representativo do tabuleiro. Posicao = (número da linha)*(número de colunas) + (número da coluna)
        char tabuleiro[linhas*colunas];

        //preencher tabuleiro com leitura das entradas
        for(int i=0; i<(linhas*colunas); i++){
                char entrada;
                cin >> entrada;
                tabuleiro[i] = entrada;

                //aproveitar o grafo para guardar a posicao das pecas no tabuleiro
                if(entrada == 'C'){
                    matriz[0][0] = i;
                }
                else if(entrada == 'P'){
                    matriz[contador][contador] = i;
                    contador++;
                }
        }

        // Obter menor distância entre as peças do tabuleiro
        menorDistancia(tabuleiro, matriz);

        //iniciar percuso dos estados a partir do local do cavalo, vértice do cavalo como visitado.
        cout << percorrerEstados(matriz, 0, 1) << endl;

        //liberar memoria
        for(int i=0; i<pecas; i++){
            delete[] matriz[i];
        }
        delete[] matriz;

        //ler número de linhas, colunas e peoes
        cin >> linhas >> colunas >> peoes;
    }
    return 0;
}