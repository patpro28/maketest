#include "data.h"
int main(int argc,char**argv){
    int seed=argc>1?std::atoi(argv[1]):0;
    return generate(argc,argv,seed<7?0:4);
}
