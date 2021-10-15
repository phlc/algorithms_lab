/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS09

Análise:
         O algoritmo parte da posição inicial do Rafael, com 0 maçãs e a cada nova maçã a memória com os melhores
         resultados das maçãs anteriores são reavaliados para verificar se a nova maça entre ou não no resultado.
         A verificação é feita dentro do "for" duplo, sendo o externo de 1 -> quantidade de maçãs e o interno de 
         (i-1) -> 0. Ou seja, na primeira iteração do "for" externo, o interno é chamado 1 vez, na segunda 2, ...,
         na enésima vez, "n" vezes, sendo "n" a quantidade de maçãs, totalizando aproximadamente (n*(n-1)/2).
         Assim, o algoritmo tem complexidade O(n^2), sendo "n" a quantidade de maçãs.
*/


//Dependencias
#include <iostream>

//Namespace
using namespace std;

/*
distancia - calcula a distancia entre dois pontos na matriz
@param int x1, y1, x2, y2
@return int dist
*/
int distancia(int x1, int y1, int x2, int y2){
    int dist = 0;

    //ate que 
    while(x1!=x2 || y1!=y2){
        if(x1<x2)
            x1++;
        else if(x2<x1)
            x2++;
        
        if(y1<y2)
            y1++;
        else if(y2<y1)
            y2++;

        dist++;
    }

    return dist;
}


/*
Main
*/
int main(){
    //Declaracoes
    int linhas, colunas, quantidade;

    //ler primeira linha de entrada
    cin >> linhas;
    cin >> colunas;
    cin >> quantidade;

    //repetir até entrada com 0s
    while(linhas || colunas || quantidade){
        //Declaracoes
        int x[quantidade+1]; //x[0] -> linha da posição inicial Rafael. x[i] -> linha da maçã i, i>0.
        int y[quantidade+1]; //y[0] -> coluna da posição inicial Rafael. y[i] -> coluna da maçã i, i>0.
        int t[quantidade+1]; //t[0] -> tempo 0 Rafael. t[i] -> tempo da maçã i, i>0.
        int max[quantidade+1]; //max[i] -> maximo possivel de maçãs coletadas após lançamento maçã i
        int resposta = 0;

        //inicializar max[0]
        max[0] = 0;

        //preencher posição e tempo das maçãs e inicializar max[]
        for(int i=1; i<=quantidade; i++){
            cin >> x[i];
            cin >> y[i]; 
            cin >> t[i];
            max[i] = 0;
        }

        
        //inicializar posição inicial de Rafael no tempo 0
        cin >> x[0];
        cin >> y[0];
        t[0] = 0;
        
        //passar por todas maças em ordem de tempo
        for(int i=1; i<=quantidade; i++){
            int maior, xMaior, yMaior, tMaior;

            //inicializar com base em t=0
            maior = 0;
            xMaior = x[0];
            yMaior = y[0];
            tMaior = 0;

            //verificar qual memória pretérita alcançável é maior
            for(int j=i-1; j>=0; j--){
                //verificar se a posicao i é alcançável pela posição j
                if((t[i]-t[j]) - distancia(x[i],y[i], x[j],y[j]) >= 0){
                    //se maçã i, faz parte da solução
                    if(maior < max[j]+1){
                        maior = max[j]+1;
                        xMaior = x[i];
                        yMaior = y[i];
                        tMaior = t[i];
                    }
                }
                
            }
            //atualizar memória do momento i para melhor opção
            max[i] = maior;
            x[i] = xMaior;
            y[i] = yMaior;
            t[i] = tMaior;

            //atualizar resposta
            if(resposta < maior){
                resposta = maior;
            }
        }


        //mostrar quantidade
        cout << resposta << endl;
        
        //ler próxima entrada
        cin >> linhas;
        cin >> colunas;
        cin >> quantidade;
    }

    //return
    return 0;   
}  
