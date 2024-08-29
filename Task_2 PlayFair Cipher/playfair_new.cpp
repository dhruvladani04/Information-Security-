#include <bits/stdc++.h>
using namespace std;
// void print_mat(vector<vector<char>> &keySquare)
// {
//     for(int i=0;i<6;i++)
//     {
//         for(int j=0;j<6;j++)
//         {
//             cout<<keySquare[i][j]<<" ";
//         }
//         cout<<endl;
//     }
// }

vector<vector<char>> genKeySquare(const string &key) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    vector<vector<char>> keySquare(6, vector<char>(6, ' '));
    string adjKey;

    for (char c : key) {
        c = toupper(c);
        if (adjKey.find(c) == string::npos) adjKey += c;
    }

    int x = 0, y = 0;
    for (char c : adjKey) {
        keySquare[x][y++] = c;
        if (y == 6) {
            y = 0;
            x++;
        }
    }

    for (char c : alphabet) {
        if (adjKey.find(c) == string::npos) {
            keySquare[x][y++] = c;
            if (y == 6) {
                y = 0;
                x++;
            }
        }
    }
    // print_mat(keySquare);
    return keySquare;
}

pair<int, int> findPos(char c, const vector<vector<char>> &keySquare) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (keySquare[i][j] == c)
                return make_pair(i, j);
        }
    }
    return make_pair(-1, -1); 
}

string prepText(const string &text) {
    string pText;
    for (size_t i = 0; i < text.length(); i++) {
        char c = toupper(text[i]);
        if (isalnum(c)) {
            pText += c;
            if (i < text.length() - 1 && c == toupper(text[i + 1])) {
                pText += 'X'; // Only add 'X' between duplicate letters
            }
        }
    }
    if (pText.length() % 2 != 0) pText += 'X'; // Ensure even length
    return pText;
}


string encrypt(const string &pText, const vector<vector<char>> &keySquare) {
    string cText;
    for (size_t i = 0; i < pText.length(); i += 2) {
        char a = pText[i];
        char b = pText[i + 1];
        auto posA = findPos(a, keySquare);
        auto posB = findPos(b, keySquare);

        if (posA.first == posB.first) {
            cText += keySquare[posA.first][(posA.second + 1) % 6];
            cText += keySquare[posB.first][(posB.second + 1) % 6];
        } else if (posA.second == posB.second) {
            cText += keySquare[(posA.first + 1) % 6][posA.second];
            cText += keySquare[(posB.first + 1) % 6][posB.second];
        } else {
            cText += keySquare[posA.first][posB.second];
            cText += keySquare[posB.first][posA.second];
        }
    }
    return cText;
}

string permuteText(const string &cText, const string &key) {
    string permutedText = cText;
    vector<int> indices(cText.length());
    iota(indices.begin(), indices.end(), 0);
    // for(auto ind:indices)
    // cout<<ind<<endl;
    sort(indices.begin(), indices.end(), [&key](int a, int b) {
        return key[a % key.length()] < key[b % key.length()];
    });

    // for(auto ind:indices)
    // cout<<ind<<endl;
    for (size_t i = 0; i < cText.length(); i++) {
        permutedText[i] = cText[indices[i]];
    }

    return permutedText;
}

string decrypt(const string &cText, const vector<vector<char>> &keySquare) {
    string pText;
    for (int i = 0; i < cText.length(); i += 2) {
        char a = cText[i];
        char b = cText[i + 1];
        auto posA = findPos(a, keySquare);
        auto posB = findPos(b, keySquare);

        if (posA.first == posB.first) {
            pText += keySquare[posA.first][(posA.second + 5) % 6];
            pText += keySquare[posB.first][(posB.second + 5) % 6];
        } else if (posA.second == posB.second) {
            pText += keySquare[(posA.first + 5) % 6][posA.second];
            pText += keySquare[(posB.first + 5) % 6][posB.second];
        } else {
            pText += keySquare[posA.first][posB.second];
            pText += keySquare[posB.first][posA.second];
        }
    }

    // Remove 'X' added between duplicate letters or at the end
    for (int i = 0; i < static_cast<int>(pText.length()) - 1; i++) {
        if (pText[i] == 'X' && (i == static_cast<int>(pText.length()) - 1 || pText[i - 1] == pText[i + 1])) {
            pText.erase(i, 1);
            i--; // Adjust index to account for the removed character
        }
    }
    if (!pText.empty() && pText.back() == 'X') {
        pText.pop_back(); // Remove padding 'X' if it exists
    }

    return pText;
}

string reversePermuteText(const string &permutedText, const string &key) {
    string cText = permutedText;
    vector<int> indices(permutedText.length());
    iota(indices.begin(), indices.end(), 0);

    sort(indices.begin(), indices.end(), [&key](int a, int b) {
        return key[a % key.length()] < key[b % key.length()];
    });

    for (size_t i = 0; i < permutedText.length(); i++) {
        cText[indices[i]] = permutedText[i];
    }
    
    return cText;
}

int main() {
    string key, pText, cText;

    cout << "Enter the key: ";
    getline(cin, key);

    vector<vector<char>> keySquare = genKeySquare(key);
    cout << "Enter the plaintext: ";
    getline(cin, pText);

    string preppedText = prepText(pText);
    cText = encrypt(preppedText, keySquare);

    // cout << "Encrypted text: " << cText << endl;

    cText = permuteText(cText, key);

    cout << "Encrypted text: " << cText << endl;

    string reversedCText = reversePermuteText(cText, key);
    string dText = decrypt(reversedCText, keySquare);

    cout << "Decrypted text: " << dText << endl;

    return 0;
}
