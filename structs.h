typedef struct page_str {
  int memoryAddress;
} page_t;


typedef struct process_str {
  int id;
  page_t * pageTable;
} process_t;