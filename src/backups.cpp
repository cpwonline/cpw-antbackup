#include "backups.h"

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

    sqlite3 *db;
    char *error = 0;
    int res;
    char *sql;
    bool is_ok = false;
    // Open database
        res = sqlite3_open(nameDB, &db);
        if (res)
        {
            fprintf(stderr, "Error to open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Database OK\n");
        }
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
        sql = new char[sql2.length()];
        for(int a = 0; a < sql2.length(); a++)
        {
            sql[a] = sql2[a];
        }
        std::cout << "\n SQL = " << sql << "\n";

    // Execute SQL statement
        res = sqlite3_exec(db, sql, NULL, 0, &error);
        if (res != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", error);
            sqlite3_free(error);
            is_ok = false;
        }
        else
        {
            fprintf(stdout, "Ready\n");
            is_ok = true;
        }

    sqlite3_close(db);

    delete[] sql;

    if(is_ok)
        return true;
    else
        return false;
}
static int selectCb(void *nada, int argc, char **argv, char **colNames){
   int i;

   for(i=0; i<argc; i++){
      printf("%s => %s\n", colNames[i], argv[i]);
   }
   printf("\n");
   return 0;
}
void backups::viewRecords()
{
    std::cout << "\n* Showing records\n";
    sqlite3 *db;
    char *error = 0;
    int res;
    char *sql;

    // Open database
        res = sqlite3_open(nameDB, &db);
        if (res)
        {
            fprintf(stderr, "Error to open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Database OK\n");
        }

    // Create SQL statement
        sql = "SELECT * FROM backups;";

    // Execute SQL statement
        res = sqlite3_exec(db, sql, selectCb, 0, &error);
        if (res != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", error);
            sqlite3_free(error);
        }
        else
        {
            fprintf(stdout, "Ready. \n");
        }

        sqlite3_close(db);
}
void backups::configureDB()
{
    // Setting up
        std::cout << "\n* Setting up database.\n";
        sqlite3 *db;
        char *error = 0;
        int res;
        char *sql;

        res = sqlite3_open(nameDB, &db);
        if (res)
        {
            fprintf(stderr, "Error to open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Databse is OK\n");
        }
    // Query
        sql = "CREATE TABLE backups ("
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
        res = sqlite3_exec(db, sql, NULL, 0, &error);
        if (res != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", error);
            sqlite3_free(error);
        }
        else
        {
            fprintf(stdout, "Database and table created.\n");
        }

    sqlite3_close(db);
}
bool backups::restartDB()
{
    // Setting up
        std::cout << "\n* Restart database.\n";
        sqlite3 *db;
        char *error = 0;
        int res;
        char *sql;

        res = sqlite3_open(nameDB, &db);
        if (res)
        {
            fprintf(stderr, "Error to open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Database is OK\n");
        }
    // Query
        sql = "DROP TABLE backups;";

    // Execute SQL statement
        res = sqlite3_exec(db, sql, NULL, 0, &error);
        if (res != SQLITE_OK)
        {
            fprintf(stderr, "Error: %s\n", error);
            sqlite3_free(error);
        }
        else
        {
            fprintf(stdout, "Backups table was deleted.\n");
        }

    sqlite3_close(db);

    configureDB();
}
