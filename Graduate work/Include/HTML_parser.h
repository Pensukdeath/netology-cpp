#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <regex>
#include <map>

#include "Utils.h"
#include "DB_Client.h"


class HTML_Parser
{
private:
	std::string url{ "" };
	Link link{};
	std::string htmlContent{ "" };
	std::map<std::string, unsigned int> wordCount{};
	DB_Client db;
	std::vector<std::string> subLinks{};

	std::vector<std::string> extractLink()
	{
		//ищем все ссылки в строке и сохраняем их в массив
		std::regex htmlLink("<a href=\"(.*?)\"");
		std::vector<std::string> arrayLinks;

		auto links_begin = std::sregex_iterator(htmlContent.begin(), htmlContent.end(), htmlLink);
		auto links_end = std::sregex_iterator();

		for (std::sregex_iterator i = links_begin; i != links_end; ++i)
		{
			std::smatch sm = *i;
			if (sm[1].str().at(0) != '#')//такая ссылка не пойдет
			{
				Link tmplink = this->UrlToLink(sm[1].str(), link);
				//если ссылка уникальна - запишем ее
				if (std::find(arrayLinks.begin(), arrayLinks.end(), LinkToURL(tmplink)) == arrayLinks.end())
				{
					arrayLinks.push_back(LinkToURL(tmplink));
				}
			}
		}
		return arrayLinks;
	}
	std::map<std::string, unsigned int> extractWords(const std::string& html)
	{	
		//формируем массив слов с количеством повторений каждого
		std::map<std::string, unsigned int> wordArray;

		const int minSize = 3;
		std::string word;
		std::string testString = html;

		std::string titleStr;
		std::smatch titleRes;
		std::string regex_str = "<title>(.?)[^<]*";
		if (std::regex_search(testString, titleRes, std::regex(regex_str)))
		{
			titleStr = titleRes.str()+"</title>";
		}

		std::string testString1 = testString;
		testString1.erase(0, testString1.find("<body"));
		testString1 = titleStr + testString1;

		std::string::iterator begin = testString1.begin();
		std::string::iterator end = testString1.end();
		while (begin != end)
		{
			while (*begin != '>')
			{
				++begin;
				if (begin >= end) break;
			}
			if (begin >= end) break;//OK
			
			while (*begin != '<')
			{
				word.erase();
				while (isAlpha(*begin))
				{
					word += *begin;
					++begin;
					if (begin >= end) break;
				}
				if (begin >= end) break;//OK
				
				if (word.length() > minSize)
				{
					toLower(word);
					wordArray[word]++;
				}
				++begin;
				if (begin >= end) break;//OK
			}
			if (begin >= end) break;//OK
		}
		return wordArray;
	}

	Link UrlToLink(const std::string& html)
	{
		//разбираем стартовую ссылку
		//формируем структуру ссылки
		std::regex ur("(https?)?(:?\/\/)?([[:alnum:]-_]+\..*?)?(\/.*)");

		std::smatch sm;
		std::regex_search(html, sm, ur);

		Link tmp_link;

		if (sm[1].length() != 0)
		{
			if (sm[1].str() == "http") {
				tmp_link.protocol = TProtocol::HTTP;
			}
			else if (sm[1].str() == "https") {
				tmp_link.protocol = TProtocol::HTTPS;
			}
		}
		else
		{
			throw "Bad first URL: not find protocol.";
		};

		if (sm[3].length() != 0)
		{
			tmp_link.host = sm[3].str();
		}
		else
		{
			throw "Bad first URL: not find host.";
		};

		if (sm[4].length() != 0)
		{
			tmp_link.query = sm[4].str();
		}
		else
		{
			tmp_link.query = '/';
		};
		return tmp_link;
	}

	Link UrlToLink(const std::string& html, const Link& url)
	{
		//преобразуем дочернюю ссылку в структуру ссылки
		//учтем, что в дочерней ссылке может не быть нужных параметров
		//берем их из родительской ссылки
		std::regex ur("(https?)?(:?\/\/)?([[:alnum:]_-]+\.[^\/]+)?(\/.*(#[^\/]+$)?)");

		std::smatch sm;
		std::regex_search(html, sm, ur);

		Link tmp_link;


		if (sm[1].length() != 0)
		{
			if (sm[1].str() == "http")
			{
				tmp_link.protocol = TProtocol::HTTP;
			}
			else if (sm[1].str() == "https")
			{
				tmp_link.protocol = TProtocol::HTTPS;
			}
		}
		else
		{
			tmp_link.protocol = url.protocol;
		};

		if (sm[3].length() != 0)
		{
			tmp_link.host = sm[3].str();
		}
		else
		{
			tmp_link.host = url.host;
		};

		if (sm[4].length() != 0)
		{
			if (sm[5].length() == 0)
			{
				tmp_link.query = sm[4].str();
			}
			else
			{
				tmp_link.query = sm[4].str().substr(0, sm[4].length() - sm[5].length());
			}
		}
		else
		{
			tmp_link.query = '/';
		}
		return tmp_link;
	}

public:
	HTML_Parser(DB_Client& db, const std::string& url)
	{
		this->db = db;
		this->url = url;
		link = UrlToLink(this->url);
	}

	~HTML_Parser() = default;

	bool parse()
	{
		htmlContent = getContent(this->link);
		if (this->htmlContent.size() == 0)
		{
			return false;
		}

		wordCount = extractWords(htmlContent);
		if (wordCount.size() == 0)
		{
			return false;
		}

		db.addLink(wordCount, GetURL());
		subLinks = extractLink();

		return true;
		
	}

	std::string GetURL()
	{
		//преобразуем структуру ссылки в строку
		if (link.protocol == TProtocol::HTTP)
		{
			return("http://" + link.host + link.query);
		}
		else
		{
			return("https://" + link.host + link.query);
		}
		
	}

	Link GetLink()
	{
		return this->link;
	}

	std::vector<std::string> getSubLinks()
	{
		return subLinks;
	}



};
