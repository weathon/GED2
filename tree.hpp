#include "multiple_ver/main.cpp"
#include "progress.cpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <hashtable.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<float> floatArray;

#define ifNULL(x) if (x == NULL)
// #define print(x) cout << x << endl;
#define print(x, y) cout << x << " " << y << endl;

#define INNER_CONSTANT 5;
struct dataPoint {
  floatArray data;
  int id;
  // string ancestorsDistancesList;
  floatArray ancestorsDistancesList;
  float distanceFromDad;
  float max = 0;
  float min = 0;
  floatArray fars = {};
  floatArray nears = {};
};

struct BallTreeNode {
  dataPoint myobject;
  BallTreeNode *left;
  BallTreeNode *right;
  float inner = 0;
  float outer = 0;
  int count = 0;
};

long long Callcount;
float d(dataPoint a, dataPoint b) { return query(a.id, b.id); }

bool cmp(dataPoint list1, dataPoint list2) {
  // by copolit
  return list1.distanceFromDad < list2.distanceFromDad;
}

void getData(vector<dataPoint> myArray, float &theMax, float &theMin,
             float &inner, float &outer) {
  sort(myArray.begin(), myArray.end(), cmp);
  //   if(myArray.size()<2)
  //   {
  //         cout<<"FUCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~"<<endl;
  //         //Ha found ya! exit(1);
  //   }
  if (myArray.size() < 2) {
    theMax = myArray[myArray.size() - 1].distanceFromDad;
    theMin = myArray[0].distanceFromDad;
    inner = myArray[myArray.size() / 2].distanceFromDad;
    outer = myArray[myArray.size() / 2].distanceFromDad;
  } else {
    theMax = myArray[myArray.size() - 1].distanceFromDad;
    theMin = myArray[0].distanceFromDad;
    inner = myArray[myArray.size() / 2 - 1].distanceFromDad;
    outer = myArray[myArray.size() / 2].distanceFromDad;
  }
  // cout<<"min"<<theMin<<endl;
}

int done = 0;
void ConstructBallTree(BallTreeNode *BT, vector<dataPoint> localobjetcs) {
  // cout<<localobjetcs[0].ancestorsDistancesList.size()<<endl;
  ifNULL(BT) {
    cout << "Error: Null pointer; line 119" << endl;
    return;
  }
  if (localobjetcs.size() == 0) {
    cout << "where is this" << endl;
    return;
  }
  if (localobjetcs.size() == 1) {
    BT->myobject = localobjetcs.at(0);
    BT->inner = 0;
    BT->outer = 0;
    BT->count = 1;
    BT->left = 0;
    BT->right = 0;
    return;
  }

  int selectedIndex = rand() % localobjetcs.size();
  swap(localobjetcs[localobjetcs.size() - 1], localobjetcs[selectedIndex]);
  BT->myobject = localobjetcs.at(localobjetcs.size() - 1);

  localobjetcs.pop_back();

  for (int i = 0; i < localobjetcs.size(); i++) {
    printProgressBar(done, N*log2(N));
    done++;
    localobjetcs[i].distanceFromDad = d((BT->myobject), localobjetcs[i]);
    if (localobjetcs[i].distanceFromDad < 0) {
      cout
          << "FUCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~"
          << endl; // jiashangzhege ji buucochucuole xkou
                   // xkouxkouhaishitongkouke shouzhi haishiemeibaocunzaochendge
      exit(1);
    }
    localobjetcs[i].ancestorsDistancesList.push_back(
        localobjetcs[i].distanceFromDad);
  }
  float a;
  getData(localobjetcs, BT->myobject.max, BT->myobject.min, BT->inner,
          BT->outer);
  vector<dataPoint> L;
  vector<dataPoint> R;

  for (int i = 0; i < localobjetcs.size(); i++) {
    if (localobjetcs[i].distanceFromDad <= BT->inner) {
      L.push_back(localobjetcs[i]);
    } else if (localobjetcs[i].distanceFromDad >= BT->outer) {
      R.push_back(localobjetcs[i]);
    } else {
      cout << "I think I am lost, can someone help me?" << endl;
    }
  }
  BT->count = localobjetcs.size();
  if (L.size() != 0) {
    BallTreeNode *tmp = new BallTreeNode;
    ifNULL(tmp) {
      cout << "Error: Null pointer; line 181" << endl;
      return;
    }
    ConstructBallTree(tmp, L);
    BT->left = tmp;
  } else {
    // forgot this
    BT->left = NULL;
  }
  if (R.size() != 0) {
    BallTreeNode *tmp2 = new BallTreeNode;
    ifNULL(tmp2) {
      cout << "Error: Null pointer; line 194" << endl;
      return;
    }
    ConstructBallTree(tmp2, R);
    BT->right = tmp2;
  } else {
    BT->right = NULL;
  }
}

void BaselineSearchRadius(BallTreeNode *BT, dataPoint ObjectQ, float r,
                          vector<dataPoint> &returnObjects) {
  ifNULL(BT) { return; }
  float dis = d(BT->myobject, ObjectQ);
  if (dis <= r) {
    returnObjects.push_back(BT->myobject);
  }

  if (dis > BT->myobject.max) {
    if (dis - BT->myobject.max > r) {
      return;
    }
  }

  if (dis < BT->myobject.min) {
    if (BT->myobject.min - dis > r) {
      return;
    }
  }

  if (dis + r >= BT->outer) {
    BaselineSearchRadius(BT->right, ObjectQ, r,
                         returnObjects); // this should be right copilot!!
  }
  if (dis - r <= BT->inner) {
    BaselineSearchRadius(BT->left, ObjectQ, r, returnObjects);
  }
}

void VerSearchRadius(BallTreeNode *BT, dataPoint ObjectQ, ui r,
                     vector<dataPoint> &returnObjects) {
  ifNULL(BT) { return; }
  // float dis = d(BT->myobject, ObjectQ);
  float s = BT->outer - r - 1;
  if (s < 0)
    s = 0;
  // ui t[] = {r + 1, s, BT->inner + r + 1};
  //   for (int i = 0; i < 3; i++) {
  //     cout << t[i] << " ";
  // }
  // cout<<endl;
  //   cout << r + 1 << " " << s << " " << BT->inner + r + 1
  //    << endl; // BT->inner is huge negative???
  // trio res = verify(BT->myobject.id, ObjectQ.id, t);

  // if (dis <= r) nonono this is r?=dis so the first is not rif(not dis>r)
  // if(not dis>=(r+1))
  // if (not res.a) {
  if (baselibe_query(ObjectQ.id, BT->myobject.id, r)) {
    returnObjects.push_back(BT->myobject);
  }

  //   if (dis + r >= BT->outer)  (dis >= BT->outer -r)  BT->outer -r <= dis not
  // BT->outer - r > dis   not BT->outer - r >= (dis+1)
  // if (res.b) // nongfanle buyong not uzo wanzhengdeyundekunyunex kk
  if(s<=0)
  {
        VerSearchRadius(BT->right, ObjectQ, r,
                    returnObjects); // this should be right copilot!!
  }
  else if(not baselibe_query(ObjectQ.id, BT->myobject.id, s)) 
  {
    VerSearchRadius(BT->right, ObjectQ, r,
                    returnObjects); // this should be right copilot!!
  }
  //   if (dis - r <= BT->inner)   BT->inner + r >= dis
  // if (not res.c) {
  // if (baselibe_query(ObjectQ.id, BT->myobject.id, BT->inner + r)) 
  {
    VerSearchRadius(BT->left, ObjectQ, r, returnObjects);
  }
}
