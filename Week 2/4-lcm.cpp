#include <iostream>

long long lcm_naive(int a, int b);
long long lcm(int a, int b);
int gcd(int a, int b);

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}

// LCM(a, b) = (a x b) / GCD(a, b) 
long long lcm(int a, int b) {
  return (long long) a * b / gcd(a, b);
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd(int n1, int n2) {
  if (n1 == 0) { // have reached reminder 0, so n2 is GCD
    return n2;
  }
  return gcd(n2 % n1, n1);
}
