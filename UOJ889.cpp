#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N=2000001;
int n,m,q,t,f[11][N];
char a[N],b[11][N];
struct sgt
{
    int sa[N],rk[N],he[N],h[N],x1[N],x2[N],pa[N],pb[11][N];
    void init_SA(int n,int *a)
    {
        int m=n+128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
    int b[N][31],lg[N];
    void init_ST(int n)
    {
        for(int i=1;i<=n;++i) b[i][0]=he[i];
        for(int i=1;i<=30;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=30;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        x=rk[x],y=rk[y];
        if(x>y) swap(x,y);
        ++x;
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
    int sum(int x1,int y1,int x2,int y2)
    {
        return sum((x1?pb[x1]:pa)[y1],(x2?pb[x2]:pa)[y2]);
    }
}T1,T2;
namespace Sub1
{
    void main()
    {
        for(int i=1;i<=q;++i)
        {
            int x,y,p;
            scanf("%d%d%d",&x,&y,&p);
            int w=T1.sum(0,p,x,y);
            if(x==n)
            {
                printf("%d\n",w);
                continue;
            }
            if(w!=0) w+=T1.sum(0,p+w,x+1,y+w-1);
            printf("%d\n",w);
        }
    }
}
namespace Sub2
{
    set<int> Set;
    bool check(int y,int p,int w)
    {
        if(w<=2) return false;
        int w1=T1.sum(0,p,1,y),w2=T2.sum(0,p+w-1,3,y+w-3);
        if(w1==0||w2==0) return false;
        if(w1+w2>=w)
        {
            if(*Set.lower_bound(max((y+w-3)-w2+1,y))<=y+w1-2) return true;
            if(b[2][y+w1-1]==a[p+w1]) return true;
            return false;
        }
        else
        {
            if(T1.sum(0,p+w1,2,y+w1-1)>=w-w1-w2) return true;
            return false;
        }
    }
    void main()
    {
        for(int i=1;i<=m-1;++i)
        {
            if(b[2][i]==b[1][i+1]) Set.insert(i);
        }
        for(int i=1;i<=q;++i)
        {
            int x,y,p;
            scanf("%d%d%d",&x,&y,&p);
            int w=T1.sum(0,p,x,y);
            if(x==3)
            {
                printf("%d\n",w);
                continue;
            }
            if(w!=0) w+=T1.sum(0,p+w,x+1,y+w-1);
            if(x==2)
            {
                printf("%d\n",w);
                continue;
            }
            int l=w+1,r=min(t-p+1,m-y+3);
            while(l<r)
            {
                int z=l+r+1>>1;
                if(check(y,p,z)) l=z;
                else r=z-1;
            }
            while(l>w&&!check(y,p,l)) --l;
            printf("%d\n",l);
        }
    }
}
int main()
{
    scanf("%d%d%d%d",&t,&n,&m,&q);
    scanf("%s",a+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",b[i]+1);
    }
    {
        static int z[N];
        int p=0;
        for(int i=1;i<=t;++i) z[T1.pa[i]=++p]=a[i];
        z[++p]=128;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j) z[T1.pb[i][j]=++p]=b[i][j];
            z[++p]=i+128;
        }
        T1.init_SA(p,z);
        T1.init_ST(p);
    }
    {
        static int z[N];
        int p=0;
        for(int i=t;i>=1;--i) z[T2.pa[i]=++p]=a[i];
        z[++p]=128;
        for(int i=1;i<=n;++i)
        {
            for(int j=m;j>=1;--j) z[T2.pb[i][j]=++p]=b[i][j];
            z[++p]=i+128;
        }
        T2.init_SA(p,z);
        T2.init_ST(p);
    }
    if(n<=2)
    {
        Sub1::main();
        return 0;
    }
    if(n==3)
    {
        Sub2::main();
        return 0;
    }
    for(int i=1;i<=q;++i)
    {
        int x,y,p;
        scanf("%d%d%d",&x,&y,&p);
        for(int j=0;j<=n;++j) for(int k=0;k<=m;++k) f[j][k]=-1e9;
        if(a[p]==b[x][y]) f[x][y]=1;
        int s=0;
        for(int j=x;j<=n;++j)
        {
            for(int k=y;k<=m;++k)
            {
                if(p+(j-x)+(k-y)>t) break;
                if(a[p+(j-x)+(k-y)]==b[j][k]) f[j][k]=max(f[j][k],max(f[j-1][k],f[j][k-1])+1);
                s=max(s,f[j][k]);
            }
        }
        printf("%d\n",s);
    }
    return 0;
}