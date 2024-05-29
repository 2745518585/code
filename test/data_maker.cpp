#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(0,7),m=0;
    for(int i=0;i<=n;++i) {int z=i?rnd(0,1):1;m+=z,cout<<z;} cout<<"\n";
    for(int i=0;i<=n;++i) {int z=rnd(0,1);m+=z,cout<<z;} cout<<"\n";
    cout<<rnd(1,m);
    return 0;
}