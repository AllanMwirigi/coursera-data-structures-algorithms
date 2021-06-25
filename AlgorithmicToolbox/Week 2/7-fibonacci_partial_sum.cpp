#include <iostream>
#include <vector>
using std::vector;

int get_fibonacci_partial_sum_last_digit(long long from, long long to);
long long fibonacci_sum_last_digit(long long n);
long long get_fibonacci_huge(long long n, long long m);
long long getPisanoPeriodSize(long long n, long long m);
long long get_fibonacci_last_digits(long long n, long long m);

int main() {
    long long from, to;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_last_digit(from, to) << '\n';
}

/*
    Given two non-negative integers 𝑚 and 𝑛, where 𝑚 ≤ 𝑛, find the last digit of the sum 𝐹𝑚 + 𝐹𝑚+1 +
    · · · + 𝐹𝑛.
    Partial Sum (from ... to) = Sum(to) - Sum(from-1)
*/
int get_fibonacci_partial_sum_last_digit(long long from, long long to) {
    if (from == to) { // the same fibonacci number
        return get_fibonacci_huge(from, 10); 
    }
    int sum2 = fibonacci_sum_last_digit(to);
    int sum1 = fibonacci_sum_last_digit(from - 1);
    // int fib = get_fibonacci_huge(from, 10); // the fibonacci num at n = from, mod = 10
    if(sum2 < sum1) sum2+=10; // make subtraction possible
    return (sum2 - sum1) % 10;
}

/*
    My formula -  Sum(n) = Fib(n+2) - 1
    0 1 1 2 3  5  8 13 21 34  55  89 144 233 377  610  987 1597 2584 4181
    0 1 2 4 7 12 20 33 54 88 143 232 376 609 986 1596 2583 4180
    0 1 1 4  9 25  64 169
    0 1 2 6 15 40 104
    
*/
long long fibonacci_sum_last_digit(long long n) {
    long long m = 1000;
    long long sum = get_fibonacci_huge(n+2, m) % 10;
    if (sum == 0) { // last digit is 0, so should be set to 9 when subtracted by 1
        return 9;
    }
    return sum - 1;
}


long long get_fibonacci_huge(long long n, long long m) {
    if (n <= 1)
        return n;
    long long n1 = n % getPisanoPeriodSize(n, m);
    return get_fibonacci_last_digits(n1, m) % 10; // only need 1 digit
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

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}