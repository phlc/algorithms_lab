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
        Vertice** lista;     //lista de vértices


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
            for(int i=0; i<=nVertices; i++){
                lista[i] = new Vertice(i); //cada lista de cada vértice só tem a sim mesmo que funciona como nó cabeça
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
        @param int v1, int v2, int valor -> vértice 1, vértice 2
        @return bool -> true = sucesso, false = falha
        */
        bool inserir(int v1, int v2){
            //definições
            bool control = false;

            //controle parâmetros
            if(v1>=0 && v1<nVertices && v2>=0 && v2<nVertices){
                //como o grafo é não direcionado, só é necessário inserir na lista do menor
                if(v1>v2){
                    int buffer = v1;
                    v1 = v2;
                    v2 = buffer;
                }


                //inserir aresta 
                Vertice* novo = new Vertice(v2);
                Vertice* prox = lista[v1];
                
                //caminhar até o final da lista ou quando o próximo for maior
                //como sempre insere o maior no menor, a lista estará sempre ordenada

                for(; prox->prox!=NULL && prox->prox->numero < novo->numero; prox=prox->prox);
                    Vertice* buffer = prox->prox;
                    prox->prox=novo;
                    prox->prox->prox = buffer;

                control = true;
            }
            return control;
        }

        /*
        desconexos - Mostra os vertices de cada elemento conexo e o número de elementos desconexos
        */
        void desconexos(){
            //declarações
            int elementos = 0;
            int visitados[nVertices]; //controle dos vértices visitados

            //inicialização
            for(int i=0; i<nVertices; i++){
                visitados[i] = 0;
            }

            //mostrar mostrar todos os vértice e seus conexos em ordem crescente
            //não mostrar novamente vértices já mostrados
            for(int i=0; i<nVertices; i++){
                //verificar se vértice ainda não foi mostrado
                if(visitados[i]==0){
                    visitados[i]=1;

                    for(Vertice* j=lista[i]; j!=NULL; j=j->prox){
                        cout << (char)j->numero <<", ";
                    }
                    cout << endl;

                    //atualizar o número de elementos conexos
                    elementos++;
                }
            }

            //mostrar número de elementos
            cout << elementos << "connected components" << endl;
        }

};

/*
Main
*/
int main(){
    //Declaracoes
    int nCasos,;

    //ler número de casos
    cin >> nCasos;

    //inserir cabos e custos como arestas valoradas  
    for(int i=0; i<nCasos; i++){
        //declaracoes
        int nVertices, nArestas;

        //ler número de vértices e arestas
        cin >> nVertices;
        cin >> nArestas;

        //criar grafo
        Grafo g = Grafo(nVertices, nArestas);

        //inserir arestas
        for(int j=0; j<nArestas; i++){
            //declaracoes - tratar letras como inteiros
            int v1, v2;
            cin >> v1;
            cin >> v2;
            g.inserir(v1, v2);
        }
        cout << "Case #" << i << ":" << endl;
        g.desconexos();
    }

    //return
    return 0;   
}  
