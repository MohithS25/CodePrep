/*Coding Exercises

  Exercise 1 — my_realloc

  Using my_malloc, my_free, and your my_memcpy from earlier, implement my_realloc. It takes a pointer to an existing allocation, the new desired size, and returns a pointer to a block of the new size with the
  original data preserved.
  
  void* my_realloc(void* ptr, size_t new_size) {
      // your implementation
  }

  Test it:
  int* arr = (int*)my_malloc(3 * sizeof(int));
  arr[0]=10; arr[1]=20; arr[2]=30;
  arr = (int*)my_realloc(arr, 6 * sizeof(int));
  arr[3]=40; arr[4]=50; arr[5]=60;
  for(int i=0;i<6;i++) std::cout << arr[i] << " ";  // 10 20 30 40 50 60
  my_free(arr);
  
  */

#include <iostream>

struct BlockHeader{
    size_t size;
    bool free;
    BlockHeader* next;
};

static unsigned char heap[1 << 20];
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
                split->size = leftover - sizeof(BlockHeader);
                split->free = true;
                split->next = current->next;
                current->size = size;
                current->next = split;
            }
            current->free = false;
            return (void*)(current+1);
        }
        current = current->next;
    }
    return nullptr;
}

void my_free(void* arr){
    if(arr == nullptr){ return; }
    BlockHeader* header = (BlockHeader*)arr - 1;
    header->free = true;
      while (header->next != nullptr && header->next->free) {
          header->size += sizeof(BlockHeader) + header->next->size;
          header->next  = header->next->next;
      }
}

void* my_memcpy(void* dst, void* src, size_t size){
    auto* d = (unsigned char*)dst;
    const auto* s = (const unsigned char*)src;
    for(size_t i = 0; i < size ; i++){
        d[i] = s[i];
    }
    return dst;
}

void* my_realloc(void* arr, size_t new_size){
    void* ptr = my_malloc(new_size);

    BlockHeader* header = (BlockHeader*)arr - 1;
    size_t old_size = header->size;

    my_memcpy(ptr,arr,old_size);
    my_free(arr);
    return ptr;
}

void heap_dump() {
      BlockHeader* current = heap_start;
      int i = 0;
      while (current != nullptr) {
          std::cout << "Block " << i++
                    << ": size=" << current->size
                    << " free=" << current->free << "\n";
          current = current->next;
      }
      std::cout<<"\n";
}

int main(){
    BlockHeader b1;
    init();
    /*int* arr = (int*)my_malloc(3 * sizeof(int));
    arr[0]=10; arr[1]=20; arr[2]=30;
    arr = (int*)my_realloc(arr, 6 * sizeof(int));
    arr[3]=40; arr[4]=50; arr[5]=60;
    for(int i=0;i<6;i++){
        std::cout << arr[i] << " ";  // 10 20 30 40 50 60
    }
    my_free(arr);*/

  void* a = my_malloc(32);
  void* b = my_malloc(64);
  void* c = my_malloc(16);
  heap_dump();   // snapshot 1   block 0 : size 32 : free 0, block 1 : size 64 : free 0, block 2 : size 16 : free 0 , block 3 : size remaining : free 1
  
  my_free(b);
  heap_dump();   // snapshot 2.  block 0 : size 32 : free 0, block 1 : size 64 : free 1, block 2 : size 16 : free 0 , block 3 : size remaining : free 1

  void* d = my_malloc(48);
  heap_dump();   // snapshot 3. block 0 : size 32 : free 0, block 1 : size 48 : free 0, block 2 : size 16 : free 1, block 3 : size 16 : free 0, block 4 : size remaining : free 1
  my_free(a);                  //block 0 : size 32 : free 1, block 1 : size 48 : free 0 , block 2 : size 16 : free 1, block 3 : size 16 : free 0, block 4 : size remaining : free 1
  heap_dump();
  my_free(d);    // think carefully — does coalescing fire here?
  heap_dump();                //block 0 : size 32 : free 1, block 1 : size 64 : free 1, block 2 : size 16 : free 0, block 4 : size remaining : free 1
    return 0;
}

