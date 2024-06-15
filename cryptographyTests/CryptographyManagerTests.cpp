#include <gtest/gtest.h>
#include "../cryptography/CryptographyManager.cpp"

// Тестирование базовой функции шифрования и дешифрования
TEST(CryptographyManagerTest, EncryptDecryptBasic) {
    std::string username = "user";
    std::string password = "password";
    CryptographyManager manager(username, password);

    std::string plaintext = "Hello, World!";
    std::string encrypted = manager.Encrypt(plaintext);
    std::string decrypted = manager.Decrypt(encrypted);

    EXPECT_EQ(plaintext, decrypted);
}

// Тестирование шифрования userId
TEST(CryptographyManagerTest, UserIdEncryption) {
    std::string username = "user";
    std::string password = "password";
    CryptographyManager manager(username, password);

    std::string encryptedUsername = manager.getUserId();
    std::string decryptedUsername = manager.Decrypt(encryptedUsername);

    EXPECT_EQ(username, decryptedUsername);
}

// Тестирование правильности установки пароля
TEST(CryptographyManagerTest, PasswordEncryption) {
    std::string username = "user";
    std::string password = "password123";
    CryptographyManager manager(username, password);

    std::string plaintext = "Hello, World!";
    std::string encrypted = manager.Encrypt(plaintext);
    std::string decrypted = manager.Decrypt(encrypted);

    EXPECT_EQ(plaintext, decrypted);
}


// Тестирование с длинным паролем
TEST(CryptographyManagerTest, LongPassword) {
    std::string username = "user";
    std::string password = "thisisaverylongpasswordthatshouldworkcorrectly";
    CryptographyManager manager(username, password);

    std::string plaintext = "Hello, World!";
    std::string encrypted = manager.Encrypt(plaintext);
    std::string decrypted = manager.Decrypt(encrypted);

    EXPECT_EQ(plaintext, decrypted);
}
