#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1e5,1e5),m=rnd(1e5,1e5),q=rnd(1e5,1e5);
    cout<<n<<"\n";
    for(int i=1;i<=n;++i)
    {
        cout<<(rnd(0,1)?rnd('a','z'):rnd('A','Z'));
    }
    cout<<"\n";
    cout<<m<<"\n";
    for(int i=1;i<=m;++i)
    {
        cout<<rnd(1,n)<<" ";
    }
    cout<<"\n";
    cout<<q<<"\n";
    for(int i=1;i<=q;++i)
    {
        cout<<rnd(1,n)<<" "<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    return 0;
}