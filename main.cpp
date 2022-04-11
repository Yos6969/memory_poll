/*
 * @Author: your name
 * @Date: 2022-04-05 20:38:51
 * @LastEditTime: 2022-04-05 22:39:29
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /memory_pool/main.cpp
 */
#include <iostream>
#include "allocator.hpp"
#include "chrono"
#include "vector"
class Foo{
    public:
        long L;
        std::string str;
        static allocator myAlloc;

    public:
        Foo(long l):L(l){}
        static void* operator new(size_t size)
        {
            return myAlloc.allocate(size);
        }
        static void operator delete(void* pdead, size_t size)
        {
            return myAlloc.deallocate(pdead, size);
        }
};
using namespace std::chrono_literals;
allocator Foo::myAlloc;
int main(int, char**) {
    std::vector<Foo*>foovec(10);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<10;i++){
    Foo* f1 = new Foo(123);
    foovec[i]=f1;
    }
    for(int i=0;i<5;i++)
    {
        delete foovec[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout<<(end-start)/1us<<std::endl;
    
    // auto start = std::chrono::high_resolution_clock::now();
    // for(int i=0; i<1000000;i++){
    // Foo* f1 = ::new Foo(123);
    // foovec[i]=f1;
    // }
    // for(int i=0;i<1000000;i++)
    // {
    //     delete foovec[i];
    // }
    // auto end = std::chrono::high_resolution_clock::now();
    // std::cout<<(end-start)/1us<<std::endl;
}
