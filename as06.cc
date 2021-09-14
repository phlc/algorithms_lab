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

        /*
        menorCaminho - Altera o grafo para constar o menor caminho entre quaisquer dois par de vértices
        */
        void menorCaminho(){
            //verificar o menor caminho entre quaisquer par de vértices
            // k é o vértice referencia. Para todos vértices, cada hora um como referencia,
            //verifica-se se a distancia direta entre dois vértices i e j é maior que i-k k-j
            // se i-k k-j for menor, atualizar para esse valor a distancia entre i-j
            for(int k=0; k<nVertices; k++){
                for(int i=0; i<nVertices; i++){
                    for(int j=0; j<nVertices; j++){
                        if(matriz[i][j] > (matriz[i][k] + matriz[k][j])){
                            matriz[i][j] = matriz[i][k] + matriz[k][j];
                        }
                    }
                }
            }
        }

        /*
        melhorOpcao - retorna o vertice nao visitado de menor custo para visitar a partir de v
        @param int v, int* visitados -> vértice atual, arranjo de visitados
        @return int p -> próximo vértice
        */
        int melhorOpcao(int v, int* visitados){
            //declaracoes
            int menor = INFINITY+1;
            int p = v;
 
            //verificar menor opção não visitada
            for(int i=0; i<nVertices; i++){
                if(i!=v && visitados[i]==0 && matriz[v][i]< menor){
                    //caminho de menor custo e vértice não visitado encontrado
                    menor = matriz[v][i];
                    p = i;
                }
            }
            return p;
        }

        /*
        caminharPorTodos - Tenta caminhar por todos os vértices do grafo
        @param int k -> k sendo o número de teletransportes
        @return int t -> t sendo o tempo total gasto para caminhar ou -1 se impossível
        */
        int caminharPorTodos (int k){
            //declaracoes
            int t = 0;
            int atual = 0;
            int proximo = 1;
            int visitados[nVertices];

            //inicialização
            visitados[0] = 1;
            for(int i=1; i<nVertices; i++){
                visitados[i] = 0;
            }

            //alterar grafo para menor caminho entre quaisquer dos dois vértices
            this->menorCaminho();

            //verificar menor caminho a partir do vértice atual para não visitado   
            proximo = melhorOpcao(atual, visitados);     
            while(atual != proximo){
                //se não tem caminho
                if(matriz[atual][proximo] == INFINITY){
                    //se tem teletransporte
                    if(k>0){
                        k--;
                        matriz[atual][proximo] = 0;
                    }
                    else{
                        return -1;
                    }
                }
                //se tem caminho
                else{
                    t+=matriz[atual][proximo];
                    visitados[proximo]=1;
                    atual = proximo;
                }
                proximo = melhorOpcao(atual, visitados);
            }
            return t;
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

        cout << g.caminharPorTodos(k) << endl;
    }

    //return
    return 0;   
}  
