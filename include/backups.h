
#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>
#include <fstream>

class backups
{
	public:
		void data();
		bool addRecord();

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
};

#endif // _BACKUPS_H_
