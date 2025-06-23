/*
Задание 2. Паттерн «Наблюдатель»
Развиваем идею с логированием и пишем класс, за которым смогут наблюдать различные наблюдатели и реагировать на те или иные события.

В задании нужно реализовать несколько классов:

Наблюдаемый класс с методами:
void warning(const std::string& message) const;
void error(const std::string& message) const;
void fatalError(const std::string& message) const;
Этот объект должен:

уметь добавлять не владеющие указатели на наблюдателей,
оповещать наблюдателей о вызове каждого из методов,
корректно обрабатывать разрушение объектов-наблюдателей.
Далее нужно реализовать небольшую иерархию классов-наблюдателей, реализующих интерфейс:
class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};
В иерархии классов-наблюдателей нужно реализовать:

класс для работы с предупреждениями, который будет печатать сообщение в консоль;
класс для работы с ошибками, который будет печатать сообщение в файл по указанному пути;
класс для работы с фатальными ошибками, который будет печатать сообщение в консоль и в файл по указанному пути.
*/

#include <fstream>
#include <iostream>
#include <vector>

class Observer 
{
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};
class WarningMessage : public Observer 
 //класс для работы с предупреждениями, который будет печатать сообщение в консоль;
{
public:
    void onWarning(const std::string& message) override 
    {
        std::cout << message << std::endl;
    }
    void onError(const std::string& message) override
    {
    }
    void onFatalError(const std::string& message) override 
    {
    }
};

class ErrorMessage : public Observer
 //класс для работы с ошибками, который будет печатать сообщение в файл по указанному пути;
{
private:
    std::ofstream logFile;
public:
    ErrorMessage(const std::string& fileName)
    {
        logFile.open(fileName);
        if (!(logFile.is_open())) {
            std::cout << "No log file " << fileName << " found" << std::endl;
        }
    }
    ~ErrorMessage()
    {
        logFile.close();
    }
    void onWarning(const std::string& message) override
    {
    }
    void onError(const std::string& message) override
    {
        logFile << message << std::endl;
    }
    void onFatalError(const std::string& message) override
    {
    }
};
class FatalErrorMessage : public Observer
 //класс для работы с фатальными ошибками, который будет печатать сообщение в консоль и в файл по указанному пути.
{
private:
    std::ofstream logFile;
public:
    FatalErrorMessage(const std::string& fileName)
    {
        logFile.open(fileName);
        if (!(logFile.is_open())) {
            std::cout << "No log file " << fileName << " found" << std::endl;
        }
    }
    ~FatalErrorMessage()
    {
        logFile.close();
    }
    void onWarning(const std::string& message) override
    {
    }
    void onError(const std::string& message) override
    {
    }
    void onFatalError(const std::string& message) override
    {
        std::cout << message << std::endl;
        logFile << message << std::endl;
    }
};

//Наблюдаемый класс с методами
class Observers
{
private:
    std::vector<Observer*> vMessages;
public:
    void addMessage(Observer* message)
     //уметь добавлять не владеющие указатели на наблюдателей
    {
        vMessages.push_back(message);
    }
    void removeMessage(Observer* message)
    //корректно обрабатывать разрушение объектов-наблюдателей
    {
        vMessages.erase(std::remove(vMessages.begin(), vMessages.end(), message), vMessages.end());
    }
    //оповещать наблюдателей о вызове каждого из методов
    void warning(const std::string& message) const
    {
        for (const auto& it : vMessages)
        {
            it->onWarning(message);
        }
    }
    void error(const std::string& message) const
    {
        for (const auto& it : vMessages)
        {
            it->onError(message);
        }
    }
    void fatalError(const std::string& message) const
    {
        for (const auto& it : vMessages)
        {
            it->onFatalError(message);
        }
    }
};

int main()
{
    Observers obServers;

    WarningMessage warning;
    obServers.addMessage(&warning);
    obServers.warning("WARNING MESSAGE");
    obServers.removeMessage(&warning);

    ErrorMessage error("ErrorLog.txt");
    obServers.addMessage(&error);
    obServers.error("ERROR MESSAGE");

    FatalErrorMessage fatal("FatalLog.txt");
    obServers.addMessage(&fatal);
    obServers.fatalError("FATAL ERROR MESSAGE");

    return 0;
}