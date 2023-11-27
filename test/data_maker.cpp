#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    cout<<rnd_pair(1,10,[&](auto x1,auto x2){return x1<x2;})<<"\n";
    cout<<rnd_pair<_LES>(1,10)<<"\n";
    cout<<rnd_pair<std::less>(1,1e5)<<"\n";
    cout<<rnd_pair<std::less<int>>(1,1e5)<<"\n";
    cout<<rnd_pair<_LES>(rdl<int,int>(1,10))<<"\n";
    cout<<rnd_pair<_LES>([&](){return rnd(1,10);})<<"\n";
    // cout<<rnd_pair<std::less>(rdl(1,10),rdl(1,1e5))<<"\n";
    cout<<rnd_pair<_LES>(rdl<int,int>(1,10),rdl<int,int>(1,1e5))<<"\n";
    return 0;
}