#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main(int argc, char *argv[]) {
  int N;
  cin >> N;
  vector<int> town(N);
  for (int i = 0; i < N; i++)
    cin >> town[i];

  ll sand = 0;
  int s = 0, e = N - 1;
  bool done = false;
  bool wasOdd = false;
  while (!done) {
    cout << s << " " << e << endl;
    int h = 0;
    int bound = s + int((e - s) / 2);
    bool odd = (e - s + 1) % 2;
    if (town[s] > town[e]) {
      bound = s + int((e - s) / 2);
      // if ((e - s) % 2 == 1) bound += 1;
      for (int i = e; i > bound - 1; i--) {
        e = i;
        if (i == bound) {
          done = true;
          break;
        }
        if (h <= town[i])
          break;
        h += 1;
        sand += h - town[i];
        // town[i] = h;
      }
      if (done) {
        if (odd)
          h++;
        for (int i = e; i > s - 1; i--) {
          if (h <= town[i]) {
            sand++;
            h--;
            continue;
          }
          sand += h - town[i];
          h--;
        }
        wasOdd = odd;
      }
    } else {
      h = town[s];
      bound = s + int((e - s) / 2);
      if (!odd)
        bound++;
      for (int i = s; i < bound + 1; i++) {
        s = i;
        if (i == bound) {
          done = true;
          break;
        }
        if (h <= town[i])
          break;
        h += 1;
        sand += h - town[i];
        // town[i] = h;
      }
      // cout << sand << endl;
      if (done) {
        if (odd)
          h++;
        for (int i = s; i < e + 1; i++) {
          if (h <= town[i]) {
            sand++;
            h--;
            continue;
          }
          sand += h - town[i];
          h--;
        }
        wasOdd = odd;
      }
    }
  }
  ll res = 0;
  if (wasOdd)
    res += N * 2 - 1;
  else
    res += N * 2;

  res += (sand - N) * 4;
  cout << res << endl;

  return 0;
}
