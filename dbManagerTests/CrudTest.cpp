#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include "fstream"
#include "../dbManager/PostgresCRUD.h"

// Test fixture
class PostgresCRUDTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::string connection_string = getConnectionStringFromFile("./config.txt");

        // Connect to the real database
        auto conn = new pqxx::connection(connection_string);
        crud = new PostgresCRUD(connection_string);

        // Set up the test table
        pqxx::work W(*conn);
        W.exec("DROP TABLE IF EXISTS test_table");
        W.exec("CREATE TABLE test_table (name TEXT, age TEXT)");
        W.commit();
    }

    std::string getConnectionStringFromFile(const std::string& filename) {
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            throw std::runtime_error("Cannot open " + filename);
        }

        std::string line;
        std::getline(configFile, line);
        configFile.close();

        std::string prefix = "db_connection_string=";
        if (line.compare(0, prefix.length(), prefix) == 0) {
            return line.substr(prefix.length());
        } else {
            throw std::runtime_error("Invalid configuration file format");
        }
    }

    void TearDown() override {
        delete crud;
    }

    PostgresCRUD* crud;
};

// Test case for the create method
TEST_F(PostgresCRUDTest, Create) {
// Prepare test data
std::string table = "test_table";
std::map<std::string, std::string> data = {{"name", "John"}, {"age", "30"}};

// Call the create method
ASSERT_NO_THROW(crud->create(table, data));

// Verify that the data is inserted correctly
pqxx::connection conn(getConnectionStringFromFile("config.txt"));
pqxx::nontransaction N(conn);
pqxx::result result = N.exec("SELECT * FROM " + table);
ASSERT_EQ(result.size(), 1); // Expecting one row
ASSERT_EQ(result[0]["name"].as<std::string>(), "John");
ASSERT_EQ(result[0]["age"].as<std::string>(), "30");
}

// Test case for the read method
TEST_F(PostgresCRUDTest, Read) {
// Prepare test data
std::string table = "test_table";
std::map<std::string, std::string> data = {{"name", "John"}, {"age", "30"}};
crud->create(table, data);

// Call the read method with a query
pqxx::result result = crud->read("SELECT * FROM " + table);

// Verify that the read operation returned the correct data
ASSERT_EQ(result.size(), 1); // Expecting one row
ASSERT_EQ(result[0]["name"].as<std::string>(), "John");
ASSERT_EQ(result[0]["age"].as<std::string>(), "30");
}

// Test case for the update method
TEST_F(PostgresCRUDTest, Update) {
// Prepare test data
std::string table = "test_table";
std::map<std::string, std::string> initial_data = {{"name", "John"}, {"age", "30"}};
crud->create(table, initial_data);

// Call the update method
std::map<std::string, std::string> updated_data = {{"age", "40"}};
ASSERT_NO_THROW(crud->update(table, updated_data, "name='John'"));

// Verify that the data is updated correctly
pqxx::connection conn(getConnectionStringFromFile("config.txt"));
pqxx::nontransaction N(conn);
pqxx::result result = N.exec("SELECT * FROM " + table);
ASSERT_EQ(result.size(), 1); // Expecting one row
ASSERT_EQ(result[0]["name"].as<std::string>(), "John");
ASSERT_EQ(result[0]["age"].as<std::string>(), "40");
}

// Test case for the delete_record method
TEST_F(PostgresCRUDTest, DeleteRecord) {
// Prepare test data
std::string table = "test_table";
std::map<std::string, std::string> data = {{"name", "John"}, {"age", "30"}};
crud->create(table, data);

// Call the delete_record method
ASSERT_NO_THROW(crud->delete_record(table, "name='John'"));

// Verify that the record is deleted
pqxx::connection conn(getConnectionStringFromFile("config.txt"));
pqxx::nontransaction N(conn);
pqxx::result result = N.exec("SELECT * FROM " + table);
ASSERT_EQ(result.size(), 0); // Expecting no rows
}
