/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS09

Análise:
         
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
        
        
        //mostrar quantidade
 //       cout << max[quantidade] << endl;
        
        //ler próxima entrada
        cin >> linhas;
        cin >> colunas;
        cin >> quantidade;
    }

    cout << distancia(1, 1, 2, 2) << endl;
    cout << distancia(1, 7, 8, 2) << endl;
    cout << distancia(4, 2, 2, 9) << endl;
    cout << distancia(1, 10, 2, 5) << endl;
    cout << distancia(9, 1, 8, 3) << endl;
    cout << distancia(5, 7, 3, 8) << endl;

    //return
    return 0;   
}  
