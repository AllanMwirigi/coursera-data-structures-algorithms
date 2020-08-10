#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

/**
 * You are going to travel to another city that is located 𝑑 miles away from your home city. Your car can travel
 * at most 𝑚 miles on a full tank and you start with a full tank. Along your way, there are gas stations at
 * distances stop1, stop2, . . . ,stop𝑛 from your home city. What is the minimum number of refills needed?
*/

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    // stops.insert(stops.begin(), 0); // add initial and final points to vector
    // stops.push_back(dist);
    if (tank > dist) {
        return 0; // no need to refuel
    }
    else if (stops.size() == 0 && tank < dist) {
        // can't make it if full distance exceeds full tank capability and no stops
         return -1;
    }
    else if (tank < stops[0]) { // first stop is too far away
        return -1;
    }
    else if (tank < (dist - stops[stops.size()-1])) { 
         // can't make it if distance between last stop and final point exceeds full tank capability
         return -1;
    }
    else{
        int refills = 0;
        int fullTank = tank;
        int size = stops.size();
        for (int i = 0; i < size; i++) {
            // tank = tank - stops[i]; 
            // if (stops[i+1]-stops[i] <= tank) { // next stop can be reached at current tank level
            //     continue;
            // }
            if (stops[i+1]-stops[i] <= tank) { // next stop can be reached at current tank level
                // tank = tank - stops[i]; 
                tank = tank - stops[i+1] - stops[i]; 
                continue;
            }
            tank = fullTank; // need to refill tank
            if (tank < stops[i+1]-stops[i]) { // if even after refilling cannot reach next stop
                return -1;
            }
            refills += 1;
        }
        return refills;
    }
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
