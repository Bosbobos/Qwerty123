#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <pqxx/pqxx>
#include <map>

class PostgresCRUD {
public:
    PostgresCRUD(const std::string& connection_string);
    ~PostgresCRUD();

    void create(const std::string& table, const std::map<std::string, std::string>& data);
    pqxx::result read(const std::string& query);
    void update(const std::string& table, const std::map<std::string, std::string>& data, const std::string& condition);
    void delete_record(const std::string& table, const std::string& condition);

private:
    pqxx::connection conn;
};

#endif // CRUD_H
