#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// Constants for MD5 Transform routine
uint32_t S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
// Function prototypes
uint32_t left_rotate(uint32_t x, uint32_t c);
void md5(uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
void md5_to_hex(uint8_t *digest, char *output);
// MD5 main computation function
void md5(uint8_t *initial_msg, size_t initial_len, uint8_t *digest)
{
        uint32_t hash_pieces[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
        uint32_t a, b, c, d, f, g, temp;
        uint32_t M[16];
        size_t offset;
        // Process each 512-bit chunk of the message
        for (offset = 0; offset < initial_len; offset += 64)
        {
                // Break chunk into sixteen 32-bit words
                for (size_t i = 0; i < 16; i++)
                {
                        M[i] = (initial_msg[offset + 4 * i + 0]) |
                               (initial_msg[offset + 4 * i + 1] << 8) |
                               (initial_msg[offset + 4 * i + 2] << 16) |
                               (initial_msg[offset + 4 * i + 3] << 24);
                }
                a = hash_pieces[0];
                b = hash_pieces[1];
                c = hash_pieces[2];
                d = hash_pieces[3];
                // Main MD5 transformation loop
                for (size_t i = 0; i < 64; i++)
                {
                        if (i < 16)
                        {
                                f = (b & c) | (~b & d);
                                g = i;
                        }
                        else if (i < 32)
                        {
                                f = (d & b) | (~d & c);
                                g = (5 * i + 1) % 16;
                        }
                        else if (i < 48)
                        {
                                f = b ^ c ^ d;
                                g = (3 * i + 5) % 16;
                        }
                        else
                        {
                                f = c ^ (b | ~d);
                                g = (7 * i) % 16;
                        }
                        temp = d;
                        d = c;
                        c = b;
                        b = b + left_rotate((a + f + K[i] + M[g]), S[i]);
                        a = temp;
                }
                hash_pieces[0] += a;
                hash_pieces[1] += b;
                hash_pieces[2] += c;
                hash_pieces[3] += d;
        }
        // Output hash in little-endian format
        for (size_t i = 0; i < 4; i++)
        {
                digest[i * 4 + 0] = (hash_pieces[i] >> 0) & 0xff;
                digest[i * 4 + 1] = (hash_pieces[i] >> 8) & 0xff;
                digest[i * 4 + 2] = (hash_pieces[i] >> 16) & 0xff;
                digest[i * 4 + 3] = (hash_pieces[i] >> 24) & 0xff;
        }
}
// Function to perform left rotate operation
uint32_t left_rotate(uint32_t x, uint32_t c)
{
        return (x << c) | (x >> (32 - c));
}
// Function to convert MD5 digest to hexadecimal string
void md5_to_hex(uint8_t *digest, char *output)
{
        static const char *hex_digits = "0123456789abcdef";
        for (size_t i = 0; i < 16; i++)
        {
                output[i * 2] = hex_digits[digest[i] >> 4];
                output[i * 2 + 1] = hex_digits[digest[i] & 0x0f];
        }
        output[32] = '\0'; // Null-terminate the string
}
int main()
{
        uint8_t message[] = "cryptography";
        size_t len = strlen((char *)message);
        uint8_t digest[16];
        char hex_digest[33];
        md5(message, len, digest);
        md5_to_hex(digest, hex_digest);
        printf("MD5 Digest: %s\n", hex_digest);
        return 0;
}
