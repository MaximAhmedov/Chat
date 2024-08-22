#include "ServDB.h"

servDB::servDB()
{
	makeConnection(mysql);
	mysql_query(&mysql, "set names cp1251");
	std::string create_user_table = "CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(25), name VARCHAR(25), password VARCHAR(32))";
	std::string create_message_table = "CREATE TABLE IF NOT EXISTS messages(message_id INT AUTO_INCREMENT PRIMARY KEY, id_sender INT, id_getter INT, time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, text TEXT)";
	mysql_query(&mysql, create_user_table.c_str());
	mysql_query(&mysql, create_message_table.c_str());
}

servDB::~servDB()
{
    mysql_close(&mysql);
}

std::string servDB::regis(std::string& login,std::string& name,std::string& passw)
{
	std::string check_user_existanse = "SELECT * FROM " + users + " WHERE login = '"+login+"'";
	mysql_query(&mysql, check_user_existanse.c_str());
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res)){
		std::string notSucces = "Login is busy, try another one!\n";
		return notSucces;
		}
	std::string reg_new_user = "INSERT INTO " + users + " (login, name, password) values('" + login + "', '" + name + "', '" + passw + "')";
	mysql_query(&mysql, reg_new_user.c_str());
    std::string succes = "succes";
	return succes;
}

std::string servDB::auth(std::string &login, std::string &passw)
{
	std::string check_user_existanse = "SELECT * FROM " + users + " WHERE login = '" + login + "'";
	mysql_query(&mysql, check_user_existanse.c_str());
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res)){
		mysql_free_result(res);
		check_user_existanse = "SELECT * FROM " + users + " WHERE login = '" + login + "' AND password = '" + passw + "'";
		mysql_query(&mysql, check_user_existanse.c_str());
		res = mysql_store_result(&mysql);
		if(mysql_num_rows(res)){
			std::string succes = "succes";
			return succes;
			}
		else{
			std::string wrongPasw = "Incorrect password!\n";
			return wrongPasw;
		}
	}
	std::string nonExistUser = "There is no user with this login!\n";
	return nonExistUser;
}

std::string servDB::chatw(std::string &userLogin, std::string &friendLogin)
{
	std::string response;
	std::string getMessages = "SELECT (select login from users where messages.id_sender = users.id) AS senderlog, time, text FROM messages WHERE id_sender = "
	"(select id from users where login = '"+userLogin+"') AND id_getter = (select id from users where login = '"+friendLogin+"')"
	" OR id_sender = (select id from users where login = '"+friendLogin+"')"
	" AND id_getter = (select id from users where login = '"+userLogin+"')";
	mysql_query(&mysql, getMessages.c_str());
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res)){
		int rowCounter = 0;
		while (row = mysql_fetch_row(res)) {
			rowCounter++;
			for (int i = 0; i < mysql_num_fields(res); i++){
				response += row[i] + delim;
			}
		}
		return "1%" + std::to_string(rowCounter) + delim + response;
	}
	else
		return response += "0%There's no messages with this user\n";
}

void servDB::addmes(std::string &senderLogin, std::string &getterLogin, std::string& text)
{
	std::string addMes = "INSERT INTO messages(id_sender, id_getter, text) values((SELECT id FROM " + users + " WHERE login = '" + senderLogin + "'),"
	" (SELECT id FROM users WHERE login = '" + getterLogin + "'), '" + text + "')";
	mysql_query(&mysql, addMes.c_str());
}

std::string servDB::alluser(std::string &userLogin)
{
	int counter = 0;
	std::string response;
	std::string getUsers = "SELECT login, name FROM " + users + " WHERE login <> '" + userLogin + "'";
	mysql_query(&mysql, getUsers.c_str());
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res)){
		while (row = mysql_fetch_row(res)) {
			response += std::to_string(++counter) + delim;
			for (int i = 0; i < mysql_num_fields(res); i++){
				response += row[i] + delim;
			}
		}
		return std::to_string(counter) + delim + response;
	}
	else
		return response += std::to_string(counter) + delim + "You are the only user\n";
}

std::string servDB::allchats(std::string& userLogin)
{
	int counter = 0;
	std::string response;
	std::string getChats = "SELECT (select login from users where users.id=gigatable.friendid) AS friendlog, (select name from users where users.id=gigatable.friendid)"
	" AS friendname FROM (select *, IF((SELECT users.id FROM users WHERE users.login = '" + userLogin + "')=messages.id_sender,messages.id_getter,messages.id_sender)"
	" AS friendid from users join messages on users.id = messages.id_sender) AS gigatable WHERE gigatable.id_sender = (SELECT users.id FROM users WHERE users.login = '" + userLogin + "')"
	" OR gigatable.id_getter = (SELECT users.id FROM users WHERE users.login = '" + userLogin + "') GROUP BY friendlog, friendname;";
	mysql_query(&mysql, getChats.c_str());
	res = mysql_store_result(&mysql);
    if(mysql_num_rows(res)){
		while (row = mysql_fetch_row(res)) {
			response += std::to_string(++counter) + delim;
			for (int i = 0; i < mysql_num_fields(res); i++){
				response += row[i] + delim;
			}
		}
		return std::to_string(counter) + delim + response;
	}
	else
		return response += std::to_string(counter) + delim + "There are no dialogues yet\n";
}

void servDB::makeConnection(MYSQL& mysql)
{
	std::string tmpUser;
	std::string tmpPasw;
	std::string dbName;
	while(true){
		mysql_init(&mysql);
		if (&mysql == nullptr) {
			std::cout << "Error: can't create MySQL-descriptor" << std::endl;
		}
		std::cout << "\nEnter user name\n";
        std::cin >> tmpUser;
		std::cout << "\nEnter user password\n";
        std::cin >> tmpPasw;
		std::cout << "\nEnter user database name\n";
        std::cin >> dbName;
		if (!mysql_real_connect(&mysql, "localhost", tmpUser.c_str(), tmpPasw.c_str(), dbName.c_str(), 0, NULL, 0)) {
			clear_screen();
			std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
			mysql_reset_connection(&mysql);
		}
		else {
			break;
		}
	}
	clear_screen();
	std::cout << "Succes connection to database!\n";
}
