#include <algorithm>
#include <tr1/unordered_map>
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
    static tr1::unordered_map<size_t, unsigned long long int> memoized_values;
    auto h = hash_fn(rows);

    if (memoized_values.find(h) != memoized_values.end()) {
        return memoized_values[h];
    }

    unsigned long long int total = 0;

    int prev = 0;
    int max_value = 0;
    int start = 0;
    int d = 0;
    for (auto v : rows) {
        if (v > max_value) {
            max_value = v;
            start += d;
            d = 1;
        } else if (v == prev) {
            d++;
        } else if (v < prev) {
            break;
        }
        prev = v;
    }

    if (max_value == 0) {
        return 1;
    }

    int max_square = min(max_value, d);

    for (int i = 1; i <= max_square; i++) {
        vector<int> rows_copy = rows;
        for (int j = 0; j < i; j++) {
            rows_copy[start + j] -= i;
        }
        total += solver(rows_copy);
    }
    memoized_values[h] = total;
    return total;
}

int main() {
    vector<int> row_sizes;
    string line;
    int nLines, nCols, row_size;

    scanf("%d", &nLines);
    scanf("%d", &nCols);
    for (int i = 0; i < nLines; i++) {
        scanf("%d", &row_size);
        row_sizes.push_back(row_size);
    }
    if (*max_element(row_sizes.begin(), row_sizes.end()) == 0) {
        printf("0\n");
        return 0;
    }
    unsigned long long int ans = solver(row_sizes);
    printf("%llu\n", ans);

    return 0;
}