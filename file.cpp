#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // read from stdin line by line until end of input
    vector<int> row_sizes;
    string line;
    while (getline(cin, line)) {
        int row_size = stoi(line);
        row_sizes.push_back(row_size);
    }
    return 0;
}