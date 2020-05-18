#include "backups.h"

void backups::data()
{
	std::cout << "\n\nGeneral";
	std::cout << "\n- Objetivo: ";
	std::cin >> target;
	std::cout << "\n- Destino: ";
	std::cin >> destiny;
	std::cout << "\n- Compresión (y/n): ";
	std::cin >> compression;
	std::cout << "\n\nFecha y hora";
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
}
bool backups::add()
{

}
