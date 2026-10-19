#include "testlib.h"
#include <set>
#include <string>
int main(int argc,char **argv) {
 registerValidation(argc,argv);

 inf.readInt(1,1000000000,"K"); inf.readEoln();
 inf.readToken("[a-zA-Z0-9]{1,100000}","S"); inf.readEoln();
 inf.readEof();
}
