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
	std::cout << "\n\nGeneral";
	std::cout << "\n- Target: ";
	std::cin >> target;
	std::cout << "\n- Destiny: ";
	std::cin >> destiny;
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
	std::cout << "\n- Repeat (y/n): ";
	std::cin >> repeat;
	std::cout << "\n- Compression (y/n): ";
	std::cin >> compression;
}
bool backups::addRecord()
{
    std::cout << "\nAdding a record\n";

    bool is_ok = false;

    // Create SQL statement in string type
        std::string sql2;
        sql2 = "INSERT INTO backups (target, destiny, compression, repeat, datetimeB, dateFreg) "
            "VALUES ("
                "'" + target + "',"
                "'" + destiny + "',"
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
                "DATETIME(STRFTIME('%s','now'), 'unixepoch')"
            ");"
        ;

        std::cout << "\n SQL2 = " << sql2 << ", size: " << sql2.length() << "\n";

    // Convert to char*
        genDB.conGen.querySQL = new char[sql2.length()];
        for(int a = 0; a < sql2.length(); a++)
        {
            genDB.conGen.querySQL[a] = sql2[a];
        }
        std::cout << "\n SQL = " << genDB.conGen.querySQL << "\n";

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, NULL, 0, & genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "Ready\n");
            is_ok = true;
        }

    delete[] genDB.conGen.querySQL;

    if(is_ok)
        return true;
    else
        return false;
}
void backups::viewRecords()
{
    std::cout << "\n* Showing records\n";

    // Create SQL statement
        genDB.conGen.querySQL = "SELECT * FROM backups;";

    // Handle records
        auto handleRecords = [](void *nada, int argc, char **argv, char **colNames) -> int
        {
            std::cout << "\n";
            for(int i=0; i<argc; i++){
                printf("%s -> %s\n", colNames[i], argv[i]);
            }
            printf("\n");
            return 0;
        };

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, handleRecords, 0,& genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "--Error--: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "--Ready--. \n");
        }
}
void backups::configureDB()
{
    std::cout << "\n* Setting up database.\n";
    genDB.conGen.error = 0;

    // Open database
        genDB.conGen.response = sqlite3_open(genDB.infoGen.nameDB,& genDB.conGen.objSQLite);
        if (genDB.conGen.response)
        {
            fprintf(stderr, "Error to open database: %s\n", sqlite3_errmsg(genDB.conGen.objSQLite));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Database OK\n");
        }
    // SQL Query
        genDB.conGen.querySQL = "CREATE TABLE backups ("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "target VARCHAR(3000) NOT NULL,"
                "destiny VARCHAR(3000) NOT NULL,"
                "compression CHAR (1) NOT NULL,"
                "repeat CHAR (1) NOT NULL,"
                "datetimeB DATETIME NOT NULL,"
                "dateFreg DATETIME NOT NULL"
            ");"
        ;

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, NULL, 0,& genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "Database and table created.\n");
        }
}
bool backups::restartDB()
{
    std::cout << "\n* Restart database.\n";

    // Query
        genDB.conGen.querySQL = "DROP TABLE backups;";

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, NULL, 0,& genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "Backups table was deleted.\n");
        }

    configureDB();
}
bool backups::deleteRecord()
{
    // Data user
        std::string id;
        std::cout << "Record ID to delete: ";
        std::cin >> id;

    // Query
        std::string toString = "DELETE FROM backups WHERE id ='" + id + "';";
        std::cout << "\ntoString: " << toString << ", size: " << toString.length() << "\n";
        // To char
            genDB.conGen.querySQL = new char[toString.length()];
            for(int a = 0; a < toString.length(); a++)
                genDB.conGen.querySQL[a] = toString[a];

        std::cout << "\nSQL: " << genDB.conGen.querySQL << ", size: " << toString.length() << "\n";

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, NULL, 0,& genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
        }
        else
        {
            fprintf(stdout, "Record from backups was deleted.\n");
        }

    // Close and delete
        delete[] genDB.conGen.querySQL;
}
bool backups::editRecord()
{
    std::cout << "\nEditing a record\n";

    bool is_ok = false;
    // Create SQL statement in string type
        std::string id;
        std::cout << "\nRecord ID: ";
        std::cin >> id;

        std::string sql2;
        sql2 = "UPDATE backups SET "
                "target='" + target + "',"
                "destiny='" + destiny + "',"
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

        std::cout << "\n SQL2 = " << sql2 << ", size: " << sql2.length() << "\n";

    // Convert to char*
        genDB.conGen.querySQL = new char[sql2.length()];
        for(int a = 0; a < sql2.length(); a++)
        {
            genDB.conGen.querySQL[a] = sql2[a];
        }
        std::cout << "\n SQL = " << genDB.conGen.querySQL << "\n";

    // Execute SQL statement
        genDB.conGen.response = sqlite3_exec(genDB.conGen.objSQLite, genDB.conGen.querySQL, NULL, 0,& genDB.conGen.error);
        if (genDB.conGen.response != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", genDB.conGen.error);
            sqlite3_free(genDB.conGen.error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "Ready\n");
            is_ok = true;
        }

    delete[] genDB.conGen.querySQL;

    if(is_ok)
        return true;
    else
        return false;
}
