#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clientfunctions.h>
#include <QApplication>
#include <QProcess>
#include <taskform.h>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    bool update_data();

signals:
    void openWindow();

private slots:
    void on_task1_clicked();
    void on_task2_clicked();
    void on_task3_clicked();
    void on_account_exit_triggered();

    void openTask(QVariantMap task);

    void on_StatLabel_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    TaskForm *tWindow;
};

#endif // MAINWINDOW_H
