#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void resizeEvent(QResizeEvent *event);
    void scaleGif();
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void validateInput();

private:
    Ui::LoginWindow *ui;
    bool isValidInput(const QString &input);
    QMovie *movie;
};

#endif // LOGINWINDOW_H
