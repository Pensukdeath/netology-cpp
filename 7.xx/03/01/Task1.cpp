/*
Задание 1. Паттерн «Команда»
Пишем команды для системы логирования.

В задании нужно реализовать наследников класса:

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};
таким образом, чтобы один наследник печатал сообщение message в консоль, а другой умел печатать сообщение в файл, по указанному пути.

Далее нужно реализовать функцию: oid print(LogCommand&);, которая будет выполнять команды.
*/

#include <iostream>
#include <fstream>
#include <vector>

class LogCommand 
{
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class Command
{
private:
    std::ofstream logFile;
public:
    void printToConsole(const std::string& msg)
    {
        //печать в консоль
        std::cout << msg << std::endl;
    }
    void printToFile(const std::string& msg)
    {
        logFile.open("log.txt");
        if (!(logFile.is_open()))
        {
            std::cout << "No log file found" << std::endl;
        }
        else
        {
            logFile << msg << std::endl;
            logFile.close();
        }
    }
};

class LogToConsole : public LogCommand
{
private:
    Command* command;
public:
    LogToConsole(Command* cmd)
    {
        command = cmd;
    }
    void print(const std::string& msg) override
    {
        command->printToConsole(msg);
    }
};

class LogToFile : public LogCommand
{
private:
    Command* command;
public:
    LogToFile(Command* cmd)
    {
        command = cmd;
    }
    void print(const std::string& msg) override
    {
        command->printToFile(msg);
    }
};

class CommandCollection
{
private:
    std::vector <LogCommand*> commands;
public:
    void addCommand(LogCommand* cmd)
    {
        commands.push_back(cmd);
    }
    void executeCommand(const int index, const std::string& msg)
    {
        commands[index]->print(msg);
    }
};
int main()
{
    Command* command = new Command();
    LogCommand* logToConsole = new LogToConsole(command);
    LogCommand* logToFile = new LogToFile(command);

    CommandCollection commandCollection;
    commandCollection.addCommand(logToConsole);
    commandCollection.executeCommand(0, "message");
    commandCollection.addCommand(logToFile);
    commandCollection.executeCommand(1, "file message");
    return 0;
}