#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    auto [x,y]=rnd_pair<std::less>(1,10);
    cout<<x<<" "<<y<<"\n";
    return 0;
}