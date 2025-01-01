#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// Function prototypes
uint32_t left_rotate(uint32_t x, uint32_t c);
void sha1(uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
void sha1_to_hex(uint8_t *digest, char *output);
// SHA-1 main computation function
void sha1(uint8_t *initial_msg, size_t initial_len, uint8_t *digest)
{
        // Initial hash values
        uint32_t hash_pieces[5] = {
            0x67452301,
            0xEFCDAB89,
            0x98BADCFE,
            0x10325476,
            0xC3D2E1F0};
        uint32_t a, b, c, d, e, f, k, temp;
        uint32_t W[80];
        size_t offset;
        // Pre-processing: adding a single 1 bit
        size_t new_len = initial_len + 1;
        while (new_len % 64 != 56)
                new_len++;
        uint8_t *msg = (uint8_t *)calloc(new_len + 8, 1);
        memcpy(msg, initial_msg, initial_len);
        msg[initial_len] = 0x80;             // append "1" bit to message
        uint64_t bits_len = 8 * initial_len; // note: we append the length in bits at the end of the buffer
        memcpy(msg + new_len, &bits_len, 8); // append the length
        // Process the message in successive 512-bit chunks
        for (offset = 0; offset < new_len; offset += 64)
        {
                // Break chunk into sixteen 32-bit big-endian words
                for (size_t i = 0; i < 16; i++)
                {
                        W[i] = (msg[offset + 4 * i] << 24) |
                               (msg[offset + 4 * i + 1] << 16) |
                               (msg[offset + 4 * i + 2] << 8) |
                               (msg[offset + 4 * i + 3]);
                }
                // Extend the sixteen 32-bit words into eighty 32-bit words
                for (size_t i = 16; i < 80; i++)
                {
                        W[i] = left_rotate(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
                }
                a = hash_pieces[0];
                b = hash_pieces[1];
                c = hash_pieces[2];
                d = hash_pieces[3];
                e = hash_pieces[4];
                // Main SHA-1 transformation loop
                for (size_t i = 0; i < 80; i++)
                {
                        if (i < 20)
                        {
                                f = (b & c) | ((~b) & d);
                                k = 0x5A827999;
                        }
                        else if (i < 40)
                        {
                                f = b ^ c ^ d;
                                k = 0x6ED9EBA1;
                        }
                        else if (i < 60)
                        {
                                f = (b & c) | (b & d) | (c & d);
                                k = 0x8F1BBCDC;
                        }
                        else
                        {
                                f = b ^ c ^ d;
                                k = 0xCA62C1D6;
                        }
                        temp = left_rotate(a, 5) + f + e + k + W[i];
                        e = d;
                        d = c;
                        c = left_rotate(b, 30);
                        b = a;
                        a = temp;
                }
                hash_pieces[0] += a;
                hash_pieces[1] += b;
                hash_pieces[2] += c;
                hash_pieces[3] += d;
                hash_pieces[4] += e;
        }
        free(msg);
        // Output hash in big-endian format
        for (size_t i = 0; i < 5; i++)
        {
                digest[i * 4 + 0] = (hash_pieces[i] >> 24) & 0xff;
                digest[i * 4 + 1] = (hash_pieces[i] >> 16) & 0xff;
                digest[i * 4 + 2] = (hash_pieces[i] >> 8) & 0xff;
                digest[i * 4 + 3] = (hash_pieces[i] >> 0) & 0xff;
        }
}
// Function to perform left rotate operation
uint32_t left_rotate(uint32_t x, uint32_t c)
{
        return (x << c) | (x >> (32 - c));
}
// Function to convert SHA-1 digest to hexadecimal string
void sha1_to_hex(uint8_t *digest, char *output)
{
        static const char *hex_digits = "0123456789abcdef";
        for (size_t i = 0; i < 20; i++)
        {
                output[i * 2] = hex_digits[digest[i] >> 4];
                output[i * 2 + 1] = hex_digits[digest[i] & 0x0f];
        }
        output[40] = '\0'; // Null-terminate the string
}
int main()
{
        uint8_t message[] = "hello";
        size_t len = strlen((char *)message);
        uint8_t digest[20];
        char hex_digest[41];
        sha1(message, len, digest);
        sha1_to_hex(digest, hex_digest);
        printf("SHA-1 Digest: %s\n", hex_digest);
        return 0;
}
