#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
int n,m,q,a[N],a2[N],b[N],c0[N],c1[N],c2[N];
void build(int t,int k)
{
    if(b[t]>=c2[t]-c1[t]+1)
    {
        b[t]=min(b[t]+k,n);
        return;
    }
    b[t]=min(b[t]+k,n);
    for(int i=c1[t];i<=c2[t];++i)
    {
        int x=max(a[i]-b[t],1);
        if(i==1) x=0;
        if(x<c1[t]) a2[i]=x;
        else a2[i]=a2[x];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    q=sqrt(n);
    for(int i=1;i<=q;++i)
    {
        c1[i]=c2[i-1]+1,c2[i]=c2[i-1]+n/q;
        if(i==q) c2[i]=n;
        for(int j=c1[i];j<=c2[i];++j) c0[j]=i;
        build(i,0);
    }
    int las=0;
    for(int ii=1;ii<=m;++ii)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            l^=las,r^=las,k^=las;
            if(c0[l]==c0[r])
            {
                for(int i=l;i<=r;++i) a[i]=max(a[i]-k,1);
                build(c0[l],0);
                continue;
            }
            for(int i=l;i<=c2[c0[l]];++i) a[i]=max(a[i]-k,1);
            build(c0[l],0);
            for(int i=c1[c0[r]];i<=r;++i) a[i]=max(a[i]-k,1);
            build(c0[r],0);
            for(int i=c0[l]+1;i<=c0[r]-1;++i) build(i,k);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x^=las,y^=las;
            while(x!=y)
            {
                int tx=max(a[x]-b[c0[x]],1),ty=max(a[y]-b[c0[y]],1);
                if(x==1) tx=0;
                if(y==1) ty=0;
                a2[x]=min(a2[x],tx),a2[y]=min(a2[y],ty);
                if(a2[x]!=a2[y])
                {
                    if(a2[x]>a2[y]) x=a2[x];
                    else y=a2[y];
                }
                else if(tx>ty) x=tx;
                else y=ty;
            }
            printf("%d\n",las=x);
        }
    }
    return 0;
}