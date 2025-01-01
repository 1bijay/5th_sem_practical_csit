#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY_LENGTH 16

// Define the S-box (substitution box)
int s_box[16] = {5, 10, 3, 6, 12, 9, 0, 11, 14, 15, 13, 7, 8, 2, 1, 4};

// Function to perform substitution using the S-box
int substitute_byte(int byte)
{
        return s_box[byte];
}

// Function to generate a random key of the specified length
void generate_key(int key[], int key_length)
{
        for (int i = 0; i < key_length; i++)
        {
                key[i] = rand() % 16; // Random number between 0 and 15
        }
}

int main()
{
        srand(time(NULL)); // Seed the random number generator

        int input_byte = rand() % 16; // Random input byte (0-15)
        int key[KEY_LENGTH];          // Array to hold the generated key

        // Generate a random key
        generate_key(key, KEY_LENGTH);

        // Display the generated key
        printf("Generated Encryption Key: ");
        for (int i = 0; i < KEY_LENGTH; i++)
        {
                printf("%d ", key[i]);
        }
        printf("\n");

        // Encrypt the input byte using the key and S-box
        int encrypted_byte = input_byte ^ key[0]; // XOR with the first key byte
        int substituted_byte = substitute_byte(encrypted_byte);

        // Display the results
        printf("\nInput Byte: %d\n", input_byte);
        printf("Encrypted Byte: %d\n", encrypted_byte);
        printf("Substituted Byte: %d\n", substituted_byte);

        return 0;
}
