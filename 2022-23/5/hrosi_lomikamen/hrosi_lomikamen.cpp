#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
  int N, M;
  cin >> N >> M;
  string sN, sM;
  cin >> sN >> sM;
  int A = 0, B, C, D;
  for (int i = -N + 1; i < M; i++) {
    int startN, startM;
    if (i < 0)
      startN = -i, startM = 0;
    else
      startN = 0, startM = i;
    int bestA = 0, bestst = 0, bestend, cur = 0, k = 0, startcur = 0;
    for (int j = 0; j + startN < N && j + startM < M; j++) {
      if (sN[j + startN] == sM[j + startM]) {
        if (cur < 0) {
          if (k < 0) {
            bestst = startcur;
            k = 0;
          }
          k += cur;
          if (bestA < k) {
            bestend = j + startN;
            bestA = k;
          }
          cur = -1;
          startcur = j + 1;
        } else
          cur++;
      }
      if (sN[j + startN] != sM[j + startM]) {
        if (cur <= 0) {
          cur--;
        } else {
          if (k < 0) {
            bestst = startcur;
            k = 0;
          }
          k += cur;
          if (bestA < k) {
            bestend = j + startN;
            bestA = k;
          }
          cur = 1;
          startcur = j + 1;
        }
      }
    }
    cout << bestA << " " << i << endl;
    if (bestA > A)
      A = bestA, B = i, C = bestst, D = bestend;
  }
  cout << A << " " << B << " " << C << " " << D << endl;
  return 0;
}
