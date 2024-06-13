#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void setupTable();
};

#endif // MAINWINDOW_H
