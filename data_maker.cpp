#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
typedef long long ll;
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    int n=3e5,m=5e5,q=1e6;
    printf("%d\n",n);
    for(int i=1;i<=n-1;++i) printf("%d %d %d\n",i,i+1,1);
    printf("%d\n",m);
    for(int i=1;i<=m;++i) printf("%d ",rnd(1,n));
    printf("%d\n",q);
    for(int i=1;i<=q;++i) cout<<rnd_pair<_LOE>(1,n)<<"\n";
    return 0;
}