#pragma once
#include <pqxx/pqxx>
/*
## База данных
Для выполнения задания рекомендуется использовать базу данных PostgreSQL.
Для подключения к базе данных рекомендуется использовать библиотеку `libpqxx`.
Настройки базы данных (хост, порт, название БД, имя пользователя, пароль) следует хранить в ini-файле конфигурации.
При первом запуске программы «Паук» следует выполнить создание таблиц базы данных, используя запрос `CREATE TABLE IF NOT EXISTS`.
*/
class DB_Client
{
private:
    std::string connectionString;
    std::string DBHost, DBPort, DBName, DBUser, DBPassword;
	
    std::string createConnectionString()
    {
        //Настройки базы данных (хост, порт, название БД, имя пользователя, пароль) следует хранить в ini-файле конфигурации.
        
        //"host=localhost port=5432 dbname=postgres user=postgres password=postgres"
        std::string res = "host = "+ DBHost +" port= "+ DBPort +" dbname = " + DBName + " user = " + DBUser + " password = " + DBPassword;
        return res;
    }

    bool findKeyword(const std::string& keyword)
    {
        pqxx::connection conn(connectionString);
        pqxx::work transact{ conn };
        bool id = transact.query_value<bool>("SELECT EXISTS(SELECT id FROM keywords WHERE keyword = \'" + keyword + "\');");
        return id;
    }

public:
    DB_Client(const std::string& DBHost, const std::string& DBPort, const std::string& DBName, const std::string& DBUser, const std::string& DBPassword) : DBHost{ DBHost }, DBPort{ DBPort }, DBName{ DBName }, DBUser{ DBUser }, DBPassword{ DBPassword }
    {
        //При первом запуске программы «Паук» следует выполнить создание таблиц базы данных, используя запрос `CREATE TABLE IF NOT EXISTS`.
        connectionString = createConnectionString();
        pqxx::connection conn(connectionString);
        pqxx::work transact(conn);
        //create tables
        transact.exec("CREATE TABLE IF NOT EXISTS keywords( "
			"id SERIAL PRIMARY KEY, "
			"keyword TEXT NOT NULL UNIQUE)"
		);
        transact.exec("CREATE TABLE IF NOT EXISTS urls( "
			"id SERIAL PRIMARY KEY, "
			"url TEXT NOT NULL UNIQUE)"
		);
        transact.exec("CREATE TABLE IF NOT EXISTS keyword_urs_qty( "
			"id_keyword INTEGER REFERENCES keywords(id), "
			"id_url INTEGER REFERENCES urls(id), "
			"quantity INTEGER NOT NULL, "
			"CONSTRAINT k_u PRIMARY KEY(id_keyword, id_url))"
		);
        transact.commit();
    }
    DB_Client() = default;

    ~DB_Client()
    {
        //nothing
    }

    bool findUrl(const std::string& url)
    {
        //ищем ссылку в таблице ссылок
        pqxx::connection conn(connectionString);
        pqxx::work transact{ conn };
        bool id = transact.query_value<bool>("SELECT EXISTS(SELECT id FROM urls WHERE url = \'" + url + "\');");
        return id;
    }

    void addLink(const std::map<std::string, unsigned int>& words, const std::string& link)
    {
        //проверяем есть ли такая ссылка
        if (findUrl(link))
        {
            return; 
        }

        //подключаемся к БД
        pqxx::connection conn(connectionString);
        pqxx::work transact{ conn };

        //добавляем новую ссылку
        transact.exec_params("INSERT INTO urls (url) VALUES ( $1 )", link);
        transact.commit();

        for (const auto& [key, value] : words)
        {
            //проверяем есть ли такое слово
            if (!findKeyword(key))
            {
                //добавим новое слово
                transact.exec_params("INSERT INTO keywords (keyword) VALUES ( $1 )", key);
                transact.commit();
            }
            //создаем новую пару в третьей таблице
            transact.exec_params("INSERT INTO keyword_urs_qty (id_keyword, id_url, quantity) VALUES ("
                        "(SELECT id FROM keywords WHERE keyword = $1),"
                "(SELECT id FROM urls WHERE url = $2), $3)", key, link, std::to_string(value));
        }
        transact.commit();
    }

    std::map<std::string, int> getUrl(const std::string& keyword)
    {
        //ищем ссылки по ключевому слову
        std::map<std::string, int> result;

        //подключаемся к БД
        pqxx::connection conn(connectionString);
        pqxx::work transact{ conn };

        //ключевое слово для поиска
        std::string key_esc = transact.esc(keyword);
        
        //выбираем все ссылки по ключевому слову
        for (auto [url, qty] : transact.query<std::string, int>
            ("SELECT u.url, kuq.quantity "
                "FROM urls u "
                "JOIN keyword_urs_qty kuq ON u.id = kuq.id_url "
                "JOIN keywords k ON kuq.id_keyword = k.id "
                "WHERE k.keyword = '" + key_esc + "' "))
        {
            result[url] = qty;
        };
        return result;//сколько раз ключевое слово встречалось на странице
    }
};