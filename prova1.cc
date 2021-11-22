/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

Prova Intermediária

Análise:
        Considerando a complexidade de cada instancia de forma independente, a função vencedor(),
        realiza apenas um loop, do tamanho das strings, fazendo assim, n iterações, sendo n o tamanho da 
        string referencia.
        Dentro de cada loop, testa-se, no pior caso, 4 vezes (n*4). O loop testa n+1 vezes. 
        Por fim, no final, para apuração do resultado e composição da string resultado,
        faz-se, no pior caso, outros 4 testes. Totalizando n*5 + 5 testes.
        Portanto, o algoritmo tem complexidade O(n).
*/

//Dependencias
#include <iostream>

//Namespace
using namespace std;


/*
vencedor - Compara a string referencia com as strings time1 e time2
@param string referencia, string time1, string time2
@return string contendo o time vencedor ou empate
*/
string vencedor(string referencia, string time1, string time2){
    //declarações
    int rodadaErro1, rodadaErro2, errosTime1, errosTime2, tamanho;
    string resultado;

    //inicialização
    errosTime1 = errosTime2 = 0;
    rodadaErro1 = rodadaErro2 = -1;
    tamanho = referencia.length();

    //percorrer as strings
    for (int i=0; i<tamanho; i++){
  
        //testar resposta do time 1 
        if(referencia[i]!=time1[i]){
            errosTime1++;

            //controlar rodada do primeiro erro
            if(rodadaErro1 == -1){
                rodadaErro1 = i;
            }
        }

        //testar resposta do time 2 
        if(referencia[i]!=time2[i]){
            errosTime2++;

            //controlar rodada do primeiro erro
            if(rodadaErro2 == -1){
                rodadaErro2 = i;
            }
        }
    }

    //apurar resulado
    if(errosTime1 > errosTime2){
        resultado = "time 2";
    }
    else if(errosTime2 > errosTime1){
        resultado = "time 1";
    }
    else{
        //caso empate verificar primeiro erro
        if(rodadaErro1 > rodadaErro2){
            resultado = "time 1";
        }
        else if(rodadaErro2 > rodadaErro1){
            resultado = "time 2";
        }
        else{
            resultado = "empate";
        }
    }

    //return
    return resultado;
}


/*
Main
*/
int main(){
    //Declaracoes
    int nEntradas;
    string correta, equipe1, equipe2;

    //ler número de casos
    cin >> nEntradas;
    
    //consumir o \n remanescente
    getline(cin, correta);

    //testar cada caso
    for(int i=1; i<nEntradas; i++){
        //ler frase correta e de cada equipe
        getline(cin, correta);
        getline(cin, equipe1);
        getline(cin, equipe2);

        //calcular e mostrar vencedor
        cout << "Instancia " << i << endl;
        cout << vencedor(correta, equipe1, equipe2) << endl;
        cout << endl;
    } 

    //testar última instância fora do loop para não gerar uma quebra de linha extra
    //ler frase correta e de cada equipe
    getline(cin, correta);
    getline(cin, equipe1);
    getline(cin, equipe2);

    //calcular e mostrar vencedor
    cout << "Instancia " << nEntradas << endl;
    cout << vencedor(correta, equipe1, equipe2) << endl;

    //return
    return 0;   
}  
