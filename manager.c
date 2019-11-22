#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"


int numberSelected = -1;
int processMaxSize;
int memorySize;
int pageSize;
int * bitMap[];
page_t * memory;

int findFirstFit(int size){
  int pagesNeeded = (size/pageSize) + ((size%pageSize > 0)? 1:0);
	printf("Precisara de %d paginas\n", pagesNeeded);
  int count = 0;
  int result = -1;
  for(int i; i < memorySize/pageSize; i++){
    printf("index %d \n", i);
    if(/*bitMap[i]*/*(bitMap + i) != 1){
      count++;
    }else{
      count = 0;
    }
    if(count == pagesNeeded){
      result = i - (pagesNeeded -1);
      printf("chega");
      //break;
    }
  }
  return result;
}

void addToMemory(int index, process_t * process){
  int pagesNeeded = (process->size/pageSize) + ((process->size%pageSize > 0)? 1:0);
  int currentIndex = index;
  int remaningSize = process->size;

  while(pagesNeeded > 1){
    bitMap[currentIndex] = 1;
    memory[currentIndex].bytesUsed = pageSize;
    remaningSize = remaningSize - pageSize;
    currentIndex++;
  }
  bitMap[currentIndex] = 1;
  memory[currentIndex].bytesUsed = remaningSize;

}

void createProccess(){
  int processId, processSize;
	printf("Digite o ID do processo\n");
  scanf("%d",&processId);
  do{
	   printf("Digite o tamanho do processo\n");
    scanf("%d",&processSize);
    if(processSize > processMaxSize) printf("O Tamanho do processo deve ser de no maximo %d bytes\n",processMaxSize);
  }
  while(processSize > processMaxSize);

  page_t * newPage;
  process_t newProcess;
  newProcess.id = processId;
  newProcess.size = processSize;

  int index = findFirstFit(processSize);
  if(index != -1){
    printf("Entrou");
    addToMemory(index, &newProcess);
  }else{
    printf("Não foi possivel criar o processo, espaço insuficiente");
  }


  printf("Novo processo criado! ID: %d - Tamanho: %d\n", processId, processSize);

}

void viewMemory(){
  int numberOfPages = memorySize/pageSize;
	printf("Memória %d\n",numberOfPages);
  for(int i = 0; i< numberOfPages;i++){
    printf("Pagina %d - Bytes usados: %d\n", i, memory[i].bytesUsed);
  }
}

int checkPowerOfTwo(int n){
  if (n == 0) return 0;

  while (n != 1){
    if (n%2 != 0) return 0;
    n = n/2;
  }

  return 1;
}

void viewPageTable(){
  int id;
	printf("Tabela de paginas\n");
	printf("Digite o ID do processo que você deseja visualizar\n");
  scanf("%d",&id);
}

void handleInput(){
  switch (numberSelected){
    case 0:
      createProccess();
      break;
    case 1:
      viewMemory();
      break;
    case 2:
      viewPageTable();
      break;
    default:
      break;
  }
  numberSelected = -1;
}

void renderMenu(){
  while(1){
    printf("[0] - Criar Processo\n");
    printf("[1] - Visualizar Memória\n");
    printf("[2] - Visualizar Tabela de Memória \n");
    scanf("%d",&numberSelected);
    handleInput();
  }
}

void renderInitialConfig(){
  printf("Simulador de gerenciamento de memoria \n");
  printf("Digite o tamanho para a memória\n");
  scanf("%d",&memorySize);

  checkPowerOfTwo(memorySize)? printf("Yes\n"): printf("No\n");

  do{
    printf("Digite o tamanho da página\n");
    scanf("%d",&pageSize);
    if(pageSize > memorySize) printf("O tamanho da pagina deve ter até %d bytes\n",memorySize);
  }while(pageSize > memorySize);
  printf("Digite o tamanho maximo para os processos \n");
  scanf("%d",&processMaxSize);

  //bitmapsize memoria/nro pgs?
  int numberOfPages = memorySize/pageSize;
  memory = (page_t*) malloc(sizeof(page_t)*numberOfPages);
  int newBitMap[numberOfPages];
  bitMap = newBitMap;//(int*) malloc(sizeof(int)*numberOfPages);
  printf("numero de paginas: %d\n", numberOfPages);

  printf("bites usados na pagina 0: %d\n", memory[0].bytesUsed);
}

int main()
{
  renderInitialConfig();
  renderMenu();
}
