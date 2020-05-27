#include "backups.h"

void backups::data()
{
	std::cout << "\n\nGeneral";
	std::cout << "\n- Objetivo: ";
	std::cin >> target;
	std::cout << "\n- Destino: ";
	std::cin >> destiny;
	std::cout << "\n- Día: ";
	std::cin >> dateBackup.day;
	std::cout << "\n- Mes: ";
	std::cin >> dateBackup.month;
	std::cout << "\n- Año: ";
	std::cin >> dateBackup.year;
	std::cout << "\n- Hora: ";
	std::cin >> timeBackup.hour;
	std::cout << "\n- Minuto: ";
	std::cin >> timeBackup.minute;
	std::cout << "\n- Segundo: ";
	std::cin >> timeBackup.second;
	std::cout << "\n- Repetición: ";
	std::cin >> repeat;
	std::cout << "\n- Compresión (y/n): ";
	std::cin >> compression;
}
bool backups::addRecord()
{
    std::cout << "\nAdding a record\n";

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
        sql = "INSERT INTO events VALUES (DATETIME(STRFTIME('%s','now'), 'unixepoch'));";

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
            fprintf(stdout, "Query is OK\n");
            bool is_ok = true;
        }

    sqlite3_close(db);

        *ofileGen << target << "," << destiny;
        *ofileGen << "," << dateBackup.day << "," << dateBackup.month;
        *ofileGen << "," << dateBackup.year << "," << timeBackup.hour;
        *ofileGen << "," << timeBackup.minute << "," << timeBackup.second;
        *ofileGen << "," << repeat << "," << compression << "\n";

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
            fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Base de datos OK\n");
        }
    // Query
        sql = "CREATE TABLE backups ("
            "id INT NOT NULL PRIMARY KEY, "
            "target VARCHAR(3000) NOT NULL, "
            "destiny VARCHAR(3000) NOT NULL, "
            "compression INT NOT NULL, "
            "repeat INT NOT NULL, "
            "freg datetime NOT NULL)"
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
            fprintf(stdout, "Base de datos y tabla creada.\n");
        }

    sqlite3_close(db);
}
