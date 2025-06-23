/*
Задание 3. Паттерн «Цепочка ответственности»
Продолжаем тему с реализацией системы логирования в соответствии с разными паттернами проектирования.

В задании нужно реализовать сообщение о логировании с типом сообщения и самим сообщением:

class LogMessage {
public:
    Type type() const;
    const std::string& message() const;
};
Всего должно быть четыре типа сообщений:

предупреждение,
ошибка,
фатальная ошибка,
неизвестное сообщение.
Далее нужно добавить обработчиков для разных типов, которые будут обрабатывать сообщения по приоритету:

фатальная ошибка,
ошибка,
предупреждение,
неизвестное сообщение.
Каждый обработчик умеет:

обрабатывать сообщение только определённого типа,
передавать сообщение следующему обработчику.
Вот что обработчик должен уметь в зависимости от типа сообщения.

Обработчик фатальной ошибки должен выбросить исключение с текстом сообщения, потому что предполагается, что программа должна прекратить выполнение после возникновения фатальной ошибки.
Обработчик обычной ошибки должен записать её в файл по указанному пути.
Обработчик предупреждения должен напечатать сообщение в консоль.
Обработчик неизвестного сообщения должен выбросить исключение с текстом о необработанном сообщении.
*/

#include <iostream>
#include <fstream>
enum Type
{
    tWarning,
    tError,
    tFatalError,
    tUnknown
};

class LogMessage 
{
private:
    Type logType{Type::tUnknown};
    std::string logMessage{""};
public:
    LogMessage(const Type type, const std::string& message) : logType{ type }, logMessage{ message }
    {
    };
    Type type() const
    {
        return this->logType;
    };
    const std::string& message() const
    {
        return this->logMessage;
    };
};

class MHandler
{
protected:
    //передавать сообщение следующему обработчику
    MHandler* nextHandler;
public:
    MHandler(MHandler* next = nullptr) : nextHandler {next}
    {
    };
    virtual ~MHandler() = default;
    virtual void checkMessage(const LogMessage& message) 
    {
    };
};

class ErrorHandler : public MHandler
{
private:
    std::ofstream errorLog;
public:
    ErrorHandler(MHandler* next, const std::string& fileName) : MHandler(next)
    {
        errorLog.open(fileName);
        if (!(errorLog.is_open())) 
        {
            std::cout << "No log file " << fileName << " found" << std::endl;
        }

    };

    ~ErrorHandler()
    {
        errorLog.close();
    };
    //обрабатывать сообщение только определённого типа
    //передавать сообщение следующему обработчику
    void checkMessage(const LogMessage& message) override
    {
        if (message.type() == Type::tError)
        {
            //это свой тип сообщения - обработаем
            errorLog << message.message() << std::endl;
        }
        else
        {
            if (nextHandler != nullptr)
            {
                //передаем следующему
                nextHandler->checkMessage(message);//полиморфизм!
            }
        }
    }
};

class WarningHandler : public MHandler
{
public:
    WarningHandler(MHandler* next) : MHandler(next)
    {
    };
    //обрабатывать сообщение только определённого типа
    //передавать сообщение следующему обработчику
    void checkMessage(const LogMessage& message) override
    {
        if (message.type() == Type::tWarning)
        {
            //это свой тип сообщения - обработаем
            std::cout << message.message() << std::endl;
        }
        else
        {
            if (nextHandler != nullptr)
            {
                //передаем следующему
                nextHandler->checkMessage(message);//полиморфизм!
            }
        }
    }
};

class FatalErrorHandler : public MHandler
{
public:
    FatalErrorHandler(MHandler* next) : MHandler(next) 
    {
    };
    //обрабатывать сообщение только определённого типа
    //передавать сообщение следующему обработчику
    void checkMessage(const LogMessage& message) override
    {
        if (message.type() == Type::tFatalError)
        {
            //это свой тип сообщения - обработаем
            std::cout << "Fatal error!" << std::endl;
            throw(message.message());
        }
        else
        {
            if (nextHandler != nullptr)
            {
                //передаем следующему
                nextHandler->checkMessage(message);//полиморфизм!
            }
        }
    }
};

class UnknownHandler : public MHandler
{
public:
    UnknownHandler(MHandler* next) : MHandler(next)
    {
    };
    //обрабатывать сообщение только определённого типа
    //передавать сообщение следующему обработчику
    void checkMessage(const LogMessage& message) override
    {
        if (message.type() == Type::tUnknown)
        {
            //это свой тип сообщения - обработаем
            std::cout << "Unknown message!" << std::endl;
            throw(message.message());
        }
        else
        {
            if (nextHandler != nullptr)
            {
                //передаем следующему
                nextHandler->checkMessage(message);//полиморфизм!
            }
        }
    }
};

int main()
{
    LogMessage message(Type::tWarning, "WARNING MESSAGE");

    UnknownHandler    unknown(nullptr);
    WarningHandler    warning(&unknown);
    ErrorHandler      error(&warning, "errorLog.txt");
    FatalErrorHandler fatalError(&error);
    fatalError.checkMessage(message);

    return 0;
}