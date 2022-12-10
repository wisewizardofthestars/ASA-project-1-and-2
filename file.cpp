#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace std {
template <>
struct hash<vector<int>> {
    std::size_t operator()(std::vector<int> const& vec) const {
        std::size_t seed = vec.size();
        for (auto x : vec) {
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = (x >> 16) ^ x;
            seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}  // namespace std

unsigned long long int solver(const vector<int>& rows) {
    hash<vector<int>> hash_fn;
    static map<size_t, int> memoized_values;
    auto h = hash_fn(rows);

    if (memoized_values.find(h) != memoized_values.end()) {
        return memoized_values[h];
    }

    unsigned long long int total = 0;
    auto max_ptr = max_element(rows.begin(), rows.end());

    unsigned long long int max_value = *max_ptr;
    unsigned long long int min_index = max_ptr - rows.begin();
    unsigned long long int max_index = min_index;
    auto next_ptr = next(max_ptr);
    while (*next_ptr == max_value) {
        max_index++;
        next_ptr = next(next_ptr);
    }

    if (max_value < 2) {
        if (max_value == 0 && memoized_values.size() == 0)
            return 0;
        return 1;
    }

    unsigned long long int max_square = min(max_value, (max_index - min_index) + 1);

    for (int i = 1; i <= max_square; i++) {
        vector<int> rows_copy = rows;
        for (int j = 0; j < i; j++) {
            rows_copy[min_index + j] -= i;
        }
        total += solver(rows_copy);
    }
    memoized_values[h] = total;
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
    unsigned long long int ans = solver(row_sizes);
    cout << ans << endl;

    return 0;
}