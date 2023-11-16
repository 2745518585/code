#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i) b[i]=1;
        b[0]=b[m+1]=0;
        int s1=0,s2=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(a[i]==-1) ++s1;
            else if(a[i]==-2) ++s2;
            else b[a[i]]=0;
        }
        for(int i=1;i<=m;++i) b[i]+=b[i-1];
        int s=0;
        for(int i=1;i<=m;++i)
        {
            if(b[i]-b[i-1]!=0) continue;
            s=max(s,min(b[i-1],s1)+min(b[m]-b[i],s2));
        }
        s=max(s,min(b[m],s1));
        s=max(s,min(b[m],s2));
        printf("%d\n",s+(m-b[m]));
    }
    return 0;
}