#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solver(const vector<int>& rows) {
    int total = 0;
    auto max_ptr = max_element(rows.begin(), rows.end());
    auto min_ptr = max_element(rows.rbegin(), rows.rend());

    int max_value = *max_ptr;
    int r = max_ptr - rows.begin();
    int max_index = rows.size() - 1 - (max_ptr - rows.begin());
    int min_index = rows.size() - 1 - distance(rows.rbegin(), min_ptr);

    if (max_value == 0) {
        return 1;
    }

    int max_square = min(max_value, (min_index - r) + 1);

    for (int i = 1; i <= max_square; i++) {
        vector<int> rows_copy = rows;
        for (int j = 0; j < i; j++) {
            rows_copy[r + j] -= i;
        }
        total += solver(rows_copy);
    }
    return total;
}

int main() {
    vector<int> row_sizes;
    string line;
    int i = 0;
    while (getline(cin, line)) {
        if (i > 1) {
            int row_size = stoi(line);
            row_sizes.push_back(row_size);
        }
        i++;
    }
    int ans = solver(row_sizes);
    cout << ans << endl;

    return 0;
}