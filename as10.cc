/*
Pucminas - Ciência da Computação - Coração Eucarístico
LPA G1 - Segunda - Manhã
Nome: Pedro Henrique Lima Carvalho
Matricula: 651230

AS10

Análise:
        Opta-se em trabalhar com int ao invés de double para melhorar a performace e não ter problema com precisão.
        Para isso trabalha-se com duas casas deslocadas. Ex: double 12.34 = int 1234.
        O algoritmo realiza 11 divisões e 11 operações de módulo até chegar em valores entre 0-4 (0.00 - 0.004). 
        Então, realiza no máximo 5 testes (4 3 2 1 0) e 4 subtrações (4-1, 3-1, 2-1, 1-1).
        Assim, na pior hipótese o algoritmo tem um número constante de operações, tendo complexidade O(1).

*/


//Dependencias
#include <iostream>

//Namespace
using namespace std;


/*
Main
*/
int main(){
    //Declaracoes
    int n100, n50, n20, n10, n5, n2; //notas
    int m100, m50, m25, m10, m5, m1; //moedas
    double entrada;
    int valor;

    //inicializar
    m1=0;

    //ler entrada
    cin >> entrada;
    
    //transformar entrada doube xx.xx para int xxxx
    valor = (int)(entrada*100.00);

    //Calcular decomposição

    //R$100,00
    n100 = valor/10000;
    valor = valor%10000;

    //R$50,00
    n50 = valor/5000;
    valor = valor%5000;

    //R$20,00
    n20 = valor/2000;
    valor = valor%2000;

    //R$10,00
    n10 = valor/1000;
    valor = valor%1000;

    //R$5,00
    n5 = valor/500;
    valor = valor%500;

    //R$2,00
    n2 = valor/200;
    valor = valor%200;

    //R$1,00
    m100 = valor/100;
    valor = valor%100;

    //R$0,50
    m50 = valor/50;
    valor = valor%50;

    //R$0,25
    m25 = valor/25;
    valor = valor%25;

    //R$0,10
    m10 = valor/10;
    valor = valor%10;

    //R$0,05
    m5 = valor/5;
    valor = valor%5;

    //R$0.01
    while(valor>0){
        valor = valor -1;
        m1++;
    }

   

    //mostrar resultado
    cout << "NOTAS:" << endl;
    cout << n100 << " nota(s) de R$ 100.00" << endl;
    cout << n50  << " nota(s) de R$ 50.00"  << endl;
    cout << n20  << " nota(s) de R$ 20.00"  << endl;
    cout << n10  << " nota(s) de R$ 10.00"  << endl;
    cout << n5   << " nota(s) de R$ 5.00"   << endl;
    cout << n2   << " nota(s) de R$ 2.00"   << endl;

    cout << "MOEDAS:" << endl;
    cout << m100 << " moeda(s) de R$ 1.00" << endl;
    cout << m50  << " moeda(s) de R$ 0.50" << endl;
    cout << m25  << " moeda(s) de R$ 0.25" << endl;
    cout << m10  << " moeda(s) de R$ 0.10" << endl;
    cout << m5   << " moeda(s) de R$ 0.05" << endl;
    cout << m1   << " moeda(s) de R$ 0.01" << endl;

    //return
    return 0;   
}  
