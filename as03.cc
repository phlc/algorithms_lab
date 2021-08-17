/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS03

Análise:
        Considerando a complexidade de cada querie de forma independente, a função hasSubsequence,
        realiza dentro de seu loop, duas comparações, uma comparando as letras das duas strings, e
        uma verificando se todas as letras da string da querie foram encontradas.
        Sendo n o número de letras da string caso, na pior hipótese, quando a string querie não for
        subsequencia, a função realizará 2*n comparações. Assim, o algoritmo tem complexidade O(n).
*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;


/*
hasSubsequence - Verifica se determinada string t é uma subsequencia da string s
@param string s, substring t
@return bool
*/
bool hasSubsequence(string s, string t){
    //declarações
    int i, j;

    //inicialização
    i = j = 0;

    //percorrer s
    while (i<s.length()){
        //somente passa para a próxima letra de t se a letra atual for encontrada em s 
        if(s[i]==t[j])
            j++;

        //todas letras foram encontradas
        if(j==t.length())
            return true;  

        i++;
    }

    //return
    return false;
}
/*
Main
*/
int main(){
    //Declaracoes
    int nCasos, nQueries;
    string caso, querie;

    //ler número de casos
    cin >> nCasos;

    //testar cada caso
    for(int i=0; i<nCasos; i++){
        //ler caso e número de queries
        cin >> caso;
        cin >> nQueries;

        //realizar todas as queries
        for(int j=0; j<nQueries; j++){
            //ler querie
            cin >> querie;

            //verificar se é subsequencia
            if(hasSubsequence(caso, querie))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    } 

    //return
    return 0;   
}  
