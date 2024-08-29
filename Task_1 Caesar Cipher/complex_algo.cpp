#include <bits/stdc++.h>
using namespace std;

string caesarCipher(string& text, int k) 
{
    string cipheredText;
    for (char c : text) 
    {
        if (c >= 'a' && c <= 'z')
        cipheredText += 'a' + (c - 'a' + k) % 26;
        else if (c >= 'A' && c <= 'Z') 
        cipheredText += 'A' + (c - 'A' + k) % 26;
        else 
        cipheredText += c;
    }
    return cipheredText;
}


string caesarDecipher(string& cipheredText, int k) 
{
    string decipheredText;
    for (char c : cipheredText) 
    {
        if (c >= 'a' && c <= 'z')
        decipheredText += 'a' + (c - 'a' - k + 26) % 26;
        else if (c >= 'A' && c <= 'Z')
        decipheredText += 'A' + (c - 'A' - k + 26) % 26;
        else
        decipheredText += c;
    }
    return decipheredText;
}
string customHash(string& str) 
{
    unsigned long long hash = 0;
    const int prime = 31;
    const int mod = 1e9 + 9;
    
    for (char c : str) {
        hash = (hash * prime + c) % mod;
    }
    
    stringstream ss;
    ss << hex << hash;
    return ss.str();
}
int32_t main() 
{
    string text;
    int k;
    cout << "Enter text to cipher: ";
    getline(cin, text);
    cout << "Enter shift value (k): ";
    cin >> k;
    string cipheredText = caesarCipher(text, k);
    cout << "Ciphered text: " << cipheredText << endl;
    string hashValue = customHash(cipheredText);
    cout << "Hash of ciphered text (custom hash): " << hashValue << endl;
    string decipheredText = caesarDecipher(cipheredText, k);
    cout << "Deciphered text: " << decipheredText << endl;
    return 0;
}