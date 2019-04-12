#include <iostream>
#include "menu.h"

int main()
{
    menu menuGen;
    char answer;

    do
    {
        menuGen.listItems();
        menuGen.handleItems();

        std::cout << "\nDo you want to exit? (y/n): ";
        std::cin >> answer;
        std::cout << "\n";
    }while(answer == 'n' || answer == 'N');

	return 0;
}
