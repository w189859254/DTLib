#include "object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DTLib
{

// 异常规格说明, 当前函数不会抛出任何异常
void* Object::operator new(unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p)
{
    free(p);
}

void* Object::operator new[](unsigned int size) throw()
{

    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

Object::~Object()
{

}

}


