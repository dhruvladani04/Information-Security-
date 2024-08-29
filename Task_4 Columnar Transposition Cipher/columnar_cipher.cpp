#include <bits/stdc++.h>
using namespace std;

string encrypt(string plainText, string key)
{
    plainText.erase(remove(plainText.begin(), plainText.end(), ' '), plainText.end());

    int keyLength = key.length();
    int textLength = plainText.length();
    int rows = ceil((double)textLength / keyLength);
    vector<vector<char>> matrix(rows, vector<char>(keyLength, 'X'));
    int index = 0;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < keyLength; j++) 
        {
            if (index < textLength) 
            {
                matrix[i][j] = plainText[index++];
            }
        }
    }
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < keyLength; ++i) {
        sortedKey.push_back(make_pair(key[i], i));
    }
    sort(sortedKey.begin(), sortedKey.end());
    string cipherText;
    for (int i = 0; i < keyLength; i++) 
    {
        int colIndex = sortedKey[i].second;
        for (int row = 0; row < rows; ++row) 
        {
            cipherText += matrix[row][colIndex];
        }
    }
    return cipherText;
}

string decrypt(string cipherText, string key) 
{
    int keyLength = key.length();
    int textLength = cipherText.length();
    int rows = ceil((double)textLength / keyLength);
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < keyLength; i++) 
    {
        sortedKey.push_back(make_pair(key[i], i));
    }
    sort(sortedKey.begin(), sortedKey.end());
    vector<vector<char>> matrix(rows, vector<char>(keyLength));
    int index = 0;

    for (int i = 0; i < keyLength; i++) {
        int colIndex = sortedKey[i].second;
        for (int row = 0; row < rows; row++) {
            if (index < textLength) {
                matrix[row][colIndex] = cipherText[index++];
            }
        }
    }
    string plainText;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < keyLength; j++) 
        {
            plainText += matrix[i][j];
        }
    }
    while (!plainText.empty() && plainText.back() == 'X') {
        plainText.pop_back();
    }

    return plainText;
}

int main() 
{
    string plainText;
    cout<<"Enter the message : ";
    getline(cin,plainText);
    string key;
    cout<<"Enter the key : ";
    cin>>key;
    string cipherText = encrypt(plainText, key);
    string output=cipherText;
    cout << "Cipher Text: ";
    for(auto ele:output)
    {
        if(ele!='X')
        cout<<ele;
    }
    cout<<endl;
    string decryptedText = decrypt(cipherText, key);
    cout << "Decrypted Text: " << decryptedText << endl;
    return 0;
}

