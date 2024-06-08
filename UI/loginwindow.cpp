#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registrationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QPalette>
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
    // Логика работы с логином/паролем должа быть здесь
}

void LoginWindow::on_registerButton_clicked()
{
    RegistrationWindow *registrationWindow = new RegistrationWindow(this);
    registrationWindow->show();
}

bool LoginWindow::isValidInput(const QString &input)
{
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])[A-Za-z]{8,32}$");
    return regex.match(input).hasMatch();
}

void LoginWindow::validateInput()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    bool isUsernameValid = isValidInput(username);
    bool isPasswordValid = isValidInput(password);

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

    ui->loginButton->setEnabled(isUsernameValid && isPasswordValid);
}
