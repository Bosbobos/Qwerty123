#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addeditdialog.h"
#include "Record.h"
#include "ConfigManager.h"
#include <QHeaderView>
#include <QDebug>
#include <chrono>
#include <iosfwd>

MainWindow::MainWindow(QWidget *parent, CryptographyManager* cryptographyManager)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbManager = new DbManager(GetDbConnectionString(), "Qwerty123");
    cryptoManager = cryptographyManager;
    setupTable();

    ui->detailsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable()
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(7);
    QStringList headers = {"Title", "Login", "Password", "URL", "Tag", "Expires", "Id"};
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setSortingEnabled(true);  // Enable sorting
    tableWidget->sortByColumn(4, Qt::AscendingOrder);  // Initial sort by Tag column
    ui->verticalLayout->addWidget(tableWidget);
    ui->verticalLayout->addWidget(ui->detailsLabel);
    tableWidget->setColumnHidden(6, true);

    fillTable();
}

void MainWindow::fillTable()
{
    dbManager->createTable();
    std::vector<Record> records = getAllUserRecordsFromDb(cryptoManager->getUserId());

    for (auto record : records)
        addRecordToTable(&record);
}

void MainWindow::on_addButton_clicked()
{
    EntryDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Record* record = new Record(cryptoManager->getUserId(),
                                    dialog.getTitle().toStdString(),
                                    dialog.getUrl().toStdString(),
                                    dialog.getUsername().toStdString(),
                                    dialog.getPassword().toStdString(),
                                    dialog.getTag().toStdString(),
                                    getDateAfterThreeMonths()
                                    );
        addRecordToTable(record);
        addRecordToDb(*record);
    }
}

void MainWindow::on_editButton_clicked()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        EntryDialog dialog(this);
        dialog.setTitle(tableWidget->item(currentRow, 0)->text());
        dialog.setUsername(tableWidget->item(currentRow, 1)->text());
        dialog.setPassword(tableWidget->item(currentRow, 2)->text());
        dialog.setUrl(tableWidget->item(currentRow, 3)->text());
        dialog.setTag(tableWidget->item(currentRow, 4)->text());
        dialog.setId(tableWidget->item(currentRow, 6)->text().toInt());

        QString oldPassword = tableWidget->item(currentRow, 2)->text();

        if (dialog.exec() == QDialog::Accepted) {
            Record newRecord = getRecordFromDialog(dialog);

            if (tableWidget->item(currentRow, 2)->text() != oldPassword)
                newRecord.setExpires(getDateAfterThreeMonths());
            else
                newRecord.setExpires(tableWidget->item(currentRow, 5)->text().toStdString());

            addRecordToTable(&newRecord, currentRow);
            addRecordToDb(newRecord, true);
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        int id = tableWidget->item(currentRow, 6)->text().toInt();
        dbManager->deleteRecord(id);
        tableWidget->removeRow(currentRow);
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString searchText = ui->searchInput->text();
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < tableWidget->columnCount(); ++j) {
            if (tableWidget->item(i, j)->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        tableWidget->setRowHidden(i, !match);
    }
}

void MainWindow::showDetails(int row, int column)
{
    Q_UNUSED(column);
    QString details = QString("Title: %1\nLogin: %2\nPassword: %3\nURL: %4\nTag: %5\nExpires%6")
                          .arg(tableWidget->item(row, 0)->text())
                          .arg(tableWidget->item(row, 1)->text())
                          .arg(tableWidget->item(row, 2)->text())
                          .arg(tableWidget->item(row, 3)->text())
                          .arg(tableWidget->item(row, 4)->text())
                          .arg(tableWidget->item(row, 5)->text());
    ui->detailsLabel->setText(details);
}

// Slot for handling column header clicks to sort by tag alphabetically
void MainWindow::on_tableHeaderClicked(int column)
{
    if (column == 4) {  // Check if the Tag column header was clicked
        if (tableWidget->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder) {
            tableWidget->sortByColumn(column, Qt::DescendingOrder);  // Sort descending on second click
        } else {
            tableWidget->sortByColumn(column, Qt::AscendingOrder);   // Sort ascending on first click
        }
    }
}

CryptographyManager *MainWindow::getCryptoManager() const {
    return cryptoManager;
}

void MainWindow::addRecordToTable(Record* record, int row)
{
    if (row == -1)
    {
        row = tableWidget->rowCount();
        tableWidget->insertRow(row);
    }
    tableWidget->setSortingEnabled(false);
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record->getRecName())));
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record->getUsername())));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(record->getPassword())));
    tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(record->getUrl())));
    tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(record->getTag())));
    tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(record->getExpires())));
    tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(record->getId())));
    tableWidget->setSortingEnabled(true);
}

Record MainWindow::getRecordFromDialog(const EntryDialog& dialog)
{
    return {dialog.getId(),
            cryptoManager->getUserId(),
            dialog.getTitle().toStdString(),
            dialog.getUrl().toStdString(),
            dialog.getUsername().toStdString(),
            dialog.getPassword().toStdString(),
            dialog.getTag().toStdString(),
            getDateAfterThreeMonths()
    };
}

void MainWindow::addRecordToDb(Record record, bool update)
{
    record.setUsername(cryptoManager->Encrypt(record.getUsername()));
    record.setPassword(cryptoManager->Encrypt(record.getPassword()));
    record.setUrl(cryptoManager->Encrypt(record.getUrl()));
    record.setRecName(cryptoManager->Encrypt(record.getRecName()));

    update ? dbManager->updateRecord(record) : dbManager->addRecord(record);
}

std::vector<Record> MainWindow::getAllUserRecordsFromDb(const std::string& username)
{
    std::vector<Record> records = dbManager->findAllUserRecords(username);
    for (auto &record : records) {
        record.setUsername(cryptoManager->Decrypt(record.getUsername()));
        record.setPassword(cryptoManager->Decrypt(record.getPassword()));
        record.setUrl(cryptoManager->Decrypt(record.getUrl()));
        record.setRecName(cryptoManager->Decrypt(record.getRecName()));
    }

    return records;
}

std::string MainWindow::getDateAfterThreeMonths()
{
    auto now = std::chrono::system_clock::now();

    // Преобразуем текущую дату в структуру std::tm
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    // Добавляем 3 месяца
    now_tm.tm_mon += 3;

    // Обрабатываем переполнение месяца
    if (now_tm.tm_mon > 11) {
        now_tm.tm_mon -= 12;
        now_tm.tm_year += 1;
    }

    // Преобразуем std::tm обратно в time_t
    std::time_t future_time = std::mktime(&now_tm);

    // Преобразуем future_time в std::tm
    std::tm future_tm = *std::localtime(&future_time);

    // Преобразуем std::tm в строку
    std::ostringstream oss;
    oss << std::put_time(&future_tm, "%Y-%m-%d");

    return oss.str();
}
