#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int T=rnd(1,10);
    cout<<T<<"\n";
    while(T--)
    {
        int n=rnd(1,100);
        cout<<n<<"\n";
        for(int i=1;i<=n;++i) cout<<rnd(-1e9,1e9)<<" ";
        cout<<"\n";
    }
    return 0;
}