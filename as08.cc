/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS08

Análise:
         
        
*/
//Macros
#define MAX 0x7ffffff

//Dependencias
#include <iostream>

//Namespace
using namespace std;

/*
mergeSort - Método de ordenamento usando merge sort
@param int arr[], int i, int j, int& cont -> int[] a ordenar, índice esquerda, índice direita, contagem movimentacoes
@return int* -> arranjo ordenado
*/
int* mergeSort(int arr[], int i, int j, int& cont){
    //Declaracoes
    int tamanho = j-i +2;
    int* resultado = new int[tamanho];

    //Sentinela
    resultado[tamanho-1] = MAX;

    //Caso base - Arranjo de um elemento
    if(i == j){
        resultado[0] = arr[i];
    }
    else{
        //Declaracoes
        int* esq;
        int* dir;
        int k = (j+i)/2;

        //Chamada recursiva
        esq = mergeSort(arr, i, k, cont);
        dir = mergeSort(arr, k+1, j, cont);

        //Merge
        int i_esq = 0; //indice esquerda
        int i_dir = 0; //indice direita

        for(int i_resultado = 0; i_resultado<tamanho-1; i_resultado++){
            if(esq[i_esq] > dir[i_dir]){
                resultado[i_resultado] = dir[i_dir];
                i_dir++;
                cont += k-i+1-i_esq; //quantos movimetacoes dir[i_dir] fez
            }
            else{
                resultado[i_resultado] = esq[i_esq];
                i_esq++;
            }
        }

        //liberar memória
        delete esq;
        delete dir;
    }

    //return
    return resultado;
}


/*
Main
*/
int main(){
    //Declaracoes
    int tamanho;

    //ler número de casos
    cin >> tamanho;

    //ler até tamanho == 0
    while(tamanho){
        //Declaracoes
        int arranjo[tamanho];
        int movimentos = 0;

        //preencher arranjo
        for(int i=0; i<tamanho; i++){
            cin >> arranjo[i];
        }

        delete mergeSort(arranjo, 0, tamanho-1, movimentos);

        //mostrar resposta
        if(movimentos%2==0){
            cout << "Carlos" << endl;
        }
        else{
            cout << "Marcelo" << endl;
        }

        //ler próxima etapa
        cin >> tamanho;
    }

    //return
    return 0;   
}  
