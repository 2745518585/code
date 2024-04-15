#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=rnd(1,10),m=rnd(1,10);
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=n;++i) cout<<rnd(1,10)<<" ";
    cout<<"\n";
    for(int i=1;i<=m;++i)
    {
        int z=rnd(1,3);
        if(z==1) cout<<"1 "<<rnd(1,10)<<"\n";
        else if(z==2) cout<<"2\n";
        else if(z==3) cout<<"3 "<<rnd_pair<_LOE>(1,n)<<"\n";
    }
    return 0;
}