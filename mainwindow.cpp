#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialize
    setWindowTitle("SQLite");
    setFixedSize(150,170);
    ui->lineEdit->setPlaceholderText("1 - 3");

    connectToDatabase();
    createTable();
    insertData();
}

void MainWindow::connectToDatabase(){
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(":memory:");

        if(!db.open())
            qWarning() << "ERROR: " << db.lastError().text();
    } else {
        qWarning() << "ERROR - no driver: " << DRIVER;
    }
}

void MainWindow::createTable(){
    QSqlQuery query("CREATE TABLE color (id INTEGER PRIMARY KEY, name TEXT)");

    if(!query.isActive()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
}

void MainWindow::insertData(){
    QSqlQuery query;

    if(!query.exec("INSERT INTO color(name) VALUES('ONE')")){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    if(!query.exec("INSERT INTO color(name) VALUES('TWO')")){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    if(!query.exec("INSERT INTO color(name) VALUES('THREE')")){
        qWarning() << "ERROR: " << query.lastError().text();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT name FROM color WHERE id = ?");
    query.addBindValue(ui->lineEdit->text().toInt());

    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
    }
    if(query.first()){
        ui->lineEdit->setText(query.value(0).toString());
    } else {
        ui->lineEdit->setText("color not found");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
