#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addeditdialog.h"
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTable();

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::showDetails);

    ui->detailsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable()
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    QStringList headers = {"Title", "Login", "Password", "URL", "Tag"};
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setSortingEnabled(true);  // Enable sorting
    tableWidget->sortByColumn(4, Qt::AscendingOrder);  // Initial sort by Tag column
    ui->verticalLayout->addWidget(tableWidget);
    ui->verticalLayout->addWidget(ui->detailsLabel);
}

void MainWindow::on_addButton_clicked()
{
    EntryDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(dialog.getTitle()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(dialog.getUsername()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(dialog.getPassword()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(dialog.getUrl()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(dialog.getTag()));
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

        if (dialog.exec() == QDialog::Accepted) {
            tableWidget->item(currentRow, 0)->setText(dialog.getTitle());
            tableWidget->item(currentRow, 1)->setText(dialog.getUsername());
            tableWidget->item(currentRow, 2)->setText(dialog.getPassword());
            tableWidget->item(currentRow, 3)->setText(dialog.getUrl());
            tableWidget->item(currentRow, 4)->setText(dialog.getTag());
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
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
    QString details = QString("Title: %1\nLogin: %2\nPassword: %3\nURL: %4\nTag: %5")
                          .arg(tableWidget->item(row, 0)->text())
                          .arg(tableWidget->item(row, 1)->text())
                          .arg(tableWidget->item(row, 2)->text())
                          .arg(tableWidget->item(row, 3)->text())
                          .arg(tableWidget->item(row, 4)->text());
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
