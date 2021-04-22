#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    ofstream fout;
    fout.open("RegisterData.txt");
    int r;
    for(int i = 0; i < 15; i++) {
        r = rand() % 256;
        fout << hex << r << endl;
    }
}
