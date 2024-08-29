#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> genKeySquare(const string &key) 
{
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // 'J' is not included here
    vector<vector<char>> keySquare(5, vector<char>(5, ' '));
    string adjKey;

    for (char c : key) 
    {
        c = toupper(c);
        if (c == 'J') 
        c = 'I'; // Treat 'J' as 'I'
        if (adjKey.find(c) == string::npos)
        adjKey += c;
    }

    int x = 0, y = 0;
    for (char c : adjKey) 
    {
        keySquare[x][y++] = c;
        if (y == 5) 
        {
            y = 0;
            x++;
        }
    }

    for (char c : alphabet) 
    {
        if (adjKey.find(c) == string::npos) 
        {
            keySquare[x][y++] = c;
            if (y == 5) 
            {
                y = 0;
                x++;
            }
        }
    }

    return keySquare;
}


pair<int, int> findPos(char c, const vector<vector<char>> &keySquare) 
{
    for (int i = 0; i < 5;i++) 
    {
        for (int j = 0; j < 5;j++) 
        {
            if (keySquare[i][j] == c)
            return make_pair(i, j);
        }
    }
    return make_pair(-1, -1); 
}


string prepText(const string &text) 
{
    string pText;
    for (size_t i = 0; i < text.length();i++) 
    {
        char c = toupper(text[i]);
        if (c == 'J') 
        c = 'I';
        pText += c;
        if (i < text.length() - 1 && c == toupper(text[i + 1]))
        pText += 'X';
    }
    if (pText.length() % 2 != 0)
    pText += 'X';
    return pText;
}


string encrypt(const string &pText, const vector<vector<char>> &keySquare) 
{
    string cText;

    for (size_t i = 0; i < pText.length(); i += 2) {
        char a = pText[i];
        char b = pText[i + 1];
        auto posA = findPos(a, keySquare);
        auto posB = findPos(b, keySquare);

        if (posA.first == posB.first) 
        { 
            cText += keySquare[posA.first][(posA.second + 1) % 5];
            cText += keySquare[posB.first][(posB.second + 1) % 5];
        } else if (posA.second == posB.second) 
        { 
            cText += keySquare[(posA.first + 1) % 5][posA.second];
            cText += keySquare[(posB.first + 1) % 5][posB.second];
        } else 
        { 
            cText += keySquare[posA.first][posB.second];
            cText += keySquare[posB.first][posA.second];
        }
    }

    return cText;
}


string decrypt(const string &cText, const vector<vector<char>> &keySquare) 
{
    string pText;
    for (size_t i = 0; i < cText.length(); i += 2) 
    {
        char a = cText[i];
        char b = cText[i + 1];
        auto posA = findPos(a, keySquare);
        auto posB = findPos(b, keySquare);

        if (posA.first == posB.first) 
        { 
            pText += keySquare[posA.first][(posA.second + 4) % 5];
            pText += keySquare[posB.first][(posB.second + 4) % 5];
        } else if (posA.second == posB.second) 
        { 
            pText += keySquare[(posA.first + 4) % 5][posA.second];
            pText += keySquare[(posB.first + 4) % 5][posB.second];
        } 
        else 
        { 
            pText += keySquare[posA.first][posB.second];
            pText += keySquare[posB.first][posA.second];
        }
    }


    for (size_t i = 1; i < pText.length();i++) {
        if (pText[i] == 'X' && pText[i - 1] == pText[i + 1])
        pText.erase(i, 1);
    }

    return pText;
}

int main() 
{
    string key, pText, cText;

    cout << "Enter the key: ";
    getline(cin, key);

    vector<vector<char>> keySquare = genKeySquare(key);

    cout << "Enter the plaintext: ";
    getline(cin, pText);

    string preppedText = prepText(pText);
    cText = encrypt(preppedText, keySquare);
    cout << "Encrypted text: " << cText << endl;

    string dText = decrypt(cText, keySquare);
    cout << "Decrypted text: " << dText << endl;

    return 0;
}
