#include "backups.h"

backups::backups()
{
    //
}
backups::~backups()
{
    //
}
void backups::data()
{
    targets backupObjetive;
    targets backupDestiny;
    datetime::date backupDate;
    datetime::time backupTime;

	std::cout << "\n\n* Recolecting data";
	std::cout << "\n** General";

    bool err = false;
    do
    {
        std::cout << "\n- Backup type (files/database): ";
        std::cin >> type;
        std::cout << "\n- Title: ";
        std::cin >> title;
        std::cout << "\n- Compression (y/n): ";
        std::cin >> compression;
        std::cout << "\n- Repeat (y/n): ";
        std::cin >> repeat;
        std::cout << "\n** Datetime run";
        std::cout << "\n- Day: ";
        std::cin >> dateBackup.day;
        std::cout << "\n- Month: ";
        std::cin >> dateBackup.month;
        std::cout << "\n- Year: ";
        std::cin >> dateBackup.year;
        std::cout << "\n- Hour: ";
        std::cin >> timeBackup.hour;
        std::cout << "\n- Minute: ";
        std::cin >> timeBackup.minute;
        std::cout << "\n- Second: ";
        std::cin >> timeBackup.second;

        switch(type)
        {
            case "files":
            {
                std::cout << "\n** Target1: Objetive";
                std::cout << "\n- Local (y/n): ";
                std::cin >> backupObjetive.local;
                std::cout << "\n- Host: ";
                std::cin >> backupObjetive.host;
                std::cout << "\n- Options: ";
                std::cin >> backupObjetive.options;
                std::cout << "\n- Objetive: ";
                std::cin >> backupObjetive.target;

                if(backupObjetive.local == 'n')
                {
                    users uObj;
                    std::cout << "\n*** User of Target1: Objetive";
                    std::cout << "\n- Username: ";
                    std::cin >> uObj.username;
                    std::cout << "\n- Password: ";
                    std::cin >> uObj.password;
                }
                break;
            }
            case "database":
            {
                users uDB;
                databases backupDatabase;
                std::cout << "\n** Database";
                std::cout << "\n- Name: ";
                std::cin >> backupDatabase.name;
                std::cout << "\n*** User of Database";
                std::cout << "\n- User: ";
                std::cin >> uDB.username;
                std::cout << "\n- Password: ";
                std::cin >> uDB.password;
                break;
            }
            default:
                std::cout << "\n --Backup type wrong--\n";
                err = true;
                break;
        }

        std::cout << "\n** Target2: Destiny";
        std::cout << "\n- Local (y/n): ";
        std::cin >> backupDestiny.local;
        std::cout << "\n- Host: ";
        std::cin >> backupDestiny.host;
        std::cout << "\n- Options: ";
        std::cin >> backupDestiny.options;
        std::cout << "\n- Destiny: ";
        std::cin >> backupDestiny.target;

        if(backupDestiny.local == 'n')
        {
            users uDest;
            std::cout << "\n*** User of Target2: Destiny";
            std::cout << "\n- Username: ";
            std::cin >> uDest.username;
            std::cout << "\n- Password: ";
            std::cin >> uDest.password;
        }
    }
    if(err == true)
        std::cout << "\Sorry, something is wrong. Try again.\n";
    while(err == true);

}
bool backups::addRecord()
{
    std::cout << "\n* Adding a record\n";

    bool is_ok = false;

    // Create SQL statement in string type
        std::string sql2;
        sql2 = "INSERT INTO backups (type, title, compression, repeat, local, , , datetimeB, dateFreg) "
            "VALUES ("
                "'" + type + "',"
                "'" + title + "',"
                "'" + compression + "',"
                "'" + repeat + "',"
                "'"
                    + std::to_string(dateBackup.day) + "-"
                    + std::to_string(dateBackup.month) + "-"
                    + std::to_string(dateBackup.year) + " "
                    + std::to_string(timeBackup.hour) + ":"
                    + std::to_string(timeBackup.minute) + ":"
                    + std::to_string(timeBackup.second) +
                "',"
        ;

        switch(type)
        {
            case "files":
            {
                sql2 = sql2 + backupObjetive.local + ","
                    + backupObjetive.host + ","
                    + backupObjetive.options + ","
                    + backupObjetive.target + ","
                ;

                if(backupObjetive.local == 'n')
                {
                    sql2 = sql2 + uObj.username + ",";
                        + uObj.password + ","
                    ;
                }
                break;
            }
            case "database":
            {
                sql2 = sql2 + backupDatabase.name + ","
                sql2 = sql2 + uDB.username + ","
                sql2 = sql2 + uDB.password + ","
                break;
            }
        }

        sql2 = sql2 + backupDestiny.local + ","
            + backupDestiny.host + ","
            + backupDestiny.options + ","
            + backupDestiny.target + ","
        ;

        if(backupDestiny.local == 'n')
        {
            sql2 = sql2 + uDest.username + ","
                + uDest.password + ","
            ;
        }

        sql2 = sql2 + "DATETIME(STRFTIME('%s','now'), 'unixepoch'));";

    // Convert to char*
        systemDB.conGen.querySQL = new char[sql2.length()];
        for(int a = 0; a < sql2.length(); a++)
        {
            systemDB.conGen.querySQL[a] = sql2[a];
        }

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0, & systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "--Ready--\n");
            is_ok = true;
        }

    delete[] systemDB.conGen.querySQL;

    if(is_ok)
        return true;
    else
        return false;
}
void backups::viewRecords()
{
    std::cout << "\n* Showing records\n";

    // Create SQL statement
        systemDB.conGen.querySQL = "SELECT * FROM backups;";

    // Handle records
        auto handleRecords = [](void *nada, int argc, char **argv, char **colNames) -> int
        {
            std::cout << "\n";
            for(int i=0; i<argc; i++){
                printf("%s: '%s' | ", colNames[i], argv[i]);
            }
            printf("\n");
            return 0;
        };

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, handleRecords, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "--Ready--. \n");
        }
}
void backups::configureDB()
{
    std::cout << "\n* Setting up database.\n";
    systemDB.conGen.error = 0;

    // Open database
        systemDB.conGen.response = sqlite3_open(systemDB.infoGen.nameDB,& systemDB.conGen.objSQLite);
        if (systemDB.conGen.response)
        {
            fprintf(stderr, "--Error to open database--: %s\n", sqlite3_errmsg(systemDB.conGen.objSQLite));
            exit(0);
        }
        else
        {
            fprintf(stderr, "--Database OK--\n");
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
            "CREATE TABLE IF NOT EXISTS users("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "user VARCHAR(50) NOT NULL,"
                "password VARCHAR(50) NOT NULL,"
                "freg DATETIME NOT NULL,"
                "id_target INTEGER,"
                "FOREIGN KEY(id_target) REFERENCES targets(id),"
                "id_database INTEGER,"
                "FOREIGN KEY(id_database) REFERENCES databases(id)"
            ");"
            "CREATRE TABLE IF NOT EXISTS databases("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(50) NOT NULL,"
                "freg DATETIME NOT NULL,"
                "id_backup INTEGER,"
                "FOREIGN KEY(id_backup) REFERENCES backups(id)"
            ");"
        ;

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "--Database and table created--.\n");
        }
}
bool backups::restartDB()
{
    std::cout << "\n* Restart database.\n";

    // Query
        systemDB.conGen.querySQL = "DROP TABLE backups;";

    // Execute SQL statement
        systemDB.conGen.response = sqlite3_exec(systemDB.conGen.objSQLite, systemDB.conGen.querySQL, NULL, 0,& systemDB.conGen.error);
        if (systemDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "--Backups table was deleted--.\n");
        }

    configureDB();
}
bool backups::deleteRecord()
{
    std::cout << "\n* Delete a record\n";

    // Data user
        std::string id;
        std::cout << "Record ID to delete: ";
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
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "--Record from backups was deleted--.\n");
        }

    // Close and delete
        delete[] systemDB.conGen.querySQL;
}
bool backups::editRecord()
{
    std::cout << "\n* Editing a record\n";

    bool is_ok = false;
    // Create SQL statement in string type
        std::string id;
        std::cout << "\nRecord ID: ";
        std::cin >> id;

        std::string sql2;
        sql2 = "UPDATE backups SET "
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
            fprintf(stderr, "--Error--: %s\n", systemDB.conGen.error);
            sqlite3_free(systemDB.conGen.error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "--Ready--\n");
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

}
