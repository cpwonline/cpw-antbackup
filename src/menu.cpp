#include "menu.h"

void menu::listItems ()
{
	short option;

	std::cout << "Bienvenido a CPW AntBackup \n";
	do
	{
		std::cout << "1) Ver lista de respaldos \n";
		std::cout << "2) Agregar un respaldo \n";
		std::cout << "3) quitar un respaldo \n";
		std::cout << "4) Editar un respaldo \n";
		std::cout << "5) Configuraciones \n";
		std::cout << "\nSu opción: ";
		std::cin >> option;
		if(option < 1 || option > 5)
			std::cout << "\nDisculpe, la opción es inválida, intente nuevamente.\n";
	}while(option < 1 || option > 5);

	currentItem = option;
}

void menu::handleItems()
{
	backups *bakGen = new backups;
	bakGen->configureDB();
	switch(currentItem)
	{
		case 1:
            bakGen->viewRecords();
			break;
		case 2:
			bakGen->data();
			if(bakGen->addRecord())
                std::cout << "\n Se guardó su backup con exito.\n";
            else
                std::cout << "\n Hubo un error al guardar el backup.\n";
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
	}
	delete bakGen;
}
