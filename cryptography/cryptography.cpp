/**
 * @file cryptography.cpp
 * @brief Реализация алгоритма блочного шифра Кузнечика (ГОСТ Р 34.12-2015).
 */
#include <iostream>
#include <iomanip>
#include <random>
#include <cstring>
#include <algorithm>
#include <sstream>

/// Длина блока в алгоритме Кузнечика = 16 байт
const int block_len = 16;

// Заимствованный код: начало

/// S-блок для нелинейного преобразования
const uint8_t S[256] = {
        252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219,
        147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129,
        28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212,
        211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181, 112,
        14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161, 150, 41, 16, 123, 154,
        199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198,
        128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185,
        3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115,
        30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163,
        165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217,
        231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113,
        103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230, 244,
        180, 192, 209, 102, 175, 194, 57, 75, 99, 182,
};

/// Инверсный S-блок для нелинейного преобразования
const uint8_t INVERSE_S[256] = {
        0xa5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
        0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18, 0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
        0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4, 0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
        0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
        0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B, 0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
        0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F, 0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
        0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
        0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11, 0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
        0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F, 0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
        0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
        0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0, 0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
        0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D, 0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
        0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
        0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88, 0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
        0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
        0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74,
};

/// вектор линейного преобразования
const uint8_t L[16] = {
        1, 148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148,
};

/// таблица степеней двойки в поле GF(2^8)
const uint8_t DEGREE[255] = {
        1, 2, 4, 8, 16, 32, 64, 128, 195, 69, 138, 215, 109, 218, 119, 238, 31, 62, 124, 248, 51, 102,
        204, 91, 182, 175, 157, 249, 49, 98, 196, 75, 150, 239, 29, 58, 116, 232, 19, 38, 76, 152, 243,
        37, 74, 148, 235, 21, 42, 84, 168, 147, 229, 9, 18, 36, 72, 144, 227, 5, 10, 20, 40, 80, 160,
        131, 197, 73, 146, 231, 13, 26, 52, 104, 208, 99, 198, 79, 158, 255, 61, 122, 244, 43, 86, 172,
        155, 245, 41, 82, 164, 139, 213, 105, 210, 103, 206, 95, 190, 191, 189, 185, 177, 161, 129,
        193, 65, 130, 199, 77, 154, 247, 45, 90, 180, 171, 149, 233, 17, 34, 68, 136, 211, 101, 202,
        87, 174, 159, 253, 57, 114, 228, 11, 22, 44, 88, 176, 163, 133, 201, 81, 162, 135, 205, 89,
        178, 167, 141, 217, 113, 226, 7, 14, 28, 56, 112, 224, 3, 6, 12, 24, 48, 96, 192, 67, 134, 207,
        93, 186, 183, 173, 153, 241, 33, 66, 132, 203, 85, 170, 151, 237, 25, 50, 100, 200, 83, 166,
        143, 221, 121, 242, 39, 78, 156, 251, 53, 106, 212, 107, 214, 111, 222, 127, 254, 63, 126, 252,
        59, 118, 236, 27, 54, 108, 216, 115, 230, 15, 30, 60, 120, 240, 35, 70, 140, 219, 117, 234, 23,
        46, 92, 184, 179, 165, 137, 209, 97, 194, 71, 142, 223, 125, 250, 55, 110, 220, 123, 246, 47,
        94, 188, 187, 181, 169, 145, 225,
};

/// таблица: по числу получить его степень в поле Галуа
const uint8_t INVERSE_DEGREE[255] = {
        0, 1, 157, 2, 59, 158, 151, 3, 53, 60, 132, 159, 70, 152, 216, 4, 118, 54, 38, 61, 47, 133,
        227, 160, 181, 71, 210, 153, 34, 217, 16, 5, 173, 119, 221, 55, 43, 39, 191, 62, 88, 48, 83,
        134, 112, 228, 247, 161, 28, 182, 20, 72, 195, 211, 242, 154, 129, 35, 207, 218, 80, 17, 204,
        6, 106, 174, 164, 120, 9, 222, 237, 56, 67, 44, 31, 40, 109, 192, 77, 63, 140, 89, 185, 49,
        177, 84, 125, 135, 144, 113, 23, 229, 167, 248, 97, 162, 235, 29, 75, 183, 123, 21, 95, 73, 93,
        196, 198, 212, 12, 243, 200, 155, 149, 130, 214, 36, 225, 208, 14, 219, 189, 81, 245, 18, 240,
        205, 202, 7, 104, 107, 65, 175, 138, 165, 142, 121, 233, 10, 91, 223, 147, 238, 187, 57, 253,
        68, 51, 45, 116, 32, 179, 41, 171, 110, 86, 193, 26, 78, 127, 64, 103, 141, 137, 90, 232, 186,
        146, 50, 252, 178, 115, 85, 170, 126, 25, 136, 102, 145, 231, 114, 251, 24, 169, 230, 101, 168,
        250, 249, 100, 98, 99, 163, 105, 236, 8, 30, 66, 76, 108, 184, 139, 124, 176, 22, 143, 96, 166,
        74, 234, 94, 122, 197, 92, 199, 11, 213, 148, 13, 224, 244, 188, 201, 239, 156, 254, 150, 58,
        131, 52, 215, 69, 37, 117, 226, 46, 209, 180, 15, 33, 220, 172, 190, 42, 82, 87, 246, 111, 19,
        27, 241, 194, 206, 128, 203, 79,
};


/**
 * @brief Выполняет умножение двух байтов в поле Галуа (GF(2^8)).
 *
 * Функция принимает два байта и выполняет их умножение в поле Галуа.
 * Если один из байтов равен 0, результатом будет 0. Иначе, используются
 * логарифмы и экспоненты для выполнения умножения.
 *
 * @param a Первый байт.
 * @param b Второй байт.
 * @return uint8_t Результат умножения в поле Галуа.
 */
uint8_t multiply_in_Galua(uint8_t a, uint8_t b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    uint8_t inda = INVERSE_DEGREE[a - 1];
    uint8_t indb = INVERSE_DEGREE[b - 1];
    size_t indmul = inda + indb;
    if (indmul >= 255) {
        indmul -= 255;
    }
    return DEGREE[indmul];
}

// Конец заимственного кода

/**
 * @brief Таблица предварительно вычисленных произведений в поле Галуа (GF(2^8)).
 */
uint8_t MULS[256][256] = {};

/**
 * @brief Создает таблицу предварительно вычисленных произведений в поле Галуа (GF(2^8)).
 */
void create_muls() {
    for (size_t i = 0; i < 256; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            MULS[i][j] = multiply_in_Galua(i, j);
        }
    }
}

/**
 * @brief Матрица для линейного преобразования.
 */
uint8_t MATRIX[block_len][256][block_len] = {};

/**
 * @brief Матрица для обратного линейного преобразования.
 */
uint8_t INVERSE_MATRIX[block_len][256][block_len] = {};

/**
 * @brief Выполняет линейное преобразование блока данных.
 *
 * @param block Блок данных длиной block_len байт.
 */
void L_transform(uint8_t block[block_len]) {
    uint8_t res[block_len] = {};
    for (uint8_t i = 0; i < block_len; ++i) {
        for (uint8_t f_ind = 0; f_ind < block_len; ++f_ind) {
            res[f_ind] ^= MATRIX[i][block[i]][f_ind];
        }
    }
    memcpy(block, res, block_len);
}

/**
 * @brief Выполняет обратное линейное преобразование блока данных.
 *
 * @param block Блок данных длиной block_len байт.
 */
void inverse_L_transform(uint8_t block[block_len]) {
    uint8_t res[block_len] = {};
    for (uint8_t i = 0; i < block_len; ++i) {
        for (uint8_t f_ind = 0; f_ind < block_len; ++f_ind) {
            res[f_ind] ^= INVERSE_MATRIX[i][block[i]][f_ind];
        }
    }
    memcpy(block, res, block_len);
}

/**
 * @brief Выполняет линейное преобразование блока данных без использования предварительно вычисленных матриц.
 *
 * @param block Блок данных длиной block_len байт.
 */
void linear_transform(uint8_t block[block_len]) {
    create_muls();
    uint8_t cur = 0;
    for (uint8_t i = 0; i < block_len; ++i) {
        for (uint8_t f_ind = 0; f_ind < block_len; ++f_ind) {
            cur ^= MULS[L[f_ind]][block[(f_ind + i) % 16]];
        }
        block[i] = cur;
        cur = 0;
    }
}

/**
 * @brief Выполняет обратное линейное преобразование блока данных без использования предварительно вычисленных матриц.
 *
 * @param block Блок данных длиной block_len байт.
 */
void inverse_linear_transform(uint8_t block[block_len]) {
    create_muls();
    uint8_t cur = 0;
    for (uint8_t i = 0; i < block_len; ++i) {
        for (uint8_t f_ind = 0; f_ind < block_len; ++f_ind) {
            cur ^= MULS[L[15 - f_ind]][block[(f_ind + block_len - i) % block_len]];
        }
        block[15 - i] = cur;
        cur = 0;
    }
}

/**
 * @brief Создает матрицы для линейного и обратного линейного преобразования.
 */
void create_MATRIX() {
    uint8_t block[block_len] = {};
    for (uint8_t i = 0; i < block_len; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            memset(block, (uint8_t) 0, block_len);
            block[i] = j;
            linear_transform(block);
            memcpy(MATRIX[i][j], block, block_len);
            memset(block, (uint8_t) 0, block_len);
            block[i] = j;
            inverse_linear_transform(block);
            memcpy(INVERSE_MATRIX[i][j], block, block_len);
        }
    }
}

/**
 * @brief Генерирует константы для раундов шифрования.
 *
 * @param round_constants Массив для хранения раундовых констант (размер 32x16).
 */
void generate_round_constants(uint8_t round_constants[32][16]) {
    // создание матриц всевозможных перемножений в поле Галуа
    create_muls();
    // делаем предподсчет для линейного преобразования
    create_MATRIX();
    // нужно 32 константы для генерации 10 ключей
    for (uint8_t i = 0; i < 32; ++i) {
        round_constants[i][0] = i + 1;
        L_transform(round_constants[i]);
    }
}

/**
 * @brief Генерация раундовых ключей для алгоритма Кузнечик с использованием сети Фейстеля.
 *
 * @param key Исходный ключ длиной 32 байта.
 * @param round_keys Массив для хранения 10 раундовых ключей, каждый длиной block_len байт.
 */
void generate(const uint8_t key[32], uint8_t round_keys[10][block_len]) {
    // получаем 32 константы: 4 итерации по 8 констант каждая
    uint8_t round_constants[32][block_len] = {};
    generate_round_constants(round_constants);

    // первые 2 ключа - половинки исходного
    memcpy(round_keys[0], key + (uint8_t) block_len, block_len);
    memcpy(round_keys[1], key, block_len);

    // сеть Фейстеля
    for (uint8_t i = 1; i < 5; ++i) {
        uint8_t left[block_len] = {};
        uint8_t right[block_len] = {};
        uint8_t new_left[block_len] = {};

        memcpy(left, round_keys[2 * (i - 1)], block_len);
        memcpy(right, round_keys[2 * (i - 1) + 1], block_len);

        for (uint8_t j = 0; j < 8; ++j) {
            for (uint8_t k = 0; k < block_len; ++k) {
                new_left[k] = S[(left[k] ^ round_constants[(i - 1) * 8 + j][k])];
            }
            L_transform(new_left);
            for (uint8_t k = 0; k < block_len; ++k) {
                new_left[k] ^= right[k];
            }
            memcpy(right, left, block_len);
            memcpy(left, new_left, block_len);
        }
        memcpy(round_keys[2 * i], left, block_len);
        memcpy(round_keys[2 * i + 1], right, block_len);
    }
}

/**
 * @brief Добавляет нулевой байт в начало строки и дополняет ее нулями до длины 32 символа.
 *
 * @param input Входная строка.
 * @return std::string Результат после дополнения.
 */
std::string padBlock(const std::string &input) {
    std::string padded = input;
    if (padded.length() < 32) {
        padded.insert(padded.begin(), '8'); // Добавляем '8' в начало
        while (padded.length() < 32) {
            padded.insert(padded.begin() + 1, '0'); // Дополняем нулями
        }
    }
    return padded;
}

/**
 * @brief Преобразует текстовую строку в её шестнадцатеричное представление.
 *
 * @param input Строка текста.
 * @return Строка, содержащая шестнадцатеричное представление входной строки.
 */
std::string textToHex(const std::string &input) {
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (char c: input) {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
    }
    return hexStream.str();
}

/**
 * @brief Преобразует шестнадцатеричную строку обратно в текст.
 *
 * @param hexInput Строка, содержащая шестнадцатеричное представление.
 * @return Строка текста.
 */
std::string hexToText(const std::string &hexInput) {

    std::string text;
    text.reserve(hexInput.length() / 2);
    for (size_t i = 0; i < hexInput.length(); i += 2) {
        std::string byteString = hexInput.substr(i, 2);
        char byte = static_cast<char>(std::stoul(byteString, nullptr, 16));
        text.push_back(byte);
    }
    return text;
}

void padKey(std::string& input_key){
    if (input_key.length() < 64) {
        while (input_key.length() < 64) {
            input_key.insert(input_key.begin() + 1, '0'); // Дополняем нулями
        }
    }
};

/**
 * @brief Преобразует строку из шестнадцатеричного представления в обратный массив uint8_t.
 *
 * @param input_key Входная строка ключа.
 * @return const uint8_t* Указатель на массив обратного ключа.
 */
const uint8_t *stringToReversedKey(std::string &input_key) {
    std::string keyHex = textToHex(input_key);
    padKey(keyHex);
    static uint8_t key[32];
    for (int i = 0; i < 32; ++i) {
        std::string part = keyHex.substr(i * 2, 2);
        key[31 - i] = std::stoul(part, nullptr, 16);
    }
    return key;
}

/**
 * @brief Преобразует строку в массив uint8_t.
 *
 * @param input Входная строка.
 * @param output Выходной массив.
 */
void convertStringToBlock(const std::string &input, uint8_t output[16]) {
    std::string paddedBlock = padBlock(input);
    std::vector<uint8_t> block_vec;
    // Преобразование строки в вектор uint8_t
    for (size_t i = 0; i < paddedBlock.size(); i += 2) {
        std::string byte_str = paddedBlock.substr(i, 2);
        uint8_t byte = std::stoul(byte_str, nullptr, 16);
        block_vec.push_back(byte);
    }
    // Разворот вектора
    std::reverse(block_vec.begin(), block_vec.end());
    // Преобразование вектора в массив
    for (size_t i = 0; i < block_vec.size(); ++i) {
        output[i] = block_vec[i];
    }
}


/**
 * @brief Шифрует блок данных с использованием раундовых ключей.
 *
 * @param block Указатель на блок данных для шифрования.
 * @param round_keys Массив раундовых ключей.
 */
void encode_block(uint8_t block[block_len], const uint8_t round_keys[10][block_len]) {
    for (uint8_t i = 0; i < 9; ++i) {
        for (uint8_t idx = 0; idx < block_len; ++idx) {
            block[idx] = S[block[idx] ^ round_keys[i][idx]];
        }
        L_transform(block);
    }
    for (uint8_t idx = 0; idx < block_len; ++idx) {
        block[idx] ^= round_keys[9][idx];
    }
}

/**
 * @brief Дешифрует блок данных с использованием раундовых ключей.
 *
 * @param block Указатель на блок данных для дешифрования.
 * @param round_keys Массив раундовых ключей.
 */
void decode_block(uint8_t block[block_len], const uint8_t round_keys[10][block_len]) {
    for (uint8_t idx = 0; idx < block_len; ++idx) {
        block[idx] ^= round_keys[9][idx];
    }
    for (int8_t i = 8; i >= 0; --i) {
        inverse_L_transform(block);
        for (uint8_t idx = 0; idx < block_len; ++idx) {
            block[idx] = INVERSE_S[block[idx]] ^ round_keys[i][idx];
        }
    }
}

/**
 * @brief Отображает блок данных в формате шифрования.
 *
 * @param block Указатель на блок данных.
 */
void displayBlockEncode(const uint8_t *block) {
    std::cout << std::hex << std::setfill('0');
    for (size_t j = 0; j < 16; ++j)
        std::cout << std::setw(2) << (int) block[15 - j];
    std::cout << std::dec << std::endl << std::endl;
}

/**
 * @brief Шифрование текста в режиме CBC.
 *
 * @param plaintext Входной текст для шифрования.
 * @param iv Вектор инициализации.
 * @param round_keys Раундовые ключи.
 * @return Зашифрованный текст.
 */
std::vector<uint8_t> cbcEncrypt(const std::vector<uint8_t> &plaintext,
                                const uint8_t round_keys[10][block_len]) {
    uint8_t iv[block_len] = {0xa5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52,
                             0x91};
    size_t num_blocks = (plaintext.size() + block_len - 1) / block_len;
    std::vector<uint8_t> ciphertext(num_blocks * block_len);
    uint8_t prev_block[block_len];
    std::memcpy(prev_block, iv, block_len);

    for (size_t i = 0; i < num_blocks; ++i) {
        uint8_t block[block_len] = {};
        size_t block_start = i * block_len;

        for (size_t j = 0; j < block_len && block_start + j < plaintext.size(); ++j) {
            block[j] = plaintext[block_start + j];
        }

        // XOR с предыдущим блоком или IV
        for (size_t j = 0; j < block_len; ++j) {
            block[j] ^= prev_block[j];
        }

        encode_block(block, round_keys);
        std::memcpy(&ciphertext[block_start], block, block_len);
        std::memcpy(prev_block, block, block_len);
    }

    return ciphertext;
}

/**
 * @brief Расшифрование текста в режиме CBC.
 *
 * @param ciphertext Входной зашифрованный текст.
 * @param iv Вектор инициализации.
 * @param round_keys Раундовые ключи.
 * @return Расшифрованный текст.
 */
std::vector<uint8_t> cbcDecrypt(const std::vector<uint8_t> &ciphertext,
                                const uint8_t round_keys[10][block_len]) {
    uint8_t iv[block_len] = {0xa5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52,
                             0x91};
    size_t num_blocks = ciphertext.size() / block_len;
    std::vector<uint8_t> plaintext(num_blocks * block_len);
    uint8_t prev_block[block_len];
    std::memcpy(prev_block, iv, block_len);

    for (size_t i = 0; i < num_blocks; ++i) {
        uint8_t block[block_len] = {};
        size_t block_start = i * block_len;

        std::memcpy(block, &ciphertext[block_start], block_len);
        uint8_t decrypted_block[block_len];
        std::memcpy(decrypted_block, block, block_len);

        decode_block(decrypted_block, round_keys);

        // XOR с предыдущим блоком или IV
        for (size_t j = 0; j < block_len; ++j) {
            plaintext[block_start + j] = decrypted_block[j] ^ prev_block[j];
        }

        std::memcpy(prev_block, block, block_len);
    }

    return plaintext;
}

/**
 * @brief Отображает блок данных в формате дешифрования.
 *
 * @param block Указатель на блок данных.
 */
void displayBlockDecode(const uint8_t *block) {
    // Преобразуем блок данных в строку
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t j = 0; j < 16; ++j)
        ss << std::setw(2) << (int) block[15 - j];
    std::string hexString = ss.str();
    // Применяем условие удаления '8' и последующих нулей
    if (!hexString.empty() && hexString[0] == '8') {
        size_t pos = 1;
        while (pos < hexString.size() && hexString[pos] == '0') {
            ++pos;
        }
        hexString = hexString.substr(pos);
    }
    // Выводим измененную строку
    std::cout << hexString << std::dec << std::endl << std::endl;
}


/* Пример использования
 * /
 */
int main() {
    std::string text = "matievmagomed2019@gmail.com";
    std::vector<uint8_t> plaintext(text.begin(), text.end());
    std::string textHex = textToHex(text);

    std::string input_key = "Qwerty123";
    const uint8_t *key = stringToReversedKey(input_key);

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    // зашифровка
    std::vector<uint8_t> ciphertext = cbcEncrypt(plaintext, round_keys);
    std::cout << "Ciphertext (hex): " << textToHex(std::string(ciphertext.begin(), ciphertext.end())) << std::endl;

    //расшифровка
    std::vector<uint8_t> decryptedtext = cbcDecrypt(ciphertext, round_keys);
    std::cout << "Decrypted text: " << std::string(decryptedtext.begin(), decryptedtext.end()) << std::endl;

    return 0;
}