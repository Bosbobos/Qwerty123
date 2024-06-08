#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QPalette>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    connect(ui->usernameInput, &QLineEdit::textChanged, this, &RegistrationWindow::validateInput);
    connect(ui->passwordInput, &QLineEdit::textChanged, this, &RegistrationWindow::validateInput);
    connect(ui->confirmPasswordInput, &QLineEdit::textChanged, this, &RegistrationWindow::validateInput);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_registerButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();
    // Logic for handling registration should be here
}

bool RegistrationWindow::isValidInput(const QString &input)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])[A-Za-z]{8,32}$");
    return regex.match(input).hasMatch();
}

void RegistrationWindow::validateInput()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();

    bool isUsernameValid = isValidInput(username);
    bool isPasswordValid = isValidInput(password);
    bool isConfirmPasswordValid = (password == confirmPassword);

    QPalette palette;
    if (isUsernameValid) {
        palette.setColor(QPalette::Base, Qt::white);
    } else {
        palette.setColor(QPalette::Base, Qt::red);
    }
    ui->usernameInput->setPalette(palette);

    if (isPasswordValid) {
        palette.setColor(QPalette::Base, Qt::white);
    } else {
        palette.setColor(QPalette::Base, Qt::red);
    }
    ui->passwordInput->setPalette(palette);

    if (isConfirmPasswordValid) {
        palette.setColor(QPalette::Base, Qt::white);
    } else {
        palette.setColor(QPalette::Base, Qt::red);
    }
    ui->confirmPasswordInput->setPalette(palette);

    ui->registerButton->setEnabled(isUsernameValid && isPasswordValid && isConfirmPasswordValid);
}
