#include "Record.h"
#include <iostream>


Record::Record(const std::string &masterUsername, const std::string &recName, const std::string &url,
               const std::string &username, const std::string &password, const std::string &tag,
               const std::string &expires, int id) : master_username(masterUsername), rec_name(recName), url(url),
                                                     username(username), password(password), tag(tag), expires(expires),
                                                     id(id) {}

int Record::getId() const {
    return id;
}

void Record::setId(int id) {
    Record::id = id;
}

const std::string &Record::getMasterUsername() const {
    return master_username;
}

void Record::setMasterUsername(const std::string &masterUsername) {
    master_username = masterUsername;
}

const std::string &Record::getRecName() const {
    return rec_name;
}

void Record::setRecName(const std::string &recName) {
    rec_name = recName;
}

const std::string &Record::getUrl() const {
    return url;
}

void Record::setUrl(const std::string &url) {
    Record::url = url;
}

const std::string &Record::getUsername() const {
    return username;
}

void Record::setUsername(const std::string &username) {
    Record::username = username;
}

const std::string &Record::getPassword() const {
    return password;
}

void Record::setPassword(const std::string &password) {
    Record::password = password;
}

const std::string &Record::getTag() const {
    return tag;
}

void Record::setTag(const std::string &tag) {
    Record::tag = tag;
}

const std::string &Record::getExpires() const {
    return expires;
}

void Record::setExpires(const std::string &expires) {
    Record::expires = expires;
}
