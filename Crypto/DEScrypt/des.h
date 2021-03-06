#ifndef DES_H
#define DES_H

#include <stdint.h>
#include <math.h>
#include <string.h>
#include <QDebug>

#define BITS_IN_BLOCK               64
#define BYTES_IN_BLOCK              8
#define S_BLOCKS_COUNT              8
#define S_BLOCK_ROWS_COUNT          4
#define S_BLOCK_COLUMNS_COUNT       16
#define BITS_IN_BYTE                8
#define FEISTEL_TRANSFORM_COUNT     16
#define TRANSFORMED_KEY_SIZE        48
#define BITS_IN_B_BLOCK             6
#define BITS_IN_SUBKEY              56

typedef uint64_t Block;
typedef uint32_t HalfBlock;


class DES
{
public:
    uint32_t encrypt(char *src, char **encrypted, uint32_t srcLength, uint64_t key);
    uint32_t decrypt(char *src, char **decrypted, uint32_t srcLength, uint64_t key);
    uint64_t generateKey();

private:
    uint32_t feistelFunction(uint32_t &halfBlock, uint64_t &key);
    uint64_t feistelTransform(uint32_t halfL, uint32_t halfR, uint64_t &key);
    uint32_t sTransform(uint64_t expandedHalfBlock);
    uint64_t cryptBlock(uint64_t block, uint64_t key, bool encrypt);
    uint64_t decryptBlock(uint64_t block, uint64_t key);
    void     PrepareKey(uint64_t &key, uint64_t &cd, uint8_t index, bool encrypt);

    uint8_t ip[BITS_IN_BLOCK] = {58, 50, 42, 34, 26, 18, 10, 2,
                                 60, 52, 44, 36, 28, 20, 12, 4,
                                 62, 54, 46, 38, 30, 22, 14, 6,
                                 64, 56, 48, 40, 32, 24, 16, 8,
                                 57, 49, 41, 33, 25, 17,  9, 1,
                                 59, 51, 43, 35, 27, 19, 11, 3,
                                 61, 53, 45, 37, 29, 21, 13, 5,
                                 63, 55, 47, 39, 31, 23, 15, 7 };

    uint8_t expansion[TRANSFORMED_KEY_SIZE] = {32,  1,  2,  3,  4,  5,  4,  5,
                                                6,  7,  8,  9,  8,  9, 10, 11,
                                               12, 13, 12, 13, 14, 15, 16, 17,
                                               16, 17, 18, 19, 20, 21, 20, 21,
                                               22, 23, 24, 25, 24, 25, 26, 27,
                                               28, 29, 28, 29, 30, 31, 32,  1 };

    uint8_t s_blocks[S_BLOCKS_COUNT][S_BLOCK_ROWS_COUNT][S_BLOCK_COLUMNS_COUNT] =
    {
        {
            {0x0e, 0x04, 0x0d, 0x01, 0x02, 0x0f, 0x0b, 0x08, 0x03, 0x0a, 0x06, 0x0c, 0x05, 0x09, 0x00, 0x07},
            {0x00, 0x0f, 0x07, 0x04, 0x0e, 0x02, 0x0d, 0x01, 0x0a, 0x06, 0x0c, 0x0b, 0x09, 0x05, 0x03, 0x08},
            {0x04, 0x01, 0x04, 0x08, 0x0d, 0x06, 0x02, 0x0b, 0x0f, 0x0c, 0x09, 0x07, 0x03, 0x0a, 0x05, 0x00},
            {0x0f, 0x0c, 0x08, 0x02, 0x04, 0x09, 0x01, 0x07, 0x05, 0x0b, 0x03, 0x0e, 0x0a, 0x00, 0x06, 0x0d}
        },
        {
            {0x0f, 0x01, 0x08, 0x0e, 0x06, 0x0b, 0x03, 0x04, 0x09, 0x07, 0x02, 0x0d, 0x0c, 0x00, 0x05, 0x0a},
            {0x03, 0x0d, 0x04, 0x07, 0x0f, 0x02, 0x08, 0x0e, 0x0c, 0x00, 0x01, 0x0a, 0x06, 0x09, 0x0b, 0x05},
            {0x00, 0x0e, 0x07, 0x0b, 0x0a, 0x04, 0x0d, 0x01, 0x05, 0x08, 0x0c, 0x06, 0x09, 0x03, 0x02, 0x0f},
            {0x0d, 0x08, 0x0a, 0x01, 0x03, 0x0f, 0x04, 0x02, 0x0b, 0x06, 0x07, 0x0c, 0x00, 0x05, 0x0e, 0x09}
        },
        {
            {0x0a, 0x00, 0x09, 0x0e, 0x06, 0x03, 0x0f, 0x05, 0x01, 0x0d, 0x0c, 0x07, 0x0b, 0x04, 0x02, 0x08},
            {0x0d, 0x07, 0x00, 0x09, 0x03, 0x04, 0x06, 0x0a, 0x02, 0x08, 0x05, 0x0e, 0x0c, 0x0b, 0x0f, 0x01},
            {0x0d, 0x06, 0x04, 0x09, 0x08, 0x0f, 0x03, 0x00, 0x0b, 0x01, 0x02, 0x0c, 0x05, 0x0a, 0x0e, 0x07},
            {0x01, 0x0a, 0x0d, 0x00, 0x06, 0x09, 0x08, 0x07, 0x04, 0x0f, 0x0e, 0x03, 0x0b, 0x05, 0x02, 0x0c}
        },
        {
            {0x07, 0x0d, 0x0e, 0x03, 0x00, 0x06, 0x09, 0x0a, 0x01, 0x02, 0x08, 0x05, 0x0b, 0x0c, 0x04, 0x0f},
            {0x0d, 0x08, 0x0b, 0x05, 0x06, 0x0f, 0x00, 0x03, 0x04, 0x07, 0x02, 0x0c, 0x01, 0x0a, 0x0e, 0x09},
            {0x0a, 0x06, 0x09, 0x00, 0x0c, 0x0b, 0x07, 0x0d, 0x0f, 0x01, 0x03, 0x0e, 0x05, 0x02, 0x08, 0x04},
            {0x03, 0x0f, 0x00, 0x06, 0x0a, 0x01, 0x0d, 0x08, 0x09, 0x04, 0x05, 0x0b, 0x0c, 0x07, 0x02, 0x0e}
        },
        {
            {0x02, 0x0c, 0x04, 0x01, 0x07, 0x0a, 0x0b, 0x06, 0x08, 0x05, 0x03, 0x0f, 0x0d, 0x00, 0x0e, 0x09},
            {0x0e, 0x0b, 0x02, 0x0c, 0x04, 0x07, 0x0d, 0x01, 0x05, 0x00, 0x0f, 0x0a, 0x03, 0x09, 0x08, 0x06},
            {0x04, 0x02, 0x01, 0x0b, 0x0a, 0x0d, 0x07, 0x08, 0x0f, 0x09, 0x0c, 0x05, 0x06, 0x03, 0x00, 0x0e},
            {0x0b, 0x08, 0x0c, 0x07, 0x01, 0x0e, 0x02, 0x0d, 0x06, 0x0f, 0x00, 0x09, 0x0a, 0x04, 0x05, 0x03}
        },
        {
            {0x0c, 0x01, 0x0a, 0x0f, 0x09, 0x02, 0x06, 0x08, 0x00, 0x0d, 0x03, 0x04, 0x0e, 0x07, 0x05, 0x0b},
            {0x0a, 0x0f, 0x04, 0x02, 0x07, 0x0c, 0x09, 0x05, 0x06, 0x01, 0x0d, 0x0e, 0x00, 0x0b, 0x03, 0x08},
            {0x09, 0x0e, 0x0f, 0x05, 0x02, 0x08, 0x0c, 0x03, 0x07, 0x00, 0x04, 0x0a, 0x01, 0x0d, 0x01, 0x06},
            {0x04, 0x03, 0x02, 0x0c, 0x09, 0x05, 0x0f, 0x0a, 0x0b, 0x0e, 0x01, 0x07, 0x06, 0x00, 0x08, 0x0d}
        },
        {
            {0x04, 0x0b, 0x02, 0x0e, 0x0f, 0x00, 0x08, 0x0d, 0x03, 0x0c, 0x09, 0x07, 0x05, 0x0a, 0x06, 0x01},
            {0x0d, 0x00, 0x0b, 0x07, 0x04, 0x09, 0x01, 0x0a, 0x0e, 0x03, 0x05, 0x0c, 0x02, 0x0f, 0x08, 0x06},
            {0x01, 0x04, 0x0b, 0x0d, 0x0c, 0x03, 0x07, 0x0e, 0x0a, 0x0f, 0x06, 0x08, 0x00, 0x05, 0x09, 0x02},
            {0x06, 0x0b, 0x0d, 0x08, 0x01, 0x04, 0x0a, 0x07, 0x09, 0x05, 0x00, 0x0f, 0x0e, 0x02, 0x03, 0x0c}
        },
        {
            {0x0d, 0x02, 0x08, 0x04, 0x06, 0x0f, 0x0b, 0x01, 0x0a, 0x09, 0x03, 0x0e, 0x05, 0x00, 0x0c, 0x07},
            {0x01, 0x0f, 0x0d, 0x08, 0x0a, 0x03, 0x07, 0x04, 0x0c, 0x05, 0x06, 0x0b, 0x00, 0x0e, 0x09, 0x02},
            {0x07, 0x0b, 0x04, 0x01, 0x09, 0x0c, 0x0e, 0x02, 0x00, 0x06, 0x0a, 0x0d, 0x0f, 0x03, 0x05, 0x08},
            {0x02, 0x01, 0x0e, 0x07, 0x04, 0x0a, 0x08, 0x0d, 0x0f, 0x0c, 0x09, 0x00, 0x03, 0x05, 0x06, 0x0b}
        }
    };

    uint8_t key_prep_transform[BITS_IN_BLOCK] = {57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
                                                 10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
                                                 63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
                                                 14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4};

    uint8_t key_offsets[FEISTEL_TRANSFORM_COUNT] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    uint8_t key_final_transform[TRANSFORMED_KEY_SIZE] = {14, 17, 11, 24,  1,  5,  3, 28,
                                                         15,  6, 21, 10, 23, 19, 12,  4,
                                                         26,  8, 16,  7, 27, 20, 13,  2,
                                                         41, 52, 31, 37, 47, 55, 30, 40,
                                                         51, 45, 33, 48, 44, 49, 39, 56,
                                                         34, 53, 46, 42, 50, 36, 29, 32};

    uint8_t permutation_func[BITS_IN_BLOCK/2] = {16,  7, 20, 21, 29, 12, 28, 17,
                                                  1, 15, 23, 26,  5, 18, 31, 10,
                                                  2,  8, 24, 14, 32, 27,  3,  9,
                                                 19, 13, 30,  6, 22, 11,  4, 25};

    uint8_t final_permutation[BITS_IN_BLOCK] = {40, 8, 48, 16, 56, 24, 64, 32,
                                                39, 7, 47, 15, 55, 23, 63, 31,
                                                38, 6, 46, 14, 54, 22, 62, 30,
                                                37, 5, 45, 13, 53, 21, 61, 29,
                                                36, 4, 44, 12, 52, 20, 60, 28,
                                                35, 3, 43, 11, 51, 19, 59, 27,
                                                34, 2, 42, 10, 50, 18, 58, 26,
                                                33, 1, 41,  9, 49, 17, 57, 25 };
};

#endif // DES_H
