#include <iostream>
#include <vector>

using namespace std;

enum Light { O = 'O', F = '-', X = 'X' };

int main(int argc, char *argv[]) {
  char c;
  vector<char> lights;
  while (cin >> c)
    lights.push_back(c);
  for (int i = 0; i < lights.size(); i++)
    if (lights[i] == 'O')
      lights[i] = '-';
  for (int i = 0; i < lights.size(); i++)
    if (lights[i] == 'X') {
      lights[i + 1] = 'O';
      lights[i - 1] = 'O';
    }
  lights[0] = 'O';
  lights[lights.size() - 1] = 'O';
  int space = 0;
  for (int i = 0; i < lights.size(); i++) {
    if (lights[i] == 'O')
      space = 0;
    else {
      space++;
      if (space == 2) {
        space = 0;
        lights[i] = 'O';
      }
    }
  }
  for (char c : lights)
    cout << c;
  cout << endl;

  return 0;
}
