/*Exercise 2 — Pool from Scratch
Implement the pool allocator from scratch. Then simulate a particle system: create a pool of 8 "particles" (each particle is just struct Particle { float x, y; int lifetime; }), allocate 5, free 2, allocate 3
more, and print which ones are alive. This tests that your free list correctly recycles blocks.
*/

#include <iostream>

struct PoolNode{
    PoolNode* next;
};

struct Pool{
    unsigned char* buffer;
    PoolNode* free_list;
    size_t block_size;
    size_t count;
};

void init(Pool& p, size_t block_size, size_t count){
    block_size = (block_size + 7) & ~7;
    block_size = block_size < sizeof(PoolNode) ? sizeof(PoolNode) : block_size;
    p.block_size = block_size;
    p.count = count;
    p.buffer = new unsigned char[block_size * count];

    p.free_list = nullptr;
    for(int i = (int)count - 1; i >= 0 ; i--){
        PoolNode* node = (PoolNode*)(p.buffer + i * block_size);
        node->next = p.free_list;
        p.free_list = node;
    }
}

void* pool_alloc(Pool& p){
    if(!p.free_list){
        return nullptr;
    }
    void* ptr = p.free_list;
    p.free_list = p.free_list->next;
    return ptr;
}

void pool_free(Pool& p, void* ptr){
    PoolNode* node = (PoolNode*)ptr;
    node->next = p.free_list;
    p.free_list = node;
}

void pool_destroy(Pool& p) {
    delete[] p.buffer;
    p.buffer = nullptr;
}

struct Particle
{
    float x, y;
    int lifetime;
};

int main(){
    Pool pool;
    init(pool, sizeof(Particle), 8);
    Particle* particles[8] = {nullptr};
    for (int i = 0; i < 5; i++)
    {
        particles[i] = (Particle*)pool_alloc(pool);
        particles[i]->x = i * 1.0f;
        particles[i]->y = i * 2.0f;
        particles[i]->lifetime = 100 - i * 10;

        std::cout << "Allocated Particle " << i
                  << " at " << particles[i] << '\n';
    }

    pool_free(pool, particles[1]);
    particles[1] = nullptr;

    pool_free(pool, particles[3]);
    particles[3] = nullptr;

    for (int i = 5; i < 8; i++)
    {
        particles[i] = (Particle*)pool_alloc(pool);

        if (particles[i] == nullptr)
        {
            std::cout << "Pool exhausted\n";
            continue;
        }

        particles[i]->x = i * 1.0f;
        particles[i]->y = i * 2.0f;
        particles[i]->lifetime = 100;

        std::cout << "Allocated Particle " << i
                  << " at " << particles[i] << '\n';
    }

    std::cout << "\nAlive Particles\n\n";

    for (int i = 0; i < 8; i++)
    {
        if (particles[i] != nullptr)
        {
            std::cout
                << "Particle " << i
                << " : Address = " << particles[i]
                << "  x = " << particles[i]->x
                << "  y = " << particles[i]->y
                << "  lifetime = " << particles[i]->lifetime
                << '\n';
        }
    }

    pool_destroy(pool);

    return 0;
}
