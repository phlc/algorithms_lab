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

//Namespace
using namespace std;


/*
Grafo - Classe para grafo simples com aresta valorada
Implementação a partir de uma matriz  de adjacencia
matriz(x,y) =  1000000 -> aresta inexistente - tempo infinito de x -> y
matrir(x,y) > 0 -> aresta existente, peso aresta(x,y) = matriz[x][y], max 30000 

*/
class Grafo {
    //Macros
    #define INFINITY 1000000 // peso máximo da aresta válida é 30000

    //Atributos
    private:
        int nVertices; //número de vértices
        int** matriz;


    //Métodos
    public:
        /*
        Construtor
        @paran int v -> número de vértices
        */
        Grafo(int v){
            //número de vértices
            nVertices = v;

            //alocação de mémoria 
            matriz = new int*[nVertices];
            for(int i=0; i<nVertices; i++){
                matriz[i] = new int[nVertices];
                
                //inicializar
                for(int j=0; j<nVertices; j++){
                    if (i==j)
                        matriz[i][j] = 0;
                    else
                        matriz[i][j] = INFINITY;
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

                //inserir aresta - grafo não direcionado - caminhamento em ambos sentidos
                matriz[v1][v2] = valor;
                matriz[v2][v1] = valor;
            
                control = true;
            }
            return control;
        }

        /*
        mostrar - mostra o grafo na tela
        */
        void mostrar(){
            for(int i=0; i<nVertices; i++){
                for(int j=0; j<nVertices; j++){
                    if(matriz[i][j] == INFINITY)
                        cout << setw(3) << -1;
                    else
                        cout << setw(3) << matriz[i][j];
                }
                cout << endl;
            }
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

    //passar por todos os casos
    for(int i=0; i<nCasos; i++){
        //Declaracoes
        int n, m, k;

        //ler quantidade de lugares(n), quantidade de rotas(m) e máximo teletransporte(k)
        cin >> n;
        cin >> m;
        cin >> k;

        //criar grafo
        Grafo g = Grafo(n);

        //inserir rotas
        for(int j=0; j<m; j++){
            int v1, v2, valor;
            cin >> v1;
            cin >> v2;
            cin >> valor;
            g.inserir(v1, v2, valor);
        }

        cout << endl;
        g.mostrar();
    }

    //return
    return 0;   
}  
