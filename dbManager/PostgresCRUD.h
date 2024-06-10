#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <pqxx/pqxx>
#include <map>

/**
 * @brief Класс для выполнения операций CRUD (Create, Read, Update, Delete) в базе данных PostgreSQL.
 */
class PostgresCRUD {
public:
    /**
     * @brief Конструктор класса PostgresCRUD.
     * @param connection_string Строка подключения к базе данных PostgreSQL.
     */
    PostgresCRUD(const std::string& connection_string);

    /**
     * @brief Деструктор класса PostgresCRUD.
     * Поскольку закрытие соединения происходит автоматически, не делает ничего.
     */
    ~PostgresCRUD();

    /**
     * @brief Создает новую запись в указанной таблице.
     * @param table Имя таблицы, в которую будет добавлена запись.
     * @param data Пара ключ-значение, представляющая данные для новой записи.
     */
    void create(const std::string& table, const std::map<std::string, std::string>& data);

    /**
     * @brief Выполняет запрос на чтение данных из базы данных.
     * @param query SQL-запрос для чтения данных.
     * @return Результат выполнения запроса в виде объекта pqxx::result.
     */
    pqxx::result read(const std::string& query);

    /**
     * @brief Обновляет существующие записи в указанной таблице.
     * @param table Имя таблицы, в которой будут обновлены записи.
     * @param data Пара ключ-значение, представляющая новые данные для записи.
     * @param condition Условие для обновления записей (например, "id = 1").
     */
    void update(const std::string& table, const std::map<std::string, std::string>& data, const std::string& condition);

    /**
     * @brief Удаляет записи из указанной таблицы.
     * @param table Имя таблицы, из которой будут удалены записи.
     * @param condition Условие для удаления записей (например, "id = 1").
     */
    void delete_record(const std::string& table, const std::string& condition);

private:
    /**
     * @brief Объект соединения с базой данных PostgreSQL.
     */
    pqxx::connection conn;
};

#endif // CRUD_H
