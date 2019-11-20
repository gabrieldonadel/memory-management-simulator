#include <stdio.h>


int numberSelected = -1;
int processMaxSize;
int memorySize;
int pageSize;

void createProccess(){
  int processId, processSize;
	printf("Digite o ID do processo\n");
  scanf("%d",&processId);
  do{

	printf("Digite o tamanho do processo\n");
  scanf("%d",&processSize);
  if(processSize > processMaxSize) printf("O Tamanhodo processo deve ser de no maximo %d bytes\n",processMaxSize);
  }while(processSize > processMaxSize);

  printf("Novo processo criado! ID: %d - Tamanho: %d\n", processId, processSize);
}

void viewMemory(){
	printf("Memória");
}

void viewPageTable(){
	printf("Tabela de paginas");
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

int main()
{
  printf("Simulador de gerenciamento de memoria \n");
  printf("Digite o tamanho para a memória\n");
  scanf("%d",&memorySize);
  printf("Digite o tamanho da página\n");
  scanf("%d",&pageSize);
  printf("Digite o tamanho maximo para os processos \n");
  scanf("%d",&processMaxSize);
  renderMenu();
}
