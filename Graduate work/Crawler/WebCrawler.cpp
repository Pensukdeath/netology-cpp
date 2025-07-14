#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "../Include/root_certificates.hpp"
#include "../Include/DB_Client.h"
#include "../Include/HTTP_HTTPs_Client.h"
#include "../Include/INI_file.h"
#include "../Include/Utils.h"
#include "../Include/Safe_Queue.h"
#include "../Include/HTML_parser.h"

/*
# Программа «Паук»
Программа «Паук» (spider), или «Краулер» (crowler), — это неотъемлемая часть поисковой системы. 
Эта программа, которая обходит интернет, следуя по ссылкам на веб-страницах. Начиная с одной страницы, 
она переходит на другие по ссылкам, найденным на этих страницах. 
«Паук» загружает содержимое каждой страницы, а затем индексирует её.
*/

//пул потоков
std::vector<std::thread> arrThread;
//очередь состоит из ссылок на скачивание
Safe_Queue <TqueueItem> queue;
//мьютекс
std::mutex mutex;
//флаг завершения работы
bool stop{ false };


//пул потоков выполняет скачивание страницы по ссылке
void doWork(DB_Client& db)
{
	std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
	while (!queue.empty())
	{
		TqueueItem work;
		std::unique_lock<std::mutex> lock(mutex);
		
		//извлекаем ссылку на скачивание
		work = queue.pop();

		std::cout << std::this_thread::get_id() << " POP " << work.url << " depth = " << work.dept << " size = " << queue.getSize() << "\n";

		HTML_Parser parser(db, work.url);
		if (parser.parse())
		{
			std::cout << "link = " << parser.GetURL() << " links count " << parser.getSubLinks().size() << std::endl;
			//если глубина рекурсии страницы еще не 0, то все ссылки со страницы надо добавить в очередь на скачивание с глубиной рекурсии -1
			if (work.dept > 0)
			{
				std::cout << "depth > 0 links count = " << parser.getSubLinks().size() << std::endl;
				for (auto& subLink : parser.getSubLinks())
				{
					if (!db.findUrl(subLink))
					{
						//если нет такой ссылки в базе данных
						TqueueItem qSubLink;
						qSubLink.url = subLink;
						qSubLink.dept = work.dept - 1;
						//пушим ссылки на скачиваниес глубиной рекурсии -1
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
		/*
		## Файл конфигурации ini
		Все настройки программ следует хранить в ini-файле. Этот файл должен парситься при запуске вашей программы.

		В этом файле следует хранить следующие параметры:
		* хост (адрес) базы данных;
		* порт, на котором запущена база данных;
		* название базы данных;
		* имя пользователя для подключения к базе данных;
		* пароль пользователя для подключения к базе данных;
		* стартовая страница для программы «Паук»;
		* глубина рекурсии для программы «Паук»;
		* порт для запуска программы-поисковика.		
		*/
		INI_file ini_file("../config.ini");

		std::string start_page = ini_file.get_value("Client.start_page");
		int recursion_depth = std::stoi(ini_file.get_value("Client.recursion_depth"));

		std::string host = ini_file.get_value("DataBase.bd_host");
		std::string port = ini_file.get_value("DataBase.bd_port");
		std::string name = ini_file.get_value("DataBase.bd_name");
		std::string user = ini_file.get_value("DataBase.bd_user");
		std::string password = ini_file.get_value("DataBase.bd_pass");

		/*
		## База данных
		Для выполнения задания рекомендуется использовать базу данных PostgreSQL.
		Настройки базы данных (хост, порт, название БД, имя пользователя, пароль) следует хранить в ini-файле конфигурации.
		Для хранения информации о частотности слов рекомендуется использовать две таблицы — «Документы» и «Слова» — 
		и реализовать между ними связь «многие-ко-многим» с помощью промежуточной таблицы. 
		В эту же промежуточную таблицу будет записана частота использования слова в документе.		
		*/
		DB_Client db(host, port, name, user, password);

		/*
		## Индексация
		В HTML-страницах также существуют ссылки, обозначаемые HTML-тегом `<a href="...">`. 
		«Паук» должен переходить по этим ссылкам и скачивать эти страницы тоже. 
		Для этого «Паук» реализует многопоточную очередь и пул потоков. 
		*/
		int cntPool = std::thread::hardware_concurrency();
		for (int i = 0; i < cntPool; i++)
		{
			arrThread.push_back(std::thread(&doWork, db));
		}

		/*
		В ini-файле конфигурации задаётся страница, которую необходимо сохранить, и «Паук» начинает свою работу именно с неё.
		Очередь состоит из ссылок на скачивание, а пул потоков выполняет задачу
		по скачиванию веб-страниц с этих ссылок и их индексацию.
		После скачивания очередной страницы «Паук» собирает все ссылки с неё и добавляет их в очередь на скачивание.
		*/		
		TqueueItem qFirstLink;
		qFirstLink.url = start_page;
		qFirstLink.dept = recursion_depth;
		
		/*
		«Паук» загружает эту страницу и индексирует её.
		*/
		queue.push(qFirstLink);
		std::cout << std::this_thread::get_id() << " PUSH " << qFirstLink.url << " depth = " << qFirstLink.dept << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));
		
		//destroy		
		for (auto& t : arrThread)
		{
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