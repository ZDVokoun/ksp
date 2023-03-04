#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int cur;
    cin >> cur;
    vector<int> res;
    int n = 2;
    while (n <= sqrt(cur)) {
      if (cur % n == 0) {
        res.push_back(n);
        cur /= n;
      } else
        n++;
    }
    res.push_back(cur);
    int prime = -1;
    int power = 1;
    for (int p : res) {
      if (prime == -1) {
        prime = p;
        continue;
      }
      if (p == prime)
        power++;
      else {
        cout << prime;
        if (power > 1)
          cout << "^" << power;
        cout << "*";
        power = 1;
        prime = p;
      }
    }
    cout << prime;
    if (power > 1)
      cout << "^" << power;
    cout << endl;
  }
  return 0;
}
