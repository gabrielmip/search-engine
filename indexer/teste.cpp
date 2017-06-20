#include <iostream>
#include <cstdio>
#include <map>
#include <string>

using namespace std;

int main(){
    string term = "ÁáuúÚûÛ";

    unsigned char c;
    for (int i = 0; i < term.length(); i++) {
        c = term[i];
        printf("%04x\n", c);
        
        // u
        if (((c >= 0xF9) and (c <= 0xFC)) or ((c >= 0xD9) and (c <= 0xDC))) {
            cout << "e U" << endl;
            // term.erase (i,1);
            term[i] = 'u';
        }
        
        // a
        else if (((c >= 0xC0) and (c <= 0xC5)) or ((c >= 0xE0) and (c <= 0xE5))) {
            // term[i] = 0x61;
            cout << "e A" << endl;
            term.erase (i,1);
            term[i] = 'a';
        } 
        // e 
        else if (((c >= 0xC8) and (c <= 0xCB)) or ((c >= 0xE8) and (c <= 0xEB))) {
            // term[i] = 0x65;
            cout << "e E" << endl;
            // term.erase (i,1);
            term[i] = 'e';
        } 
        // i 
        else if (((c >= 0xC8) and (c <= 0xCB)) or ((c >= 0xE8) and (c <= 0xEB))) {
            // term[i] = 0x65;
            cout << "e I" << endl;
            // term.erase (i,1);
            term[i] = 'i';
        }
        // o
        else if (((c >= 0xF2) and (c <= 0xF5)) or ((c >= 0xD2) and (c <= 0xD6))) {
            // term[i] = 0x65;
            cout << "e O" << endl;
            // term.erase (i,1);
            term[i] = 'o';
        }
        else {
            cout << "e D" << endl;
            term[i] = tolower(term[i]);
        }
    }
    cout << term << endl;
}

