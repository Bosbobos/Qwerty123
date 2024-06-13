#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(QWidget *parent = nullptr);
    ~EntryDialog();

    QString getTitle() const;
    void setTitle(const QString &title);

    QString getUsername() const;
    void setUsername(const QString &username);

    QString getPassword() const;
    void setPassword(const QString &password);

    QString getUrl() const;
    void setUrl(const QString &url);

    QString getTag() const;
    void setTag(const QString &tag);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::EntryDialog *ui;
};

#endif // ENTRYDIALOG_H
