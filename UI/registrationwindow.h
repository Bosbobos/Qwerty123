#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_registerButton_clicked();
    void validateInput();

private:
    Ui::RegistrationWindow *ui;
    bool isValidInput(const QString &input);
};

#endif // REGISTRATIONWINDOW_H
