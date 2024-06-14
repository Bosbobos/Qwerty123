#include "authManager.h"

AuthManager::AuthManager(const std::string& connection_string, const std::string& table_name)
        : db(connection_string), table_name(table_name) {}

void AuthManager::createTable() {
    std::string create_table_sql =
            "CREATE TABLE IF NOT EXISTS " + table_name + " ("
                                                         "id SERIAL PRIMARY KEY, "
                                                         "login VARCHAR(128) UNIQUE"
                                                         ");";
    db.read(create_table_sql);
}

void AuthManager::addRecord(const std::string& login) {
    std::map<std::string, std::string> data = {{"login", login}};
    db.create(table_name, data);
}

bool AuthManager::loginExists(const std::string& login) {
    std::string query = "SELECT COUNT(*) FROM " + table_name + " WHERE login = '" + login + "';";
    pqxx::result r = db.read(query);
    return r[0][0].as<int>() > 0;
}
