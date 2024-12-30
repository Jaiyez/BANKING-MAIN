// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(Database::getInstance())
{
    ui->setupUi(this);
    if (!db.connectToDatabase()) {
        QMessageBox::critical(this, "Error", "Failed to connect to database.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString name = ui->nameInput->text();
    QMap<QString, QVariant> data;
    data["name"] = name;
    if (db.insertData("Customer", data)) { // Check
        QMessageBox::information(this, "Success", "Data added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add data.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QString condition = QString("id = %1").arg(ui->idInput->text().toInt());
    if (db.deleteData("Users", condition)) {
        QMessageBox::information(this, "Success", "Data deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete data.");
    }
}

void MainWindow::on_updateButton_clicked()
{
    int id = ui->idInput->text().toInt();
    QString newName = ui->nameInput->text();
    QMap<QString, QVariant> data;
    data["name"] = newName;
    QString condition = QString("id = %1").arg(id);
    if (db.updateData("Users", data, condition)) {
        QMessageBox::information(this, "Success", "Data updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update data.");
    }
}

void MainWindow::on_viewButton_clicked()
{
    QSqlQuery query = db.fetchData("SELECT id, name FROM Users");
    QString result;
    while (query.next()) {
        result += QString("ID: %1, Name: %2\n")
        .arg(query.value(0).toInt())
            .arg(query.value(1).toString());
    }
    ui->textDisplay->setPlainText(result);
}



