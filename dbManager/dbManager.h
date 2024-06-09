#ifndef DBMANAGERTESTS_DBMANAGER_H
#define DBMANAGERTESTS_DBMANAGER_H

#include "PostgresCRUD.h"
#include "vector"
#include "../Entities/Record.h"

class DbManager {
public:
    explicit DbManager(const std::string& connection_string);

    void createTable();

    void addRecord(const std::string& master_username,
                   const std::string& rec_name,
                   const std::string& url,
                   const std::string& username,
                   const std::string& password,
                   const std::string& tag,
                   const std::string& expires);

    void updatePassword(int id, const std::string& password);

    void updateTag(int id, const std::string& tag);

    void deleteRecord(int id);

    Record findRecord(int id);

    std::vector<Record> findAllUserRecords(const std::string& username);

    std::vector<Record> findAllUserRecordsWithTag(const std::string& username, const std::string& tag);

private:
    PostgresCRUD db;

    std::vector<Record> resultToRecord(const pqxx::result& result);
};


#endif //DBMANAGERTESTS_DBMANAGER_H
