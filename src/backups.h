/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * backups.h
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

#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>

class backups
{
	public:
		void hola();

		void saludar();

	protected:

	private:
		struct time
		{
			short hour, minute, second;
		};
		struct date
		{
			short day, month, year;
		};
		std::string target;
		std::string destiny;
		bool compression;
		time timeBackup;
		date dateBackup;
};

#endif // _BACKUPS_H_

