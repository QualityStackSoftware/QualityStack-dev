#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <global>


class BrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserWindow();
    ~BrowserWindow();

    void init(const QString& id, const QStringList& msg);

signals:

public slots:

private:
    QString m_id;
    QStringList m_msg;

};

#endif // BROWSERWINDOW_H
