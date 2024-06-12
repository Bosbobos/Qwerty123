#ifndef QWERTY123_RECORD_H
#define QWERTY123_RECORD_H


#include <string>

struct Record {
    /// Id записи в БД
    int id;
    /// Логин пользователя в менеджере
    std::string master_username;
    /// Название записи
    std::string rec_name;
    /// URL, от которого представлены логин и пароль
    std::string url;
    /// Сохранённый логин
    std::string username;
    /// Сохранённый пароль
    std::string password;
    /// Тег записи
    std::string tag;
    /// Дата истечения записи
    std::string expires;

    Record(int id, const std::string &masterUsername, const std::string &recName, const std::string &url,
           const std::string &username, const std::string &password, const std::string &tag, const std::string &expires);

    Record(const std::string &masterUsername, const std::string &recName, const std::string &url,
           const std::string &username, const std::string &password, const std::string &tag, const std::string &expires);

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
