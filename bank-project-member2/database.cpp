#include "database.h"
#include <QDebug>

// Initialize the singleton instance
Database* Database::instance = nullptr;

// Singleton access method
Database& Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return *instance;
}

// Private constructor
Database::Database() {
    // Initialize the database connection
    QString connectionString = "DRIVER={ODBC Driver 17 for SQL Server};"
                               "SERVER=DESKTOP-UHH5UOO\\SQLEXPRESS;"
                               "DATABASE=Banking;"
                               "Trusted_Connection=Yes;";
    db = QSqlDatabase::addDatabase("QODBC"); // Using ODBC driver
    db.setDatabaseName(connectionString);
}

// Destructor
Database::~Database() {
    if (db.isOpen()) {
        db.close();
    }
}

// Connect to the database
bool Database::connectToDatabase() {
    if (!db.open()) {
        qDebug() << "Database Connection Error:" << db.lastError().text();
        return false;
    }
    qDebug() << "Database connected successfully.";
    return true;
}

// Insert data into a table
bool Database::insertData(const QString& table, const QMap<QString, QVariant>& data) {
    QStringList columns = data.keys();
    QStringList placeholders;
    QVariantList values;

    for (const QString& column : columns) {
        placeholders << ":" + column;
        values << data.value(column);
    }

    QString queryStr = QString("INSERT INTO %1 (%2) VALUES (%3)")
                           .arg(table)
                           .arg(columns.join(", "))
                           .arg(placeholders.join(", "));

    QSqlQuery query;
    query.prepare(queryStr);

    for (const QString& column : columns) {
        query.bindValue(":" + column, data.value(column));
    }

    if (!query.exec()) {
        qDebug() << "Insert Error:" << query.lastError().text();
        return false;
    }

    return true;
}

// Update data in a table
bool Database::updateData(const QString& table, const QMap<QString, QVariant>& data, const QString& condition) {
    QStringList setClauses;
    QVariantList values;

    for (auto it = data.begin(); it != data.end(); ++it) {
        setClauses << QString("%1 = :%1").arg(it.key());
    }

    QString queryStr = QString("UPDATE %1 SET %2 WHERE %3")
                           .arg(table)
                           .arg(setClauses.join(", "))
                           .arg(condition);

    QSqlQuery query;
    query.prepare(queryStr);

    for (auto it = data.begin(); it != data.end(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qDebug() << "Update Error:" << query.lastError().text();
        return false;
    }

    return true;
}

// Delete data from a table
bool Database::deleteData(const QString& table, const QString& condition) {
    QString queryStr = QString("DELETE FROM %1 WHERE %2").arg(table).arg(condition);
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Delete Error:" << query.lastError().text();
        return false;
    }
    return true;
}

// Fetch data with a custom query
QSqlQuery Database::fetchData(const QString& queryStr) {
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Fetch Error:" << query.lastError().text();
    }
    return query;
}
