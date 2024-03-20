#include <DatabaseConnector.h>
#include <cppconn/driver.h>

DatabaseConnector::DatabaseConnector(const std::string &server_, const std::string &username_, const std::string &password_)
    : server(server_), username(username_), password(password_) {
    driver = sql::mysql::get_mysql_driver_instance();
    
    connectToDatabase();
}

bool DatabaseConnector::connectToDatabase() {
    try {
        // std::cout<<server<<"   "<<username<<"  "<<password<<std::endl;
        dbConnection = driver->connect(server, username, password);
        dbConnection->setSchema("Sysmonitor");        //test
        return true;
    } catch (sql::SQLException &e) {
        std::cout<<"dbconnector error!!: "<<e.what()<<std::endl;
        return false;
    }
}

void DatabaseConnector::disconnectFromDatabase() {
    if (dbConnection) {
        dbConnection->close();
        delete dbConnection;
    }
}

