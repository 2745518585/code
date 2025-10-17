#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
bool h[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n+1;++i) a[i]=-1,h[i]=false;
        int u=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            h[a[i]]=true;
            if(a[i]==0) ++u;
        }
        int p1=1,p2=n;
        while(a[p1]==p1) ++p1;
        while(a[p2]==p2) --p2;
        if(u==1)
        {
            if(a[p1]==0&&!h[p1]) ++p1;
            if(a[p2]==0&&!h[p2]) --p2;
            while(a[p1]==p1) ++p1;
            while(a[p2]==p2) --p2;
        }
        if(p1<p2) printf("%d\n",p2-p1+1); 
        else printf("0\n");
    }
    return 0;
}