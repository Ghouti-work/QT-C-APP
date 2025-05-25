#include <QProcess>           // For running external process
#include <QJsonDocument>      // For JSON serialization/deserialization
#include <QJsonObject>        // For JSON object manipulation
#include <QByteArray>         // For handling raw byte data
#include <QString>            // QString type
#include <QProgressBar>       // For UI progress bar manipulation
#include <QTextEdit>          // For UI text edits
#include <QLineEdit>          // For UI line edit (URL input)
#include <QMessageBox>
#include <QProcessEnvironment> // For setting environment variables on QProcess
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) // initialize ui
{
    ui->setupUi(this);
    connectBackend(); // now ui->button_summarize will work
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectBackend() {
    connect(ui->button_summarize, &QPushButton::clicked, this, &MainWindow::handleSummarize);
    connect(ui->button_exit, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(ui->button_reset, &QPushButton::clicked, this, &MainWindow::resetForm);
    connect(ui->button_save, &QPushButton::clicked, this, &MainWindow::saveSummary);
}

void MainWindow::handleSummarize() {
    QString url = ui->lineEdit_url->text();
    if (url.isEmpty()) return;

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(30);

    QProcess *process = new QProcess(this);
    process->setProgram("backend/youtube_backend");

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("API_KEY", "AIzaSyAHN3wWqATm1_0pzuTVrU7qmer7OAOE1eE");  // <-- add your actual key here
    process->setProcessEnvironment(env);

    QJsonObject json;
    json["url"] = url;
    QByteArray inputData = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";

    QByteArray *outputBuffer = new QByteArray();

    connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
        *outputBuffer += process->readAllStandardOutput();
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [=](int, QProcess::ExitStatus) {
                QJsonParseError err;
                QJsonDocument doc = QJsonDocument::fromJson(*outputBuffer, &err);

                if (err.error != QJsonParseError::NoError || !doc.isObject()) {
                    QMessageBox::critical(this, "Parse Error", "Failed to parse JSON from backend.");
                } else {
                    QJsonObject obj = doc.object();
                    ui->textEdit_transcript->setPlainText(obj["transcript"].toString());
                    ui->textEdit_summary->setPlainText(obj["summary"].toString());
                    ui->progressBar->setValue(100);
                }

                outputBuffer->clear();
                delete outputBuffer;
                process->deleteLater();
            });

    process->start();
    process->write(inputData);
    process->closeWriteChannel();
}

void MainWindow::resetForm() {
    // TODO: Clear fields, etc.
}

void MainWindow::saveSummary() {
    // TODO: Save summary logic
}



