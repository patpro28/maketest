#include <array>
#include <cstdlib>
#include <iostream>
int main(int argc,char**argv){
    const std::array<std::array<int,4>,8> cases={{{0,4,2,7},{0,6,2,9},{0,4,4,10},{0,4,6,13},
                                               {1,4,4,7},{1,4,7,10},{0,270,135,7},{1,270,135,7}}};
    int seed=argc>1?std::atoi(argv[1]):0;
    auto x=cases.at(seed);
    std::cout<<x[0]<<' '<<x[1]<<' '<<x[2]<<' '<<x[3]<<'\n';
}
