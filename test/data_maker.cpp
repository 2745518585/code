#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int n=rnd(1,4000),m=rnd(1,4000);
    cout<<n<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,2)<<" ";cout<<"\n";
    cout<<m<<"\n";
    for(int i=1;i<=m;++i)
    {
        if(rnd(0,1)) cout<<"1 "<<rnd_pair<_LOE>(1,n)<<"\n";
        else cout<<"2 "<<rnd(1,n)<<" "<<rnd(1,2)<<"\n";
    }
    return 0;
}