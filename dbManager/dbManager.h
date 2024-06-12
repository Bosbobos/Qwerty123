#ifndef DBMANAGERTESTS_DBMANAGER_H
#define DBMANAGERTESTS_DBMANAGER_H

#include "PostgresCRUD.h"
#include "vector"
#include "../Entities/Record.h"

/**
 * @brief Класс DbManager отвечает за управление базой данных Qwerty123.
 */
class DbManager {
public:
    /**
     * @brief Конструктор класса DbManager.
     * @param connection_string Строка подключения к базе данных.
     */
    explicit DbManager(const std::string& connection_string, const std::string& table_name);

    /**
     * @brief Создает таблицу Qwerty123, если она не существует.
     */
    void createTable();

    /**
     * @brief Добавляет запись в таблицу Qwerty123.
     * @param record Запись, которую нужно добавить.
     */
    void addRecord(Record record);

    /**
     * @brief Обновляет пароль записи по идентификатору.
     * @param id Идентификатор записи.
     * @param password Новый пароль.
     */
    void updatePassword(int id, const std::string& password);

    /**
     * @brief Обновляет тег записи по идентификатору.
     * @param id Идентификатор записи.
     * @param tag Новый тег.
     */
    void updateTag(int id, const std::string& tag);

    /**
     * @brief Удаляет запись по идентификатору.
     * @param id Идентификатор записи.
     */
    void deleteRecord(int id);

    /**
     * @brief Находит запись по идентификатору.
     * @param id Идентификатор записи.
     * @return Запись в виде объекта Record.
     * @throws std::runtime_error Если запись не найдена.
     */
    Record findRecord(int id);

    /**
     * @brief Находит все записи пользователя по имени пользователя.
     * @param username Имя пользователя.
     * @return Вектор записей в виде объектов Record.
     */
    std::vector<Record> findAllUserRecords(const std::string& username);

    /**
     * @brief Находит все записи пользователя по имени пользователя и тегу.
     * @param username Имя пользователя.
     * @param tag Тег.
     * @return Вектор записей в виде объектов Record.
     */
    std::vector<Record> findAllUserRecordsWithTag(const std::string& username, const std::string& tag);
private:
    std::string table_name;
    PostgresCRUD db;

    std::vector<Record> resultToRecord(const pqxx::result& result);
};


#endif //DBMANAGERTESTS_DBMANAGER_H
