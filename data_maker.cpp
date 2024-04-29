#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
typedef long long ll;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,5);
    cout<<n<<"\n";
    auto a=rnd_range(n*3);
    for(auto i:a) cout<<(i-1)%n+1<<" ";
    cout<<"\n";
    a=rnd_range(n*3);
    for(auto i:a) cout<<(i-1)%n+1<<" ";
    return 0;
}