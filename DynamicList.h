#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "Seqlist.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity; // Ë³Ðò´æ´¢¿Õ¼äµÄ´óÐ¡
public:
    DynamicList(int capacity)   // ÉêÇë¿Õ¼ä
    {
        this->m_array = new T[capacity];
        if(this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T* array = new T[capacity];

            if(array != NULL)
            {
                int length = (this->m_length < capacity? this->m_length : capacity);

                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* tmp = this->m_array;

                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] tmp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList objec ...");
            }
        }
    }

    ~DynamicList()
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICLIST_H

