#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> generateCustomMapping() 
{
    unordered_map<char, int> customMap;
    int value = 2;
    for (char c = 'A'; c <= 'Z'; c++) 
    {
        customMap[c] = value;
        value += 2;
    }
    return customMap;
}

int getFibonacciLength(int n) 
{
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    while (b < n) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;  
}


string encrypt(string plaintext, string key, unordered_map<char, int> &customMap) 
{
    string ciphertext = "";
    int keyLength = key.length();
    
    // Encrypt each character
    for (int i = 0; i < plaintext.length(); i++) 
    {
        char p = toupper(plaintext[i]);
        char k = toupper(key[i % keyLength]);  
        int p_val = customMap[p];
        int k_val = customMap[k];
        int c_val = (p_val + k_val) % 52;
        for (auto &entry : customMap) 
        {
            if (entry.second == c_val) 
            {
                ciphertext += entry.first;
                break;
            }
        }
        if (i + 1 < keyLength) 
        {  
            key[i + 1] = ciphertext.back(); 
        }
    }
    return ciphertext;
}

string decrypt(string ciphertext, string key, unordered_map<char, int> &customMap) 
{
    string plaintext = "";
    int keyLength = key.length();
    for (int i = 0; i < ciphertext.length(); i++) 
    {
        char c = toupper(ciphertext[i]);
        char k = toupper(key[i % keyLength]);  
        int c_val = customMap[c];
        int k_val = customMap[k];
        int p_val = (c_val - k_val + 52) % 52; 
        for (auto &entry : customMap) 
        {
            if (entry.second == p_val) 
            {
                plaintext += entry.first;
                break;
            }
        }
        if (i + 1 < keyLength) 
        {  
            key[i + 1] = c; 
        }
    }
    return plaintext;
}
int main() 
{
    string plaintext, key;
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    unordered_map<char, int> customMap = generateCustomMapping();
    int requiredKeyLength = getFibonacciLength(plaintext.length());
    cout << "Enter the key (length " << requiredKeyLength << "): ";
    getline(cin, key);
    while (key.length() != requiredKeyLength) 
    {
        cout << "Key length does not match required length (" << requiredKeyLength << "). Please try again: ";
        getline(cin, key);
    }
    string ciphertext = encrypt(plaintext, key, customMap);
    cout << "Encrypted Text: " << ciphertext << endl;
    string decryptedText = decrypt(ciphertext, key, customMap);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}
