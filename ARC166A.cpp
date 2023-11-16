#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
char a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s%s",&n,a+1,b+1);
        int w1=0,w2=0,w3=0;
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(b[i]=='C')
            {
                if(a[i]!='C') u=false;
                if(w1>0) u=false;
                w1=w2=w3=0;
            }
            else
            {
                if(a[i]=='A') ++w1;
                else if(a[i]=='B') ++w2;
                else ++w3;
                if(b[i]=='A') --w1;
                else --w2;
                if(w2>0) u=false;
            }
        }
        if(w1>0||w2>0) u=false;
        w1=w2=w3=0;
        for(int i=n;i>=1;--i)
        {
            if(b[i]=='C')
            {
                if(a[i]!='C') u=false;
                if(w1>0) u=false;
                w1=w2=w3=0;
            }
            else
            {
                if(a[i]=='B') ++w1;
                else if(a[i]=='A') ++w2;
                else ++w3;
                if(b[i]=='B') --w1;
                else --w2;
                if(w2>0) u=false;
            }
        }
        if(u==false||w1>0||w2>0) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}
