#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m);
long long get_fibonacci_huge(long long n, long long m);

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}

/*
    compute 𝐹𝑛 modulo 𝑚, where 𝑛 may be really huge: up to 10^14. 
    For such values of 𝑛, an algorithm looping for 𝑛 iterations will not fit into one second for sure. 
    Therefore we need to avoid such a loop.
    We want to get the last digit(s) of the fibonacci number like in fibonacci_last_digit but m different
*/
long long get_fibonacci_huge(long long n, long long m) {
    
}

int getPisanoPeriodSize() {
    /* for any integer 𝑚 ≥ 2, the sequence 𝐹𝑛 mod 𝑚 is periodic. 
    The period always starts with 01 and is known as Pisano period. */

}

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}
