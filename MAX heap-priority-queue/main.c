#include <stdio.h>

//2 2 2 4 4 4 8 8 11 13 19 32 -1

/*
DESENVOLVIDO POR MATTEO C SAVAN
github: matteosavan
*/

#include <stdio.h>
#include <stdlib.h>


typedef int T;
#define qtdd_MAX_elementos 1000

struct fila_de_prioridade_heap {
  T vetor[qtdd_MAX_elementos];
  int i_ultimo_elemento_vazio;
};

typedef struct fila_de_prioridade_heap fila_prioridade;
int vazia (fila_prioridade *fila){
  return fila->i_ultimo_elemento_vazio==0;
}
void inicializar_fila_de_prioridade_heap(fila_prioridade *fila){
  fila->i_ultimo_elemento_vazio = 0;
}

int indice_pai(int i_filho){
  return (i_filho-1)/2;
}

void swap(int i_novo_elemento,int i_elemento_pai, T vetor[]){
  T aux;
  aux = vetor[i_novo_elemento];
  vetor[i_novo_elemento] = vetor[i_elemento_pai];
  vetor[i_elemento_pai] = aux;
  return;
}

void printar_vetor(T vetor[], int i_ultimo_elemento){
  for(int i=0;i<i_ultimo_elemento;i++){
    printf(" %d", vetor[i]);
  }
  printf("\n");
}

void consertar_fixUp(int i_novo_elemento, int vetor[]){
  if (i_novo_elemento==0)return; //caso base. Quando estamos verificando o primeiro nó do vetor
 
  if (vetor[indice_pai(i_novo_elemento)] < vetor[i_novo_elemento]){
    swap(i_novo_elemento, indice_pai(i_novo_elemento), vetor);
    consertar_fixUp(indice_pai(i_novo_elemento), vetor);
  }
  else return;
}

void adicionar_a_heap(T elemento, fila_prioridade *fila){
  fila->vetor[fila->i_ultimo_elemento_vazio] = elemento; //coloca o elemento no final do vetor
  if (vazia(fila)){ //caso o vetor esteja vazio
    (fila->i_ultimo_elemento_vazio)++;
    return;
  }
  else {
    consertar_fixUp(fila->i_ultimo_elemento_vazio, fila->vetor);
    (fila->i_ultimo_elemento_vazio)++;
  }
  //printar_vetor(fila->vetor, fila->i_ultimo_elemento_vazio);
}
//aqui em cima eu garanto que ta certo


int maior_entre(T vetor[], int i_pai, int i_ultimo_elemento_preenchido){
  int pai, filho_1, filho_2;
  int filho_1_ok=0, filho_2_ok=0;
  pai = vetor[i_pai];
  int i_filho_1=i_pai*2+1, i_filho_2=i_pai*2+2;

  if((i_filho_1)>i_ultimo_elemento_preenchido){//caso os filhos estejam fora do vetor
    return i_pai; //só temos o pai
  }
  
  if(i_ultimo_elemento_preenchido>=(i_filho_1)){
    filho_1 = vetor[i_filho_1];
    filho_1_ok = 1;
  }
  
  if(i_ultimo_elemento_preenchido>=(i_filho_2)){
    filho_2 = vetor[i_filho_2];
    filho_2_ok = 1;
  }

  //caso só tivermos o pai já foi coberto

  //caso tenhamos o filho 1 e o filho 2:
  if(filho_1_ok && filho_2_ok){
    if (pai>= filho_1 && pai>= filho_2){
      return i_pai;
    }
    else {
      if (filho_1>=filho_2){
        return i_filho_1;
      }
      else{
        return i_filho_2;
      }
    }
  }

  //caso temos o pai e o filho 1:
  if (filho_1_ok){
    if (pai>=filho_1){
      return i_pai;
    }
    else return i_filho_1;
  }

  //caso temos só o filho 2:
  if (filho_2_ok){
    if (pai>=filho_2)return i_pai;
    else return i_filho_2;
  }

  else{
    printf ("ERRO");
  }
}

void consertar_fixDown(fila_prioridade *fila, int i_pai, int i_ultimo_elemento_preenchido){
  
  int indice_maior_entre_pai_e_filhos = maior_entre(fila->vetor, i_pai, i_ultimo_elemento_preenchido);

  if (indice_maior_entre_pai_e_filhos==i_pai)return;
  else{
    swap(indice_maior_entre_pai_e_filhos, i_pai, fila->vetor);
    //printf("trocou pelo indice %d\n", indice_maior_entre_pai_e_filhos);
    consertar_fixDown(fila, indice_maior_entre_pai_e_filhos, i_ultimo_elemento_preenchido);
  }
}

T remover_maior_da_heap (fila_prioridade *fila){
  if (vazia(fila)){
    printf("vazia\n");
    return 0; //caso vazia
  }
  
  T maior = fila->vetor[0]; //o maior é sempre o primeiro elemento do vetor
  int indice_ultimo_elemento_preenchido = (fila->i_ultimo_elemento_vazio)-1;
  (fila->i_ultimo_elemento_vazio) = fila->i_ultimo_elemento_vazio-1;//como vamos remover o elemento então temos que decrementar o contador

  fila->vetor[0] = fila->vetor[indice_ultimo_elemento_preenchido];

  swap(0, indice_ultimo_elemento_preenchido, fila->vetor);
  
  consertar_fixDown(fila, 0, indice_ultimo_elemento_preenchido);  
  return maior;
}

int main(void) {
  //se quiser testar:
  fila_prioridade fila;
  inicializar_fila_de_prioridade_heap(&fila);
  int a;
  while(1){
    
    scanf("%d", &a);
    if (a==-1)break;
    adicionar_a_heap(a, &fila);
 
  }
  while(!vazia(&fila)){
    a = remover_maior_da_heap(&fila); 
  printf("o elemento removido foi %d\n", a);
  }

  return 0;
}}