#ifndef QWERTY123_RECORD_H
#define QWERTY123_RECORD_H


#include <string>

struct Record {
    int id;
    std::string master_username;
    std::string username;
    std::string password;
    std::string tag;

    // Constructors
    Record(int id, const std::string& master_username, const std::string& username, const std::string& password, const std::string& tag);

    // Getters
    int getId() const;
    std::string getMasterUsername() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getTag() const;

    // Setters
    void setId(int id);
    void setMasterUsername(const std::string& master_username);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setTag(const std::string& tag);
};


#endif //QWERTY123_RECORD_H
