#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "CryptographyManager.h"
#include "dbManager.h"
#include "addeditdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, CryptographyManager* cryptographyManager = nullptr);
    ~MainWindow();

    CryptographyManager *getCryptoManager() const;

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void showDetails(int row, int column);
    void on_tableHeaderClicked(int column);

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    CryptographyManager* cryptoManager;
    DbManager* dbManager;

/**
 * @brief Инициализирует таблицу в пользовательском интерфейсе.
 *
 * Этот метод настраивает виджет таблицы, задавая ее столбцы,
 * заголовки и другие необходимые свойства для отображения записей.
 */
    void setupTable();

/**
 * @brief Заполняет таблицу начальными данными.
 *
 * Этот метод заполняет таблицу расшифрованными записями пользователя из базы данных.
 */
    void fillTable();

/**
 * @brief Добавляет запись в таблицу пользовательского интерфейса.
 *
 * @param record Указатель на объект Record, который нужно добавить.
 * @param row Индекс строки, в которую нужно добавить запись. Если -1, запись добавляется в новую строку.
 *
 * Этот метод вставляет запись в виджет таблицы на указанную строку.
 * Если индекс строки равен -1, запись добавляется в конец таблицы.
 */
    void addRecordToTable(Record* record, int row = -1);

/**
 * @brief Создает объект Record из данных диалогового окна.
 *
 * @param dialog Ссылка на объект EntryDialog, содержащий данные от пользователя.
 * @return Объект Record, заполненный данными из диалогового окна.
 *
 * Этот метод извлекает информацию из EntryDialog и создает
 * новый объект Record с введенными данными, включая установку даты истечения
 * срока через три месяца от текущей даты.
 */
    Record getRecordFromDialog(const EntryDialog& dialog);

/**
 * @brief Добавляет или обновляет запись в базе данных.
 *
 * @param record Объект Record, который нужно добавить или обновить в базе данных.
 * @param update Флаг, указывающий, нужно ли обновить существующую запись (true) или добавить новую (false).
 *
 * Этот метод шифрует необходимые поля объекта Record
 * перед добавлением или обновлением записи в базе данных.
 */
    void addRecordToDb(Record record, bool update = false);

/**
 * @brief Получает все записи пользователя из базы данных.
 *
 * @param username Имя пользователя, для которого нужно получить записи.
 * @return Вектор объектов Record, принадлежащих указанному пользователю.
 *
 * Этот метод извлекает все записи пользователя из базы данных,
 * расшифровывает их и возвращает в виде вектора объектов Record.
 */
    std::vector<Record> getAllUserRecordsFromDb(const std::string& username);

/**
 * @brief Получает дату через три месяца от текущей даты.
 *
 * @return Строка, представляющая дату через три месяца в формате "ГГГГ-ММ-ДД".
 *
 * Этот метод вычисляет дату, добавляя три месяца к текущей дате,
 * и возвращает ее в виде строки в формате "ГГГГ-ММ-ДД".
 */
    std::string getDateAfterThreeMonths();
};

#endif // MAINWINDOW_H
