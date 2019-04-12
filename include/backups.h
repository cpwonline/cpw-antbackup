#ifndef _BACKUPS_H_
#define _BACKUPS_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "sqlite3.h"

class backups
{
	public:
        backups();
        ~backups();
		void data();
		bool addRecord();
		void viewBackups();
		void viewTargets(char* id);
		void viewDatabases(char* id);
		void viewUsers(char* id);
		void viewRecords();
		bool deleteRecord();
		bool editRecord();
		void configureDB();
		bool restartDB();
		bool makeBackup();

	protected:

	private:
        // Structs and unions
            struct targets
            {
                short id;
                std::string target, host, options, local;
            };

            struct users
            {
                short id;
                std::string username, password;
            };

            struct databases
            {
                short id;
                std::string name;
            };


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
            struct db
            {
                struct info
                {
                    //info();
                    const char* nameDB;
                };
                struct connection
                {
                    ~connection()
                    {
                        sqlite3_close(objSQLite);
                    }
                    void convertToChar(std::string);
                    bool executeSQL(char* obj);
                    void deleteMemory();
                    bool makeEvery(std::string sql2, char* title);

                    sqlite3* objSQLite;
                    char* error = 0;
                    int response;
                    char* querySQL;
                };

                info infoGen;
                connection conGen;
            }
            systemDB;

        // Objects
            short id;
            std::string type, title;
            char compression, repeat;

            targets backupObjetive;
            targets backupDestiny;
            datetime::date backupDate;
            datetime::time backupTime;

            users uObj;
            users uDB;
            databases backupDatabase;
            users uDest;

};

#endif // _BACKUPS_H_
