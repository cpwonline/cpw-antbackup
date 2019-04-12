#include "backups.h"

backups::backups()
{
    systemDB.infoGen.nameDB = "cpw_antbackup.db";
}
backups::~backups()
{
    //
}
void backups::data()
{

	std::cout << "\n|--Recolecting data";
	std::cout << "\n   |--General";

    bool err = false;
    do
    {
        std::cout << "\n      |-- Backup type (files/database): ";
        std::cin >> type;
        std::cout << "      |-- Title: ";
        std::cin >> title;
        std::cout << "      |-- Compression (y/n): ";
        std::cin >> compression;
        std::cout << "      |-- Repeat (y/n): ";
        std::cin >> repeat;
        std::cout << "   |--Datetime run\n";
        std::cout << "      |-- Day: ";
        std::cin >> backupDate.day;
        std::cout << "      |-- Month: ";
        std::cin >> backupDate.month;
        std::cout << "      |-- Year: ";
        std::cin >> backupDate.year;
        std::cout << "      |-- Hour: ";
        std::cin >> backupTime.hour;
        std::cout << "      |-- Minute: ";
        std::cin >> backupTime.minute;
        std::cout << "      |-- Second: ";
        std::cin >> backupTime.second;

        if(type == "files")
        {
            std::cout << "   |--Target1: Objetive\n";
            std::cout << "      |-- Local (y/n): ";
            std::cin >> backupObjetive.local;
            std::cout << "      |-- Host: ";
            std::cin >> backupObjetive.host;
            std::cout << "      |-- Options: ";
            std::cin >> backupObjetive.options;
            std::cout << "      |-- Objetive: ";
            std::cin >> backupObjetive.target;

            if(backupObjetive.local == "n")
            {
                std::cout << "      |--User of Target1: Objetive\n";
                std::cout << "         |-- Username: ";
                std::cin >> uObj.username;
                std::cout << "         |-- Password: ";
                std::cin >> uObj.password;
            }
        }
        else if(type == "database")
        {
            std::cout << "\n   |--Database\n";
            std::cout << "      |-- Name: ";
            std::cin >> backupDatabase.name;
            std::cout << "      |--User of Database";
            std::cout << "         |-- User: ";
            std::cin >> uDB.username;
            std::cout << "         |-- Password: ";
            std::cin >> uDB.password;
        }
        else
        {
            std::cout << "\n   |--Error: Backup type wrong\n";
            err = true;
        }

        std::cout << "   |--Target2: Destiny\n";
        std::cout << "      |-- Local (y/n): ";
        std::cin >> backupDestiny.local;
        std::cout << "      |-- Host: ";
        std::cin >> backupDestiny.host;
        std::cout << "      |-- Options: ";
        std::cin >> backupDestiny.options;
        std::cout << "      |-- Destiny: ";
        std::cin >> backupDestiny.target;

        if(backupDestiny.local == "n")
        {
            std::cout << "      |--User of Target2: Destiny\n";
            std::cout << "         |-- Username: ";
            std::cin >> uDest.username;
            std::cout << "         |-- Password: ";
            std::cin >> uDest.password;
        }

        if(err == true)
            std::cout << "\n   |--Error: Sorry, something is wrong. Try again.\n";
    }
    while(err == true);

    /*bool (*option[2])();
    option[0] = addRecord;
    option[1] = editRecord;

    bool result = option[next];*/
}

bool backups::addRecord()
{
    std::cout << "\n|--Adding a record";

    bool is_ok = false;

    // Backups
        // Create SQL string type statement
            std::string sql2;
            sql2 = "INSERT INTO backups (type, title, compression, repeat, timeRun, freg)"
                " VALUES ("
                    "'" + type + "',"
                    "'" + title + "',"
                    "'" + compression + "',"
                    "'" + repeat + "',"
                    "'"
                        + std::to_string(backupDate.day) + "-"
                        + std::to_string(backupDate.month) + "-"
                        + std::to_string(backupDate.year) + " "
                        + std::to_string(backupTime.hour) + ":"
                        + std::to_string(backupTime.minute) + ":"
                        + std::to_string(backupTime.second) +
                    "', "
                    "DATETIME(STRFTIME('%s','now'), 'unixepoch')"
                ");"
            ;

        is_ok = systemDB.conGen.makeEvery(sql2, "Backups");

    // Files (Objetive) or Databases
        // if is files or database
            if(type == "files")
            {
                sql2 = "INSERT INTO targets (local, host, options, target, freg, id_backup)"
                    " VALUES ("
                        "'" + backupObjetive.local + "',"
                        "'" + backupObjetive.host + "',"
                        "'" + backupObjetive.options + "',"
                        "'" + backupObjetive.target + "',"
                        "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                        "(SELECT MAX(id) FROM backups)"
                    ");"
                ;
            }
            else if(type == "database")
            {
                sql2 = "INSERT INTO databases (name, freg, id_backup) "
                    "VALUES ("
                        "'" + backupDatabase.name + "',"
                        "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                        "(SELECT MAX(id) FROM backups)"
                    ");"
                ;
            }

        is_ok = systemDB.conGen.makeEvery(sql2, "Files (objetive) or database");

    // Database user
        if(type == "database")
        {
            // Create SQL string type statement
                    sql2 = "INSERT INTO users (user, password, freg, id_database) "
                        "VALUES ("
                            "'" + uDB.username + "',"
                            "'" + uDB.password + "',"
                            "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                            "(SELECT MAX(id) FROM databases)"
                        ");"
                    ;

            is_ok = systemDB.conGen.makeEvery(sql2, "Database user");
        }

    // Target user: objetive
        if(backupObjetive.local == "n" && type == "files")
        {
            // Create SQL string type statement
                    sql2 = "INSERT INTO users (user, password, freg, id_target) "
                        "VALUES ("
                            "'" + uObj.username + "',"
                            "'" + uObj.password + "',"
                            "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                            "(SELECT MAX(id) FROM targets)"
                        ");"
                    ;

            is_ok = systemDB.conGen.makeEvery(sql2, "Target user: objetive");
        }

    // Target destiny
        // SQL String
                sql2 = "INSERT INTO targets (local, host, options, target, freg, id_backup)"
                    " VALUES ("
                        "'" + backupDestiny.local + "',"
                        "'" + backupDestiny.host + "',"
                        "'" + backupDestiny.options + "',"
                        "'" + backupDestiny.target + "',"
                        "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                        "(SELECT MAX(id) FROM backups)"
                    ");"
                ;

            is_ok = systemDB.conGen.makeEvery(sql2, "Target destiny");

    // Destiny user
        if(backupDestiny.local == "n")
        {
            // Create SQL string type statement
                sql2 = "INSERT INTO users (user, password, freg, id_target) "
                    "VALUES ("
                        "'" + uDest.username + "',"
                        "'" + uDest.password + "',"
                        "DATETIME(STRFTIME('%s','now'), 'unixepoch'),"
                        "(SELECT MAX(id) FROM targets)"
                    ");"
                ;

            is_ok = systemDB.conGen.makeEvery(sql2, "Destiny user");
        }

    if(is_ok)
        return true;
    else
        return false;
}
void backups::viewRecords()
{
    std::cout << "\n|--Showing records";

    // Create SQL statement
        systemDB.conGen.querySQL = "SELECT * FROM backups;";

    // Handle records
        auto handleRecords = [](void *nothing, int argc, char **argv, char **colNames) -> int
        {
            std::cout << "\n";
            for(int i=0; i<argc; i++){
                printf("%s: '%s' | ", colNames[i], argv[i]);
            }
            printf("\n");
            return 0;
        };
        printf("\n");

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, handleRecords, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "\n   |--Error: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "\n   |--Result: OK. \n");
        }
}
void backups::configureDB()
{
    std::cout << "\n|--Setting up database.";
    systemDB.conGen.error = 0;

    // Open database
        systemDB.conGen.response = sqlite3_open(systemDB.infoGen.nameDB,& systemDB.conGen.objSQLite);
        if (systemDB.conGen.response)
        {
            fprintf(stderr, "\n   |--Error: Error to open database: %s.\n", sqlite3_errmsg(systemDB.conGen.objSQLite));
            exit(0);
        }
        else
        {
            fprintf(stdout, "\n   |--Result: Database OK.\n");
        }
    // SQL Query
        systemDB.conGen.querySQL = "CREATE TABLE IF NOT EXISTS backups ("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "title VARCHAR(50) NOT NULL,"
                "type VARCHAR(10) NOT NULL,"
                "compression CHAR (1) NOT NULL,"
                "repeat CHAR (1) NOT NULL,"
                "timeRun DATETIME NOT NULL,"
                "freg DATETIME NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS targets("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "target VARCHAR(3000) NOT NULL,"
                "local CHAR(1) NOT NULL,"
                "host VARCHAR(50) NOT NULL,"
                "options VARCHAR(3000) NOT NULL,"
                "freg DATETIME NOT NULL,"
                "id_backup INTEGER,"
                "FOREIGN KEY(id_backup) REFERENCES backups(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS databases("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(50) NOT NULL,"
                "freg DATETIME NOT NULL,"
                "id_backup INTEGER,"
                "FOREIGN KEY(id_backup) REFERENCES backups(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS users("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "user VARCHAR(50) NOT NULL,"
                "password VARCHAR(50) NOT NULL,"
                "freg DATETIME NOT NULL,"
                "id_target INTEGER,"
                "id_database INTEGER,"
                "FOREIGN KEY(id_target) REFERENCES targets(id),"
                "FOREIGN KEY(id_database) REFERENCES databases(id)"
            ");"
        ;

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "\n   |--Error: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
            fprintf(stdout, "\n   |--Result: Database and tables OK.\n");

}
bool backups::restartDB()
{
    std::cout << "\n|--Restart database.";

    // Query
        systemDB.conGen.querySQL = "DROP TABLE backups;"
            "DROP TABLE targets;"
            "DROP TABLE users;"
            "DROP TABLE databases;"
        ;

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "\n   |--Error: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "\n   |--Result: OK.\n");
        }

    configureDB();
    return true;
}
bool backups::deleteRecord()
{
    std::cout << "\n|--Delete a record";

    // Data user
        std::string id;
        std::cout << "\n   |-- Record ID to delete: ";
        std::cin >> id;

    // Query
        std::string toString = "DELETE FROM backups WHERE id ='" + id + "';";

    // To char
        systemDB.conGen.querySQL = new char[toString.length()];
        for(int a = 0; a < toString.length(); a++)
            systemDB.conGen.querySQL[a] = toString[a];

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "\n   |--Error: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "\n   |--Result: Record from backups was deleted--.\n");
        }

    // Close and delete
        delete[] systemDB.conGen.querySQL;
        return true;
}
bool backups::editRecord()
{
    std::cout << "\n|--Editing a record";

    bool is_ok = false;
    // Create SQL statement in string type
        std::string id;
        std::cout << "\n   |-- Record ID: ";
        std::cin >> id;

        std::string sql2;
        /*sql2 = "UPDATE backups SET "
                "title='" + title + "',"
                "target='" + target + "',"
                "destiny='" + destiny + "',"
                "type='" + type + "',"
                "local='" + local + "',"
                "compression='" + compression + "',"
                "repeat='" + repeat + "',"
                "datetimeB='"
                    + std::to_string(dateBackup.day) + "-"
                    + std::to_string(dateBackup.month) + "-"
                    + std::to_string(dateBackup.year) + " "
                    + std::to_string(timeBackup.hour) + ":"
                    + std::to_string(timeBackup.minute) + ":"
                    + std::to_string(timeBackup.second) +
                "',"
                "dateFreg=DATETIME(STRFTIME('%s','now'), 'unixepoch') "
                "WHERE id='" + id + "'"
            ";"
        ;
*/
    // Convert to char*
        systemDB.conGen.querySQL = new char[sql2.length()];
        for(int a = 0; a < sql2.length(); a++)
        {
            systemDB.conGen.querySQL[a] = sql2[a];
        }

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "\n   |--Error: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "\n   |--Result: OK.\n");
            is_ok = true;
        }

    delete[] systemDB.conGen.querySQL;

    if(is_ok)
        return true;
    else
        return false;
}
bool backups::makeBackup()
{
    return true;
}
void backups::db::connection::convertToChar(std::string sql2)
{

    querySQL = new char[sql2.length()];
    for(int a = 0; a < sql2.length(); a++)
    {
        querySQL[a] = sql2[a];
    }
}
bool backups::db::connection::executeSQL(char* obj)
{

    response = sqlite3_exec(objSQLite, querySQL, NULL, 0, & error);
    if (response != SQLITE_OK)
    {
        fprintf(stderr, "\n   |--Error: %s\n", error);
        sqlite3_free(error);
        return false;
    }
    else
    {
        fprintf(stdout, "\n   |--Result: OK %s\n", obj);
        return true;
    }
}
void backups::db::connection::deleteMemory()
{
    delete[] querySQL;
}
bool backups::db::connection::makeEvery(std::string sql2, char* title)
{
    // Convert to char*
        convertToChar(sql2);

    // Execute SQL statement
        bool res = executeSQL(title);

    // Delete dynamic memory
        deleteMemory();

    return res;
}
