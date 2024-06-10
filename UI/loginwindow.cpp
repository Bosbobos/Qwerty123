#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registrationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QMovie>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Инициализация QMovie с GIF-анимацией
    movie = new QMovie(":/resources/resources/loading_animation.gif");
    ui->AuthGIF->setMovie(movie);

    // Запуск анимации
    connect(movie, &QMovie::finished, movie, &QMovie::start);
    movie->start();

    // Масштабирование GIF-а до размеров QLabel
    connect(movie, &QMovie::frameChanged, this, &LoginWindow::scaleGif);

    QString defaultStyle = "QLineEdit { border: 2px solid grey; }";

    ui->usernameInput->setStyleSheet(defaultStyle);
    ui->passwordInput->setStyleSheet(defaultStyle);

    connect(ui->usernameInput, &QLineEdit::textChanged, this, &LoginWindow::validateInput);
    connect(ui->passwordInput, &QLineEdit::textChanged, this, &LoginWindow::validateInput);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::scaleGif()
{
    if (movie->currentFrameNumber() == 0) {
        QSize GIFSize = ui->AuthGIF->size();
        QSize movieSize = movie->scaledSize();
        if (movieSize != GIFSize) {
            movie->setScaledSize(GIFSize);
        }
    }
}

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    scaleGif();
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (isValidInput(username) && isValidInput(password)) {
        processLogin(username, password); // Вызов функции для обработки логина
    } else {
        showErrorMessage("Please check your username and password format.");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegistrationWindow *registrationWindow = new RegistrationWindow(this);
    registrationWindow->show();
}

bool LoginWindow::isValidInput(const QString &input)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[A-Za-z\\d]{8,32}$");
    return regex.match(input).hasMatch();
}

void LoginWindow::validateInput()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    bool isUsernameValid = isValidInput(username);
    bool isPasswordValid = isValidInput(password);

    QString validStyle = "QLineEdit { border: 2px solid green; }";
    QString invalidStyle = "QLineEdit { border: 2px solid red; }";
    QString defaultStyle = "QLineEdit { border: 2px solid grey; }";

    ui->usernameInput->setStyleSheet(username.isEmpty() ? defaultStyle : (isUsernameValid ? validStyle : invalidStyle));
    ui->passwordInput->setStyleSheet(password.isEmpty() ? defaultStyle : (isPasswordValid ? validStyle : invalidStyle));

    ui->loginButton->setEnabled(isUsernameValid && isPasswordValid);
}

void LoginWindow::processLogin(const QString &username, const QString &password)
{
    // Пример логики проверки логина и пароля
    bool loginSuccessful = false;

    // Здесь добавьте логику для проверки логина и пароля в базе данных

    if (loginSuccessful) {
        goToMainScreen();
    } else {
        showErrorMessage("Invalid username or password. Please try a different login/password.");
    }
}

void LoginWindow::showErrorMessage(const QString &message)
{
    ui->errorMessageLabel->setText(message);
    ui->errorMessageLabel->setStyleSheet("QLabel { color: red; }");
}

void LoginWindow::goToMainScreen()
{
    // Здесь добавить логику для перехода на основной экран
}
