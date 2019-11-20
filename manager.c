#include <stdio.h>
#include "structs.h"


int numberSelected = -1;
int processMaxSize;
int memorySize;
int pageSize;
int * bitMap;

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
  printf("Novo processo criado! ID: %d - Tamanho: %d\n", processId, processSize);
}

void viewMemory(){
	printf("Memória\n");
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
  do{
    printf("Digite o tamanho da página\n");
    scanf("%d",&pageSize);
    if(pageSize > memorySize) printf("O tamanho da pagina deve ter até %d bytes\n",memorySize);
  }while(pageSize > memorySize);
  printf("Digite o tamanho maximo para os processos \n");
  scanf("%d",&processMaxSize);

  //bitmapsize memoria/nro pgs?

}

int main()
{
  renderInitialConfig();
  renderMenu();
}
