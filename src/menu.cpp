#include "menu.h"

void menu::listItems ()
{
	short option;

	std::cout << "\nWelcome to CPW AntBackup\n";
	do
	{
		std::cout << "|--List: \n";
		std::cout << "   |-- 1) See backups list \n";
		std::cout << "   |-- 2) Add a backup \n";
		std::cout << "   |-- 3) Delete a backup \n";
		std::cout << "   |-- 4) Edit a backup \n";
		std::cout << "   |-- 5) Others \n";
		std::cout << "\nYour choice: ";
		std::cin >> option;

		switch(option)
		{
            case 5:
                std::cout << "\n   |--Others:\n";
                std::cout << "      |-- 6) Restart database\n";
                std::cout << "      |-- 7) Backups status\n";
                std::cout << "      |-- 8) Make every backup now (force)\n";
                std::cout << "\nYour choice: ";
                std::cin >> option;
                break;
		}

		if(option < 1 || option > 8)
			std::cout << "\n|--Error: Sorry, invalid option. Try again.\n";
	}while(option < 1 || option > 8);

	currentItem = option;
}

void menu::handleItems()
{
	bakGen->configureDB();
	switch(currentItem)
	{
		case 1:
            bakGen->viewRecords();
			break;
		case 2:
			bakGen->data();
			if(bakGen->addRecord())
			{
                std::cout << "\n   |--Result: Backup successfully saved.";
            }
            else
			{
                std::cout << "\n   |--Error: Error to save backup.";
            }
			break;
		case 3:
			if(bakGen->deleteRecord())
			{
                std::cout << "\n   |--Result: Backup successfully deleted.";
            }
            else
			{
                std::cout << "\n   |--Error: Error to delete backup.";
            }
			break;
		case 4:
			bakGen->data();
			if(bakGen->editRecord())
			{
                std::cout << "\n   |--Result: Backup successfully edited.";
            }
            else
            {
                std::cout << "\n   |--Error: Error to edit backup.";
            }
			break;
        case 6:
            bakGen->restartDB();
            break;
        case 7:
            break;
        case 8:
            bakGen->makeBackup();
            break;
	}
}
void menu::loop()
{
    bakGen = new backups;
    char answer;

    do
    {
        listItems();
        handleItems();

        std::cout << "\n|--Do you want to exit? (y/n)";
        std::cout << "\n\nYour choice: ";
        std::cin >> answer;
        std::cout << "\n";
    }while(answer == 'n' || answer == 'N');

    delete bakGen;
}
