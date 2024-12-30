#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>
#include <QVariant>

class Database {
public:
    // Returns the singleton instance
    static Database& getInstance();

    // Connects to the database
    bool connectToDatabase();

    // CRUD Operations
    bool insertData(const QString& table, const QMap<QString, QVariant>& data);
    bool updateData(const QString& table, const QMap<QString, QVariant>& data, const QString& condition);
    bool deleteData(const QString& table, const QString& condition);
    QSqlQuery fetchData(const QString& queryStr);

    // Destructor
    ~Database();

private:
    // Private constructor for Singleton
    Database();

    // Disable copy constructor and assignment
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase db;

    // Declaration of the static instance pointer
    static Database* instance;
};

#endif // DATABASE_H
