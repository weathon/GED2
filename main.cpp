#include "tree.hpp"
#include <iostream>

using namespace std;

int N = 200;
int main() {
  init();
  BallTreeNode rootNewBT;
  vector<dataPoint> Objects;
  Objects.resize(N);
  for (int i = 0; i < N; i++) {
    Objects[i].id = i;
  }
  cout << "start" << endl;
  auto start = chrono::high_resolution_clock::now();
  ConstructBallTree(&rootNewBT, Objects);
  auto end = chrono::high_resolution_clock::now();
  cout << "C++ Tree Build Time: "
       << chrono::duration_cast<chrono::duration<double>>(end - start).count()
       << endl;
  // https://cplusplus.com/reference/chrono/high_resolution_clock/now/

  vector<dataPoint> ans;
  int count = 0;

  for (int _ = 0; _ <= 30; _++) {
    start = chrono::high_resolution_clock::now();
    ans.clear(); VerSearchRadius(&rootNewBT, Objects[0], _, ans);
    end = chrono::high_resolution_clock::now();
    cout << "Tree ans: " << ans.size() << endl;
    cout << "Tree time: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << endl;

    start = chrono::high_resolution_clock::now();
    count = 0;
    for (auto i : Objects) {
      if (d(Objects[0], i) <= _) {
        count += 1;
      }
    }
    end = chrono::high_resolution_clock::now();
  
    cout << "BF ans: " << count << endl;
    cout << "BF time: " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << endl;

    if(count!=ans.size())
    {
        cout<<"OOBA"<<endl;
        exit(1);
    }
  }

  return 0;
}