/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS05

Análise:
        O algoritmo utiliza uma adaptação do algortimo de busca em profundidade para obter uma arranjo com as raízes
        de cada spanningtree do grafo. Como a busca é feita sempre a partir do menor vértice, a raiz será sempre o 
        menor. A busca em produndidade entre em cada vértice apena uma vez, no entanto, testa todos os vértices conectados
        ao vértice atual. Assim, em que pese entre apenas uma vez em cada vértice, sendo em tese O(n), sendo n o número de
        vértices, são feitos, no pior caso(grafo completo) n^2 testes, assim O(n^2).
        Acredito que seria possível uma melhor implementação do DFS, mas a necessidade de se imprimir os vértices de cada
        elemento conexo em ordem crescente também implica na necessidade de se realizar O(n^2) testes, sendo n o número 
        de vértices.
        Esses são os dois momentos mais custos do algoritmo, sendo a inserção e demais métodos mais eficientes, portanto, 
        desconsiderados na análise.
        
*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;

/*
Vertice - Classe para implementar um vértice com ponteiro para o próximo
*/
class Vertice{
public:
    //atributos
    int numero;
    Vertice* prox;

    //construtor
    Vertice(int n){
        numero = n;
        prox = NULL;
    }
};


/*
Grafo - Classe para grafo simples
Implementação a partir de uma lista  de adjacencia

*/
class Grafo {

    //Atributos
    private:
        int nVertices;      //número de vértices
        int nArestas;       //número de arestas
        Vertice** lista;   //lista de vértices


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
            lista = new Vertice*[v];
            
            //inicialização
            for(int i=0; i<nVertices; i++){
                lista[i]= NULL;
            }
        }  

        /*
        mostrar - mostra o grafo
        */
        void mostrar(){
            for(int i=0; i<nVertices; i++){
                cout << i << ": ";
                for(Vertice* v=lista[i]; v!=NULL; v=v->prox){
                    cout << "(" << v->numero << ")";
                }
                cout << endl;
            }
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
            if(v1>=0 && v1<nVertices && v2>=0 && v2<nVertices){

                //inserir aresta - grafo não direcionado (v1->v2 e v2->v1)
                Vertice* novo = new Vertice(v2);
                Vertice* prox = NULL;
                
                //verificar lista vazia
                if(lista[v1]==NULL)
                    lista[v1]=novo;
                else{
                    //caminhar até o final da lista
                    for(prox=lista[v1]; prox->prox!=NULL; prox=prox->prox);
                    prox->prox=novo;
                }

                novo = new Vertice(v1);
                prox = NULL;
                
                //verificar lista vazia
                if(lista[v2]==NULL)
                    lista[v2]=novo;
                else{
                    //caminhar até o final da lista
                    for(prox=lista[v2]; prox->prox!=NULL; prox=prox->prox);
                    prox->prox=novo;
                }

                control = true;
            }
            return control;
        }

        /*
        dfs - Adaptação de DeepFirstSearch para preencher um arranjo com a informação da raíz da spanningtree de cada vértice
        @param int raiz, int pos, int* raizes -> raiz original, posição na busca, arranjo raizes
        */
        void dfs(int raiz, int pos, int* raizes){
            for(Vertice* i=lista[pos]; i!=NULL; i=i->prox){
                
                //vertices ainda nao descobertos
                if(raizes[i->numero] == -1){
                    raizes[i->numero] = raiz;
                    dfs(raiz,i->numero, raizes);
                }
            }

        }

        /*
        conexos - mostra os vertices de cada elemento conexo do grafo
        */
        void conexos(){
            //declarações
            int* raizes = new int[nVertices]; // arranjo com as raizes de cada vertice de cada spanningtree
            int elementos = 0; //numero de elementos desconexos
            

            //inicialização
            for(int i=0; i<nVertices; i++){
                raizes[i] = -1; // todos vértices que são raizes deles mesmos
            }

            //realizar busca em profundidade e armazenar as raízes de cada vértice em raízes[]
            for(int i=0; i<nVertices; i++){
                //vertices ainda nao descobertos
                if(raizes[i] ==-1){
                    raizes[i] = i;
                    dfs(i, i, raizes);
                }
            }

            //mostrar conexos
            for(int i=0; i<nVertices; i++){
                int controle = 0;
                for(int j=0; j<nVertices; j++){
                    if(raizes[j] == i){
                        controle = 1;
                        cout << char(j+97) << ",";
                    }
                }
                if(controle == 1){
                    elementos++;
                    cout << endl;
                }
            }

            //mostrar número de elementos desconexos
            cout << elementos << " connected components" << endl;
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

    //verificar cada caso  
    for(int i=1; i<=nCasos; i++){
        //declaracoes
        int nVertices, nArestas;

        //ver número de vértices e aresta
        cin >> nVertices;
        cin >> nArestas;

        Grafo g = Grafo(nVertices, nArestas);

        for(int j=0; j<nArestas; j++){
            //tratar vertices como inteiros (a=0, b=1, ...)
            char v1, v2;
            cin >> v1;
            cin >> v2;
            g.inserir((int)v1-97, (int)v2-97);
        }

        //mostrar
        cout << "Case #" << i << ":" << endl;
        g.conexos();
        if(i<nCasos)
            cout << endl;
    }

    //return
    return 0;   
}  
