#ifndef DBMANAGERTESTS_DBMANAGER_H
#define DBMANAGERTESTS_DBMANAGER_H

#include "PostgresCRUD.h"
#include "vector"
#include "../Entities/Record.h"

/**
 * @brief Класс DbManager отвечает за управление любой базой данных с конкретной структурой.
 */
class DbManager {
public:
    /**
     * @brief Конструктор класса DbManager.
     * @param connection_string Строка подключения к базе данных.
     * @param table_name Название таблицы в базе данных
     */
    explicit DbManager(const std::string& connection_string, const std::string& table_name);

    /**
     * @brief Создает таблицу с заданным в поле названием, если она не существует.
     */
    void createTable();

    /**
     * @brief Добавляет запись в таблицу.
     * @param record Запись, которую нужно добавить.
     */
    void addRecord(Record record);

    /**
     * @brief Полностью обновляет запись в БД на основе переданной.
     * @param record Новый вид записи.
     */
    void updateRecord(const Record& record);

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
    /// Средство управления базой данных
    PostgresCRUD db;
    /// Имя таблицы
    std::string table_name;


    /// Метод конвертации record в std::map
    std::map<std::string, std::string> recordToMap(const Record& record);

    /// Метод конвертации pqxx::result в std::vector<Record>
    std::vector<Record> resultToRecord(const pqxx::result& result);
};


#endif //DBMANAGERTESTS_DBMANAGER_H
