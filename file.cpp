#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int solver(const vector<int>& rows) {
    static map<vector<int>, int> memoized_values;
    if (memoized_values.find(rows) != memoized_values.end()) {
        return memoized_values[rows];
    }
    int total = 0;
    auto max_ptr = max_element(rows.begin(), rows.end());

    int max_value = *max_ptr;
    int min_index = max_ptr - rows.begin();
    int max_index = min_index;
    auto next_ptr = next(max_ptr);
    while (*next_ptr == max_value) {
        max_index++;
        next_ptr = next(next_ptr);
    }

    if (max_value == 1) {
        return 1;
    }

    int max_square = min(max_value, (max_index - min_index) + 1);

    for (int i = 1; i <= max_square; i++) {
        vector<int> rows_copy = rows;
        for (int j = 0; j < i; j++) {
            rows_copy[min_index + j] -= i;
        }
        total += solver(rows_copy);
    }
    memoized_values[rows] = total;
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