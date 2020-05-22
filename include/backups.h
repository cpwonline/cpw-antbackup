
#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>
#include <fstream>
#include "sqlite3.h"

class backups
{
	public:
        backups() : nameDB("cpw_cantbackup.db"){}
		void data();
		bool addRecord();
		void viewRecords();
		void configureDB();

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
		char compression, repeat;
		time timeBackup;
		date dateBackup;
		std::ofstream *ofileGen;
		const char* nameDB;
};

#endif // _BACKUPS_H_
