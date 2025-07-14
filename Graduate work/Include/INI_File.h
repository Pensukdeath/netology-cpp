#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include "Utils.h"
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

using myINI = std::map<std::string, std::map<std::string, std::string> >;
using myINI_item = std::map<std::string, std::string>;

class INI_file
{
private:
	myINI _values;
	std::string _fileName;

public:
	INI_file(const std::string& fileName) : _fileName{ fileName }
	{
		int strNum{ 0 };
		std::string str{ "" };
		std::string sectionName{ "" };

		//std::cout << "create a INI parser, file: " << fileName << std::endl;
		//read file
		std::ifstream input(_fileName);
		if (!input)
		{
			std::string a = "Ошибка открытия файла ";
			a.append(_fileName);
			throw (a.data());
		}

		while (std::getline(input, str)) // Так можно считывать до тех пор пока считывается.
		{
			strNum++;
			trim(str);
			if (!str.empty())
			{
				//*Если файл содержит некорректный синтаксис, нужно указать в исключении, на какой строке встретилась проблема.

				//строка не пустая
				trim(str);

				//if comment					
				if (str[0] == ';')
				{
					//*Строка комментариев.
					//Имеет формат : `; строка комментариев `. <br / > Парсер должен игнорировать такие строки, с ними ничего делать не нужно.
				}
				else if (str[0] == '[')
				{
					//*Строка имени секции — обозначает имя новой секции переменных.
					//Имеет формат : `[имя_секции] `. <br / > Пробелы и символы табуляции, стоящие до открывающей и после закрывающей скобки, игнорируются.
					if (str.back() == ']')
					{
						//section
						sectionName = str.substr(1, str.size() - 2);
						_values[sectionName];	//делаем это на случай пустой секции(нет ключей)
					}
					else
					{
						std::string a = "Section error in line ";
						a.append(std::to_string(strNum));
						throw (a.data());
					}
				}
				else
				{
					//*Строка задания переменной — задаёт значение переменной.
					//Имеет формат : ` название_переменной = значение_переменной `. <br / > Количество пробелов между символами равенства может быть произвольным.
					//Для простоты будем считать, что значения могут быть либо строкой, либо числом.Несколько значений не допускается.						
					std::istringstream iss(str);
					std::string item{ "" }, value{ "" };

					std::getline(iss, item, '=');
					std::getline(iss, value);

					trim(item);
					if (item == "")
					{
						std::string a = "Item error in line ";
						a.append(std::to_string(strNum));
						throw (a.data());
					}

					trim(value);

					//ищем комментарии в конце строки
					size_t flag = value.find(';');
					if (flag != std::string::npos)
					{
						value = value.substr(0, flag - 1);
						trim(value);
					}

					//запоминаем значение в ТЕКСТОВОМ формате
					_values[sectionName][item] = value;

				}
			}
		}
		input.close();

	}
		
	~INI_file() = default;

	std::string get_value(const std::string& sectionAndItem) const
	{
		//Вам нужно реализовать класс парсера INI - файлов, который предоставляет для пользователя одну шаблонную функцию, позволяющую получить значение переменной в определённой секции.
		size_t flag = sectionAndItem.find('.');
		if (flag == std::string::npos)
		{
			std::string a = "Incorrect format of Section.Item: ";
			a.append(sectionAndItem);
			throw (a.data());
		}
		//делаем расшифровку параметров поиска
		std::string section = sectionAndItem.substr(0, flag);
		std::string key = sectionAndItem.substr(flag + 1);

		//ищем секцию
		auto it = _values.find(section);
		if (it == _values.end())
		{
			std::string a = "Section do not exists: ";
			a.append(section);
			throw (a.data());
		}
		//ищем ключ в секции
		auto item_it = it->second.find(key);
		if (item_it == it->second.end())
		{
			//*Если искомого значения переменной нет, нужно вывести подсказку для пользователя — названия других переменных из этой секции.Возможно, пользователь опечатался.
			std::string result{ "\nThis is available items:\n" };
			auto it = _values.find(section);

			for (myINI_item::const_iterator eptr = it->second.begin(); eptr != it->second.end(); eptr++)
			{
				result = result + "- " + eptr->first + "\n";
			}
			std::string a = "Item do not exists: ";
			a.append(sectionAndItem);
			a.append(result);
			throw (a.data());
		}


		if (_values.at(section).at(key) == "")
		{
			//значение пустое
			std::string a = "Value do not exists: ";
			a.append(_values.at(section).at(key).data());
			throw (a.data());
		}
		//конвертируем в нужный тип через стрим
		std::istringstream iss(_values.at(section).at(key));
		std::string value;
		if (!(iss >> value))
		{
			std::string a = "Error of convert value: ";
			a.append(_values.at(section).at(key).data());
			throw (a.data());
		}
		return value;
	}

};

