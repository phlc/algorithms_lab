/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS03

Análise:
    
*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;


/*
hasSubsequence - Verifica se determinado string t é uma subsequencia da string s
@param string s, substring t
@return bool
*/
bool hasSubsequence(string s, string t){
    //declarações
    bool found = false;
    int i, j;

    //inicialização
    i = j = 0;

    //percorrer s
    while (!found && i<s.length()){
        if(s[i]==t[j])
            j++;
        if(j==t.length())
            found = true;        
        i++;
    }

    //return
    return found;
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
        cin >> caso;
        cin >> nQueries;
        for(int j=0; j<nQueries; j++){
            cin >> querie;
            if(hasSubsequence(caso, querie))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    } 


    return 0;   
}  
