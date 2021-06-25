#include <iostream>

/**
 * The goal in this problem is to find the minimum number of coins needed to change the input value
(an integer) into coins with denominations 1, 5, and 10.
*/

int get_change(int m) {
  int numCoins = 0;
  int denoms[] = {10, 5, 1};
  for (int i = 0; i < 3; i++) {
    numCoins += m/denoms[i];
    m = m%denoms[i];
  }
  
  return numCoins;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}