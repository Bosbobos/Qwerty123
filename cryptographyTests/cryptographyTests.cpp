#include <gtest/gtest.h>
#include "../cryptography/cryptography.cpp"

TEST(MultiplyInGaluaTest, NonZeroCases) {
    EXPECT_EQ(multiply_in_Galua(2, 2), 4);
    EXPECT_EQ(multiply_in_Galua(5, 10), 34);
    EXPECT_EQ(multiply_in_Galua(20, 40), 101);
    EXPECT_EQ(multiply_in_Galua(50, 100), 154);
}

TEST(MultiplyInGaluaTest, ZeroCases) {
    EXPECT_EQ(multiply_in_Galua(0, 0), 0);
    EXPECT_EQ(multiply_in_Galua(0, 1), 0);
    EXPECT_EQ(multiply_in_Galua(1, 0), 0);
    EXPECT_EQ(multiply_in_Galua(0, 5), 0);
    EXPECT_EQ(multiply_in_Galua(5, 0), 0);
}

TEST(MultiplyInGaluaTest, EdgeCases) {
    EXPECT_EQ(multiply_in_Galua(255, 255), 6);
    EXPECT_EQ(multiply_in_Galua(128, 128), 119);
    EXPECT_EQ(multiply_in_Galua(1, 255), 255);
}

TEST(CreateMulsTest, ValidateTableNonZero) {
    create_muls();
    EXPECT_EQ(MULS[1][1], 1);
    EXPECT_EQ(MULS[2][2], 4);
    EXPECT_EQ(MULS[3][7], multiply_in_Galua(3, 7));
}

TEST(CreateMulsTest, ValidateTableWithZero) {
    create_muls();
    // Test with zero inputs
    for (size_t i = 0; i < 256; ++i) {
        EXPECT_EQ(MULS[i][0], 0) << "Mismatch at (" << i << ", 0)";
        EXPECT_EQ(MULS[0][i], 0) << "Mismatch at (0, " << i << ")";
    }
}

TEST(CreateMulsTest, ValidateTableFullRange) {
    create_muls();
    //полная проверка диапазона, чтобы убедиться, что каждая запись соответствует функции multiply_in_Galua
    for (size_t i = 0; i < 256; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            EXPECT_EQ(MULS[i][j], multiply_in_Galua(i, j)) << "Mismatch at (" << i << ", " << j << ")";
        }
    }
}

TEST(CreateMulsTest, ValidateTableSymmetry) {
    create_muls();
    //убедитесь, что таблица симметрична относительно умножения
    for (size_t i = 0; i < 256; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            EXPECT_EQ(MULS[i][j], MULS[j][i]) << "Asymmetry at (" << i << ", " << j << ")";
        }
    }
}


// Тест для проверки функции vectorToHex
TEST(VectorToHexTest, ConvertVectorToHex) {
    std::vector<uint8_t> bytes = {0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c, 0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2,
                                  0x89, 0x0d};
    std::string expected = "d456584dd0e3e84cc3166e4b7fa2890d";

    std::string result = vectorToHex(bytes);

    ASSERT_EQ(result, expected);
}

// Дополнительный тест для пустого вектора байтов
TEST(VectorToHexTest, EmptyByteVector) {
    std::vector<uint8_t> bytes = {};
    std::string expected;

    std::string result = vectorToHex(bytes);

    ASSERT_EQ(result, expected);
}

// Тест для проверки функции hexToVector
TEST(HexToVectorTest, ConvertHexToVector) {
    std::string hexString = "d456584dd0e3e84cc3166e4b7fa2890d";
    std::vector<uint8_t> expected = {0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c, 0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2,
                                     0x89, 0x0d};

    std::vector<uint8_t> result = hexToVector(hexString);

    ASSERT_EQ(result, expected);
}

// Дополнительный тест для пустой hex строки
TEST(HexToVectorTest, EmptyHexString) {
    std::string hexString;
    std::vector<uint8_t> expected = {};

    std::vector<uint8_t> result = hexToVector(hexString);

    ASSERT_EQ(result, expected);
}


TEST(PadKeyTest, BasicFunctionality) {
    std::string input_key = "s";
    padKey(input_key);

    // Проверяем, что длина строки стала равной 64 символам
    ASSERT_EQ(input_key.length(), 64);

    // Проверяем, что первый символ остался первым
    ASSERT_EQ(input_key[0], 's');

    // Проверяем, что следующие символы дополнены нулями
    for (size_t i = 1; i < 64; ++i) {
        ASSERT_EQ(input_key[i], '0');
    }
}

// Дополнительный тест для строки длиной больше 64 символов (должна остаться неизменной)
TEST(PadKeyTest, LongKeyNoChange) {
    std::string input_key = "this_is_a_long_key_that_is_more_than_64______________________________";
    std::string original_key = input_key;
    padKey(input_key);

    // Проверяем, что строка осталась неизменной
    ASSERT_EQ(input_key, original_key);
}

// Дополнительный тест для пустой строки (должна заполниться нулями до 64 символов)
TEST(PadKeyTest, EmptyKey) {
    std::string input_key = "0";
    padKey(input_key);

    // Проверяем, что длина строки стала равной 64 символам
    ASSERT_EQ(input_key.length(), 64);

    // Проверяем, что вся строка заполнена нулями
    for (size_t i = 0; i < 64; ++i) {
        ASSERT_EQ(input_key[i], '0');
    }
}


TEST(XorBlocksTest, BasicTest) {
    uint8_t block1[] = {0xFF, 0x00, 0xAA};
    const uint8_t block2[] = {0x0F, 0x0F, 0x0F};
    const uint8_t expected[] = {0xF0, 0x0F, 0xA5};

    xorBlocks(block1, block2, 3);

    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(block1[i], expected[i]);
    }
}

TEST(XorBlocksTest, ZeroLengthTest) {
    uint8_t block1[] = {0xFF, 0x00, 0xAA};
    const uint8_t block2[] = {0x0F, 0x0F, 0x0F};

    xorBlocks(block1, block2, 0);

    EXPECT_EQ(block1[0], 0xFF);
    EXPECT_EQ(block1[1], 0x00);
    EXPECT_EQ(block1[2], 0xAA);
}

TEST(XorBlocksTest, FullXorTest) {
    uint8_t block1[] = {0x01, 0x02, 0x03};
    const uint8_t block2[] = {0x01, 0x02, 0x03};
    const uint8_t expected[] = {0x00, 0x00, 0x00};

    xorBlocks(block1, block2, 3);

    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(block1[i], expected[i]);
    }
}

std::string bytes_to_hex_string(const uint8_t *bytes, size_t len) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        oss << std::setw(2) << static_cast<int>(bytes[i]);
    }
    return oss.str();
}

// Проверка корректной генерации ключей
TEST(KuznechikTest, GenerateRoundKeys) {
    uint8_t key[32] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
            0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
            0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
    };

    std::string expected_output =
            "7766554433221100ffeeddccbbaa9988\n"
            "efcdab89674523011032547698badcfe\n"
            "448cc78cef6a8d2243436915534831db\n"
            "04fd9f0ac4adeb1568eccfe9d853453d\n"
            "acf129f44692e5d3285e4ac468646457\n"
            "1b58da3428e832b532645c16359407bd\n"
            "b198005a26275770de45877e7540e651\n"
            "84f98622a2912ad73edd9f7b0125795a\n"
            "17e5b6cd732ff3a52331c77853e244bb\n"
            "43404a8ea8ba5d755bf4bc1674dde972\n";

    uint8_t round_keys[10][block_len];
    generate(key, round_keys);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (const auto &round_key: round_keys) {
        for (unsigned char j : round_key)
            oss << std::setw(2) << static_cast<int>(j);
        oss << '\n';
    }
    oss << std::dec;

    std::string output = oss.str();
    ASSERT_EQ(output, expected_output) << "Generated round keys output does not match the expected value.";
}


// Функция L_transform
TEST(LTransformTest, CorrectTransformation) {
    uint8_t block1[block_len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
                                 0xa5, 0x64};
    uint8_t expected1[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                    0x56, 0xd4};

    uint8_t block2[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                 0x56, 0xd4,};
    uint8_t expected2[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                    0xd2, 0x79};

    uint8_t block3[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                 0xd2, 0x79};
    uint8_t expected3[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                    0x93, 0x0e};

    uint8_t block4[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                 0x93, 0x0e,};
    uint8_t expected4[block_len] = {0x80, 0x85, 0x4b, 0xb4, 0xb0, 0xbc, 0x97, 0xfd, 0x04, 0xa2, 0x0a, 0xee, 0x4f, 0x09,
                                    0xa8, 0xe6};
    linear_transform(block1);
    linear_transform(block2);
    linear_transform(block3);
    linear_transform(block4);

    for (size_t i = 0; i < block_len; ++i) {
        EXPECT_EQ(block1[i], expected1[i]) << "Byte " << i << " is incorrect for block1.";
        EXPECT_EQ(block2[i], expected2[i]) << "Byte " << i << " is incorrect for block2.";
        EXPECT_EQ(block3[i], expected3[i]) << "Byte " << i << " is incorrect for block3.";
        EXPECT_EQ(block4[i], expected4[i]) << "Byte " << i << " is incorrect for block4.";
    }
}

// Функция inverse_L_transform

TEST(InverseLTransformTest, CorrectInverseTransformation) {
    uint8_t expected1[block_len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
                                    0xa5, 0x64};
    uint8_t block1[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                 0x56, 0xd4};

    uint8_t expected2[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                    0x56, 0xd4,};
    uint8_t block2[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                 0xd2, 0x79};

    uint8_t expected3[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                    0xd2, 0x79};
    uint8_t block3[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                 0x93, 0x0e};

    uint8_t expected4[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                    0x93, 0x0e,};
    uint8_t block4[block_len] = {0x80, 0x85, 0x4b, 0xb4, 0xb0, 0xbc, 0x97, 0xfd, 0x04, 0xa2, 0x0a, 0xee, 0x4f, 0x09,
                                 0xa8, 0xe6};

    inverse_linear_transform(block1);
    inverse_linear_transform(block2);
    inverse_linear_transform(block3);
    inverse_linear_transform(block4);

    for (size_t i = 0; i < block_len; ++i) {
        EXPECT_EQ(block1[i], expected1[i]) << "Byte " << i << " is incorrect for block1.";
        EXPECT_EQ(block2[i], expected2[i]) << "Byte " << i << " is incorrect for block2.";
        EXPECT_EQ(block3[i], expected3[i]) << "Byte " << i << " is incorrect for block3.";
        EXPECT_EQ(block4[i], expected4[i]) << "Byte " << i << " is incorrect for block4.";
    }
}


TEST(KuznechikTransformTest, LTransform) {
    uint8_t block1[block_len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
                                 0xa5, 0x64};
    uint8_t expected1[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                    0x56, 0xd4};

    uint8_t block2[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                 0x56, 0xd4,};
    uint8_t expected2[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                    0xd2, 0x79};

    uint8_t block3[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                 0xd2, 0x79};
    uint8_t expected3[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                    0x93, 0x0e};


    create_MATRIX(); // Создаем матрицы перед тестированием
    uint8_t block[block_len];

    // Тест 1
    memcpy(block, block1, block_len);
    L_transform(block);
    EXPECT_EQ(memcmp(block, expected1, block_len), 0);

    // Тест 2
    memcpy(block, block2, block_len);
    L_transform(block);
    EXPECT_EQ(memcmp(block, expected2, block_len), 0);

    // Тест 3
    memcpy(block, block3, block_len);
    L_transform(block);
    EXPECT_EQ(memcmp(block, expected3, block_len), 0);
}

TEST(KuznechikTransformTest, InverseLTransform) {
    uint8_t block1[block_len] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
                                 0xa5, 0x64};
    uint8_t expected1[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                    0x56, 0xd4};

    uint8_t block2[block_len] = {0x0d, 0x89, 0xa2, 0x7f, 0x4b, 0x6e, 0x16, 0xc3, 0x4c, 0xe8, 0xe3, 0xd0, 0x4d, 0x58,
                                 0x56, 0xd4,};
    uint8_t expected2[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                    0xd2, 0x79};

    uint8_t block3[block_len] = {0x9a, 0xde, 0xa5, 0xfe, 0x4f, 0xbc, 0x2f, 0xd4, 0x4c, 0x58, 0x7b, 0xb8, 0x21, 0x62,
                                 0xd2, 0x79};
    uint8_t expected3[block_len] = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c, 0x1a, 0x69,
                                    0x93, 0x0e};


    create_MATRIX(); // Создаем матрицы перед тестированием
    uint8_t block[block_len];

    // Тест 1
    memcpy(block, expected1, block_len);
    inverse_L_transform(block);
    EXPECT_EQ(memcmp(block, block1, block_len), 0);

    // Тест 2
    memcpy(block, expected2, block_len);
    inverse_L_transform(block);
    EXPECT_EQ(memcmp(block, block2, block_len), 0);

    // Тест 3
    memcpy(block, expected3, block_len);
    inverse_L_transform(block);
    EXPECT_EQ(memcmp(block, block3, block_len), 0);
}

TEST(MatrixCreationTest, MatrixValues) {
    // Перед каждым тестом очищаем матрицы
    memset(MATRIX, 0, sizeof(MATRIX));
    memset(INVERSE_MATRIX, 0, sizeof(INVERSE_MATRIX));

    // Создаем матрицы
    create_MATRIX();

    // Проверяем, что матрицы MATRIX и INVERSE_MATRIX заполнены корректно
    uint8_t block[block_len];
    for (uint8_t i = 0; i < block_len; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            // Проверка для MATRIX
            memset(block, 0, block_len);
            block[i] = static_cast<uint8_t>(j);
            linear_transform(block);
            EXPECT_EQ(memcmp(MATRIX[i][j], block, block_len), 0);

            // Проверка для INVERSE_MATRIX
            memset(block, 0, block_len);
            block[i] = static_cast<uint8_t>(j);
            inverse_linear_transform(block);
            EXPECT_EQ(memcmp(INVERSE_MATRIX[i][j], block, block_len), 0);
        }
    }
}

TEST(EncodeDecodeTest, EncodeBlock) {
    uint8_t block[block_len] = {0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44, 0x33,
                                0x22, 0x11};
    const uint8_t key[32] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    };
    create_muls();


    // делаем предподсчет для линейного преобразования
    create_MATRIX();

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);
    const uint8_t expected_encoded_block[block_len] = {0xcd, 0xed, 0xd4, 0xb9, 0x42, 0x8d, 0x46, 0x5a, 0x30, 0x24, 0xbc,
                                                       0xbe, 0x90, 0x9d, 0x67, 0x7f,};

    encode_block(block, round_keys);

    for (size_t i = 0; i < block_len; ++i) {
        EXPECT_EQ(block[i], expected_encoded_block[i]) << "Byte " << i << " is incorrect for block.";
    }
}

TEST(EncodeDecodeTest, DecodeBlock) {
    uint8_t block[block_len] = {0xcd, 0xed, 0xd4, 0xb9, 0x42, 0x8d, 0x46, 0x5a, 0x30, 0x24, 0xbc, 0xbe, 0x90, 0x9d,
                                0x67, 0x7f,};
    const uint8_t key[32] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    };
    create_muls();
    // делаем пред подсчет для линейного преобразования
    create_MATRIX();
    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    const uint8_t expected_decoded_block[block_len] = {0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66,
                                                       0x55, 0x44, 0x33, 0x22, 0x11};

    decode_block(block, round_keys);

    EXPECT_EQ(0, memcmp(block, expected_decoded_block, block_len));
}

// Тесты
TEST(CBCEncryptTest, EncryptEmptyText) {
    std::vector<uint8_t> plaintext = {};
    uint8_t round_keys[10][block_len] = {
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0} // Простые раундовые ключи для теста
    };

    std::vector<uint8_t> ciphertext = cbcEncrypt(plaintext, round_keys);
    EXPECT_TRUE(ciphertext.empty());
}

TEST(CBCEncryptTest, EncryptSingleBlock) {
    std::vector<uint8_t> plaintext = {0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44,
                                      0x33, 0x22, 0x11
    };
    const uint8_t key[32] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    };
    create_muls();

    // делаем предподсчет для линейного преобразования
    create_MATRIX();

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    std::vector<uint8_t> expected_ciphertext = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c,
                                                0x1a, 0x69,
                                                0x93, 0x0e};

    std::vector<uint8_t> ciphertext = cbcEncrypt(plaintext, round_keys);

    EXPECT_EQ(ciphertext.size(), block_len);

}

TEST(CBCDecryptTest, DecryptSingleBlock) {
    std::vector<uint8_t> plaintext = {0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x77, 0x66, 0x55, 0x44,
                                      0x33, 0x22, 0x11
    };
    const uint8_t key[32] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
    };
    create_muls();

    // делаем предподсчет для линейного преобразования
    create_MATRIX();

    // создаем ключи
    uint8_t round_keys[10][block_len] = {};
    generate(key, round_keys);

    std::vector<uint8_t> expected_ciphertext = {0x13, 0x3c, 0x51, 0x6b, 0xf6, 0x68, 0x7b, 0x8b, 0x40, 0x60, 0xfc, 0x0c,
                                                0x1a, 0x69,
                                                0x93, 0x0e};

    std::vector<uint8_t> ciphertext = cbcEncrypt(plaintext, round_keys);

    EXPECT_EQ(ciphertext.size(), block_len);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}