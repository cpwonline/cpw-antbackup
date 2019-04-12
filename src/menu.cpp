/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * menu.cpp
 * Copyright (C) 2019 CPW Online <cpwonline@hotmail.com>
 *
 * net.cpwonline.cpw-antbackup is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * net.cpwonline.cpw-antbackup is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
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
	switch(currentItem)
	{
		case 1:
			std::cout << "\nOpción 1\n";
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
	}
}

