#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

#include "../Include/root_certificates.hpp"
#include "../Include/DB_Client.h"
#include "../Include/HTTP_HTTPs_Client.h"
#include "../Include/INI_file.h"
#include "../Include/Utils.h"
#include "../Include/Safe_Queue.h"
#include "../Include/HTML_parser.h"

// пул потоков
std::vector<std::thread> arrThread;
// очередь состоит из ссылок на скачивание
Safe_Queue<TqueueItem> queue;
// мьютекс
std::mutex mutex;

// пул потоков выполняет скачивание страницы по ссылке
void doWork(DB_Client& db)
{
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    while (!queue.empty())
    {
        TqueueItem work;
        std::unique_lock<std::mutex> lock(mutex);

        if (queue.empty()) break;

        work = queue.pop();

        std::cout << std::this_thread::get_id() << " POP " << work.url << " depth = " << work.dept << " size = " << queue.getSize() << "\n";

        HTML_Parser parser(db, work.url);
        if (parser.parse())
        {
            std::cout << "link = " << parser.GetURL() << " links count " << parser.getSubLinks().size() << std::endl;

            if (work.dept > 0)
            {
                std::cout << "depth > 0 links count = " << parser.getSubLinks().size() << std::endl;
                for (auto& subLink : parser.getSubLinks())
                {
                    if (!db.findUrl(subLink))
                    {
                        TqueueItem qSubLink;
                        qSubLink.url = subLink;
                        qSubLink.dept = work.dept - 1;
                        queue.push(qSubLink);
                        std::cout << std::this_thread::get_id() << " PUSH " << qSubLink.url << " depth = " << qSubLink.dept << "\n";
                    }
                }
            }
        }

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        INI_file ini_file("../config.ini");

        std::string start_page = ini_file.get_value("Client.start_page");
        int recursion_depth = std::stoi(ini_file.get_value("Client.recursion_depth"));

        std::string host = ini_file.get_value("DataBase.bd_host");
        std::string port = ini_file.get_value("DataBase.bd_port");
        std::string name = ini_file.get_value("DataBase.bd_name");
        std::string user = ini_file.get_value("DataBase.bd_user");
        std::string password = ini_file.get_value("DataBase.bd_pass");

        DB_Client db(host, port, name, user, password);

        // создаём стартовую ссылку
        TqueueItem qFirstLink;
        qFirstLink.url = start_page;
        qFirstLink.dept = recursion_depth;

        queue.push(qFirstLink);
        std::cout << std::this_thread::get_id() << " PUSH " << qFirstLink.url << " depth = " << qFirstLink.dept << std::endl;

        // создаём пул потоков
        int cntPool = std::thread::hardware_concurrency();
        for (int i = 0; i < cntPool; i++)
        {
            arrThread.emplace_back(std::thread(&doWork, std::ref(db)));
        }

        // дожидаемся завершения
        for (auto& t : arrThread)
        {
            if (t.joinable())
                t.join();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    system("pause");
    return 0;
}
