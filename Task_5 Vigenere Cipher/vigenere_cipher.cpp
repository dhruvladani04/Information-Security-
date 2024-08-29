#include <bits/stdc++.h>
using namespace std;
string encrypt(string plaintext, string key) 
{
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i++) 
    {
        char p = toupper(plaintext[i]);
        char k = toupper(key[i]);
        char c = (p + k - 2 * 'A') % 26 + 'A';
        ciphertext += c;
    }
    return ciphertext;
}
string decrypt(string ciphertext, string key) 
{
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); i++) 
    {
        char c = toupper(ciphertext[i]);
        char k = toupper(key[i]);
        char p = (c - k + 26) % 26 + 'A';
        plaintext += p;
    }
    return plaintext;
}

int main() 
{
    string plaintext, key;
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    while (true) 
    {
        cout << "Enter the key (must be the same length as the plaintext): ";
        getline(cin, key);
        if (key.length() == plaintext.length()) 
        {
            break;
        } 
        else 
        {
            cout << "Key length does not match plaintext length. Please try again." << endl;
        }
    }
    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted Text: " << ciphertext << endl;
    string decryptedText = decrypt(ciphertext, key);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}
