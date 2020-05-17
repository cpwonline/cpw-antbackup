/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * backups.cpp
 * Copyright (C) 2019 Jose Felix Rivas Carrasco <cpwonline@hotmail.com>
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

#include "backups.h"

void backups::hola()
{
	std::cout << "\nObjetivo: ";
	std::cin >> target;
	std::cout << "\nDestino: ";
	std::cin >> destiny;
	std::cout << "\n¿Compresión? (y/n): ";
	std::cin >> compression;
	std::cout << "\nObjetivo: ";
	std::cin >> target;
	return true;
}

