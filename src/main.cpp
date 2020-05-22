#include <iostream>
#include "menu.h"

int main()
{
    char answer;
    do
    {
        menu menuGen;
        menuGen.listItems();
        menuGen.handleItems();

        std::cout << "\n¿Desea volver a inicio? (y/n): ";
        std::cin >> answer;
        std::cout << "\n";
    }while(answer != 'y' || answer != 'Y');

	return 0;
}
