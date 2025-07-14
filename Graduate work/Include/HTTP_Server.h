#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include "DB_Client.h"
#include "Utils.h"

/*
## Программа-поисковик
Программа-поисковик выполняет поиск по базе данных, ранжирует результат и возвращает его пользователю. 
В настоящих поисковых системах ранжирование выполняется по множеству критериев, 
однако для простоты будем ранжировать страницу по частоте упоминания искомых слов в документе.

Изнутри поисковик представляет из себя HTTP-сервер, который принимает два вида запросов: POST и GET. 
Порт, на котором будет запущен HTTP-сервер, должен взять из ini-файла конфигурации.

По запросу GET открывается простая статическая HTML-страница с формой поиска. На форме должно быть поле ввода, 
а также кнопка поиска.

По запросу POST происходит извлечение из базы данных результата запроса и его ранжирование, 
а затем перед пользователем открывается простая статическая веб-страница с результатами поиска.

Для простоты запрос можно анализировать только в виде слов, разделённых пробелами. 
Все прочие знаки препинания игнорируются. Можно также ограничить длину запроса — не более четырёх слов.

Для извлечения данных напишите SQL-запрос. Запрос должен быть следующим: 
взять документы, в которых встречаются все слова из запроса, и отсортировать их по суммарному количеству 
упоминаний слов в документе.
*/

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


class HTTP_Server : public std::enable_shared_from_this<HTTP_Server>
{
protected:

	tcp::socket socket_;

	beast::flat_buffer buffer_{8192};

	http::request<http::dynamic_body> request_;

	http::response<http::dynamic_body> response_;

	net::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(60)};

	std::vector<std::string> getKeyword(const std::string& str)
	{
		//извлекаем все ключевые слова из строки
		//они свяызаны друг с другом символом ПЛЮС
		std::vector<std::string> result;
		std::string value = str;
		toLower(value);
		std::string::size_type pos_end = 0;
		std::string::size_type pos_begin = 0;
		do
		{
			//отделяем очередное слово
			pos_end = value.find('+', pos_begin);
			std::string sub_str = value.substr(pos_begin, pos_end - pos_begin);
			if (sub_str.find_first_not_of(letters) == std::string::npos && sub_str.length() > 3)
			{
				//ищем слово в выходном списке
				//если его нет - добавляем в список
				if (std::find(result.begin(), result.end(), sub_str) == result.end())
				{
					result.push_back(sub_str);
				}
			}
			pos_begin = pos_end + 1;
		} while (pos_end != std::string::npos);

		return result;
	}

	void readRequest()
	{
		//читаем запросы от клиентов
		auto self = shared_from_this();

		http::async_read(
			socket_,
			buffer_,
			request_,
			[self](beast::error_code ec,
				std::size_t bytes_transferred)
			{
				boost::ignore_unused(bytes_transferred);
				if (!ec)
					self->processRequest();
			});
	}	
	
	void processRequest()
	{
		//разбираем запрос
		response_.version(request_.version());
		response_.keep_alive(false);

		switch (request_.method())
		{
		case http::verb::get:
			//ответим
			response_.result(http::status::ok);
			response_.set(http::field::server, "Beast");
			//По запросу GET открывается простая статическая HTML-страница с формой поиска. На форме должно быть поле ввода, 
			//а также кнопка поиска.
			createResponseGet();//формируем тело ответа
			break;
		case http::verb::post:
			//ответим
			response_.result(http::status::ok);
			response_.set(http::field::server, "Beast");
			//По запросу POST происходит извлечение из базы данных результата запроса и его ранжирование, 
			//а затем перед пользователем открывается простая статическая веб - страница с результатами поиска.
			createResponsePost();//формируем тело ответа
			break;

		default:
			//неизвестный запрос
			//ответим
			response_.result(http::status::bad_request);
			response_.set(http::field::content_type, "text/plain");
			//формируем тело ответа
			beast::ostream(response_.body())
			<< "Invalid request-method '"
			<< std::string(request_.method_string())
			<< "'";
			break;
		}

		writeResponse();
	}	

	void createResponseGet()
	{
		//По запросу GET открывается простая статическая HTML-страница с формой поиска. На форме должно быть поле ввода, 
		//а также кнопка поиска.
		if (request_.target() == "/")
		{
			response_.set(http::field::content_type, "text/html");
			beast::ostream(response_.body())
			<< "<html>\n"
			<< "<head><meta charset=\"UTF-8\"><title>WEB Search</title></head>\n"
			<< "<body>\n"
			<< "<h1>Search</h1>\n"
			<< "<p>Welcome!<p>\n"
			<< "<form action=\"/\" method=\"post\">\n"
			<< "    <label for=\"search\">Search:</label><br>\n"
			<< "    <input type=\"text\" id=\"search\" name=\"search\"><br>\n"
			<< "    <input type=\"submit\" value=\"Search\">\n"
			<< "</form>\n"
			<< "</body>\n"
			<< "</html>\n";
		}
		else
		{
			response_.result(http::status::not_found);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body()) << "File not found\r\n";
		}
	}	

	void createResponsePost()
	{
		//По запросу POST происходит извлечение из базы данных результата запроса и его ранжирование, 
		//а затем перед пользователем открывается простая статическая веб - страница с результатами поиска.
		if (request_.target() == "/")
		{
			std::string s = buffers_to_string(request_.body().data());//читаем параметр поиска

			std::cout << "POST data: " << s << std::endl;

			size_t pos = s.find('=');
			if (pos == std::string::npos)
			{
				//параметр не указан
				response_.result(http::status::not_found);
				response_.set(http::field::content_type, "text/plain");
				beast::ostream(response_.body()) << "File not found\r\n";
				return;
			}
			//читаем ключ и значение параметра
			std::string key = s.substr(0, pos);
			std::string value = s.substr(pos + 1);
			//русский язык :)
			std::string utf8value = convert_to_utf8(value);

			if (key != "search") 
			{
				//параметр должен иметь ключ search
				response_.result(http::status::not_found);
				response_.set(http::field::content_type, "text/plain");
				beast::ostream(response_.body()) << "File not found\r\n";
				return;
			}
			
			/*
			Для извлечения данных напишите SQL-запрос. Запрос должен быть следующим:
			взять документы, в которых встречаются все слова из запроса, и отсортировать их по суммарному количеству
			упоминаний слов в документе.
			*/
			std::vector<std::string> keywords = getKeyword(value);//ищем все уникальные ключевые слова в значении параметра(они связаны через символ ПЛЮС)
			
			if(keywords.size() > 0)
			{
				std::map<std::string, int> db_result;
				for (const std::string& s : keywords) 
				{
					for (const auto& [key, value] : db_->getUrl(s))	//ищем все ссылки с ключевыми словами и суммируем их частоту вхождения
					{
						db_result[key] += value;
					}
				}
				if (db_result.size() > 0)
				{
					std::multimap<int, std::string, std::greater<int>> db_result_sort;//сортируем список по убыванию частоты вхождения
					for (const auto& [key, value] : db_result)
					{
						db_result_sort.insert({ value, key });//формируем выходной список
					}
					print_result(db_result_sort);//печатаем табличку
				}
				else
				{
					print_not_found();
				}
			}
			else 
			{
				print_bad_request();
			}
		}
		else
		{
			response_.result(http::status::not_found);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body()) << "File not found\r\n";
		}
	}
	
	void writeResponse()
	{
		//отвечаем клиенту
		auto self = shared_from_this();

		response_.content_length(response_.body().size());

		http::async_write(
			socket_,
			response_,
			[self](beast::error_code ec, std::size_t)
			{
				self->socket_.shutdown(tcp::socket::shutdown_send, ec);
				self->deadline_.cancel();
			});
	}	
	
	void checkDeadline()
	{
		//таймер сервера
		//если что-то не так - закроем сокет
		auto self = shared_from_this();

		deadline_.async_wait(
			[self](beast::error_code ec)
			{
				if (!ec)
				{
					self->socket_.close(ec);
				}
			});
	}	


public:
	HTTP_Server(tcp::socket socket, DB_Client* db): socket_(std::move(socket)), db_{ db }
	{
	}	
	void start()
	{
		readRequest();
		checkDeadline();
	}	
private:
	DB_Client* db_;
	
	void print_not_found()
	{
		response_.set(http::field::content_type, "text/html");
		beast::ostream(response_.body())
		<< "<html>\n"
		<< "<head><meta charset=\"UTF-8\"><title>WEB Search</title></head>\n"
		<< "<body>\n"
		<< "<h1>Search</h1>\n"
		<< "<p>Response:<p>\n"
		<< "<ul>\n"
		<< "<p><b> No matches found </b></p>"
		<< "</ul>\n"
		<< "</body>\n"
		<< "</html>\n";
	}	
	void print_bad_request()
	{
		response_.set(http::field::content_type, "text/html");
		beast::ostream(response_.body())
		<< "<html>\n"
		<< "<head><meta charset=\"UTF-8\"><title>WEB Search</title></head>\n"
		<< "<body>\n"
		<< "<h1>Search</h1>\n"
		<< "<p>Response:<p>\n"
		<< "<ul>\n"
		<< "<p><b> Bad request </b></p>"
		<< "<p> The request must consist of English words longer than 3 characters </p>"
		<< "</ul>\n"
		<< "</body>\n"
		<< "</html>\n";
	}	
	void print_result(const std::vector<std::string>& searchResult)
	{
		response_.set(http::field::content_type, "text/html");
		beast::ostream(response_.body())
		<< "<html>\n"
		<< "<head><meta charset=\"UTF-8\"><title>WEB Search</title></head>\n"
		<< "<body>\n"
		<< "<h1>Search</h1>\n"
		<< "<p>Response:<p>\n"
		<< "<ul>\n";

		for (const auto& url : searchResult) 
		{

			beast::ostream(response_.body())
			<< "<li><a href=\""
			<< url << "\">"
			<< url << "</a></li>\n";
		}

		beast::ostream(response_.body())
		<< "</ul>\n"
		<< "</body>\n"
		<< "</html>\n";
	}	
	
	void print_result(const std::multimap<int, std::string, std::greater<int>>& searchResult)
	{
		int result_size = 10;
		response_.set(http::field::content_type, "text/html");
		beast::ostream(response_.body())
		<< "<html>\n"
		<< "<head><meta charset=\"UTF-8\"><title>WEB Search</title></head>\n"
		<< "<body>\n"
		<< "<h1>Search</h1>\n"
		<< "<p>Response:<p>\n"
		<< "<table>\n";

		for (const auto& [key, value] : searchResult)
		{
			beast::ostream(response_.body())
			<< "<tr>\n<td><a href = \""
			<< value << "\">"
			<< value << "</a></td>\n"
			<< "<td>" << key << "</td>\n</tr>\n";
			--result_size;
			if (result_size == 0) break;
		}

		beast::ostream(response_.body())
		<< "</table>\n"
		<< "</body>\n"
		<< "</html>\n";
	}	
	
};