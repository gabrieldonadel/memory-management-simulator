#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int numberSelected = -1;
int numberOfPages;
int processMaxSize;
int memorySize;
int pageSize;
int *bitMap;
page_t *memory;
process_t *processes;

int findFreeProcessIndex()
{
  int result = -1;
  for (int i = 0; i < numberOfPages; i++)
  {
    if (processes[i].id == -1)
    {
      result = i;
      break;
    }
  }
  return result;
}

int findProcessIndex(int id)
{
  int result = -1;
  for (int i = 0; i < numberOfPages; i++)
  {
    if (processes[i].id == id)
    {
      result = i;
      break;
    }
  }
  return result;
}

int doesProcessFit(int size)
{
  int pagesNeeded = (size / pageSize) + ((size % pageSize > 0) ? 1 : 0);
  int count = 0;
  for (int i = 0; i < numberOfPages; i++)
  {
    if (bitMap[i] != 1)
    {
      count++;
    }
    if (count == pagesNeeded)
    {
      return 1;
    }
  }
  return -1;
}

int findFirstFit(int size)
{
  int pagesNeeded = (size / pageSize) + ((size % pageSize > 0) ? 1 : 0);
  int count = 0;
  int result = -1;
  for (int i = 0; i < numberOfPages; i++)
  {
    if (bitMap[i] != 1)
    {
      count++;
    }
    else
    {
      count = 0;
    }
    if (count == pagesNeeded)
    {
      result = i - (pagesNeeded - 1);
      break;
    }
  }
  return result;
}

void addToMemory(process_t process)
{
  int pagesNeeded = (process.size / pageSize) + ((process.size % pageSize > 0) ? 1 : 0);
  int remainingPages = pagesNeeded;
  int remainingSize = process.size;

  int currentProcessIndex = findFreeProcessIndex();
  process.pageTable = malloc(sizeof(int) * pagesNeeded);

  for (int i = 0; i < numberOfPages; i++)
  {
    if (bitMap[i] != 1)
    {
      bitMap[i] = 1;
      process.pageTable[pagesNeeded - remainingPages] = i;

      if (remainingPages > 1)
      {
        memory[i].bytesUsed = pageSize;

        remainingSize = remainingSize - pageSize;
        remainingPages--;
      }
      else
      {
        memory[i].bytesUsed = remainingSize;
        break;
      }
    }
  }

  processes[currentProcessIndex] = process;
}

void createProccess()
{
  int processId, processSize;
  printf("Digite o ID do processo\n");
  scanf("%d", &processId);
  do
  {
    printf("Digite o tamanho do processo\n");
    scanf("%d", &processSize);
    if (processSize > processMaxSize)
      printf("O Tamanho do processo deve ser de no maximo %d bytes\n\n", processMaxSize);
  } while (processSize > processMaxSize);

  process_t newProcess;
  newProcess.id = processId;
  newProcess.size = processSize;

  int fit = doesProcessFit(processSize);
  if (fit != -1)
  {
    addToMemory(newProcess);
    printf("Novo processo criado! ID: %d - Tamanho: %d\n", processId, processSize);
  }
  else
  {
    printf("Não foi possivel criar o processo, espaço insuficiente\n");
  }
}

void viewMemory()
{
  printf("################################\n");
  printf("#%30s#\n", " ");
  printf("%-12sMemória%12s\n", "# ", " #");
  printf("#%30s#\n", " ");
  printf("################################\n\n");
  for (int i = 0; i < numberOfPages; i++)
  {
    printf("Pagina %d - Bytes usados: %d\n", i, memory[i].bytesUsed);
  }
}

void viewPageTable()
{
  int id;
  printf("Digite o ID do processo que você deseja visualizar a tabela de paginas\n");
  scanf("%d", &id);
  int index = findProcessIndex(id);
  if (index == -1)
  {
    printf("Não foi possivel localizar o processo com o ID %d\n", id);
  }
  else
  {
    int pagesUsed = (processes[index].size / pageSize) + ((processes[index].size % pageSize > 0) ? 1 : 0);
    printf("#########################################\n");
    printf("#%39s#\n", " ");
    printf("%-12sTabela de Paginas%12s\n", "# ", " #");
    printf("#%39s#\n", " ");
    printf("#########################################\n");
    printf("#%16s#%16s#%5s#\n", " ", " ", " ");
    printf("#  ID da pagina  #  bytes usados  #  %%  #\n");
    printf("#%-16s#%-16s#%5s#\n", " ", " ", " ");
    printf("#########################################\n");
    printf("#%-16s#%-16s#%5s#\n", " ", " ", " ");
    for (int i = 0; i < pagesUsed; i++)
    {
      int pageId = processes[index].pageTable[i];
      int bytesUsed = memory[pageId].bytesUsed;
      printf("#%7s%02d%7s#%6s%04d%6s# %03d #\n", " ", pageId, " ", " ", bytesUsed, " ", (bytesUsed * 100 / pageSize));
    }
    printf("#%-16s#%-16s#%5s#\n", " ", " ", " ");
    printf("#########################################\n");
  }
}

void cleanScreen()
{
  for (int i = 0; i < 40; i++)
  {
    printf("\n");
  }
}

void handleInput()
{
  cleanScreen();
  switch (numberSelected)
  {
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

void renderMenu()
{
  while (1)
  {
    printf("\n");
    printf("[0] - Criar Processo\n");
    printf("[1] - Visualizar Memória\n");
    printf("[2] - Visualizar Tabela de Memória \n");
    scanf("%d", &numberSelected);
    handleInput();
  }
}

void renderInitialConfig()
{
  printf("\n\n");
  printf("###################################################\n");
  printf("#%49s#\n", " ");
  printf("%-7s%s%7s\n", "# ", "Simulador de gerenciamento de memoria", "#");
  printf("#%49s#\n", " ");
  printf("###################################################\n");
  printf("\n\n");
  printf("Digite o tamanho para a memória\n");
  scanf("%d", &memorySize);

  do
  {
    printf("Digite o tamanho da página\n");
    scanf("%d", &pageSize);
    if (pageSize > memorySize)
      printf("O tamanho da pagina deve ter até %d bytes\n", memorySize);
  } while (pageSize > memorySize);

  do
  {
    printf("Digite o tamanho maximo para os processos \n");
    scanf("%d", &processMaxSize);
    if (processMaxSize > memorySize)
      printf("O tamanho da processo deve ter até %d bytes\n", memorySize);
  } while (processMaxSize > memorySize);

  numberOfPages = memorySize / pageSize;
  memory = (page_t *)malloc(sizeof(page_t) * numberOfPages);
  bitMap = malloc(sizeof(int) * numberOfPages);
  processes = (process_t *)malloc(sizeof(process_t) * numberOfPages);
  for (int i = 0; i < numberOfPages; i++)
  {
    processes[i].id = -1;
    memory[i].bytesUsed = 0;
    bitMap[i] = 0;
  }
  printf("numero de paginas: %d\n", numberOfPages);
}

int main()
{
  renderInitialConfig();
  cleanScreen();
  renderMenu();
}
