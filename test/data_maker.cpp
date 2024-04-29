#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,1);
    cout<<T<<"\n";
    while(T--)
    {
        int n=rnd(5e5,5e5),m=rnd(5,5);
        cout<<n<<" "<<m<<"\n";
        auto a=rnd_range(n);
        for(auto i:a) cout<<i<<" ";
        cout<<"\n";
    }
    return 0;
}