#include "Database.h"

Database::Database()
{
}

Database::~Database()
{
}

int Database::callbackVectorPair(void* Used, int argc, char** argv, char** azColName)
{
	std::vector<std::pair<std::string, std::string>>* data = (std::vector< std::pair<std::string, std::string>>*)Used;
	for (int i = 0; i < argc; i++)
		data->emplace_back(azColName[i], argv[i]);
	return 0;
}

int Database::callbackInt(void* count, int argc, char** argv, char** azColName)
{
	int *c = (int*)count;
	*c = atoi(argv[0]);
	return 0;
}

void Database::createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);
}

void Database::createTable(const char* s, std::string table)
{
	sqlite3 *DB;
	char* messageError;

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		std::string sql = "CREATE TABLE " + table;

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK)
		{
			std::cerr << "Error creating table: " << messageError << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created successfully" << std::endl;
		sqlite3_close(DB);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}

void Database::deleteTable(const char * s, std::string table)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "DROP TABLE " + table + ";";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error deleting table: " << messageError << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Table deleted successfully" << std::endl;

	sqlite3_close(DB);
}

void Database::insertData(const char* s, std::string table, std::string data)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "INSERT INTO " + table + " VALUES(" + data + ");";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error inserting records: " << messageError << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Data inserted successfully" << std::endl;

	sqlite3_close(DB);
}

void Database::deleteData(const char* s, std::string table, std::string what)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "DELETE FROM " + table + " WHERE " + what + ";";

	if (what == "CLEAR")
		sql = "DELETE FROM " + table + ";";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error deleting records: " << messageError << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Data deleted successfully" << std::endl;

	sqlite3_close(DB);
}

void Database::selectData(const char* s, std::vector<std::pair<std::string , std::string>>& data, std::string table, std::string what)
{
	sqlite3* DB;

	char* messageError;
	std::string sql = "SELECT * FROM " + table + ";";

	if (what != "")
		sql = "SELECT * FROM " + table + " WHERE " + what + ";";

	data.clear();
	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), callbackVectorPair, &data, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error selecting data: " << messageError << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Data selected successfully!" << std::endl;

	sqlite3_close(DB);
}

int Database::getCount(const char* s, std::string table)
{
	sqlite3 *DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	int count = 0;
	std::string sql = "SELECT COUNT(*) FROM " + table + ";";

	exit = sqlite3_exec(DB, sql.c_str(), callbackInt, &count, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error gettig count: " << messageError << std::endl;
		sqlite3_free(messageError);
		sqlite3_close(DB);
		return -1;
	}
	sqlite3_close(DB);

	return count;
}

void Database::printData(std::vector<std::pair<std::string, std::string>> data)
{
	for (unsigned int i = 0; i < data.size(); i++)
		std::cout << data[i].first << " : " << data[i].second << std::endl;
}

