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
  vector<pair<int, set<pair<int, int>>>> process;
  set<pair<int, int>> current;
  int nOfEmpty = 0;
  for (Item it : items) {
    if (it.sVykem.size() == 0 && current.size() != 0)
      continue;
    if (it.sVykem.size() > 0) {
      current.insert(make_pair(it.m, it.i));
      if (!it.v)
        nOfEmpty++;
    } else if (it.sVykem.size() == 0) {
      process.push_back(make_pair(nOfEmpty, current));
      current = set<pair<int, int>>();
      nOfEmpty = 0;
    }
  }
  set<int> toRemove;
  for (auto group : process) {
    auto it = group.second.end();
    for (int i = 0; i < group.first; i++)
      toRemove.insert((--it)->second);
  }
  int weight = 0;
  map<int, int> res;
  bool emptyBefore = false;
  bool toRemoveBefore = false;
  for (Item it : items) {
    if (it.sVykem.size() == 0)
      continue;
    if (toRemove.find(it.i) != toRemove.end()) {
      if (it.v) {
        if (emptyBefore) {
          res[it.i] = it.i - 1;
          emptyBefore = false;
        } else {
          toRemoveBefore = true;
        }
      }
    } else {
      weight += items[it.i].m;
      if (!it.v) {
        emptyBefore = true;
        toRemoveBefore = false;
      }
    }
  }
}
