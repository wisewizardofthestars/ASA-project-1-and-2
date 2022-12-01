#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

long solver(const vector<long>& rows) {
    static map<vector<long>, long> memoized_values;
    if (memoized_values.find(rows) != memoized_values.end()) {
        return memoized_values[rows];
    }

    long total = 0;
    auto max_ptr = max_element(rows.begin(), rows.end());

    long max_value = *max_ptr;
    long min_index = max_ptr - rows.begin();
    long max_index = min_index;
    auto next_ptr = next(max_ptr);
    while (*next_ptr == max_value) {
        max_index++;
        next_ptr = next(next_ptr);
    }

    if (max_value < 2) {
        return 1;
    }

    long max_square = min(max_value, (max_index - min_index) + 1);

    for (long i = 1; i <= max_square; i++) {
        vector<long> rows_copy = rows;
        for (long j = 0; j < i; j++) {
            rows_copy[min_index + j] -= i;
        }
        total += solver(rows_copy);
    }
    memoized_values[rows] = total;
    return total;
}

int main() {
    vector<long> row_sizes;
    string line;
    long i = 0;
    while (getline(cin, line)) {
        if (i > 1) {
            long row_size = stoi(line);
            row_sizes.push_back(row_size);
        }
        i++;
    }
    long ans = solver(row_sizes);
    cout << ans << endl;

    return 0;
}