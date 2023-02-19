#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

struct SubtreeInfo {
  int v;
  bool onlyManagers;
  bool opened;
};

pair<int, bool> count(vector<pair<int, bool>> graph[], map<int, char> &rooms,
                      int v) {
  int res = 0;
  for (auto it : graph[v - 1]) {
    auto child = count(graph, rooms, it.first);
    // cout << child.first << " " << child.second << " " << it.first << endl;
    // cout << rooms[it.first] << endl;
    res += child.first;
    if (!child.second && it.second)
      res++;
    else if (child.second && !it.second)
      res++;
  }
  if (graph[v - 1].size() == 0)
    return make_pair(0, rooms[v] == 'P');
  return make_pair(res, true);
}

bool removeEmpty(vector<pair<int, bool>> graph[], map<int, char> &rooms,
                 int v) {
  vector<pair<int, bool>> newSubtree;
  for (auto it = graph[v - 1].begin(); it != graph[v - 1].end(); ++it)
    if (!removeEmpty(graph, rooms, it->first))
      newSubtree.push_back(*it);
  graph[v - 1] = newSubtree;
  auto isEmpty = rooms.find(v);
  if ((isEmpty != rooms.end() && isEmpty->second == 'E') ||
      (isEmpty == rooms.end() && graph[v - 1].size() == 0))
    return true;
  return false;
}

pair<bool, bool> reduce(vector<pair<int, bool>> graph[], map<int, char> &rooms,
                        int v) {
  bool onlyManagers = true;
  bool opened = false;
  vector<SubtreeInfo> ress;
  for (auto it = graph[v - 1].begin(); it != graph[v - 1].end(); ++it) {
    pair<bool, bool> res = reduce(graph, rooms, (*it).first);
    // cout << it->first << " " << res.first << " " << res.second << endl;
    onlyManagers = onlyManagers && res.first;
    opened = opened || (res.second && (*it).second);
    ress.push_back(
        SubtreeInfo{(*it).first, res.first,
                    res.first ? res.second && (*it).second : it->second});
  }
  if (!onlyManagers || v == 1) {
    vector<pair<int, bool>> newSubtree;
    for (auto it = ress.begin(); it != ress.end(); ++it) {
      if (it->onlyManagers) {
        graph[it->v - 1] = vector<pair<int, bool>>();
        rooms[it->v] = it->onlyManagers ? 'M' : 'P';
      }
      newSubtree.push_back(make_pair(it->v, it->opened));
    }
    graph[v - 1] = newSubtree;
  }
  if (graph[v - 1].size() == 0) {
    return make_pair(rooms[v] == 'M', true);
  }
  return make_pair(onlyManagers, opened);
}

signed main() {
  int N, M;
  cin >> N >> M;
  vector<pair<int, bool>> graph[N];
  for (int i = 1; i < N; i++) {
    int u, v;
    char ch;
    cin >> u >> v >> ch;
    bool open = ch == 'O';
    graph[u - 1].push_back(make_pair(v, open));
  }
  map<int, char> rooms;
  for (int i = 0; i < M; i++) {
    int v;
    char ch;
    cin >> v >> ch;
    rooms[v] = ch;
  }
  removeEmpty(graph, rooms, 1);
  reduce(graph, rooms, 1);
  // for (int i = 0; i < N - 1; i++) {
  //   cout << i << " -";
  //   for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
  //     cout << " (" << it->first << " " << it->second << ")";
  //   }
  //   cout << endl;
  // }
  auto res = count(graph, rooms, 1);
  cout << res.first << endl;
  // for (auto it = rooms.begin(); it != rooms.end(); ++it) {
  //   cout << it->first << " " << it->second << endl;
  // }
}
