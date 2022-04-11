/*
 * @Author: your name
 * @Date: 2022-04-05 21:27:54
 * @LastEditTime: 2022-04-05 22:40:00
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /memory_pool/allocator.cpp
 */
#include<cstddef>
#include<malloc.h>
class allocator{
    private:
        struct obj
        {
            obj* next;
        };

    public:
        void* allocate(size_t);
        void deallocate(void*, size_t);
    
    private:
        obj* freeStore = nullptr;
        const int CHUNK = 5;
};

void* allocator::allocate(size_t size)
{
    obj* p;
    if(!freeStore)
    {
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);

        for(int i=0; i < (CHUNK-1); ++i)
        {
            p->next = (obj*)((char*)p+size);
            p = p->next;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void allocator::deallocate(void *p, size_t)
{
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}
