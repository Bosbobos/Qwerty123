#include <gtest/gtest.h>
#include "../cryptography/CryptographyManager.cpp"

TEST(CryptographyTest, EncryptDecryptBasic) {
    std::string plaintext = "Hello, World!";
    std::string password = "password";

    std::string encrypted = Encrypt(plaintext, password);
    std::string decrypted = Decrypt(encrypted, password);

    EXPECT_EQ(plaintext, decrypted);
}
