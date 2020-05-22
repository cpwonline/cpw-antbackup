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
