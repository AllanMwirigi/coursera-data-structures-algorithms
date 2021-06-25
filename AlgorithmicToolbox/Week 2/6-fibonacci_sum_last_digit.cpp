#include <iostream>

int fibonacci_sum_naive(long long n);
int fibonacci_sum_last_digit(long long n);
long long get_fibonacci_huge(long long n, long long m);
long long getPisanoPeriodSize(long long n, long long m);
long long get_fibonacci_last_digits(long long n, long long m);

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_naive(n);
    std::cout << fibonacci_sum_last_digit(n) << "\n";
}

/*
    I have come up with the formula that Sum(n) = Fib(n+2) - 1
    0 1 1 2 3  5  8 13 21 34  55 89  144 233 377  610  987 1597 2584 4181
    0 1 2 4 7 12 20 33 54 88 143 232 376 609 986 1596 2583 4180
*/
int fibonacci_sum_last_digit(long long n) {
    long long m = 1000;
    long long sum = get_fibonacci_huge(n+2, m) % 10; // mod 10 because we need only a single digit
    if (sum == 0) { // last digit is 0, so should be set to 9 when subtracted by 1
        return 9;
    }
    return sum - 1;
}


long long get_fibonacci_huge(long long n, long long m) {
    if (n <= 1)
        return n;
    long long n1 = n % getPisanoPeriodSize(n, m);
    return get_fibonacci_last_digits(n1, m);
}

long long getPisanoPeriodSize(long long n, long long m) {
    
    long long f1 = 0, f2 = 1;
    for (long long i = 2; i <= n; ++i) {
        long long fib = f1 + f2;
        f1 = f2;
        f2 = fib % m;
        if(f1 == 0 && f2 == 1) { // new period
            return i-1; // should be i-2 but changes since we are starting from 0 not 1 in the count
        }
    }
}

long long get_fibonacci_last_digits(long long n, long long m) {
    if (n <= 1)
        return n;
    long long f1 = 0, f2 = 1;
    for (long long i = 2; i <= n; ++i) {
        long long fib = f1 + f2;
        f1 = f2;
        f2 = fib % m;
    }
    // std::cout << list[n-1];
    return f2;
}

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}
