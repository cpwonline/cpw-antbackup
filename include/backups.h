
#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>
#include <fstream>

class backups
{
	public:
		void data();
		bool add();

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
		bool compression, repeat;
		time timeBackup;
		date dateBackup;
		ofstream *ofileGen;
};

#endif // _BACKUPS_H_
