#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include <fstream>
#include "../dbManager/authManager.h"
#include "ConfigManager.h"

// Test fixture to set up the environment
class AuthManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::string connection_string = GetDbConnectionString();

        auto conn = new pqxx::connection(connection_string);
        pqxx::work W(*conn);
        W.exec("DROP TABLE IF EXISTS AuthTest");
        W.commit();

        // Initialize AuthManager with connection string
        authManager = new AuthManager(connection_string, "AuthTest");
        authManager->createTable(); // Ensure the table exists before each test
    }

    void TearDown() override {
        delete authManager;
    }

    // Pointer to AuthManager instance
    AuthManager* authManager;
};

// Test case to check table creation
TEST_F(AuthManagerTest, CreateTableTest) {
    // Ensure table creation succeeds
    EXPECT_NO_THROW(authManager->createTable());
}

// Test case to check record insertion
TEST_F(AuthManagerTest, AddRecordTest) {
    // Insert a record
    std::string login = "test_login";
    EXPECT_NO_THROW(authManager->addRecord(login));

    // Check if the record was added
    EXPECT_TRUE(authManager->loginExists(login));
}

// Test case to check login existence
TEST_F(AuthManagerTest, LoginExistsTest) {
    // Insert a record
    std::string login = "test_login";
    authManager->addRecord(login);

    // Check if the login exists
    EXPECT_TRUE(authManager->loginExists(login));

    // Check for a login that does not exist
    EXPECT_FALSE(authManager->loginExists("nonexistent_login"));
}

// Test case to check for duplicate login insertion
TEST_F(AuthManagerTest, DuplicateLoginTest) {
    // Insert a record
    std::string login = "duplicate_login";
    authManager->addRecord(login);

    // Try to insert a duplicate login
    EXPECT_THROW(authManager->addRecord(login), pqxx::sql_error);
}
