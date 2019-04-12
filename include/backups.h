
#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>
#include "sqlite3.h"

class backups
{
	public:
        backups();
        ~backups();
		void data();
		bool addRecord();
		void viewRecords();
		bool deleteRecord();
		bool editRecord();
		void configureDB();
		bool restartDB();
	protected:

	private:
        struct datetime
        {
            struct time
            {
                short hour, minute, second;
            };
            struct date
            {
                short day, month, year;
            };
        };
		struct database
		{
            struct info
            {
                info() : nameDB("cpw_antbackup.db"){}
                const char* nameDB;
            };
            struct connection
            {
                ~connection()
                {
                    sqlite3_close(objSQLite);
                }
                sqlite3 *objSQLite;
                char *error = 0;
                int response;
                char *querySQL;
            };

            info infoGen;
            connection conGen;
		};
		std::string target;
		std::string destiny;
		char compression, repeat;
		datetime::date dateBackup;
		datetime::time timeBackup;
		database genDB;
};

#endif // _BACKUPS_H_
