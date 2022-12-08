#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

long long int solver(const vector<long long int>& rows) {
    static map<vector<long long int>, long long int> memoized_values;
    if (memoized_values.find(rows) != memoized_values.end()) {
        return memoized_values[rows];
    }

    long long int total = 0;
    auto max_ptr = max_element(rows.begin(), rows.end());

    long long int max_value = *max_ptr;
    long long int min_index = max_ptr - rows.begin();
    long long int max_index = min_index;
    auto next_ptr = next(max_ptr);
    while (*next_ptr == max_value) {
        max_index++;
        next_ptr = next(next_ptr);
    }

    if (max_value < 2) {
        return 1;
    }

    long long int max_square = min(max_value, (max_index - min_index) + 1);

    for (long long int i = 1; i <= max_square; i++) {
        vector<long long int> rows_copy = rows;
        for (long long int j = 0; j < i; j++) {
            rows_copy[min_index + j] -= i;
        }
        total += solver(rows_copy);
    }
    memoized_values[rows] = total;
    return total;
}

int main() {
    vector<long long int> row_sizes;
    string line;
    long long int i = 0;
    while (getline(cin, line)) {
        if (i > 1) {
            long long int row_size = stoi(line);
            row_sizes.push_back(row_size);
        }
        i++;
    }
    long long int ans = solver(row_sizes);
    cout << ans << endl;

    return 0;
}