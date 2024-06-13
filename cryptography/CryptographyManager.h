#ifndef CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H
#define CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H

#include <string>

std::string Encrypt(const std::string& plaintext, std::string password);

std::string Decrypt(const std::string& ciphertext, std::string password);

#endif //CRYPTOGRAPHY_CRYPTOGRAPHYMANAGER_H
