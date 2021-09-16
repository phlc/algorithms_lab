/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS06

Análise:
        Operação de maior custo do algoritimo é O(n^3), sendo n o número de vértices. É realizada pelo
        método menorCaminho(), que altera o grafo para constar uma aresta entre quaisquer dois pares
        de vértices. Se há componentes desconexos, a aresta criada entre um componente e outro recebe o 
        valor de INFINITO. Há vários outros métodos da ordem de O(n^2) e O(n), mas que não alteram a 
        complexidade do algoritimo.
        
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
    #define INFINITO 1000000 // peso máximo da aresta válida é 30000

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
            int menor = INFINITO;
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
        melhorInicio - Em um componente sem vértice de início pré-determinado, escolher o que gera menor tempo
        @param int c, int* comp -> número do componente, arranjo com o controle de vertices/componente
        @return int v -> melhor vértice de início
        */
        int melhorInicio(int c, int* comp){
            int v = -1;
            int tempo = INFINITO;
            int atual = -1;
            int proximo = -1;


            //testar todos os vértices do componente
            for(int i=0; i<nVertices; i++){
                int t = 0;
                if(comp[i] == c){            
                    int visit[nVertices]; //controle vértices visitados local
                    //inicialização
                    for(int j=0; j<nVertices; j++){
                        visit[j] = 0;
                    }
                    atual = i;
                    visit[atual] = 1;
                    proximo = melhorOpcao(i, visit);
                    while(atual != proximo){

                        t+= matriz[atual][proximo]; //armazenar tempo melhor caminho
                        visit[proximo]=1; //marcar próximo vértice como visitado
                        atual = proximo;
                        proximo = melhorOpcao(atual, visit);
                    }
                    //se t melhor que tempo
                    if(t<tempo){
                        tempo = t;
                        v = i;
                    }
                }
            }
            return v;
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
            int proximo = 0;
            int nComponentes = 0;
            int nCaminhamentos = 0;
            int visitados[nVertices]; //controle vértices visitados
            int componentes[nVertices]; //controle componentes desconexos
            int tempos[nVertices-1];

            //inicialização
            visitados[0] = 1;
            componentes[0] = -1; 
            for(int i=1; i<nVertices; i++){
                visitados[i] = 0;
                componentes[i] = -1;
                tempos[i-1] = 0;
            }

            //alterar grafo para menor caminho entre quaisquer dos dois vértices
            this->menorCaminho();

            //calcular número de componentes
            nComponentes = calcularComponentes(componentes);
            //verificar se número de teletransportes é suficiente para passsar por todos os componentes
            if(k < nComponentes-1){
                return -1;
            }
            else{
                k = k -nComponentes +1; //descontar os teletransportes necessários para pular entre componentes
                nCaminhamentos = nCaminhamentos +nComponentes -1; //considerar os teletransportes como caminhamentos
            }

            //criar vetor como o número de vértices de cada componente
            int verticesPorComponente[nComponentes];
            for(int i=0; i<nComponentes; i++){
                verticesPorComponente[i] = 0;
                for(int j=0; j<nVertices; j++){
                    if(componentes[j] == i){
                        verticesPorComponente[i]++;
                    }
                }
            }

            //verificar melhor caminho dentro da componente 0 (vértice inicial pré-determinado)
            proximo = melhorOpcao(atual, visitados);
            while(atual != proximo){
                tempos[nCaminhamentos] = matriz[atual][proximo]; //armazenar tempo melhor caminho
                
                visitados[proximo]=1; //marcar próximo vértice como visitado
                atual = proximo;
                nCaminhamentos++; 
                proximo = melhorOpcao(atual, visitados);
            }

            //passar pelas demais componentes
            for(int i=0; i<nComponentes; i++){
                //verificar melhor vertice de inicio
                atual = melhorInicio(i, componentes);
                visitados[atual]=1;
                //verificar melhor caminho dentro da componente 0 (vértice inicial pré-determinado)
                proximo = melhorOpcao(atual, visitados);
                while(atual != proximo){
                    tempos[nCaminhamentos] = matriz[atual][proximo]; //armazenar tempo melhor caminho
                    visitados[proximo]=1; //marcar próximo vértice como visitado
                    atual = proximo;
                    nCaminhamentos++; 
                    proximo = melhorOpcao(atual, visitados);
                }
            }
            //ordenar tempos de caminhamentos
            for(int i=1; i<nVertices-1; i++){
                int j=i-1;
                while(j>=0 && tempos[j+1]<tempos[j]){
                    int buffer = tempos[j+1];
                    tempos[j+1] = tempos[j];
                    tempos[j] = buffer;
                    j--;
                }
            }

            for(int i=0; i<nVertices-1-k; i++){
                t+=tempos[i];
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
