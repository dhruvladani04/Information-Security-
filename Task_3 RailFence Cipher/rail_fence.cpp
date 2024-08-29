#include <bits/stdc++.h>
using namespace std;
string railFenceEncrypt(string& message, int rails) 
{
    vector<string> fence(rails);
    bool fl = true; 
    int row = 0;
    for (char c : message) 
    {
        fence[row] += c;
        if (row == 0) 
        fl=true;
        else if (row == rails - 1) 
        fl=false;
        row+=(fl)?1:-1;
    }
    string encrypted;
    for (auto& row : fence) {
        encrypted += row;
    }
    return encrypted;
}


string railFenceDecrypt(const string& encrypted, int rails) {
    vector<int> railLengths(rails, 0);
    bool fl = true;
    int row = 0;
    for (char c : encrypted) 
    {
        railLengths[row]++;
        if (row == 0)
            fl = true;
        else if (row == rails - 1)
            fl = false;
        row += (fl) ? 1 : -1;
    }

   
    vector<string> fence(rails);
    int pos = 0;
    for (int i = 0; i < rails; ++i) 
    {
        fence[i] = encrypted.substr(pos, railLengths[i]);
        pos += railLengths[i];
    }


    string decrypted;
    row = 0;
    fl = true;
    vector<int> index(rails, 0);

    for (int i = 0; i < encrypted.size(); i++) 
    {
        decrypted += fence[row][index[row]++];
        if (row == 0)
            fl = true;
        else if (row == rails - 1)
            fl = false;
        row += (fl) ? 1 : -1;
    }

    return decrypted;
}

int main() {
    cout<<"Enter the message ";
    string message;
    cin>>message;
    cout<<"Enter the key : ";
    int rails;
    cin>>rails;
    string encrypted = railFenceEncrypt(message, rails);
    cout << "Encrypted: " << encrypted << endl;
    string decrypted = railFenceDecrypt(encrypted, rails);
    cout << "Decrypted: " << decrypted << endl;
    return 0;
}