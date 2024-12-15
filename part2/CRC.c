#include <stdio.h>
#include <string.h>

#define POLY_SIZE strlen(generator)

// Global Variables
char t[128], checksum[128], generator[] = "10001000000100001";
int message_length;

// Function to Perform XOR Operation
void perform_xor() {
    for (int i = 1; i < POLY_SIZE; i++) {
        checksum[i] = (checksum[i] == generator[i]) ? '0' : '1';
    }
}

// Function to Compute CRC
void compute_crc() {
    for (int i = 0; i < POLY_SIZE; i++) {
        checksum[i] = t[i];
    }

    int i = POLY_SIZE;
    do {
        if (checksum[0] == '1') {
            perform_xor();
        }

        // Shift the checksum to the left
        for (int j = 0; j < POLY_SIZE - 1; j++) {
            checksum[j] = checksum[j + 1];
        }

        checksum[POLY_SIZE - 1] = t[i++];
    } while (i <= message_length + POLY_SIZE - 1);
}

// Function to Append Checksum to the Message
void append_checksum() {
    for (int i = message_length; i < message_length + POLY_SIZE - 1; i++) {
        t[i] = checksum[i - message_length];
    }
    t[message_length + POLY_SIZE - 1] = '\0';
}

// Function to Insert Error
void insert_error() {
    int error_position;
    printf("Enter the position where error is to be inserted: ");
    scanf("%d", &error_position);

    // Introduce error by flipping the bit
    t[error_position] = (t[error_position] == '0') ? '1' : '0';
    printf("Erroneous data: %s\n", t);
}

// Function to Detect Errors
void detect_error() {
    compute_crc();

    for (int i = 0; i < POLY_SIZE - 1; i++) {
        if (checksum[i] == '1') {
            printf("Error detected.\n");
            return;
        }
    }
    printf("No error detected.\n");
}

int main() {
    printf("Enter the data polynomial: ");
    scanf("%s", t);

    printf("\nGenerating Polynomial is: %s", generator);

    message_length = strlen(t);

    // Append N-1 zeros to the input message
    for (int i = message_length; i < message_length + POLY_SIZE - 1; i++) {
        t[i] = '0';
    }
    t[message_length + POLY_SIZE - 1] = '\0';

    printf("\nModified input is: %s", t);

    // Compute CRC and Append Checksum
    compute_crc();
    printf("\nChecksum is: %s", checksum);

    append_checksum();
    printf("\nFinal codeword is: %s", t);

    // Error Detection
    int error_flag;
    printf("\nTest error detection (0: yes, 1: no)? ");
    scanf("%d", &error_flag);

    if (error_flag == 0) {
        insert_error();
    }

    detect_error();

    return 0;
}
