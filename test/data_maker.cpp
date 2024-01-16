#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=1e5;
    printf("%d\n",n);
    auto a=rnd_range(n);
    for(auto i:a) printf("%d ",i);
    return 0;
}