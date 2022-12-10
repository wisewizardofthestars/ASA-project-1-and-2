#include <algorithm>
#include <tr1/unordered_map>
#include <string>
#include <vector>

using namespace std;

size_t hash_vector(const vector<int>& v) {
    size_t seed = v.size();
    for (auto i : v) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

unsigned long long int solver(const vector<int>& rows) {
    size_t h = hash_vector(rows);
    static tr1::unordered_map<size_t, unsigned long long int> memoized_values;

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