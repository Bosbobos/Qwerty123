#include "addeditdialog.h"
#include "ui_addeditdialog.h"

EntryDialog::EntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);

    // Connect signals and slots only once
    connect(ui->okButton, &QPushButton::clicked, this, &EntryDialog::on_okButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &EntryDialog::on_cancelButton_clicked);
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

QString EntryDialog::getTitle() const
{
    return ui->titleInput->text();
}

void EntryDialog::setTitle(const QString &title)
{
    ui->titleInput->setText(title);
}

QString EntryDialog::getUsername() const
{
    return ui->usernameInput->text();
}

void EntryDialog::setUsername(const QString &username)
{
    ui->usernameInput->setText(username);
}

QString EntryDialog::getPassword() const
{
    return ui->passwordInput->text();
}

void EntryDialog::setPassword(const QString &password)
{
    ui->passwordInput->setText(password);
}

QString EntryDialog::getUrl() const
{
    return ui->urlInput->text();
}

void EntryDialog::setUrl(const QString &url)
{
    ui->urlInput->setText(url);
}

QString EntryDialog::getTag() const
{
    return ui->tagInput->text();
}

void EntryDialog::setTag(const QString &tag)
{
    ui->tagInput->setText(tag);
}

void EntryDialog::on_okButton_clicked()
{
    accept();
}

void EntryDialog::on_cancelButton_clicked()
{
    reject();
}
