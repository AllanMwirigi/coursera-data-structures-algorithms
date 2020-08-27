#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;

// Challenge - find max product in a set of given numbers

int64_t MaxPairwiseProduct(const vector<int>& numbers);
int64_t MaxPairwiseProductSlow(const vector<int>& numbers);
void stressTest();

// VS Code - code-runner
// "code-runner.executorMap": {
//     "cpp": "cd $dir && g++ $fileName -o $dir/bin/$fileNameWithoutExt && $dir/bin/$fileNameWithoutExt",
// }

int main() {
    // stressTest();
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}

int64_t MaxPairwiseProduct(const vector<int>& numbers) {
    // get the two maximum values and find their product
    int64_t max1 = 0 , max2 = 0;
    int n = numbers.size();
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            max1 = numbers[i];
            continue;
        }
        if (i > 0 && numbers[i] >= max1) {
            max2 = max1;
            max1 = numbers[i];
            continue;
        }
        if (i > 0 && numbers[i] >= max2) {
            max2 = numbers[i];
        }
    }
    return max1 * max2;
}

void stressTest() {
    // values generated are pseudo random in that the same sequence of values are generated, hence the tests are consistent/reproducible
    while (true) {
        int n = rand() % 10 + 2; // random number btwn 2 and 11
        cout << n << "\n";
        vector<int> nums;
        for (int i = 0; i < n; ++i) {
            int val = rand() % 100000; // random number btwn 0 and 100000
            nums.push_back(val); 
            cout << val << " ";
        }
        cout << "\n";
        // try any number of solutions in order to identify what is wrong in any in order to narrow down
        // can modify the range of n and val
        int64_t res1 = MaxPairwiseProduct(nums);
        int64_t res2 = MaxPairwiseProductSlow(nums);
        if(res1 == res2) {
            cout << "OK\n";
        } else {
            cout << "Wrong: " << res1 << " " << res2 << "\n";
            break;
        } 
    }

}

// this solution is slow as it gets all possible products
int64_t MaxPairwiseProductSlow(const vector<int>& numbers) {
    int64_t max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                (int64_t)numbers[first] * (int64_t)numbers[second]);
        }
    }

    return max_product;
}

/* 
Edge cases to look into if solutions failing:
 - equal values/inputs
 - strings with single or few letters
 - integer overflow
 - time limit or ram exceeded
 - uninitialized variables i.e. might have garbage values initially
 - check for any extra output statements added when debugging
*/