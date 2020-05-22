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
    ofileGen = new std::ofstream;
    bool is_ok = true;

    ofileGen->open("data/backupsList.db",std::ios::app);

    if(ofileGen->is_open())
    {
        *ofileGen << target << "," << destiny;
        *ofileGen << "," << dateBackup.day << "," << dateBackup.month;
        *ofileGen << "," << dateBackup.year << "," << timeBackup.hour;
        *ofileGen << "," << timeBackup.minute << "," << timeBackup.second;
        *ofileGen << "," << repeat << "," << compression << "\n";
    }
    else
        is_ok = false;

    ofileGen->close();
    delete ofileGen;

    if(is_ok)
        return true;
    else
        return false;
}
void backups::viewRecords()
{

}
void backups::configureDB()
{
    // Setting up
        std::cout "\n* Setting up database.\n"
        sqlite3 *db;
        char *error = 0;
        int res;
        char *sql;

        res = sqlite3_open("cpw_ant_backup.db", &db);
        if (res)
        {
            fprintf(stderr, "\nNo se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "\nBase de datos OK\n");
        }
    // Query
        sql = "CREATE TABLE backups ("
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
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
            fprintf(stderr, "\nError: %s\n", error);
            sqlite3_free(error);
        }
        else
        {
            fprintf(stdout, "\nBase de datos y tabla creada.\n");
        }

    sqlite3_close(db);
}
