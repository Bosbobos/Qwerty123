#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    QString defaultStyle = "QLineEdit { border: 2px solid grey; }";

    ui->usernameInput->setStyleSheet(defaultStyle);
    ui->passwordInput->setStyleSheet(defaultStyle);
    ui->confirmPasswordInput->setStyleSheet(defaultStyle);

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

    if (isValidInput(username) && isValidInput(password) && password == confirmPassword) {
        processRegistration(username, password); // Вызов функции для обработки регистрации
    }
}

bool RegistrationWindow::isValidInput(const QString &input)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[A-Za-z\\d]{8,32}$");
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

    QString validStyle = "QLineEdit { border: 2px solid green; }";
    QString invalidStyle = "QLineEdit { border: 2px solid red; }";
    QString defaultStyle = "QLineEdit { border: 2px solid grey; }";

    ui->usernameInput->setStyleSheet(username.isEmpty() ? defaultStyle : (isUsernameValid ? validStyle : invalidStyle));
    ui->passwordInput->setStyleSheet(password.isEmpty() ? defaultStyle : (isPasswordValid ? validStyle : invalidStyle));
    ui->confirmPasswordInput->setStyleSheet(confirmPassword.isEmpty() ? defaultStyle : (isConfirmPasswordValid ? validStyle : invalidStyle));

    ui->registerButton->setEnabled(isUsernameValid && isPasswordValid && isConfirmPasswordValid);
}

void RegistrationWindow::processRegistration(const QString &username, const QString &password)
{
    // Здесь добавьте логику для шифрования, отправку данных и сверку на повторение в БД  при регистрации:

    // ...

    // Успешная регистрация
    QMessageBox::information(this, "Registration", "Registration successful for user: " + username);
}
