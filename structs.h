typedef struct page_str {
  int bytesUsed;
} page_t;


typedef struct process_str {
  int id;
  int size;
  int * pageTable;
} process_t;
