#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headers;
    headers << "Name" << "Mobile" << "Email" << "Birthday";

    ui->contactTable->setColumnCount(4);
    ui->contactTable->setHorizontalHeaderLabels(headers);

    ui->contactTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // DATABASE CONNECTION
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("contacts.db");

    if(!db.open())
    {
        QMessageBox::critical(this,"Database Error","Cannot open database");
    }

    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS contacts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT,"
               "mobile TEXT,"
               "email TEXT,"
               "birthday TEXT)");

    loadContacts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadContacts()
{
    ui->contactTable->setRowCount(0);

    QSqlQuery query("SELECT name,mobile,email,birthday FROM contacts");

    int row = 0;

    while(query.next())
    {
        ui->contactTable->insertRow(row);

        for(int i=0;i<4;i++)
        {
            ui->contactTable->setItem(row,i,
                                      new QTableWidgetItem(query.value(i).toString()));
        }

        row++;
    }
}

void MainWindow::on_addButton_clicked()
{
    QString name = QInputDialog::getText(this,"Name","Enter Name");
    QString mobile = QInputDialog::getText(this,"Mobile","Enter Mobile");
    QString email = QInputDialog::getText(this,"Email","Enter Email");
    QString birthday = QInputDialog::getText(this,"Birthday","Enter Birthday");

    if(name.isEmpty() || mobile.isEmpty() || email.isEmpty())
    {
        QMessageBox::warning(this,"Error","All fields required");
        return;
    }

    if(!email.contains("@"))
    {
        QMessageBox::warning(this,"Error","Invalid Email");
        return;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO contacts(name,mobile,email,birthday) "
                  "VALUES(:name,:mobile,:email,:birthday)");

    query.bindValue(":name", name);
    query.bindValue(":mobile", mobile);
    query.bindValue(":email", email);
    query.bindValue(":birthday", birthday);

    query.exec();

    loadContacts();
}

void MainWindow::on_editButton_clicked()
{
    int row = ui->contactTable->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(this,"Error","Select a contact first");
        return;
    }

    QString name = QInputDialog::getText(this,"Name","Edit Name");
    QString mobile = QInputDialog::getText(this,"Mobile","Edit Mobile");
    QString email = QInputDialog::getText(this,"Email","Edit Email");
    QString birthday = QInputDialog::getText(this,"Birthday","Edit Birthday");

    QSqlQuery query;

    query.prepare("UPDATE contacts SET name=?, mobile=?, email=?, birthday=? "
                  "WHERE id = (SELECT id FROM contacts LIMIT 1 OFFSET ?)");

    query.addBindValue(name);
    query.addBindValue(mobile);
    query.addBindValue(email);
    query.addBindValue(birthday);
    query.addBindValue(row);

    query.exec();

    loadContacts();
}

void MainWindow::on_deleteButton_clicked()
{
    int row = ui->contactTable->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(this,"Error","Select a contact first");
        return;
    }

    QSqlQuery query;

    query.prepare("DELETE FROM contacts "
                  "WHERE id = (SELECT id FROM contacts LIMIT 1 OFFSET ?)");

    query.addBindValue(row);

    query.exec();

    loadContacts();
}
