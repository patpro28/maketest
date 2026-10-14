#include <algorithm>
#include <set>
#include "testlib.h"
#include "params.h"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    inf.readInt(1,B_MAX,"B"); inf.readSpace(); inf.readInt(1,M_MAX,"M"); inf.readEoln();
    for(int i=0;i<10;++i) { if(i) inf.readSpace(); inf.readInt(1,C_MAX,"C"); } inf.readEoln();
    inf.readEof();
}
