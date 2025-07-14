#pragma once
#include <regex>
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/ssl.h>

#include "Utils.h"

/*
Изнутри программа «Паук» представляет из себя HTTP-клиент, который переходит по ссылкам, скачивает HTML-страницы и анализирует их содержимое, добавляя записи в базу данных.
*/

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ip = boost::asio::ip;
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;

bool isText(const boost::beast::multi_buffer::const_buffers_type& b)
{
	for (auto itr = b.begin(); itr != b.end(); itr++)
	{
		for (int i = 0; i < (*itr).size(); i++)
		{
			if (*((const char*)(*itr).data() + i) == 0)
			{
				return false;
			}
		}
	}

	return true;
}

std::string getContent_Redirect(const Link& url)
{
	//получим содержимое HTML-страницы по redirect-ссылке
	std::string result;
	try
	{
		std::string host = url.host;
		std::string query = url.query;

		net::io_context ioc;
		//проверим тип протокола!!
		if (url.protocol == TProtocol::HTTPS)
		{
			//защищенное соединение по порту 443
			ssl::context ctx(ssl::context::tlsv13_client);
			ctx.set_default_verify_paths();

			beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);
			stream.set_verify_mode(ssl::verify_none);//отключим проверку сертификата

			stream.set_verify_callback([](bool preverified, ssl::verify_context& ctx) {
				return true; // Accept any certificate
				});


			if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
				beast::error_code ec{ static_cast<int>(::ERR_get_error()), net::error::get_ssl_category() };
				throw beast::system_error{ ec };
			}

			ip::tcp::resolver resolver(ioc);
			get_lowest_layer(stream).connect(resolver.resolve({ host, "https" }));
			get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

			//посылаем Get-запрос
			http::request<http::empty_body> req{ http::verb::get, query, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

			stream.handshake(ssl::stream_base::client);
			http::write(stream, req);

			//читаем ответ
			beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(stream, buffer, res);
			//проверим на ошибки
			if (isText(res.body().data()))
			{
				result = buffers_to_string(res.body().data());
				//std::cout << result << std::endl;
			}
			else
			{
				std::cout << "This is not a text link, bailing out..." << std::endl;
			}
			//отключаемся
			beast::error_code ec;
			stream.shutdown(ec);
			if (ec == net::error::eof)
			{
				ec = {};
			}

			if (ec)
			{
				std::cout << ec.message() << std::endl;
				//throw beast::system_error{ ec };
			}
		}
		else
		{
			//обычное соединение по порту 80
			tcp::resolver resolver(ioc);
			beast::tcp_stream stream(ioc);

			auto const results = resolver.resolve(host, "http");

			stream.connect(results);
			//посылаем Get-запрос
			http::request<http::string_body> req{ http::verb::get, query, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			http::write(stream, req);

			//читаем ответ
			beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(stream, buffer, res);
			//проверяем на ошибки
			if (isText(res.body().data()))
			{
				result = buffers_to_string(res.body().data());
			}
			else
			{
				std::cout << "This is not a text link, bailing out..." << std::endl;
			}
			//отключаемся
			beast::error_code ec;
			stream.socket().shutdown(tcp::socket::shutdown_both, ec);

			if (ec && ec != beast::errc::not_connected)
				throw beast::system_error{ ec };

		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "redirect page is read" << std::endl;
	return result;
}

std::string getContent(const Link& url)
{
	//получим содержимое HTML-страницы по ссылке
	std::string result;
	std::string Redirect_URL = "";
	Link redirectLink;
	try
	{
		std::string host = url.host;
		std::string query = url.query;

		net::io_context ioc;
		//проверим тип протокола!!
		if (url.protocol == TProtocol::HTTPS)
		{
			//защищенное соединение по порту 443
			ssl::context ctx(ssl::context::tlsv13_client);
			ctx.set_default_verify_paths();

			beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);
			stream.set_verify_mode(ssl::verify_none);//отключим проверку сертификата

			stream.set_verify_callback([](bool preverified, ssl::verify_context& ctx) {
				return true; // Accept any certificate
				});


			if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
				beast::error_code ec{ static_cast<int>(::ERR_get_error()), net::error::get_ssl_category() };
				throw beast::system_error{ ec };
			}

			ip::tcp::resolver resolver(ioc);
			get_lowest_layer(stream).connect(resolver.resolve({ host, "https" }));
			get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

			//посылаем Get-запрос
			http::request<http::empty_body> req{ http::verb::get, query, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

			stream.handshake(ssl::stream_base::client);
			http::write(stream, req);
			
			//читаем ответ
			beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(stream, buffer, res);
			if (res.result_int() == 301 || res.result_int() == 307)
			{
				//redirect
				for (auto& h : res.base())
				{
					std::cout << h.name_string() << " " << h.value() << std::endl;
					if (h.name_string() == "location")
					{						
						Redirect_URL = h.value();
						redirectLink = UrlToLink(Redirect_URL, url);
						break;
					}
				}
			}
			//проверим на ошибки
			if (isText(res.body().data()))
			{
				result = buffers_to_string(res.body().data());
			}
			else
			{
				std::cout << "This is not a text link, bailing out..." << std::endl;
			}
			//отключаемся
			beast::error_code ec;
			stream.shutdown(ec);
			if (ec == net::error::eof) 
			{
				ec = {};
			}

			if (ec) 
			{
				std::cout << ec.message() << std::endl;
				//throw beast::system_error{ ec };
			}
		}
		else
		{
			//обычное соединение по порту 80
			tcp::resolver resolver(ioc);
			beast::tcp_stream stream(ioc);

			auto const results = resolver.resolve(host, "http");

			stream.connect(results);
			//посылаем Get-запрос
			http::request<http::string_body> req{ http::verb::get, query, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			http::write(stream, req);

			//читаем ответ
			beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(stream, buffer, res);
			if (res.result_int() == 301 || res.result_int() == 307)
			{
				//redirect
				for (auto& h : res.base())
				{
					if (h.name_string() == "location")
					{
						Redirect_URL = h.value();
						redirectLink = UrlToLink(Redirect_URL, url);
						break;
					}
				}
			}
			//проверяем на ошибки
			if (isText(res.body().data()))
			{
				result = buffers_to_string(res.body().data());
			}
			else
			{
				std::cout << "This is not a text link, bailing out..." << std::endl;
			}
			//отключаемся
			beast::error_code ec;
			stream.socket().shutdown(tcp::socket::shutdown_both, ec);

			if (ec && ec != beast::errc::not_connected)
				throw beast::system_error{ ec };

		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	if (redirectLink.host != "")
	{
		//надо идти на redirect ссылку и ее читать
		std::cout << url.host << url.query << " - REDIRECT to - " << Redirect_URL << std::endl;
		result = getContent_Redirect(redirectLink);
	}
	return result;
}

