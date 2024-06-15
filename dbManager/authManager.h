#ifndef DBMANAGER_AUTHMANAGER_H
#define DBMANAGER_AUTHMANAGER_H


#include "PostgresCRUD.h"

/**
 * @brief Класс, отвечающий за аутентификацию.
 */
class AuthManager {
public:
    /**
     * @brief Конструктор класса AuthManager.
     * @param connection_string Строка подключения к базе данных.
     * @param table_name Название таблицы в базе данных
     */
    AuthManager(const std::string& connection_string, const std::string& table_name);

    /**
     * @brief Создает таблицу с заданным в поле названием, если она не существует.
     */
    void createTable();

    /**
     * Добавляет запись в базу данных.
     * @param login Логин, который нужно добавить.
     */
    void addRecord(const std::string& login);

    /**
     * Проверяет, присутствует ли заданный логин в базе данных.
     * @param login Логин, наличие которого нужно проверить.
     * @return True, если логин существует, иначе false.
     */
    bool loginExists(const std::string& login);

private:
    /// Средство управления базой данных
    PostgresCRUD db;
    /// Имя таблицы
    std::string table_name;
};


#endif //DBMANAGER_AUTHMANAGER_H
