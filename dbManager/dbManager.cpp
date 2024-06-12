#include "dbManager.h"

DbManager::DbManager(const std::string& connection_string, const std::string& table_name)
        : db(connection_string), table_name(table_name) {}

void DbManager::createTable() {
    std::string create_table_sql =
            "CREATE TABLE IF NOT EXISTS " + table_name + " ("
                                                         "id SERIAL PRIMARY KEY, "
                                                         "master_username VARCHAR(50), "
                                                         "rec_name VARCHAR(50), "
                                                         "url VARCHAR(255), "
                                                         "username VARCHAR(50), "
                                                         "password VARCHAR(50), "
                                                         "tag VARCHAR(50), "
                                                         "expires VARCHAR(50)"
                                                         ");";
    db.read(create_table_sql);
}

void DbManager::addRecord(Record record) {
    std::map<std::string, std::string> data = recordToMap(record);
    db.create(table_name, data);
}

void DbManager::updateRecord(const Record& record) {
    std::map<std::string, std::string> data = recordToMap(record);
    std::string condition = "id = " + std::to_string(record.id);
    db.update(table_name, data, condition);
}

void DbManager::updatePassword(int id, const std::string& password) {
    std::string condition = "id = " + std::to_string(id);
    std::map<std::string, std::string> data = {{"password", password}};
    db.update(table_name, data, condition);
}

void DbManager::updateTag(int id, const std::string& tag) {
    std::string condition = "id = " + std::to_string(id);
    std::map<std::string, std::string> data = {{"tag", tag}};
    db.update(table_name, data, condition);
}

void DbManager::deleteRecord(int id) {
    std::string condition = "id = " + std::to_string(id);
    db.delete_record(table_name, condition);
}

Record DbManager::findRecord(int id) {
    std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
    pqxx::result r = db.read(query);
    if (r.empty()) {
        throw std::runtime_error("Record not found");
    }
    return resultToRecord(r)[0];
}

std::vector<Record> DbManager::findAllUserRecords(const std::string& username) {
    std::string query = "SELECT * FROM " + table_name + " WHERE username = '" + username + "';";
    pqxx::result r = db.read(query);

    return resultToRecord(r);
}

std::vector<Record> DbManager::findAllUserRecordsWithTag(const std::string& username, const std::string& tag) {
    std::string query = "SELECT * FROM " + table_name + " WHERE username = '" + username + "' AND tag LIKE '%" + tag + "%';";
    pqxx::result r = db.read(query);

    return resultToRecord(r);
}

std::map<std::string, std::string> DbManager::recordToMap(const Record& record) {
    return {
            {"master_username", record.master_username},
            {"rec_name",        record.rec_name},
            {"url",             record.url},
            {"username",        record.username},
            {"password",        record.password},
            {"tag",             record.tag},
            {"expires",         record.expires}
    };
}

std::vector<Record> DbManager::resultToRecord(const pqxx::result &result) {
    std::vector<Record> records;

    for (const auto &row: result) {
        int id = row["id"].as<int>();
        std::string master_username = row["master_username"].as<std::string>();
        std::string rec_name = row["rec_name"].as<std::string>();
        std::string url = row["url"].as<std::string>();
        std::string username = row["username"].as<std::string>();
        std::string password = row["password"].as<std::string>();
        std::string tag = row["tag"].as<std::string>();
        std::string expires = row["expires"].as<std::string>();

        records.emplace_back(id, master_username, rec_name, url, username, password, tag, expires);
    }

    return records;
}
