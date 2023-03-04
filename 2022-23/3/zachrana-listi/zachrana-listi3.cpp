#include <bits/stdc++.h>
#include <utility>

#define ll long long

const int TREE_SIZE = 2048;
using namespace std;

struct Item {
  int i;
  int m;
  bool v;
  vector<int> sVykem;
  bool erased;
  bool done = false;
};

struct Node {
  struct Node *children[TREE_SIZE];
  int frec = 0;
  int inRange = 0;
};

struct Node *getNode(void) {
  struct Node *n = new Node;
  for (int i = 0; i < TREE_SIZE; i++)
    n->children[i] = NULL;
  return n;
}

void insert(Node *p, set<int> lst, int inRange) {
  Node *cur = p;
  cur->frec++;
  for (int n : lst) {
    if (cur->children[n] == NULL)
      cur->children[n] = getNode();
    cur = cur->children[n];
    cur->frec++;
  }
  cur->inRange = inRange;
}

bool compare(Item a, Item b) {
  if (a.m > b.m)
    return true;
  else
    return false;
}

bool compare2(pair<int, int> a, pair<int, int> b) {
  if (a.first < b.first)
    return true;
  else
    return false;
}
//
// bool compare2(Item a, Item b) {
//   if (a.i < b.i)
//     return true;
//   else
//     return false;
// }
//
// bool compare3(Item a, Item b) {
//   if (a.v < b.v) {
//     return true;
//   } else if (a.v > b.v)
//     return false;
//   else
//     return compare(a, b);
// }

bool compare4(pair<set<int>, int> a, pair<set<int>, int> b) {
  if (a.first < b.first)
    return false;
  else
    return true;
  // auto ita = a.first.begin();
  // auto itb = b.first.begin();
  // for (int i = 0; i < min(a.first.size(), b.first.size()); i++) {
  //   if (*ita < *itb)
  //     return false;
  //   ita++;
  //   itb++;
  // }
  // return true;
}
//
// void test2(vector<Item> &items, int i, int K, int N, vector<int> &links,
//            map<int, int> deleted) {
//   if (items[i].done) {
//     // cout << items[i].i << endl;
//     return;
//   }
//   items[i].done = true;
//   cout << items[i].i << endl;
//   for (int v : items[i].sVykem) {
//     if (deleted[v] == 2 * K)
//       continue;
//     deleted[v]++;
//     if (deleted[v] == 2 * K) {
//       for (int j = v - K < 0 ? 0 : v - K; j < (v + K + 1 > N ? N : v + K +
//       1);
//            j++) {
//         if (links[j] != i)
//           test2(items, links[j], K, N, links, deleted);
//         cout << " " << j << endl;
//       }
//     }
//   }
// }
//
// bool test(vector<Item> &items, int &groupsDone, int &erased, vector<int>
// &links,
//           map<int, int> &deleted, int i, int K, int N, vector<int> &sVykem) {
//   if (items[i].done)
//     return false;
//   if (items.size() - erased == sVykem.size())
//     return true;
//   bool notDelete = false;
//
//   for (int v : items[i].sVykem) {
//     if (deleted[v] == 2 * K) {
//       notDelete = true;
//       deleted[v]++;
//       continue;
//     }
//     deleted[v]++;
//     if (deleted[v] == 2 * K) {
//       // notDelete = true;
//       for (int j = v - K < 0 ? 0 : v - K; j < (v + K + 1 > N ? N : v + K +
//       1);
//            j++) {
//         test2(items, links[j], K, N, links, deleted);
//         // test(items, groupsDone, erased, links, deleted, links[j], K, N,
//         // sVykem);
//       }
//     }
//   }
//   if (!notDelete) {
//     items[i].erased = true;
//     erased++;
//   }
//   items[i].done = true;
//   return false;
// }

set<pair<int, int>> search(struct Node *root, int nodeName = -1) {
  set<pair<int, int>> found;
  bool noChildren = true;
  for (int i = 0; i < TREE_SIZE; i++) {
    if (root->children[i] != NULL) {
      noChildren = false;
      set<pair<int, int>> toAdd = search(root->children[i], i);
      found.insert(toAdd.begin(), toAdd.end());
    }
  }
  if (found.size() == 0)
    found.insert(make_pair(nodeName, root->inRange));
  else if (nodeName == -1) {
  } else {
    int vyko = found.rbegin()->second;
    found.erase(--found.end());
    found.insert(make_pair(nodeName, vyko));
  }
  // for (pair<int, int> p : found)
  //   cout << "(" << p.first << ", " << p.second << ")"
  //        << "; ";
  // cout << endl;
  return found;
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
    items[i] = Item{i, m, v, vector<int>(), false};
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
  vector<int> links(N);
  for (int i = 0; i < items.size(); i++)
    links[items[i].i] = i;
  struct Node *root = getNode();
  for (int i : sVykem) {
    set<int> positions;
    for (int j = i - K < 0 ? 0 : i - K; j < (i + K + 1 > N ? N : i + K + 1);
         j++) {
      positions.insert(links[j]);
    }
    insert(root, positions, i);
  }
  set<pair<int, int>> el = search(root);
  ll weight = 0;
  for (pair<int, int> res : el)
    weight += items[res.first].m;
  cout << weight << endl;
  for (pair<int, int> res : el)
    cout << res.second + 1 << " " << items[res.first].i + 1 << endl;
  return 0;
  // map<int, int> result;
  // ll weight = 0;
  // for (Item it : items)
  //   cout << it.i << endl;
  // for (int i = 0; i < N; i++) {
  //   // cout << "== " << items[i].i << " ==" << endl;
  //   vector<pair<set<int>, int>> toCompare;
  //   for (int v : items[i].sVykem) {
  //     if (result.find(v + 1) != result.end())
  //       continue;
  //     set<int> first;
  //     for (int j = v - K < 0 ? 0 : v - K; j < (v + K + 1 > N ? N : v + K +
  //     1);
  //          j++)
  //       if (!items[links[j]].done)
  //         first.insert(links[j]);
  //
  //     toCompare.push_back(make_pair(first, v));
  //   }
  //   items[i].done = true;
  //   if (toCompare.size() == 0)
  //     continue;
  //   sort(toCompare.begin(), toCompare.end(), compare4);
  //   result[toCompare[0].second + 1] = items[i].i + 1;
  //   // for (int n : toCompare[0].first)
  //   //   cout << n << " ";
  //   // cout << endl;
  //   weight += items[i].m;
  // }
  //
  // cout << weight << endl;
  // for (auto it : result)
  //   cout << it.first << " " << it.second << endl;
  // map<int, int> deleted;
  // for (int i = 0; i < K; i++) {
  //   deleted[i] = K - i;
  //   deleted[N - 1 - i] = K - i;
  // }
  // int erased = 0;
  // int groupsDone = 0;
  // for (int i = items.size() - 1; i >= 0; i--) {
  //   cout << "  " << items[i].i << endl;
  //   if (test(items, groupsDone, erased, links, deleted, i, K, N, sVykem))
  //     break;
  // }
  // for (int i = items.size() - 1; i >= 0; i--) {
  //   if (items[i].done)
  //     continue;
  //   if (items.size() - erased == sVykem.size() - groupsDone)
  //     break;
  //   bool notDelete = false;
  //
  //   for (int v : items[i].sVykem) {
  //     if (deleted[v] == 2 * K) {
  //       groupsDone++;
  //       deleted[v]++;
  //       erased++;
  //       continue;
  //     }
  //     deleted[v]++;
  //     if (deleted[v] == 2 * K) {
  //       for (int j = v - K < 0 ? 0 : v - K; j < (v + K + 1 > N ? N : v + K +
  //       1);
  //            j++) {
  //         if (!items[links[j]].done) {
  //           for (int vv : items[links[j]].sVykem) {
  //             deleted[vv]++;
  //             if (deleted[vv] == 2 * K + 1) {
  //               groupsDone++;
  //             };
  //           }
  //           items[links[j]].done = true;
  //           erased++;
  //         }
  //       }
  //     }
  //   }
  //   if (!notDelete) {
  //     items[i].erased = true;
  //     erased++;
  //   }
  //   items[i].done = true;
  // }

  // map<int, int> captured;
  // map<int, int> res;
  // for (Item it : items)
  //   if (!it.erased)
  //     for (int v : it.sVykem)
  //       captured[v]++;
  // ll weight = 0;
  // for (Item it : items)
  //   if (!it.erased)
  //     weight += it.m;
  // sort(items.begin(), items.end(), compare2);
  // bool findWithout = false;
  // bool findWith = false;
  // int i = 0;
  // for (Item it : items) {
  //   if (findWith) {
  //     if (it.i - i > K) {
  //       findWith = false;
  //       continue;
  //     }
  //     if (it.v) {
  //       res[it.i + 1] = i + 1;
  //       i = it.i;
  //       if (it.erased)
  //         findWith = false;
  //     }
  //   } else if (findWithout) {
  //     if (it.i - i > K) {
  //       findWithout = false;
  //       continue;
  //     }
  //     if (!it.erased) {
  //       res[i + 1] = it.i + 1;
  //       i = it.i;
  //       if (!it.v) {
  //         findWithout = false;
  //       }
  //     }
  //   } else {
  //     if (it.erased && it.v) {
  //       i = it.i;
  //       findWithout = true;
  //     } else if (!it.erased && !it.v) {
  //       i = it.i;
  //       findWith = true;
  //     }
  //     // else if (it.v)
  //     //   res[it.i + 1] = it.i + 1;
  //   }
  // }
  // for (int i : sVykem)
  //   if (res.find(i + 1) == res.end())
  //     res[i + 1] = i + 1;

  // while (true) {
  //   sort(items.begin(), items.end(), compare3);
  //   if (items[0].v)
  //     break;
  //   int best = -1;
  //   for (int v : items[0].sVykem) {
  //     if (best == -1 || captured[best] < 1 || captured[v] < captured[best])
  //       best = v;
  //     captured[v]--;
  //   }
  //   res[best + 1] = items[0].i + 1;
  //   for (int i = 0; i < items.size(); i++)
  //     if (items[i].i == best)
  //       items[i].v = false;
  //   items.erase(items.begin());
  // }

  // sort(items.begin(), items.end(), compare);
  // vector<int> links = vector<int>(N);
  // for (int i = 0; i < N; ++i)
  //   links[items[i].i] = i;
  //
  // vector<pair<int, int>> res;
  // int weight = 0;
  //
  // while (true) {
  //   map<vector<int>, int> groups;
  //   int withoutGroup = 0;
  //   for (Item it : items) {
  //     if (it.sVykem.size() == 0 || it.used) {
  //       withoutGroup++;
  //       continue;
  //     }
  //     groups[it.sVykem]++;
  //     if (groups[it.sVykem] == it.sVykem.size()) {
  //       int cur = it.sVykem[0];
  //       for (int i = cur - K < 0 ? 0 : cur - K;
  //            i < (cur + K + 1 > N ? N : cur + K + 1); i++) {
  //         auto itt = find(items[links[i]].sVykem.begin(),
  //                         items[links[i]].sVykem.end(), cur);
  //         if (itt != items[links[i]].sVykem.end())
  //           items[links[i]].sVykem.erase(itt);
  //       }
  //       res.push_back(make_pair(cur + 1, it.i + 1));
  //       weight += it.m;
  //       items[links[it.i]].used = true;
  //       break;
  //     }
  //   }
  //   if (withoutGroup == items.size())
  //     break;
  // }
  // cout << res.size() << " " << sVykem.size() << endl;
  //
  //
  // cout << weight << endl;
  // for (auto i : res)
  //   cout << i.first << " " << i.second << endl;
}
