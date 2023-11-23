// Roll NO: 31274
// Cyclic Redundancy Check
// Batch N2

#include <bits/stdc++.h>
using namespace std;

// Function to perform XOR operation on two characters
char xorOperation(char a, char b) {
    if (a == b)
        return '0';
    else
        return '1';
}

// Function to perform Cyclic Redundancy Check (CRC)
void crc(char data[], char key[]) {
    int dataSize = strlen(data);
    int keySize = strlen(key);

    // Appending zeros to the data to make room for the remainder
    for (int i = 0; i < keySize - 1; i++)
        data[dataSize + i] = '0';

    data[dataSize + keySize - 1] = '\0';

    int codeSize = dataSize + keySize - 1;

    char temp[50], remainder[50];

    // Initializing the remainder with the first 'keySize' bits of data
    for (int i = 0; i < keySize; i++)
        remainder[i] = data[i];

    for (int j = keySize; j <= codeSize; j++) {
        for (int i = 0; i < keySize; i++)
            temp[i] = remainder[i];

        if (remainder[0] == '0') {
            for (int i = 0; i < keySize - 1; i++)
                remainder[i] = temp[i + 1];
        } else {
            for (int i = 0; i < keySize - 1; i++)
                remainder[i] = xorOperation(temp[i + 1], key[i + 1]);
        }

        if (j != codeSize)
            remainder[keySize - 1] = data[j];
        else
            remainder[keySize - 1] = '\0';
    }

    // Appending the remainder to the original data
    for (int i = 0; i < keySize - 1; i++)
        data[dataSize + i] = remainder[i];

    data[codeSize] = '\0';
    cout << "CRC=" << remainder << "\nDataword=" << data;
}

// Function to take user input for data and key
int menu() {
    int dataSize, keySize;
    cout << "Enter data size: ";
    cin >> dataSize;
    char data[dataSize];
    cout << "Enter key size: ";
    cin >> keySize;
    char key[keySize];
    cout << "Enter data: ";
    cin >> data;
    cout << "Enter the key: ";
    cin >> key;
    crc(data, key);
    char choice;
    cout << "\n\nEnter another value? (y/n): ";
    cin >> choice;
    if (choice == 'y') {
        return 1;
    }
    return 0;
}

int
