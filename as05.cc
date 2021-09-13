/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS05

Análise:
        

*/

//Dependencias
#include <iostream>
#include <iomanip>

//Namespace
using namespace std;

/*
Grafo - Classe para grafo simples
Implementação a partir de dois arranjos paralelos de tamanho[número de arestas]. 
Vert_1[i] e Vert_2[i] contêm cada um dos vértices ligados pela aresta Ai.
Obs: tratando char como int -> número = a-97 = 0

*/
class Grafo{

    //Atributos
    private:
        int n_vertices;  //número de vértices
        int n_arestas;   //número de arestas inseridas
        int max_arestas; //número máximo de arestas
        int* Vert_1;         
        int* Vert_2;  


    //Métodos
    public:
        /*
        Construtor
        @paran int v, int a -> número de vértices, número máximo de arestas
        */
        Grafo(int v, int a){
            //número de vértices
            n_vertices = v;
            n_arestas = 0; 
            max_arestas = a;

            //alocação de memória
            Vert_1 = new int[max_arestas];
            Vert_2 = new int[max_arestas];

            //inicialização
            for(int i=0; i<max_arestas; i++){
                Vert_1[i] = Vert_2[i] = -1;
            }
        }  

        /*
        mostrar - mostra o grafo
        */
        void mostrar(){
            for(int i=1; i<=max_arestas; i++){
                cout << setw(2) << Vert_1[i] << " ";
            }
            cout << endl;
            for(int i=1; i<=max_arestas; i++){
                cout << setw(2) << Vert_2[i] << " ";
            }
            cout << endl;
        } 

        /*
        inserir - insere uma aresta no grafo
        @param int v1, int v2 -> vértice 1, vértice 2
        @return bool -> true = sucesso, false = falha
        */
        bool inserir(int v1, int v2){
            //definições
            bool control = false;

            //controle parâmetros
            if(v1>=0 && v1<n_vertices && v2>=0 && v2<n_vertices && n_arestas<max_arestas){

                //inserir valores
                Vert_1[n_arestas+1] = v1;
                Vert_2[n_arestas+1] = v2;

                //atualizar variáveis
                n_arestas++;
                control = true;
            }
            return control;
        }

        /*
        desconexos - Verificar o custo mínimo a partir do algoritmo de Kruskal em um disjoit set
        @return int -> int custo
        Obs: para árvore invertida utliza um arranjo[1, número de aresta], sendo que arranjo[i] < 0 indica
        que aquela aresta é uma raiz e tem |arranjo[i]-1| filhos.
        */
        int custoMinimo(){
            //declarações
            int custo = 0;
            int pais[n_vertices+1]; //arranho par controle do pais de cada vértice

            //inicialização - cada aresta forma um conjunto unitário
            for(int i=0; i<=n_vertices; i++){
                pais[i] = -1;
            }

            //analisar a inclusão das arestas nos conjuntos da menor para a maior
            for(int i=1; i<=max_arestas; i++){
                //declarações locais
                int raiz_v1 = Vert_1[i];
                int raiz_v2 = Vert_2[i];

                //obter raizes de Vert_1[i] e Vert_2[i]
                while(pais[raiz_v1] >= 0){
                    raiz_v1 = pais[raiz_v1];
                }
                while(pais[raiz_v2] >= 0){
                    raiz_v2 = pais[raiz_v2];
                }

                //se forem diferentes - não forma ciclo
                if(raiz_v1 != raiz_v2){

                    //incluir a que tem menos filhos na árvore que tem mais
                    if(raiz_v1 < raiz_v2){
                        pais[raiz_v1] += pais[raiz_v2];
                        pais[raiz_v2] = raiz_v1;
                    }
                    else{
                        pais[raiz_v2] += pais[raiz_v1];
                        pais[raiz_v1] = raiz_v2;
                    }
                }
            }
            return custo;
        }
};

/*
Main
*/
int main(){
    //Declaracoes
    int nCasos;

    //ler número de casos
    cin >> nCasos;

    //analisar cada caso  
    for(int i=1; i<=nCasos; i++){
        //declaracoes
        int nVertices, nArestas;
        char vertice1, vertice2;

        //ler numero de vértices e arestas
        cin >> nVertices;
        cin >> nArestas;

        //criar grafo
        Grafo g = Grafo(nVertices, nArestas);

        //ler arestas e inserir no grafo
        for(int j=0; j<nArestas; j++){
            cin >> vertice1;
            cin >> vertice2;

            //inserir como número(0 = a-97, 1 = b-97 ...)
            g.inserir(vertice1-97, vertice2-97);
        }

        g.mostrar();
        
    }

    //return
    return 0;   
}  
