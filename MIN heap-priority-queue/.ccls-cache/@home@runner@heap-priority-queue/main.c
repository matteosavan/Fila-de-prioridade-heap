#include <stdio.h>
typedef int T;
#define qtdd_MAX_elementos 15

struct fila_de_prioridade_heap {
  T vetor[qtdd_MAX_elementos];
  int i_ultimo_elemento_vazio;
};

typedef struct fila_de_prioridade_heap fila_prioridade;

void inicializar_fila_de_prioridade_heap(fila_prioridade *fila){
  fila->i_ultimo_elemento_vazio = 0;
}

int i_pai(int indice_filho){
  if(((indice_filho-1)/2)<0)printf("PROBL");
  return (indice_filho-1)/2;
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
  if (i_novo_elemento==0)return; //caso base
  int i_elemento_pai = i_pai(i_novo_elemento);
  
  if (vetor[i_novo_elemento]<vetor[i_elemento_pai]){
    swap(i_novo_elemento,i_elemento_pai, vetor);
    if(i_elemento_pai!=0)return consertar_fixUp(i_elemento_pai,  vetor);
  }
    
  else return;
}

void adicionar_a_heap(T elemento, fila_prioridade *fila){
  fila->vetor[fila->i_ultimo_elemento_vazio] = elemento;

  if ((fila->i_ultimo_elemento_vazio) ==0){ //caso o vetor esteja vazio
    (fila->i_ultimo_elemento_vazio)++;
    return;
  }
  
  else {
    consertar_fixUp(fila->i_ultimo_elemento_vazio, fila->vetor);
  
    (fila->i_ultimo_elemento_vazio)++;
  }
}

int menor_entre(T vetor[], int i_pai, int i_ultimo_elemento){
  int pai, filho_1, filho_2;
  int filho_1_ok=0, filho_2_ok=0;
  pai = vetor[i_pai];
  int i_filho_1=i_pai*2+1, i_filho_2=i_pai*2+2;

  if((i_filho_1)>i_ultimo_elemento){//caso o filho esteja fora do vetor
  
    return i_pai; 
  }
  
  if(i_ultimo_elemento>=(i_filho_1)){
    filho_1 = vetor[i_filho_1];
    filho_1_ok = 1;
  }
  
  if(i_ultimo_elemento>=(i_filho_2)){
    filho_2 = vetor[i_filho_2];
    filho_2_ok = 1;
  }

  //caso só tivermos o pai já foi coberto

  //caso tenhamos o filho 1 e o filho 2:
  if(filho_1_ok && filho_2_ok){
    if (pai<= filho_1 && pai<= filho_2){
      return pai;
    }
    else {
      if (filho_1<=filho_2){
        return i_filho_1;
      }
      else{
        return i_filho_2;
      }
    }
  }

  //caso temos o pai e o filho 1:
  if (filho_1_ok){
    if (pai<=filho_1){
      return i_pai;
    }
    else return i_filho_1;
  }

  //caso temos só o filho 2:
  if (filho_2_ok){
    if (pai<=filho_2)return pai;
    else return i_filho_2;
  }
  
}

void consertar_fixDown(T vetor[], int i_pai, int i_ultimo_elemento){
  int indice_menor_entre_pai_e_filhos = menor_entre(vetor, i_pai, i_ultimo_elemento);

  if (indice_menor_entre_pai_e_filhos==i_pai)return;
  else{
    swap(indice_menor_entre_pai_e_filhos, i_pai, vetor);
    return consertar_fixDown(vetor, indice_menor_entre_pai_e_filhos, i_ultimo_elemento);
  }
}

T remover_menor_da_heap (fila_prioridade *fila){
  if (fila->i_ultimo_elemento_vazio==0)return 0; //caso vazia
  T menor = fila->vetor[0];
  (fila->i_ultimo_elemento_vazio)--;
  int indice_ultimo_elemento = (fila->i_ultimo_elemento_vazio);

  fila->vetor[0] = fila->vetor[indice_ultimo_elemento];

  consertar_fixDown(fila->vetor, 0, indice_ultimo_elemento-1);    
  
  return menor;
}

int main(void) {
  fila_prioridade fila;
  inicializar_fila_de_prioridade_heap(&fila);

  int a;
  
  a = remover_menor_da_heap(&fila);
  printar_vetor(fila.vetor, fila.i_ultimo_elemento_vazio);
  printf("o elemento removido foi %d\no indice do ultimo elemento vazio é: %d\n\n", a, fila.i_ultimo_elemento_vazio);

  adicionar_a_heap(8, &fila);
  adicionar_a_heap(5, &fila);
  adicionar_a_heap(7, &fila);
  adicionar_a_heap(2, &fila);
  printar_vetor(fila.vetor, fila.i_ultimo_elemento_vazio);
  printf("o indice do ultimo elemento vazio é: %d\n\n", fila.i_ultimo_elemento_vazio);

  a = remover_menor_da_heap(&fila);
  printar_vetor(fila.vetor, fila.i_ultimo_elemento_vazio);
  printf("o elemento removido foi %d\no indice do ultimo elemento vazio é: %d\n", a, fila.i_ultimo_elemento_vazio);

  a = remover_menor_da_heap(&fila);
  printar_vetor(fila.vetor, fila.i_ultimo_elemento_vazio);
  printf("o elemento removido foi %d\no indice do ultimo elemento vazio é: %d\n", a, fila.i_ultimo_elemento_vazio);
  

  return 0;
}