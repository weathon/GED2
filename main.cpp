#define DATASET_NAME "PubChem15.txt"
#define  N 4000
#include "tree.hpp"
#include <iostream>

using namespace std;


int main() {
  init();
  BallTreeNode rootNewBT;
  vector<dataPoint> Objects;
  Objects.resize(N);
  for (int i = 0; i < N; i++) {
    Objects[i].id = i;
  }
  cout << "Read data complete" << endl;
  auto start = chrono::high_resolution_clock::now();
  ConstructBallTree(&rootNewBT, Objects);
  auto end = chrono::high_resolution_clock::now();
  cout << "C++ Tree Build Time: "
       << chrono::duration_cast<chrono::duration<double>>(end - start).count()
       << endl;
  // https://cplusplus.com/reference/chrono/high_resolution_clock/now/

  vector<dataPoint> ans;
  int count = 0;
  int BF;
  printf("r, dataset, N, VTree Time, Baseline Time");
  for (int _ = 0; _ <= 10; _++) {
    cout << _ << ",";
    cout << DATASET_NAME << ",";
    cout << N << ",";
    // start = chrono::high_resolution_clock::now();
    // ans.clear();
    // BaselineSearchRadius(&rootNewBT, Objects[_], 3, ans);
    // end = chrono::high_resolution_clock::now();
    // cout << "ETree ans: " << ans.size() << endl;
    // cout << "ETree time: "
    //      << chrono::duration_cast<chrono::duration<double>>(end -
    //      start).count()
    //      << endl;

    start = chrono::high_resolution_clock::now();
    ans.clear();
    VerSearchRadius(&rootNewBT, Objects[20], _, ans);
    end = chrono::high_resolution_clock::now();
    // cout << "VTree ans: " << ans.size() << endl;
    cout << chrono::duration_cast<chrono::duration<double>>(end - start).count()
         << ",";

    // start = chrono::high_resolution_clock::now();
    // count = 0;
    // for (auto i : Objects) {
    //   if (d(Objects[20], i) <= _) {
    //     count += 1;
    //   }
    // }
    // end = chrono::high_resolution_clock::now();
    // BF = count;
    // cout << "BF ans: " << count << endl;
    // cout << "BF time: "
    //      << chrono::duration_cast<chrono::duration<double>>(end -
    //      start).count()
    //      << endl;

    start = chrono::high_resolution_clock::now();
    count = 0;
    for (auto i : Objects) {
      // cout<<baselibe_query(i.id, 0, _)<<endl;
      if (baselibe_query(i.id, 20, _)) {
        count += 1;
      }
    }
    end = chrono::high_resolution_clock::now();

    // cout << "Baseline ans: " << count << endl;
    // cout << "Baseline time: "
    cout << chrono::duration_cast<chrono::duration<double>>(end - start).count()
         << "," << endl;
    ;

    if (BF != ans.size()) {
      cout << "OOBA" << endl;
      exit(1);
    }
  }

  return 0;
}