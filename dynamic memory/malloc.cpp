#include <iostream>

struct BlockHeader {
    size_t       size;
    bool         free;
    BlockHeader* next;
};

static unsigned char heap[1<<20];
static BlockHeader* heap_start = nullptr;

void init(){
heap_start = (BlockHeader*)heap;                              //typecast heap to BlockHeader and assign to heap_start
heap_start->size = sizeof(heap) - sizeof(BlockHeader);        // size of free region
heap_start->free = true;                                      // set heap block as free
heap_start->next = nullptr;                                   // first heap block so points to null
}

void* my_malloc(size_t size){
    BlockHeader* current = heap_start;

    while(current != nullptr){
        if(current->free && current->size >= size){
            size_t leftover = current->size - size;
            if(leftover > sizeof(BlockHeader) + 8){
                BlockHeader* split = (BlockHeader*)((unsigned char*)(current + 1) + size);
                split->size  = leftover - sizeof(BlockHeader);
                split->free  = true;
                split->next  = current->next;
                current->size = size;
                current->next = split;
            }
            current->free = false;
            return (void*)(current + 1);
        }
        current = current->next;
    }
    return nullptr;
  }

  void my_free(void* ptr) {
      if (ptr == nullptr) return;
      BlockHeader* header = (BlockHeader*)ptr - 1;
      header->free = true;
      while (header->next != nullptr && header->next->free) {
          header->size += sizeof(BlockHeader) + header->next->size;
          header->next  = header->next->next;
      }
  }

  // diagnostic — lets you see the heap state
void heap_dump() {
      BlockHeader* current = heap_start;
      int i = 0;
      while (current != nullptr) {
          std::cout << "Block " << i++
                    << ": size=" << current->size
                    << " free=" << current->free << "\n";
          current = current->next;
      }
}

int main(){
    BlockHeader b;
    init();
    int* p = (int*)my_malloc(30);
    int* q = (int*)my_malloc(30);
    int* q1 = (int*)my_malloc(30);
    heap_dump();
    my_free(p);
    //my_free(q1);
    my_free(q);
    heap_dump();
    my_free(q1);
    heap_dump();
    
    //int* q = (int*)my_malloc(30);
    //heap_dump();
    return 0;

}