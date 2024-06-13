#include <cstdint>
#include <string>
#include <vector>
#include "cryptography.h"
#include "CryptographyManager.h"

std::string Encrypt(const std::string& plaintext, std::string password) {
    std::string textHex = textToHex(plaintext);
    std::vector<uint8_t> encoded(plaintext.begin(), plaintext.end());

    const uint8_t *key = stringToReversedKey(password);

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    // зашифровка
    std::vector<uint8_t> ciphertext = cbcEncrypt(encoded, round_keys);
    return textToHex(std::string(ciphertext.begin(), ciphertext.end()));
}

std::string Decrypt(const std::string& ciphertext, std::string password) {
    const uint8_t *key = stringToReversedKey(password);

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
