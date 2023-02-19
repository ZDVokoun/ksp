#include <bits/stdc++.h>
#include <cstdint>
#include <utility>

#define ll long long

using namespace std;

struct Item {
  int i;
  int m;
  bool v;
  vector<int> sVykem;
  bool erased = false;
  bool done = false;
};

bool compare(Item a, Item b) {
  if (a.m > b.m)
    return true;
  else
    return false;
}

void task(vector<Item> &items, int &bestCur, int &bestWeight,
          map<int, int> &bestRes, int maxPairs, int cur,
          map<int, int> res = map<int, int>(), int weight = 0) {
  if (res.size() == maxPairs || cur > bestCur || cur >= items.size()) {
    if (bestWeight < weight) {
      bestWeight = weight;
      bestRes = res;
    }
    return;
  }
  bool empty = true;
  for (int vyko : items[cur].sVykem) {
    if (res.find(vyko) == res.end()) {
      empty = false;
      map<int, int> newRes = res;
      newRes[vyko] = items[cur].i;
      task(items, bestCur, bestWeight, bestRes, maxPairs, cur + 1, newRes,
           weight + items[cur].m);
    }
  }
  if (empty)
    task(items, bestCur, bestWeight, bestRes, maxPairs, cur + 1, res, weight);
}

signed main() {
  int N = 0, K = 0;
  cin >> N >> K;
  vector<Item> items = vector<Item>(N);
  vector<int> sVykem;
  for (int i = 0; i < N; ++i) {
    int m;
    bool v;
    cin >> m >> v;
    items[i] = Item{i, m, v, vector<int>()};
    if (v)
      sVykem.push_back(i);
  }
  for (int i : sVykem) {
    for (int j = i - K < 0 ? 0 : i - K; j < (i + K + 1 > N ? N : i + K + 1);
         j++) {
      items[j].sVykem.push_back(i);
    }
  }

  for (int i = N - 1; i >= 0; i--)
    if (items[i].sVykem.size() == 0)
      items.erase(items.begin() + i);
  sort(items.begin(), items.end(), compare);
  vector<int> prefixSums(items.size());
  int bestCur = INT32_MAX;
  // prefixSums[items.size() - 1] = items[items.size() - 1].m;
  // for (int i = items.size() - 2; i >= 0; --i)
  //   prefixSums[i] = prefixSums[i + 1] + items[i].m;
  int bestWeight = 0;
  map<int, int> bestRes;
  task(items, bestCur, bestWeight, bestRes, sVykem.size(), 0);
  cout << bestWeight << endl;
  for (auto pair : bestRes)
    cout << pair.first + 1 << " " << pair.second + 1 << endl;
}
