#include <iostream>

int get_fibonacci_last_digit_naive(int n);
int get_fibonacci_last_digit(int n);

int main() {
    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    int c = get_fibonacci_last_digit(n);
    std::cout << c << '\n';
}

// last digit of a large fibonacci number. use modulo
int get_fibonacci_last_digit(int n) {
    if (n <= 1)
        return n;
    int f1 = 0, f2 = 1;
    for (int i = 2; i <= n; ++i) {
        int fib = f1 + f2;
        f1 = f2;
        f2 = fib % 10;
    }
    // std::cout << list[n-1];
    return f2;
}

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}
