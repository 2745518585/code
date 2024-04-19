#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,3),m=rnd(1,3);
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,3)<<" ";cout<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,3)<<" ";cout<<"\n";
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) cout<<rnd(1,3)<<" ";cout<<"\n";
    }
    for(int i=1;i<=m;++i)
    {
        cout<<rnd_pair<_LOE>(1,n)<<" "<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    return 0;
}