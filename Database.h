/************************************************************************************
 * @file Database.h
 *
 * @brief SQLite database interaction with C++
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include "Sqlite/sqlite3.h"

class Database
{
private:

	// Callback used in saving vector pair of strings
	static int callbackVectorPair(void* Used, int argc, char** argv, char** azColName);
	
	// Callback used in saving int value
	static int callbackInt(void* count, int argc, char** argv, char** azColName);
	
public:
	Database();
	virtual ~Database();

	void createDB(const char* s);
	/************************************************************************************
	*	Creates a database
	*
	*	s 		database location
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*************************************************************************************/

	
	void createTable(const char* s, std::string table);
	/************************************************************************************
	*	Creates a table
	*
	*	s 		database location
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	table	table name and description
	*			"TABLENAME("
	*			"DATE			CHAR(20)	PRIMARY KEY NOT NULL,"
	*			"ID				INT			UNIQUE		NOT NULL,"
	*			"TEMPERATURE	REAL		NOT NULL);"
	*
	*************************************************************************************/


	void deleteTable(const char* s, std::string table);
	/************************************************************************************
	*	Deletes a table
	*
	*	s 		database location
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	table	table name
	*			"TABLENAME"
	*
	*************************************************************************************/
	
	
	void insertData(const char* s, std::string table, std::string data);
	/************************************************************************************
	*	Inserts a record into a table
	*
	*	s 		database location 
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	table	table name 
	*			"nameoftable"
	*
	*	data	data to insert	
	*			"'10-10-1010 10:10:10', 1, 23, 45, 13"
	*
	*************************************************************************************/


	void deleteData(const char* s, std::string table, std::string what);
	/************************************************************************************
	*	Deletes a record from a table
	*
	*	s 		database location, 
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	table	table name, 
	*			"nameoftable"
	*
	*	what	what to look for	
	*			"ID=23"
	*
	*	To delete everything from a table, what="CLEAR"
	*************************************************************************************/


	void selectData(const char* s, std::vector<std::pair<std::string, std::string>>& data, std::string table, std::string what);
	/************************************************************************************
	*	Selects a record from a table
	*
	*	s 		database location
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	data	vector where data will be stored at
	*			data
	*
	*	table	table name
	*			"nameoftable"
	*
	*	what	what to look for	
	*			"ID=23"
	*
	*	To select whole table, what=""
	*************************************************************************************/


	int getCount(const char* s, std::string table);
	/************************************************************************************
	*	Returns number of records in a table, -1 if table is nonexistent
	*
	*	s 		database location
	*			"C:\Users\USER\Documents\Database\nameofdatabase.db"
	*
	*	table	table name
	*			"nameoftable"
	*
	*************************************************************************************/


	void printData(std::vector<std::pair<std::string, std::string>> data);
	/************************************************************************************
	*	Prints out selected record
	*
	*	data	vector containing stored data
	*			data
	*
	*	Use selectData() to fill in data vector then pass it to printData()
	*************************************************************************************/
};

#endif

