#include <iostream>

int fibonacci_sum_squares(long long n);
int get_fibonacci_huge(long long n, long long m);
long long getPisanoPeriodSize(long long n, long long m);
long long get_fibonacci_last_digits(long long n, long long m);

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_squares_naive(n);
    std::cout << fibonacci_sum_squares(n) << '\n';
}

/*
    Challenge - compute last digit of the sum of sq(F0)+sq(F1)+....sq(Fn)
    My formula -  Sum(n) = Fib(n) * Fib(n+1);
    0 1 1 2  3  5   8  13 21 34  55  89 144 233 377  610  987 1597 2584 4181
    0 1 1 4  9 25  64 169
    0 1 2 6 15 40 104
    
*/
int fibonacci_sum_squares(long long n) {
    long long m = 10; // Q: What influences choice of m?
    return (get_fibonacci_huge(n, m) * get_fibonacci_huge(n+1, m)) % 10;
}

/*
    compute 𝐹𝑛 modulo 𝑚, where 𝑛 may be really huge: up to 10^14. 
    For such values of 𝑛, an algorithm looping for 𝑛 iterations will not fit into one second for sure. 
    Therefore we need to avoid such a loop.
    We want to get the last digit(s) of the fibonacci number like in fibonacci_last_digit but m different
    For any integer 𝑚 ≥ 2, the sequence 𝐹𝑛 mod 𝑚 is periodic. 
    The period always starts with 01 and is known as Pisano period.
    Therefore, to compute, say, 𝐹(2015) mod 3 we just need to find the remainder of 2015 when divided 
    by 8 (period size). Since 2015 = 251 · 8 + 7, we conclude that 𝐹(2015) mod 3 = 𝐹(7) mod 3 = 1.
*/
int get_fibonacci_huge(long long n, long long m) {
    if (n <= 1)
        return n;
    long long n1 = n % getPisanoPeriodSize(n, m);
    return get_fibonacci_last_digits(n1, m) % 10; // only need 1 digit in this case
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

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}
