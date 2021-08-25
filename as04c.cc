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
#include <iomanip>

//Namespace
using namespace std;

/*
Grafo - Classe para grafo simples com aresta valorada
Implementação a partir de três arranjos paralelos de tamanho[número de arestas + 1], posição[0] ignorada para 
facilitar operações. Vert_1[i] e Vert_2[i] contêm cada um dos vértices ligados pela aresta Ai. Valores[i] contém 
o valor da aresta.

*/
class Grafo{

    //Atributos
    private:
        int n_vertices;  //número de vértices
        int n_arestas;   //número de arestas inseridas
        int max_arestas; //número máximo de arestas
        int* Vert_1;         
        int* Vert_2;  
        int* Valores;


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
            Vert_1 = new int[max_arestas+1];
            Vert_2 = new int[max_arestas+1];
            Valores = new int[max_arestas+1];

            //inicialização
            for(int i=0; i<=max_arestas; i++){
                Vert_1[i] = Vert_2[i] = Valores[i] = -1;
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
            for(int i=1; i<=max_arestas; i++){
                cout << setw(2) << Valores[i] << " ";
            }
            cout << endl;
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
            if(v1>0 && v1<=n_vertices && v2>0 && v2<=n_vertices && n_arestas<max_arestas){

                //inserir valores
                Vert_1[n_arestas+1] = v1;
                Vert_2[n_arestas+1] = v2;
                Valores[n_arestas+1] = valor;

                //atualizar variáveis
                n_arestas++;
                control = true;
            }
            return control;
        }

    private:
        //macros para heapsort
        #define RIGHT(i)    ((i)*2)+1
        #define LEFT(i)     ((i)*2)
        #define PARENT(i)   ((i)/2)

        /*
        swap - método auxiliar de heapsort para troca de elementos nos arranjos
        @param int i, int j - posições dos valores a sere trocados
        */
        void swap(int i, int j){
            int buffer_v1, buffer_v2, buffer_valor;

            buffer_v1 = Vert_1[i];
            buffer_v2 = Vert_2[i];
            buffer_valor = Valores[i];

            Vert_1[i] = Vert_1[j];
            Vert_2[i] = Vert_2[j];
            Valores[i] = Valores[j];

            Vert_1[j] = buffer_v1;
            Vert_2[j] = buffer_v2;
            Valores[j] = buffer_valor;

        }

        /*
        heapify - método auxiliar de heapsort para reorganizar o heap
        @param int i - posição do elemento alterado
        */
        void heapify(int i, int tamanho){
            int esq = LEFT(i);
            int dir = RIGHT(i);
            int maior = i;

            if(esq <= tamanho && Valores[esq] > Valores[i]){
                maior = esq;
            }
            if(dir <= tamanho && Valores[dir] > Valores[maior]){
                maior = dir;
            }
            if(maior != i){
                swap(i, maior);
                heapify(maior, tamanho);
            }

        }

    public:
        /*
        heapsort - método para ordenar os arranjos do grafo pela valor
        */
        void heapsort(){
            //declarações
            int tamanho = max_arestas;

            //construir heap
            for(int i=PARENT(tamanho); i>0; i--){
                heapify(i, tamanho);
            }         

            //ordenar heap
            for(int i=tamanho; i>1; i--){
                swap(1, tamanho);
                tamanho--;
                heapify(1, tamanho);
            } 
        }

        /*
        custoMinimo - Verificar o custo mínimo a partir do conceito minimum spanning tree construida a partir 
        da algoritmo prim
        @return int -> int custo
        */
        int custoMinimo(){
            //declarações
            int custo = 0;
            

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

g.mostrar();
cout << endl;
g.heapsort();
g.mostrar();

    //calcular e mostrar custo minimo
//    cout << g.custoMinimo() << endl;

    //return
    return 0;   
}  
