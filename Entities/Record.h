#ifndef QWERTY123_RECORD_H
#define QWERTY123_RECORD_H


#include <string>

struct Record {
    int id;
    std::string master_username;
    std::string rec_name;
    std::string url;
    std::string username;
    std::string password;
    std::string tag;
    std::string expires;

    Record(const std::string &masterUsername, const std::string &recName, const std::string &url,
           const std::string &username, const std::string &password, const std::string &tag, const std::string &expires,
           int id);

    int getId() const;

    void setId(int id);

    const std::string &getMasterUsername() const;

    void setMasterUsername(const std::string &masterUsername);

    const std::string &getRecName() const;

    void setRecName(const std::string &recName);

    const std::string &getUrl() const;

    void setUrl(const std::string &url);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getTag() const;

    void setTag(const std::string &tag);

    const std::string &getExpires() const;

    void setExpires(const std::string &expires);
};


#endif //QWERTY123_RECORD_H
