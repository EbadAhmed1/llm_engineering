
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>

// Linear Congruential Generator class
class LCG {
public:
    LCG(uint32_t seed, uint32_t a=1664525, uint32_t c=1013904223, uint32_t m=4294967296) 
    : value(seed), a(a), c(c), m(m) {}

    uint32_t next() {
        value = (a * value + c) % m;
        return value;
    }

private:
    uint32_t value, a, c, m;
};

// Function to compute the maximum subarray sum using the generated random numbers
int64_t max_subarray_sum(int n, uint32_t seed, int32_t min_val, int32_t max_val) {
    LCG lcg(seed);
    std::vector<int32_t> random_numbers(n);
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = lcg.next() % (max_val - min_val + 1) + min_val;
    }
    
    int64_t max_sum = std::numeric_limits<int64_t>::min();
    for (int i = 0; i < n; ++i) {
        int64_t current_sum = 0;
        for (int j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) max_sum = current_sum;
        }
    }
    return max_sum;
}

// Function to compute the total max subarray sum over 20 runs
int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int32_t min_val, int32_t max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        uint32_t seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;        // Number of random numbers
    uint32_t initial_seed = 42; // Initial seed for the LCG
    int32_t min_val = -10; // Minimum value of random numbers
    int32_t max_val = 10;  // Maximum value of random numbers

    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " seconds" << std::endl;
    
    return 0;
}
