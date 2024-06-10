#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include "../dbManager/dbManager.h"

// Test fixture to set up the environment
class DbManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize DbManager with connection string
        dbManager = new DbManager("host=localhost port=5431 dbname=postgres user=postgres password=P@ssw0rd");
        dbManager->createTable(); // Ensure the table exists before each test
    }

    void TearDown() override {
        delete dbManager;
    }

    // Pointer to DbManager instance
    DbManager* dbManager;
};

// Test case to check table creation
TEST_F(DbManagerTest, CreateTableTest) {
    // Ensure table creation succeeds
    EXPECT_NO_THROW(dbManager->createTable());
}

// Test case to check record insertion
TEST_F(DbManagerTest, AddRecordTest) {
    // Insert a record
    Record record(1, "master", "record1", "http://example.com", "user", "password", "tag", "2023-12-31");
    dbManager->addRecord(record);

    // Find the inserted record
    Record record = dbManager->findRecord(1);

    // Check if the record is found
    EXPECT_EQ(record.getMasterUsername(), "master");
    EXPECT_EQ(record.getRecName(), "record1");
    EXPECT_EQ(record.getUrl(), "http://example.com");
    EXPECT_EQ(record.getUsername(), "user");
    EXPECT_EQ(record.getPassword(), "password");
    EXPECT_EQ(record.getTag(), "tag");
    EXPECT_EQ(record.getExpires(), "2023-12-31");
}

// Test case to check record updating
TEST_F(DbManagerTest, UpdateRecordTest) {
    // Insert a record
    dbManager->addRecord("master", "record1", "http://example.com", "user", "password", "tag", "2023-12-31");

    // Update the password of the inserted record
    dbManager->updatePassword(1, "new_password");

    // Find the updated record
    Record record = dbManager->findRecord(1);

    // Check if the password is updated
    EXPECT_EQ(record.getPassword(), "new_password");
}

// Test case to check record deletion
TEST_F(DbManagerTest, DeleteRecordTest) {
    // Insert a record
    dbManager->addRecord("master", "record1", "http://example.com", "user", "password", "tag", "2023-12-31");

    // Delete the inserted record
    dbManager->deleteRecord(1);

    // Attempt to find the deleted record
    EXPECT_THROW(dbManager->findRecord(1), std::runtime_error);
}

// Test case to check finding records by username
TEST_F(DbManagerTest, FindAllUserRecordsTest) {
    // Insert records for a specific username
    dbManager->addRecord("master", "record1", "http://example.com", "user1", "password1", "tag1", "2023-12-31");
    dbManager->addRecord("master", "record2", "http://example.com", "user1", "password2", "tag2", "2023-12-31");

    // Find all records for the given username
    std::vector<Record> records = dbManager->findAllUserRecords("user1");

    // Ensure the correct number of records is returned
    EXPECT_EQ(records.size(), 2);
}

// Test case to check finding records by username and tag
TEST_F(DbManagerTest, FindAllUserRecordsWithTagTest) {
    // Insert records for a specific username with a specific tag
    dbManager->addRecord("master", "record1", "http://example.com", "user2", "password1", "tag1", "2023-12-31");
    dbManager->addRecord("master", "record2", "http://example.com", "user2", "password2", "tag1", "2023-12-31");
    dbManager->addRecord("master", "record3", "http://example.com", "user2", "password3", "tag2", "2023-12-31");

    // Find all records for the given username and tag
    std::vector<Record> records = dbManager->findAllUserRecordsWithTag("user2", "tag1");

    // Ensure the correct number of records is returned
    EXPECT_EQ(records.size(), 2);
}
