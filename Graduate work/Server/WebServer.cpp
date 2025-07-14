
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <map>
#ifdef WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

/*
## Программа-поисковик
Программа-поисковик выполняет поиск по базе данных, ранжирует результат и возвращает его пользователю. 
В настоящих поисковых системах ранжирование выполняется по множеству критериев, однако для простоты 
будем ранжировать страницу по частоте упоминания искомых слов в документе.
*/

#include "../Include/INI_File.h"
#include "../Include/DB_Client.h"
#include "../Include/HTTP_Server.h"
#include "../Include/Utils.h"


// "Loop" forever accepting new connections.
void httpServer(tcp::acceptor& acceptor, tcp::socket& socket, DB_Client& db)
{
	acceptor.async_accept(socket,
		[&](beast::error_code ec)
		{
			if (!ec)
				std::make_shared<HTTP_Server>(std::move(socket), &db)->start();
			httpServer(acceptor, socket, db);
		});
}


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		INI_file ini_file("../config.ini");
		//подключаемся к БД
		std::string host = ini_file.get_value("DataBase.bd_host");
		std::string name = ini_file.get_value("DataBase.bd_name");
		std::string dbPort = ini_file.get_value("DataBase.bd_port");
		std::string user = ini_file.get_value("DataBase.bd_user");
		std::string pass = ini_file.get_value("DataBase.bd_pass");
		DB_Client db(host, dbPort, name, user, pass);//OK

		//Порт, на котором будет запущен HTTP-сервер, должен взять из ini-файла конфигурации.
		unsigned short port = static_cast<unsigned short>(std::stoi(ini_file.get_value("Server.server_port")));
		auto const address = net::ip::make_address("0.0.0.0");

		//запускаем сервер
		net::io_context ioc{1};

		tcp::acceptor acceptor{ioc, { address, port }};
		tcp::socket socket{ioc};
		httpServer(acceptor, socket, db);

		std::cout << "Open browser and connect to http://localhost:" <<  port << " to see the web server operating" << std::endl;

		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	system("pause");
	return 0;
}