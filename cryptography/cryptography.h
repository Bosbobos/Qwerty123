#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

const int block_len = 16;

extern const uint8_t S[256];
extern const uint8_t INVERSE_S[256];
extern const uint8_t L[16];
extern const uint8_t DEGREE[255];
extern const uint8_t INVERSE_DEGREE[255];

uint8_t multiply_in_Galua(uint8_t a, uint8_t b);

extern uint8_t MULS[256][256];
void create_muls();

extern uint8_t MATRIX[block_len][256][block_len];
extern uint8_t INVERSE_MATRIX[block_len][256][block_len];

void L_transform(uint8_t block[block_len]);
void inverse_L_transform(uint8_t block[block_len]);
void linear_transform(uint8_t block[block_len]);
void inverse_linear_transform(uint8_t block[block_len]);
void create_MATRIX();

void generate_round_constants(uint8_t round_constants[32][block_len]);
void generate(const uint8_t key[32], uint8_t round_keys[10][block_len]);

std::string textToHex(const std::string &input);

void padKey(std::string &input_key);

const uint8_t *stringToReversedKey(std::string &input_key);

std::vector<uint8_t> hexToVector(const std::string &hex);

std::string vectorToHex(const std::vector<uint8_t> &vec);

void encode_block(uint8_t block[block_len], const uint8_t round_keys[10][block_len]);

void decode_block(uint8_t block[block_len], const uint8_t round_keys[10][block_len]);

void xorBlocks(uint8_t *block1, const uint8_t *block2, size_t length);

std::vector<uint8_t> cbcEncrypt(const std::vector<uint8_t> &plaintext, const uint8_t round_keys[10][block_len]);

std::vector<uint8_t> cbcDecrypt(const std::vector<uint8_t> &ciphertext, const uint8_t round_keys[10][block_len]);

#endif // CRYPTOGRAPHY_H
