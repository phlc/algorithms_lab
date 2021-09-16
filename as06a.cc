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

//Macros
#define INFINITO 1000000 // peso máximo da aresta válida é 30000
#define MAX 2147483647 // valor máximo


/*
No - Classe nó para criação de um nó para uma pilha de alocação dinâmica
*/
class No {
public:  
    //Atributos
    int t; //tempo
    No* prox; //próximo nó

    //Construtor
    No(int v){
        t = v;
        prox = NULL;
    }
};

/*
Pilha - Classe para uma "pilha ordenada" para organização dos nós
*/
class Pilha{
public:
    //Atributos
    No* inicio;
    int soma;

    //Construtor
    Pilha(){
        inicio = new No(INFINITO); // nó cabeça
        soma = 0;
    }

    /*
    inserir - insere um novo valor na Pilha mantendo ordenada de forma decrescente
    @param int v -> novo valor
    */
    void inserir(int v){
        No* novo = new No(v);
        No* i=inicio;
        for(; i->prox!=NULL && i->prox->t > novo->t; i=i->prox)
        ;
        No* buffer = i->prox;
        i->prox = novo;
        novo->prox = buffer;

        soma = soma + v;
    }

    /*
    remover - remove o topo da Pilha
    @return int v -> valor do nó removido ou -1 se pilha vazia
    */
    int remover(){
        if(inicio->prox == NULL)
            return -1;
        else{
            No* buffer = inicio->prox;
            inicio->prox = inicio->prox->prox;
            soma = soma - buffer->t;

            return (buffer->t);
        }
    }

    /*
    mostrar - mostra os valores da pilha
    */
    void mostrar(){
        for(No* i=inicio; i!=NULL; i=i->prox){
            cout << i->t << " ";
        }
        cout << endl;
    }
};


/*
Grafo - Classe para grafo simples com aresta valorada
Implementação a partir de uma matriz  de adjacencia
matriz(x,y) =  1000000 -> aresta inexistente - tempo infinito de x -> y
matrir(x,y) > 0 -> aresta existente, peso aresta(x,y) = matriz[x][y], max 30000 

*/
class Grafo {
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
                        matriz[i][j] = INFINITO;
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
            if(v1>=0 && v1<nVertices && v2>=0 && v2<nVertices 
                    && valor < matriz[v1][v2] && v1!=v2){

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
                    if(matriz[i][j] == INFINITO)
                        cout << setw(5) << -1;
                    else
                        cout << setw(5) << matriz[i][j];
                }
                cout << endl;
            }
        }

        /*
        menorTodosPares - Altera o grafo para constar o menor caminho entre quaisquer dois par de vértices
        */
        void menorTodosPares(){
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
        calcularComponentes - Calcula o número de componentes do grafo
        @param int* componentes -> arranjo para armazenar a qual componente cada vertice pertence
        @return int -> número de compoenente
        */
        int calcularComponentes(int* componentes){
            //declarações
            int contador = 0;
            int nComponentes = 0;

            //analisar todos os vértices
            while(contador<nVertices){

                //verificar vértices ainda não incluídos em uma componente
                int vertice = 0;
                while(componentes[vertice]!=-1){
                    vertice++;
                }

                //criar nova componente para o vértice
                componentes[vertice] = nComponentes;
                contador++;
                
                //verificar todos dos vértices conexos a vertice
                for(int i=0; i<nVertices; i++){
                    if(vertice!=i & matriz[vertice][i] != INFINITO){
                        componentes[i] = nComponentes;
                        contador++;
                    }
                }
                nComponentes++;
            }
            return nComponentes;
        }

        /*
        testarCaminhos - Testa recursivamente os caminhos para descobrir o menor
        @param int* visitados, int atual, int level -> arranjo para controle dos visitados, vértice atual
        @return Pilha* -> ponteiro para pilha com os melhores caminhamentos e tempo total
        */
        Pilha* testarCaminhos(int* visitados, int atual){
            Pilha* tempos[nVertices]; //armazenamento das listas retornadas
            int controle = 0;

            //inicialização
            for(int i=0; i<nVertices; i++){
                tempos[i] = NULL;
            }

            //chamar recursivamente demais
            for(int i=0; i<nVertices; i++){
                if(visitados[i]==0){
                    visitados[i] = 1;
                    tempos[i] = testarCaminhos(visitados, i);
                    tempos[i]->inserir(matriz[atual][i]);
                    visitados[i] = 0;
                    controle = 1;
                }
            }

            //se não há mais vértices final da recursão
            if(controle == 0){
                return (new Pilha());
            }

            //verificar a melhor opção
            int melhor = -1;
            int melhorTempo = MAX;
            for(int i=0; i<nVertices; i++){
                if(tempos[i]!=NULL && melhorTempo > tempos[i]->soma){
                    melhor = i;
                    melhorTempo = tempos[i]->soma;
                }
            }

            return tempos[melhor];
        }

        /*
        testarCaminhos - Testa recursivamente os caminhos para descobrir o menor
        @return Pilha* -> ponteiro para pilha com os melhores caminhamentos e tempo total
        */
        Pilha* testarCaminhos(){
            Pilha* resp;
            int visitados[nVertices]; //controle vértices visitados
            Pilha* tempos[nVertices]; //armazenamento das listas retornadas

            //inicialização
            for(int i=0; i<nVertices; i++){
                visitados[i] = 0;
                tempos[i] = NULL;
            }

            //começar vértice 1
            visitados[0] = 1;

            //chamar recursivamente demais
            for(int i=1; i<nVertices; i++){
                if(visitados[i]==0){
                    visitados[i] = 1;
                    tempos[i] = testarCaminhos(visitados, i);
                    tempos[i]->inserir(matriz[0][i]); //começar do vértice 1
                    visitados[i] = 0;
                }
            }

            //verificar a melhor opção
            int melhor = -1;
            int melhorTempo = MAX;
            for(int i=0; i<nVertices; i++){
                if(tempos[i]!=NULL && melhorTempo > tempos[i]->soma){
                    melhor = i;
                    melhorTempo = tempos[i]->soma;
                }
            }

            return tempos[melhor];
        }

        /*
        tempoOtimo - Descobre o menor tempo para caminhar por todos os vértices do grafo
        @param int k -> k sendo o número de teletransportes
        @return int t -> t sendo o tempo total gasto para caminhar ou -1 se impossível
        */
        int tempoOtimo(int k){
            //declaracoes
            int t = 0;
            int nComponentes = 0;
            int componentes[nVertices]; //controle componentes desconexos

            //inicialização
            for(int i=0; i<nVertices; i++){
                componentes[i] = -1;
            }
            
            //verificar se número de teletransportes é suficiente para passsar por todos os vértices sem caminhar
            if(nVertices-1 <= k){
                return 0;
            }

            //alterar grafo para menor caminho entre quaisquer dos dois vértices
            this->menorTodosPares();

            //calcular número de componentes
            nComponentes = calcularComponentes(componentes);
            //verificar se o número de teletransportes é insuficiente para conectar todos componentes desconexos
            if(k < nComponentes-1){
                return -1;
            }

            Pilha* tempos = testarCaminhos();

            for(int i=0; i<k; i++){
                tempos->remover();
            }

            return tempos->soma;
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
        
        
        cout << g.tempoOtimo(k) << endl;
    }

    //return
    return 0;   
}  
