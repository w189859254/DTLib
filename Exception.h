#ifndef EXCEPTION_H
#define EXCEPTION_H


namespace DTLib
{

#define THROW_EXCEPTION(e, m)(throw e(m, __FILE__, __LINE__))


class Exception
{
protected:
    char* m_message;  // 说明当前异常的详细信息
    char* m_location;   // 说明发生异常点

    // 重载了构造函数，构造函数里面的逻辑都一样，所以使用一个辅助函数
    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator = (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;

};


class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0){}
    ArithmeticException(const char* message) : Exception(message){}
    ArithmeticException(const char* file, int line) : Exception(file, line){}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line){}

    ArithmeticException(const ArithmeticException& e) : Exception(e){}

    ArithmeticException& operator =(const ArithmeticException& e)
    {
        Exception::operator =(e);

        return *this;
    }


};








}







#endif // EXCEPTION_H
