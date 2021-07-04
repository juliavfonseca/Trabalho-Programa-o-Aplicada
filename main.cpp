#include <iostream>
#include <fstream>

using namespace std;

struct tComplexos{
  float real;
  float imag;
};

struct tNo{
  tComplexos equacao;
  tNo* proximo;
};

tNo* criaNo(float parteReal, float parteImaginaria){
  tNo*no = new tNo;
  no->equacao.real = parteReal;
  no->equacao.imag = parteImaginaria;
  no->proximo = NULL;
  return no;
}

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho;
};

void inicializaLista(tLista* pLista){
  pLista->primeiro = NULL;
  pLista -> ultimo = NULL;
  pLista->marcador = NULL;
  pLista->tamanho = 0;
}

int obterTamanho(tLista* pLista){
  return pLista->tamanho;
}

bool listaVazia(tLista* pLista){
  return (pLista->tamanho == 0);
}

bool finalLista(tLista* pLista){
  return (pLista->marcador == NULL);
}

void incluirNoFim(tLista* pLista, float parteReal, float parteImaginaria){
  tNo* no;
  no = criaNo( parteReal, parteImaginaria );

  if(listaVazia(pLista)){
    pLista->primeiro = no;
  }
  else{
    pLista->ultimo->proximo = no;
  }

  pLista->ultimo = no;
  pLista->marcador = no;
  pLista->tamanho++;
}

void imprimirLista(tLista* pLista){
  pLista->marcador = pLista->primeiro;

  while(!finalLista(pLista)){
    float real = pLista->marcador->equacao.real;
    float imag = pLista->marcador->equacao.imag;
    if(imag < 0)
      cout << "Z = " << real << " " << imag << "i" << endl;
    else      
      cout << "Z = " << real << " + " << imag << "i" << endl;
    pLista->marcador = pLista->marcador->proximo;
  }
}

void excluirPosicao(tLista* pLista, int pos){
  tNo* anterior;
  tNo* aux;
  tNo* apagado;

  if(!listaVazia(pLista)){
    pLista->marcador = pLista->primeiro;

    if(pos < obterTamanho(pLista)){
      pLista->primeiro = pLista->marcador->proximo;
    }
    else{
      for(int i = 0; i < pos; i++){
        anterior = pLista->marcador;
        pLista->marcador = pLista->marcador->proximo;
        aux = pLista->marcador->proximo;
      }
      anterior->proximo = aux;
    }
    apagado = pLista->marcador;
    free(apagado);
  }
}

bool gravarNumerosComplexos(tLista* pLista){

  ofstream arqComplexosSaida("arquivo.txt");
  float r, i;

  if(arqComplexosSaida.is_open()){
    pLista->marcador = pLista->primeiro;

    while(!finalLista(pLista)){
      r = pLista->marcador->equacao.real;
      i = pLista->marcador->equacao.imag;
      arqComplexosSaida << r << " " << i << endl;
      pLista->marcador = pLista->marcador->proximo;
    }

    arqComplexosSaida.close();
    return true;
    
  }else{
    return false;
  }
}

int main() {

  tLista* numerosComplexos = new tLista;

  inicializaLista(numerosComplexos);

  int opcao, N, contador;
  float r, i;
  ifstream arqComplexos;

  cout << "O tamanho da lista eh: " << obterTamanho(numerosComplexos) << endl << endl;  

  opcao = 1;

  while(opcao < 3){

    cout << "Opcoes a escolher:" << endl;
    cout << "1-Ler dados" << endl;
    cout << "2-Gravar dados" << endl;
    cout << "3-Encerrar" << endl;
    cout << "Op.: ";
    cin >> opcao;

    switch(opcao){

      case 1: cout << "\nEquacoes:" << endl << endl;
              
              arqComplexos.open("arquivo.txt");

              while(!arqComplexos.eof()){
                arqComplexos >> r >> i;
                incluirNoFim( numerosComplexos, r, i );
              }

              imprimirLista(numerosComplexos);
              arqComplexos.close();
              cout << "\n";
              
              break;
      
      case 2: cout << "\nQuer gravar quantos numeros complexos? ";
              cin >> N;
              
              for (contador=0; contador<N; contador++){
                cout << "\nDigite a parte real da equacao: ";
                cin >> r;
                cout << "Digite a parte imaginaria da equacao (sem o i): ";
                cin >> i;
                incluirNoFim( numerosComplexos, r, i );
              }
              
              cout << "\nGravando dados: ";
             
              bool retorno = gravarNumerosComplexos(numerosComplexos);
              
              if(retorno == true){
                cout << "Ok!" << endl << endl;
              }else{
                cout << "*Erro*" << endl << endl;
              }

              break;

    }

  }

}