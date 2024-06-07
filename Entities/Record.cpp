#include "Record.h"
#include <iostream>

// Constructor
Record::Record(int id, const std::string& master_username, const std::string& username, const std::string& password, const std::string& tag)
        : id(id), master_username(master_username), username(username), password(password), tag(tag) {}

// Getters
int Record::getId() const {
    return id;
}

std::string Record::getMasterUsername() const {
    return master_username;
}

std::string Record::getUsername() const {
    return username;
}

std::string Record::getPassword() const {
    return password;
}

std::string Record::getTag() const {
    return tag;
}

// Setters
void Record::setId(int id) {
    this->id = id;
}

void Record::setMasterUsername(const std::string& master_username) {
    this->master_username = master_username;
}

void Record::setUsername(const std::string& username) {
    this->username = username;
}

void Record::setPassword(const std::string& password) {
    this->password = password;
}

void Record::setTag(const std::string& tag) {
    this->tag = tag;
}
