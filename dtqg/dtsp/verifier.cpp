#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
registerValidation(argc,argv);
inf.readInt(0,COUNT_MAX,"a");inf.readSpace();inf.readInt(0,COUNT_MAX,"b");inf.readSpace();inf.readInt(0,COUNT_MAX,"c");inf.readSpace();inf.readInt(1,S_MAX,"s");inf.readEoln();
inf.readEof();
}
