#include <cstdint>
#include <string>
#include <vector>
#include "cryptography.h"
#include "CryptographyManager.h"

std::string CryptographyManager::Encrypt(const std::string& plaintext) {
    std::string textHex = textToHex(plaintext);
    std::vector<uint8_t> encoded(plaintext.begin(), plaintext.end());

    const uint8_t *key = stringToReversedKey(this->password);

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    // зашифровка
    std::vector<uint8_t> ciphertext = cbcEncrypt(encoded, round_keys);
    return textToHex(std::string(ciphertext.begin(), ciphertext.end()));
}

std::string CryptographyManager::Decrypt(const std::string& ciphertext) {
    const uint8_t *key = stringToReversedKey(this->password);

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    // преобразуем hex строку в вектор байтов
    std::vector<uint8_t> Ciphertext = hexToVector(ciphertext);
    // расшифровка
    std::vector<uint8_t> decryptedtext = cbcDecrypt(Ciphertext, round_keys);
    std::string decrypted_string(decryptedtext.begin(), decryptedtext.end());

    return decrypted_string;
}

CryptographyManager::CryptographyManager(const std::string &username, const std::string &password) : username(username),
                                                                                                     password(password) {
    userId = Encrypt(username);
}

const std::string &CryptographyManager::getUserId() const {
    return userId;
}
