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

    void setupTable();
    void fillTable();
    void addRecordToTable(Record* record, int row = -1);
    Record getRecordFromDialog(const EntryDialog& dialog);
    void addRecordToDb(Record record, bool update = false);
    std::vector<Record> getAllUserRecordsFromDb(const std::string& username);
    std::string getDateAfterThreeMonths();
};

#endif // MAINWINDOW_H
