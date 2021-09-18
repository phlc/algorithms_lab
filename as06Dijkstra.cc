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
Aresta - Classe Aresta para criação de uma aresta a ser inserida em um lista de caminhamento
*/
class Aresta {
public:  
    //Atributos
    int v1;
    int v2;
    int custo;
    Aresta* prox; //próxima aresta da lista

    //Construtor
    Aresta(int vert1, int vert2, int cust){
        this->v1 = vert1;
        this->v2 = vert2;
        this->custo = cust;
        prox = NULL;
    }
};

/*
Caminho - Classe caminho - Uma lista ordenada de arestas que compoem um caminho
Armazena custo total do caminho, vertices visitados, número de teletransportes
*/
class Caminho{
public:
    //Atributos
    Aresta* cabeca;
    int nVertices;
    int teles;
    int soma;
    int* visitados;
    int nVisitados;
    int atual; //vértice do caminhamento
    int descoberto; //melhor vértice descoberto
    Caminho* prox;

    //Construtor
    Caminho(int n, int k){
        cabeca = new Aresta(-1, -1, INFINITO+1); // aresta cabeça
        teles = k;
        nVertices = n;
        soma = 0;
        visitados = new int[nVertices]; //v = número de vértices
        nVisitados = 0;
        atual = -1;
        descoberto = -1;
        prox = NULL;

        //inicialização
        for(int i=0; i<nVertices; i++){
            visitados[i]=0;
        }
    }

    /*
    copiar - copia um caminhamento em seu estado atual - menos prox
    */
    Caminho* copiar(){
        //novo caminho
        Caminho* copia = new Caminho(this->nVertices, this->teles);
        copia->soma = this->soma;
        copia->visitados = new int[copia->nVertices];
        copia->nVisitados = this->nVisitados;
        copia->atual = this->atual;
        copia->descoberto = this->descoberto;
        copia->prox = NULL;

        //copia lista aresta
        for(int i=0; i<nVertices; i++){
            copia->visitados[i] =  this->visitados[i];
        }

        return copia;
    }

    /*
    inserir - insere uma nova aresta na lista mantendo ordenada de forma decrescente
    @param int v -> novo valor
    */
    void inserir(int v1, int v2, int custo){
        Aresta* nova = new Aresta(v1, v2, custo);
        Aresta* i=cabeca;
        for(; i->prox!=NULL && i->prox->custo > nova->custo; i=i->prox)
        ;
        Aresta* buffer = i->prox;
        i->prox = nova;
        nova->prox = buffer;

        //o caminhamento vai até v1 e descobre v2. Mas a soma já considera custo de chegar a v2;
        this->visitados[v1] = 1;
        this->nVisitados++;
        this->atual = v1;
        this->descoberto = v2;
        this->soma = this->soma + custo;
    }

    /*
    remover - remove a maior aresta da fila
    @return int custo -> custo da aresta removida ou -1 se pilha vazia
    */
    int remover(){
        if(cabeca->prox == NULL)
            return -1;
        else{
            Aresta* buffer = cabeca->prox;
            cabeca->prox = cabeca->prox->prox;
            soma = soma - buffer->custo;

            return (buffer->custo);
        }
    }

    /*
    mostrar - mostra os valores da pilha
    */
    void mostrar(){
        cout << "Soma: " << soma << " Teles: " <<  teles << " Visitados: " << nVisitados << " nVertices: "
             << nVertices << " Atual: " << atual << " Descoberto: " << descoberto << endl;
        for(Aresta* i=cabeca; i!=NULL; i=i->prox){
            cout << "v1: " <<  i->v1 << " v2: " << i->v2 << " custo: " << i->custo << " "; 
        }
        cout << endl;
    }
};

/*
Fila - Fila de caminhos ordenada para gerenciar proximo caminhamento 
*/
class Fila{
public:
    //Atributos
    Caminho* cabeca;

    //Construtor
    Fila(int n, int k){
        cabeca = new Caminho(n, k); // Caminho cabeça
        cabeca->soma = -1; // nunca sair da cabeça
    }

    /*
    inserir - insere novo caminho 
    @param Caminho* novo -> novo caminho
    Obs: a princípio a gestão e criação de caminhos sera feita fora. Se houver tempo realizo encapsulamento das classes
    */
    void inserir(Caminho* novo){
        Caminho* i=cabeca;
        for(; i->prox!=NULL && i->prox->soma < novo->soma; i=i->prox)
        ;
        Caminho* buffer = i->prox;
        i->prox = novo;
        novo->prox = buffer;
    }

    /*
    remover - remove o topo da Pilha
    @return Caminho* removido -> caminho removido
    */
    Caminho* remover(){
        Caminho* removido = NULL;
        if(cabeca->prox != NULL){
            removido = cabeca->prox;
            cabeca->prox = cabeca->prox->prox;
        }
        return removido;
    }

    /*
    mostrar - mostra os valores da pilha
    */
    void mostrar(){
        for(Caminho* i=cabeca; i!=NULL; i=i->prox){
            i->mostrar();
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
        testarCaminhos - Testa os caminhos para descobrir o menor
        @param int k -> número de teletransportes
        @return Caminho* -> ponteiro para o Caminho com os melhores caminhamentos e tempo total
        */
        Caminho* testarCaminhos(int k){
            Fila* tempos = new Fila(nVertices, k); //armazenamento das listas retornadas
            
            //Criar caminhos a partir vértice inicial
            //Verificar arestas não descobertas
            for(int i=1; i<nVertices; i++){
                if(matriz[0][i]!=INFINITO){
                    Caminho* buffer = new Caminho(nVertices, k);
                    buffer->inserir(0, i, matriz[0][i]);
                    tempos->inserir(buffer);
                }
            }

            //Repetir até passar por todos os vértices
            Caminho* c = tempos->remover();
            while(c->nVisitados<nVertices){
                //Verificar arestas não descobertas
                for(int i=0; i<nVertices; i++){
                    
                    //ultimo vertice descoberto não visitado
                    if(c->nVisitados == nVertices-1){
                        Caminho* novo = c->copiar();    
                        novo->inserir(c->descoberto, c->descoberto, 0);
                        tempos->inserir(novo);

                    }
                    else if(c->descoberto!=i && c->visitados[i]==0 && matriz[c->descoberto][i]!=INFINITO){
                        Caminho* novo = c->copiar();
                        novo->inserir(c->descoberto, i, matriz[c->descoberto][i]);
                        tempos->inserir(novo);
                    }
                }
                c = tempos->remover();
cout << "soma: " << c->soma << endl;
            }

            return c;
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

            Caminho* melhor = testarCaminhos(k);

            for(int i=0; i<melhor->teles; i++){
                melhor->remover();
            }

            return melhor->soma;
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
