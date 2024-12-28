#include <stdio.h>  
#include <string.h>  
   
// Function to perform Rail Fence Cipher encryption  
void railFenceEncrypt(char *message, int railCount) {  
    int messageLength = strlen(message);  
    char rails[railCount][messageLength];  
    int row = 0, col = 0;  
    int direction = 1; // 1 for downward, -1 for upward  
   
    for (int i = 0; i < messageLength; i++) {  
        rails[row][col] = message[i];  
        col++;  
   
        // Check for direction change  
        if (row == 0) {  
            direction = 1;  
        } else if (row == railCount - 1) {  
            direction = -1;  
        }  
   
        // Move to the next row  
        row += direction;  
    }  
   
    // Printing the encrypted message  
    printf("Encrypted message: ");  
    for (int i = 0; i < railCount; i++) {  
        for (int j = 0; j < messageLength; j++) {  
            if (rails[i][j] != 0) {  
                printf("%c", rails[i][j]);  
            }  
        }  
    }  
    printf("\n");  
}  
   
// Function to perform Rail Fence Cipher decryption  
void railFenceDecrypt(char *encryptedMessage, int railCount) {  
    int messageLength = strlen(encryptedMessage);  
    char rails[railCount][messageLength];  
    int row = 0, col = 0;  
    int direction = 1;  
    int decryptIndex = 0;  
   
    // Initialize the rails with placeholders  
    for (int i = 0; i < railCount; i++) {  
        for (int j = 0; j < messageLength; j++) {  
            rails[i][j] = ' ';  
        }  
    }  
  
    // Fill the rails with encrypted characters  
    for (int i = 0; i < messageLength; i++) {  
        if (row == 0) {  
            direction = 1;  
        } else if (row == railCount - 1) {  
            direction = -1;  
        }  
   
        rails[row][col] = '*'; // Placeholder to mark the rail positions  
        col++;  
   
        // Move to the next row  
        row += direction;  
    }  
   
    // Populate the rail positions with encrypted characters  
    for (int i = 0; i < railCount; i++) {  
        for (int j = 0; j < messageLength; j++) {  
            if (rails[i][j] == '*') {  
                rails[i][j] = encryptedMessage[decryptIndex++];  
            }  
        }  
    }  
   
    // Reading the decrypted message  
    row = 0;  
    col = 0;  
    direction = 1;  
    char decryptedMessage[1000];  
   
    for (int i = 0; i < messageLength; i++) {  
        decryptedMessage[i] = rails[row][col];  
        col++;  
   
        // Check for direction change  
        if (row == 0) {  
            direction = 1;  
        } else if (row == railCount - 1) {  
            direction = -1;  
        }  
   
        // Move to the next row  
        row += direction;  
    }  
   
    // Null-terminate the decrypted message  
    decryptedMessage[messageLength] = '\0';  
   
    // Printing the decrypted message  
    printf("Decrypted message: %s\n", decryptedMessage);  
}  
   
int main() {  
    char message[1000];  
    int railCount;  
   
    printf("Enter the message to encrypt: ");  
    scanf("%[^\n]s", message);  
   
    printf("Enter the rail count: ");  
    scanf("%d", &railCount);  
   
    // Encryption  
    railFenceEncrypt(message, railCount);  
   
    // Decryption (using the encrypted message)  
    railFenceDecrypt("HNOLLOELWRDLOD", railCount);  
   
    return 0;  
}
