#include <algorithm>
#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main(int argc, char *argv[]) {
  int N;
  cin >> N;
  vector<ll> town(N);
  for (int i = 0; i < N; i++)
    cin >> town[i];

  vector<ll> firstWay(N);
  ll h = town[0];
  for (int i = 0; i < N; i++) {
    if (h < town[i])
      h = town[i];
    h++;
    firstWay[i] = h;
  }
  vector<ll> secondWay(N);
  h = town[N - 1];
  for (int i = N - 1; i >= 0; i--) {
    if (h < town[i])
      h = town[i];
    h++;
    secondWay[i] = h;
  }
  vector<ll> finalWay(N);
  ll sand = 0;
  for (int i = 0; i < N; i++) {
    finalWay[i] = min(firstWay[i], secondWay[i]);
    sand += finalWay[i] - town[i];
  }

  ll largest = 0;
  int smallestOccurence = 0;
  for (int i = 0; i < N; i++) {
    if (largest < finalWay[i]) {
      largest = finalWay[i];
      smallestOccurence = 1;
    } else if (largest == finalWay[i])
      smallestOccurence++;
  }
  ll res = 0;
  if (smallestOccurence % 2 == 1)
    res += N * 2 - 1;
  else
    res += N * 2;

  res += (sand - N) * 4;
  cout << res << endl;

  return 0;
}
