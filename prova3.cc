/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

Prova 3

Análise:
        O problema pode ser reduzido ao problema NP-completo da soma dos subconjuntos. Ou seja, verificar se
        é possivel obter um numero k, com a soma de quaisquer elementos de um conjunto.
        No caso, o numero de pontes chegando em uma determinada regiao seria um elemento, e o conjunto seria 
        composto pelos numero de pontes chegando em cada regiao.
        Utilizando uma matriz [r+1]x[k+1], sendo r o numero de elementos do conjunto e k a soma a ser obtida, 
        podemos verificar se é possível somar elementos == k utilizando programacao dinamica em tempo pseudo-
        polinomial.
        O codigo tem dois "for", um dentro do outro, sendo que o externo repete r vezes e o interno k vezes.
        Assim, a complexidade do codigo é O(r*k), sendo r o numero de regioes do problema e k o valor da soma
        a ser obtida.
*/

//Dependencias
#include <iostream>
#include <iomanip>

//Namespace
using namespace std;


/*
somaPossivel - verifica se é possivel obter "k" somando os numeros de qualquer subconjunto de "arr" com "r" elementos
@param arr[r], int r, k -> conjunto dos elementos, numero de elementos, soma desejada
@return bool 
*/
bool somaPossivel(int arr[], int r, int k){
    //criar uma matriz [r+1] por [k+1]
    //assim as linhas terão os valores de arr e as colunas as somas possiveis ate k
    bool mat[r+1][k+1];

    //inicializar a primeira coluna, da soma = 0 para Verdadeiro
    //sempre possivel soma = 0 -> conjunto vazio
    for(int i=0; i<=r; i++){
        mat[i][0] = true;
    }

    //inicializar a primeira linha, salvo [0][0] para falso
    //se a soma nao é 0 e nao utiliza o conjunto vazio é falso
    for(int i=1; i<=k; i++){
        mat[0][i] = false;
    }

    //preencher matriz verificando apos a inclusao de cada elemento
    //se e possivel chegar a determinada soma ate k
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= k; j++) {
            //se a soma a ser obtida for menor que o valor a ser considerado
            //copia o valor de cima (acumla o valor)
            if (j < arr[i]){
                mat[i][j] = mat[i-1][j];
            }

            //se a soma a ser obtida for maior ou igual ao valor considerado
            //o resultado sera igual ao de cima OU de cima - valor
            if (j >= arr[i])
                mat[i][j] = mat[i - 1][j] || mat[i - 1][j - arr[i]];
        }
    }

    return mat[r][k];
}


/*
Main
*/
int main(){
    //Declarações Iniciais
    int r, k;

    //Ler numero de regioes e pontes
    cin >> r;
    cin >> k;
   
    //repetir até EOF
    while(!cin.eof()){
        //criar um arranjo com r+1 posicoes
        int arr[r+1];

        //inicializar arranjo
        for(int i=0; i<=r; i++){
            arr[i] = 0;
        }

        //ler pontes e somar 1 em cada regiao ligada pela ponte
        for(int i=0; i<k; i++){
            //declaracoes locais
            int r1, r2;

            //ler regioes ligadas pelas pontes
            cin >> r1;
            cin >> r2;

            //somar no arranho numero de pontes em cada regiao
            arr[r1]++;
            arr[r2]++;

            
        }

        if(somaPossivel(arr, r, k))
            cout << "S" << endl;
        else
            cout << "N" << endl;

        //Ler proxima entrada
        cin >> r;
        cin >> k;

    }


    //return
    return 0;   
}  
