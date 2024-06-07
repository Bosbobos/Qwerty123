#include "PostgresCRUD.h"

PostgresCRUD::PostgresCRUD(const std::string& connection_string)
        : conn(connection_string) {
    if (!conn.is_open()) {
        throw std::runtime_error("Can't open database");
    }
}

PostgresCRUD::~PostgresCRUD() {
}

void PostgresCRUD::create(const std::string& table, const std::map<std::string, std::string>& data) {
    std::string sql = "INSERT INTO " + table + " (";

    for (const auto& pair : data) {
        sql += pair.first + ",";
    }
    sql.pop_back(); // Remove trailing comma

    sql += ") VALUES (";

    for (const auto& pair : data) {
        sql += conn.quote(pair.second) + ",";
    }
    sql.pop_back(); // Remove trailing comma

    sql += ");";

    pqxx::work W(conn);
    W.exec(sql);
    W.commit();
}

pqxx::result PostgresCRUD::read(const std::string& query) {
    pqxx::nontransaction N(conn);
    return N.exec(query);
}

void PostgresCRUD::update(const std::string& table, const std::map<std::string, std::string>& data, const std::string& condition) {
    std::string sql = "UPDATE " + table + " SET ";

    for (const auto& pair : data) {
        sql += pair.first + "=" + conn.quote(pair.second) + ",";
    }
    sql.pop_back(); // Remove trailing comma

    sql += " WHERE " + condition + ";";

    pqxx::work W(conn);
    W.exec(sql);
    W.commit();
}

void PostgresCRUD::delete_record(const std::string& table, const std::string& condition) {
    std::string sql = "DELETE FROM " + table + " WHERE " + condition + ";";

    pqxx::work W(conn);
    W.exec(sql);
    W.commit();
}
