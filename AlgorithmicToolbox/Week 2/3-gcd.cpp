#include <iostream>
#include <cassert>

int gcd_naive(int a, int b);
int gcd(int a, int b);

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}

/*
  Basic Euclidean Algorithm for GCD
  The algorithm is based on below facts.

  If we subtract smaller number from larger (we reduce larger number), GCD doesn’t change. So if we keep subtracting repeatedly the larger of two, we end up with GCD.
  Now instead of subtraction, if we divide smaller number, the algorithm stops when we find remainder 0.
*/
int gcd(int n1, int n2) {
  if (n1 == 0) { // have reached reminder 0, so n2 is GCD
    return n2;
  }
  return gcd(n2 % n1, n1);
}

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}