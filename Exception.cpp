#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void Exception::init(const char *message, const char *file, int line)
{
    //m_message = message;  不能保证外部message的生命周期
    m_message = strdup(message);

    if( file != NULL )
    {
        char sl[16] = {0};

        itoa(line, sl, 10);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file,line);
}

// 从init可以看出若发生复制需要深拷贝，所以需要实现这两个函数
Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator = (const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}


// C++ 规定但凡自定义析构函数，不管是不是纯虚析构函数，都必须提供实现
// 在析构一个对象时，肯定会调用父类的析构函数
Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}


