#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "cryptography.cpp"
#include "authManager.cpp"
#include "ConfigManager.h"
#include "CryptographyManager.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    QString defaultStyle = "QLineEdit { border: 1px solid grey; }";

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

    QString validStyle = "QLineEdit { border: 1px solid green; }";
    QString invalidStyle = "QLineEdit { border: 1px solid red; }";
    QString defaultStyle = "QLineEdit { border: 1px solid grey; }";

    ui->usernameInput->setStyleSheet(username.isEmpty() ? defaultStyle : (isUsernameValid ? validStyle : invalidStyle));
    ui->passwordInput->setStyleSheet(password.isEmpty() ? defaultStyle : (isPasswordValid ? validStyle : invalidStyle));
    ui->confirmPasswordInput->setStyleSheet(confirmPassword.isEmpty() ? defaultStyle : (isConfirmPasswordValid ? validStyle : invalidStyle));

    ui->registerButton->setEnabled(isUsernameValid && isPasswordValid && isConfirmPasswordValid);
}

void RegistrationWindow::processRegistration(const QString &username, const QString &password)
{
    CryptographyManager* cryptoManager = new CryptographyManager(username.toStdString(), password.toStdString());
    AuthManager* auth = new AuthManager(GetDbConnectionString(), "Auth");
    auth->createTable();
    bool alreadyRegistered = auth->loginExists(cryptoManager->getUserId());

    if (alreadyRegistered)
        QMessageBox::warning (this, "Registration", "Such" + username + " already exists in the database, enter a different username");
    else
    {
        auth->addRecord(cryptoManager->getUserId());
        QMessageBox::information(this, "Registration", "Registration successful for user: " + username);
    }
}
