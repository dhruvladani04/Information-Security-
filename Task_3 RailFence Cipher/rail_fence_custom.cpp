#include <bits/stdc++.h>
using namespace std;

string railFenceEncrypt(const string& message, int rails, int step) 
{
    vector<string> fence(rails);
    int row = 0;
    bool down = true;
    for (int i = 0; i < message.size(); i++) 
    {
        fence[row] += message[i];

        if (down) 
        {
            row += step;
            if (row >= rails) 
            {
                row = rails - 2;
                down = false;
            }
        } 
        else 
        {
            row -= step;
            if (row < 0) 
            {
                row = 1;
                down = true;
            }
        }
    }

    string encrypted;
    for (auto& r : fence) 
    {
        encrypted += r;
    }
    return encrypted;
}


string railFenceDecrypt(const string& encrypted, int rails, int step) 
{
    vector<int> railLengths(rails, 0);
    int row = 0;
    bool down = true;

    for (int i = 0; i < encrypted.size(); i++) 
    {
        railLengths[row]++;
        if (down) {
            row += step;
            if (row >= rails) {
                row = rails - 2;
                down = false;
            }
        } else {
            row -= step;
            if (row < 0) {
                row = 1;
                down = true;
            }
        }
    }

    vector<string> fence(rails);
    int pos = 0;
    for (int i = 0; i < rails; i++) 
    {
        fence[i] = encrypted.substr(pos, railLengths[i]);
        pos += railLengths[i];
    }

    string decrypted;
    row = 0;
    down = true;
    vector<int> index(rails, 0);

    for (int i = 0; i < encrypted.size(); i++) 
    {
        decrypted += fence[row][index[row]++];

        if (down) 
        {
            row += step;
            if (row >= rails) 
            {
                row = rails - 2;
                down = false;
            }
        } 
        else 
        {
            row -= step;
            if (row < 0) 
            {
                row = 1;
                down = true;
            }
        }
    }

    return decrypted;
}

int main() {
    cout << "Enter the message: ";
    string message;
    cin >> message;
    cout << "Enter the number of rails: ";
    int rails;
    cin >> rails;
    cout << "Enter the step size: ";
    int step;
    cin >> step;
    string encrypted = railFenceEncrypt(message, rails, step);
    cout << "Encrypted: " << encrypted << endl;
    string decrypted = railFenceDecrypt(encrypted, rails, step);
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}
