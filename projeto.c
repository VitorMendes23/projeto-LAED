#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10

// Defines
typedef int TipoChave;

typedef struct
{
  int Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct
{
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */
// Ordena entrada
int contaQuantidade(int *p, int quantidade);
void preencheMatriz(int *p, int quantidade, int **matriz, int quantColunas);
void imprimeMatriz(int **matriz, int quantColunas);
void mergeSort(int *vetor, int quantidade);
int eliminaRepetidosSequenciais(int *vetor, int quantidade);

// Lista
void FLVazia(TipoLista *Lista);
int Vazia(TipoLista Lista);
void Insere(TipoItem x, TipoLista *Lista);
void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);
void Imprime(TipoLista Lista);

/* ========================================================================= */

/* ========================================================================== */
/*
int main(int argc, char *argv[])
{ struct timeval t;

  TipoLista lista;
  TipoItem item;
  int vetor[MAX];
  TipoApontador p;
  int i, j, k, n;
  float  tamanho=0;
  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  FLVazia(&lista);


  //Gera uma permutacao aleatoria de chaves entre 1 e MAX
  for(i = 0; i < MAX; i++) vetor[i] = i + 1;
  for(i = 0; i < MAX; i++)
    { k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      n = vetor[k];
      vetor[k] = vetor[j];
      vetor[j] = n;
    }
  //Insere cada chave na lista
  for (i = 0; i < MAX; i++)
    { item.Chave = vetor[i];
      Insere(item, &lista);
      tamanho++;
      printf("Inseriu: %d \n", item.Chave);
    }
  Imprime(lista);

  //Retira cada chave da lista
  for(i = 0; i < MAX; i++)
    { //escolhe uma chave aleatoriamente
      k = (int) ((tamanho) * rand() / (RAND_MAX + 1.0));
      p = lista.Primeiro;
      //retira chave apontada
      Retira(p, &lista, &item);
      tamanho--;
      printf("Retirou: %d\n", item.Chave);
    }
  Imprime (lista);
  return(0);
}*/

// Chave, Tipo, NumElementos e PontoMedio
//

// MAIN - Análise de segmentos com elementos iguais
int main(void)
{

  int quantidade;
  scanf("%d", &quantidade);

  int *p;
  p = (int *)malloc(sizeof(int) * quantidade);
  for (int i = 0; i < quantidade; i++)
  {
    scanf("%d", &p[i]);
  }

  int quantColunas = contaQuantidade(p, quantidade);

  // Criando a matriz
  int **matriz;
  matriz = (int **)malloc(2 * sizeof(int *));
  for (int i = 0; i < 2; i++)
  {
    matriz[i] = (int *)malloc(quantColunas * sizeof(int));
    for (int j = 0; j < quantColunas; j++)
    {
      matriz[i][j] = 0;
    }
  }

  preencheMatriz(p, quantidade, matriz, quantColunas);
  imprimeMatriz(matriz, quantColunas);
}

int contaQuantidade(int *p, int quantidade)
{

  int quant = 0;
  int anterior = -1;
  for (int i = 0; i < quantidade; i++)
  {
    if (p[i] != anterior)
    {
      anterior = p[i];
      quant++;
    }
  }

  return quant;
}

void preencheMatriz(int *p, int quantidade, int **matriz, int quantColunas)
{

  int anterior = p[0];
  int quant = 0;
  int contrMatriz = 0;
  int contrVetor = 0;

  int *copiap;

  copiap = (int *)malloc(sizeof(int) * quantidade);
  for (int i = 0; i < quantidade; i++)
  {
    copiap[i] = p[i];
  }

  mergeSort(copiap, quantidade);
  eliminaRepetidosSequenciais(copiap, quantidade);

  while (1)
  {
    int i = 0;
    while (1)
    {
      if (p[contrVetor] == copiap[i])
      {
        switch (p[contrVetor])
        {
        case 0:
          matriz[0][contrMatriz] = 0;
          break;
        case 128:
          matriz[0][contrMatriz] = 1;
          break;
        case 255:
          matriz[0][contrMatriz] = 2;
          break;
        }
        break;
      }
      i++;
    }

    while (p[contrVetor] == anterior)
    {
      quant++;
      contrVetor++;
      if (contrVetor > quantidade)
      {
        contrVetor--;
        if (p[contrVetor] == 0)
          quant--;
        matriz[1][contrMatriz] = quant;
        return;
      }
    }
    anterior = p[contrVetor];
    matriz[1][contrMatriz] = quant;
    quant = 0;
    contrMatriz++;
  }
}

void imprimeMatriz(int **matriz, int quantColunas)
{
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < quantColunas; i++)
    {
      printf("%d", matriz[j][i]);
      if (i != quantColunas - 1)
        printf(" ");
    }
    printf("\n");
  }
}

void mergeSort(int *vetor, int quantidade)
{
  for (int i = 0; i < quantidade; i++)
  {
    for (int j = 0; j < quantidade; j++)
    {
      if (vetor[i] < vetor[j])
      {
        int intermediario = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = intermediario;
      }
    }
  }
}

int eliminaRepetidosSequenciais(int *vetor, int quantidade)
{
  int quantidadeFinal = 1;

  for (int i = 1; i < quantidade; i++)
  {
    if (vetor[i - 1] != vetor[i])
    {
      vetor[quantidadeFinal] = vetor[i];
      quantidadeFinal++;
    }
  }
  return quantidadeFinal;
}

void FLVazia(TipoLista *Lista)
{
  Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  {
    printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p->Prox;
  *Item = q->Item;
  p->Prox = q->Prox;
  if (p->Prox == NULL)
    Lista->Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{
  TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
  {
    printf("%d\n", Aux->Item.Chave);
    Aux = Aux->Prox;
  }
}