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
Vertice - Classe para implementar um vértice valorado com ponteiro para o próximo
*/
class Vertice{
public:
    //atributos
    int numero;
    int valor;
    Vertice* prox;

    //construtor
    Vertice(int n, int v){
        numero = n;
        valor = v;
        prox = NULL;
    }
};


/*
Grafo - Classe para grafo simples com aresta valorada
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
            lista = new Vertice*[v+1]; //intervalo dos vértice [1, v]. Desconsidera lista[0].
            
            //inicialização
            for(int i=0; i<=nVertices; i++){
                lista[i]= NULL;
            }
        }  

        /*
        mostrar - mostra o grafo
        */
        void mostrar(){
            for(int i=1; i<=nVertices; i++){
                cout << i << ": ";
                for(Vertice* v=lista[i]; v!=NULL; v=v->prox){
                    cout << "(" << v->numero << ", " << v->valor << ")";
                }
                cout << endl;
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

            //controle parâmetros
            if(v1>0 && v1<=nVertices && v2>0 && v2<=nVertices){

                //inserir aresta - grafo não direcionado (v1->v2 e v2->v1)
                Vertice* novo = new Vertice(v2, valor);
                Vertice* prox = NULL;
                
                //verificar lista vazia
                if(lista[v1]==NULL)
                    lista[v1]=novo;
                else{
                    //caminhar até o final da lista
                    for(prox=lista[v1]; prox->prox!=NULL; prox=prox->prox);
                    prox->prox=novo;
                }

                novo = new Vertice(v1, valor);
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
        custoMinimo - Verificar o custo mínimo a partir do conceito minimum spanning tree construida a partir 
        da algoritmo prim
        @return int -> int custo
        */
        int custoMinimo(){
            //declarações
            int custo = 0;
            int visitados[nVertices+1]; //controle dos vértices visitados
            int incluidos = 0; //controle para verifica se todos os vértice foram incluídos

            //inicialização
            for(int i=0; i<=nVertices; i++){
                visitados[i] = 0;
            }

            //incluir vértice inicial - 1
            visitados[1] = 1;
            incluidos++;

            //repetir até incluir todos
            while(incluidos<nVertices){
                //declarações locais
                int menor = 10001; //valor máximo = 10000
                int incluir; //número do vértice a ser incluído
                
                //verificar todos já incluídos
                for(int i=1; i<=nVertices; i++){
                    if(visitados[i]==1){
                        //percorrer todos os vértices adjacentes a visitados[i]
                        for(Vertice* v=lista[i]; v!=NULL; v=v->prox){
                            //verificar se vértice adjacente não foi incluído e custo inclusão menor
                            if(visitados[v->numero]==0 && menor>v->valor){
                                menor = v->valor;
                                incluir = v->numero;
                            }
                        }

                    }
                }
                visitados[incluir] = 1;
                incluidos++;
                custo+=menor;
            }

            return custo;
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
