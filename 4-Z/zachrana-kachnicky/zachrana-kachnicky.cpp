#include <iostream>
#include <vector>

#define ll long long

using namespace std;

int main(int argc, char *argv[]) {
  ll N, D;
  cin >> N >> D;
  vector<ll> rybnik(N);
  for (int i = 0; i < N; i++)
    cin >> rybnik[i];
  ll res = 0;
  ll max = rybnik[D - 1] + 1;
  for (int i = D - 1; i >= 0; i--) {
    if (rybnik[i] < max) {
      res += max - rybnik[i];
      rybnik[i] = max;
    } else
      max = rybnik[i];
  }
  for (int i = D; i < N; i++) {
    if (rybnik[i] < rybnik[D - 1]) {
      res += rybnik[D - 1] - rybnik[i];
      rybnik[i] = rybnik[D - 1];
    } else
      break;
  }
  // while (true) {
  //   ll highest = 0;
  //   ll newLevel = 0;
  //   for (int i = 0; i < N; i++) {
  //     if (rybnik[i] < rybnik[i + 1]) {
  //       highest = i + 1;
  //       break;
  //     }
  //   }
  //   newLevel = rybnik[highest];
  //   if (highest > D - 1)
  //     newLevel = rybnik[D - 1] + 1;
  //   for (int i = 0; i < highest; i++)
  //     if (newLevel > rybnik[i]) {
  //       res += newLevel - rybnik[i];
  //       rybnik[i] = newLevel;
  //     }
  //   // for (ll s : rybnik)
  //   //   cout << s << " ";
  //   // cout << endl;
  //   if (highest > D - 1)
  //     break;
  // }
  cout << res << endl;
  return 0;
}
