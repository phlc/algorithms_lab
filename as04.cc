/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS04

Análise:
        
        
*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;


/*
Grafo - Classe para grafo simples com aresta valorada
Implementação a partir de uma matriz  de adjacencia
matriz(x,y) = 0 -> aresta inexistente
matrir(x,y) > 0 -> aresta existente, valor = matriz[x][y] 

*/
class Grafo {

    //Atributos
    private:
        int nVertices; //número de vértices
        int nArestas; //número de arestas
        int** matriz;


    //Métodos
    public:
        /*
        Construtor
        @paran int v, int a -> número de vértices, número máximo de arestas
        */
        Grafo(int v, int a){
            //número de vértices
            nVertices = v;
            nArestas = a; 

            //alocação de mémoria 
            matriz = new int*[nVertices];
            for(int i=0; i<nVertices; i++){
                matriz[i] = new int[nVertices];
                
                //inicializar
                for(int j=0; j<nVertices; j++){
                    matriz[i][j] = 0;
                }
            }
        }

        /*
        Destrutor
        */
        ~Grafo(){
            for(int i=0; i<nVertices; i++){
                delete[] matriz[i];
            }
        }

        /*
        inserir - insere uma aresta valorada no grafo
        @param int v1, int v2, int valor -> vértice 1, vértice 2, valor
        @return bool -> true = sucesso, false = falha
        */
        bool inserir(int v1, int v2, int valor){
            //definições
            bool control = false;

            //normalizar v1 e v2 para números [0, nVertices]
            v1--;
            v2--;

            //controle parâmetros
            if(v1>=0 && v1<nVertices && v2>=0 && v2<nVertices){

                //inserir aresta - grafo não direcionado
                matriz[v1][v2] = valor;
                matriz[v2][v1] = valor;
            
                control = true;
            }
            return control;
        }

    private:
        /*
        deepFirstSearch - Overload - Recursivo
        @param int v -> vértice de início, int* pais -> arranjo de ancestralidade, int* visitados -> vértices visitados
        */
        void deepFirstSearch(int v, int* pais, int* visitados){
            //caminhamento
            //verificar todas arestas de v
            for(int i=v+1; i%nVertices!=v; i++){
                //se houver aresta e o vértice adjacente não tiver sido visitado
                if(matriz[v][i%nVertices]>0 && visitados[i%nVertices]==0){
                    pais[i%nVertices] = v;
                    visitados[i%nVertices] = 1;
                    deepFirstSearch(i%nVertices, pais, visitados);
                }
            }
        }

    public:
        /*
        deepFirstSearch - realiza busca em profundidade para acessar todos os vertices
        @param int v -> vértice de início
        @param int* pais
        */
        int* deepFirstSearch(int v){
            //controle de parâmetros
            if(v<0 || v>=nVertices)
                return NULL;
            
            //declarações
            int* visitados = new int[nVertices];
            int* pais = new int[nVertices];

            //inicialização dos arranjos
            for(int i=0; i<nVertices; i++){
                pais[i] = -1;
                visitados[i] = 0;
            }

            //vértice inicial
            pais[v] = v;
            visitados[v] = 1;

            //caminhamento
            //verificar todas arestas de v
            for(int i=v+1; i%nVertices!=v; i++){
                //se houver aresta e o vértice adjacente não tiver sido visitado
                if(matriz[v][i]>0 && visitados[i%nVertices]==0){
                    pais[i%nVertices] = v;
                    visitados[i%nVertices] = 1;
                    deepFirstSearch(i%nVertices, pais, visitados);
                }
            }

            //liberar memória
            delete[] visitados;

            return pais;
        }
        /* 
        isConnected - Verica se um grafo é conexo
        @return bool 
        */
        bool isConnected(){
            int n = 0; //número de vértices alcançados

            //realizar busca em profundidade a partir do vértice 0
            int* pais = this->deepFirstSearch(0);
            
            //contar vértices acessados
            for(int i=0; i<nVertices; i++){
                if(pais[i] != -1){
                    n++;
                }
            }

            //liberar memoria
            delete[] pais;

            //se o número de vértices acessados != nVertices, não é conexo
            return nVertices==n;
        }

        /*
        custoMinimo - Verificar o custo mínimo a partir do conceito minimum spanning tree construida a partir 
        da remoção da aresta de maior custo que não transforma o grafo em desconexo
        @return int -> int custo
        */
        int custoMinimo(){

            //declaraçoes
            int custoTotal, v1, v2, maior;
            int controle[nVertices][nVertices]; // matriz de controle das arestas mantidas

            //inicialização
            maior = 0;  //maior valor encontrado
            custoTotal = 0;
            for(int i=0; i<nVertices; i++){
                for(int j=0; j<nVertices; j++){
                    controle[i][j] = 0;
                }
            }

            //minimum spanning tree terá nVertices-1 arestas
            while(nArestas>nVertices-1){

                //achar a aresta mais custosa
                for(int i=1; i<nVertices; i++){
                    for(int j=0; j<i; j++){
                        //verificar se aresta não foi previamente mantida e achar o maior valor
                        if(controle[i][j]==0 && matriz[i][j]>maior){
                            maior = matriz[i][j];
                            v1 = i;
                            v2 = j;
                        }
                    }
                }

                //remover aresta
                matriz[v1][v2] = matriz[v2][v1] = 0;

                //verificar se matriz continua conexa
                if(this->isConnected()){
                    nArestas--;
                }
                //retornar arestas - grafo ficou desconexo
                else{

                    matriz[v1][v2] = matriz[v2][v1] = maior;
                    //marcar aresta como não removível
                    controle[v1][v2] = controle[v2][v1] = 1;
                }
                //reiniciar variáveis
                maior = 0;
            }

            //somar todas as arestas
            for(int i=1; i<nVertices; i++){
                for(int j=0; j<i; j++){
                    custoTotal+=matriz[i][j];
                }
            }
            return custoTotal;
        }

};

/*
Main
*/
int main(){
    //Declaracoes
    int nRoteadores, nCabos, rot1, rot2, custo;

    //ler número de cabos e roteadores
    cin >> nRoteadores;
    cin >> nCabos;

    //criar grafo com nRoteadores vértices 
    Grafo g = Grafo(nRoteadores, nCabos);

    //inserir cabos e custos como arestas valoradas  
    for(int i=0; i<nCabos; i++){
        cin >> rot1;
        cin >> rot2;
        cin >> custo;
        g.inserir(rot1, rot2, custo);
    }

    //calcular e mostrar custo minimo
    cout << g.custoMinimo() << endl;

    //return
    return 0;   
}  
