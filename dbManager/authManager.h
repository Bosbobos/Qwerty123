#ifndef DBMANAGER_AUTHMANAGER_H
#define DBMANAGER_AUTHMANAGER_H


#include "PostgresCRUD.h"

class AuthManager {
public:
    AuthManager(const std::string& connection_string, const std::string& table_name);

    void createTable();
    void addRecord(const std::string& login);
    bool loginExists(const std::string& login);

private:
    PostgresCRUD db;
    std::string table_name;
};


#endif //DBMANAGER_AUTHMANAGER_H
