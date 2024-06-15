#ifndef CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H
#define CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H

#include <string>

class CryptographyManager {
public:
    CryptographyManager(const std::string &username, const std::string &password);
    /*
     * Зашифрование текста паролем, хранящимся в
     */
    std::string Encrypt(const std::string &plaintext);
    std::string Decrypt(const std::string &ciphertext);

    const std::string &getUserId() const;

private:
    std::string username;
    std::string password;
    std::string userId;
};

#endif //CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H
