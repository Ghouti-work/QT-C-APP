// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectBackend();
    void handleSummarize();
    void resetForm();
    void saveSummary();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H




