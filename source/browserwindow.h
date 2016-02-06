#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <global>


class BrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget *parent = 0);
    ~BrowserWindow();

signals:

public slots:
};

#endif // BROWSERWINDOW_H
