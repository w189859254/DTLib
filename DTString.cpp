#include <cstring>
#include <cstdlib>
#include "DTString.h"
#include "Exception.h"

using namespace std;

namespace DTLib
{

void String::init(const char *s)
{
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String object ...");
    }
}

String::String()
{
    init("");
}

String::String(const char *s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}


bool String::equal(const char *l, const char *r, int len) const
{
    bool ret = true;

    for(int i=0; i<len && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}
bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}
bool String::startWith(const String& s) const
{
    return (startWith(s.m_str));
}
bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);

        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}
bool String::endOf(const String& s) const
{
    return (endOf(s.m_str));
}

char& String::operator [] (int i)
{
    if( (0 <= i) && (i < m_length) )
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
}
char String::operator[] (int i) const
{
    return (const_cast<String&>(*this))[i];
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}
bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s);
}
bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}
bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}
bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}
String String::operator + (const char* s) const
{
    String ret;
    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if(str)
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memroty to add String values ...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    return (*this = *this + s);
}
String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}
String& String::operator = (const char* s)
{
    if(m_str != s)
    {
        char* str = strdup(s ? s : "");

        if(str)
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new String value ...");
        }
    }

    return *this;
}
String& String::operator = (char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}

