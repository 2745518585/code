#include<bits/stdc++.h>
#include"orita.hpp"
using namespace std;
using namespace orita;
int main(int argc,char **argv)
{
    register_all(argc,argv);
    int TOT=rnd(1,1);
    printf("%d\n",TOT);
    while(TOT--)
    {
        int n=rnd(1,10),m=rnd(1,10),q=rnd(1,10);
        printf("%d %d\n",n,m);
        int x=0;
        for(int i=1;i<=n;++i)
        {
            printf("%d ",x+=rnd(1,n/2));
        }
        printf("\n");
        printf("%d\n",q);
        for(int i=1;i<=q;++i)
        {
            cout<<rnd_pair<_LES>(1,n)<<"\n";
        }
    }
    return 0;
}