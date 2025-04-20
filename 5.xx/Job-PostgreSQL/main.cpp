#include <pqxx/pqxx>
#include <iostream>
#include <vector>

class ClientManager {
private:
    pqxx::connection conn;

public:
    ClientManager(const std::string& conn_str) : conn(conn_str) {}

    void create_tables() {
        pqxx::work txn(conn);
        txn.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY, "
            "first_name TEXT, "
            "last_name TEXT, "
            "email TEXT UNIQUE);"
        );
        txn.exec(
            "CREATE TABLE IF NOT EXISTS phones ("
            "id SERIAL PRIMARY KEY, "
            "client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE, "
            "phone TEXT);"
        );
        txn.commit();
    }

    void add_client(const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3);",
                        first_name, last_name, email);
        txn.commit();
    }

    void add_phone(int client_id, const std::string& phone) {
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2);", client_id, phone);
        txn.commit();
    }

    void update_client(int client_id, const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec_params("UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4;",
                        first_name, last_name, email, client_id);
        txn.commit();
    }

    void delete_phone(int phone_id) {
        pqxx::work txn(conn);
        txn.exec_params("DELETE FROM phones WHERE id = $1;", phone_id);
        txn.commit();
    }

    void delete_client(int client_id) {
        pqxx::work txn(conn);
        txn.exec_params("DELETE FROM clients WHERE id = $1;", client_id);
        txn.commit();
    }

    void find_client(const std::string& search) {
        pqxx::work txn(conn);
        pqxx::result r = txn.exec_params(
            "SELECT c.id, c.first_name, c.last_name, c.email, p.phone "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE c.first_name ILIKE $1 OR c.last_name ILIKE $1 OR c.email ILIKE $1 OR p.phone ILIKE $1;",
            "%" + search + "%");

        for (auto row : r) {
            std::cout << "ID: " << row["id"].c_str()
                      << ", Name: " << row["first_name"].c_str() << " " << row["last_name"].c_str()
                      << ", Email: " << row["email"].c_str()
                      << ", Phone: " << (row["phone"].is_null() ? "None" : row["phone"].c_str())
                      << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    ClientManager manager("host=192.168.50.15 port=5432 dbname=test2 user=postgres password=12345678");

    manager.create_tables();
    manager.add_client("Иван", "Иванов", "ivanov@yandex.ru");
    manager.add_phone(1, "+79161234567");
    manager.update_client(1, "Иван", "Иванов", "ivan_new@yandex.ru");
    manager.find_client("Иван");
    manager.delete_phone(1);
    manager.delete_client(1);

    return 0;
}
