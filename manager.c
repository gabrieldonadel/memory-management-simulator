#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


int numberSelected = -1;
int processMaxSize;
int memorySize;
int pageSize;
int * bitMap;
page_t * memory;

void createProccess(){
  int processId, processSize;
	printf("Digite o ID do processo\n");
  scanf("%d",&processId);
  do{
	   printf("Digite o tamanho do processo\n");
    scanf("%d",&processSize);
    if(processSize > processMaxSize) printf("O Tamanhodo processo deve ser de no maximo %d bytes\n",processMaxSize);
  }
  while(processSize > processMaxSize);

  page_t * newPage;
  process_t newProcess;

  memory[0].bytesUsed = 10;
  printf("Novo processo criado! ID: %d - Tamanho: %d\n", processId, processSize);

  printf("bites usados na pagina 0: %d\n", memory[0].bytesUsed);
}

void viewMemory(){
	printf("Memória %ld\n",sizeof(&memory)/sizeof(&memory[0]));
  for(int i = 0; i< sizeof(memory)/sizeof(memory[0]);i++){
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
  memory =  malloc(sizeof(page_t)*numberOfPages);
  printf("numero de paginas: %d\n", numberOfPages);

  printf("bites usados na pagina 0: %d\n", memory[0].bytesUsed);
}

int main()
{
  renderInitialConfig();
  renderMenu();
}
