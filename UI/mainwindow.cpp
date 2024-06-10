#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "entrydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTable();

    /* Врубаем не все кнопочки пока что
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::showDetails);
*/
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
    ui->verticalLayout->addWidget(tableWidget);
}
// Логика кнопок ДОЛЖНА БЫТЬ ниже:

