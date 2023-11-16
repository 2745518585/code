#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
struct str
{
    int l,r,h,t;
}a[N];
struct tree
{
    int l,r,s1,s2;
}T[N<<2];
bool cmp(str a,str b)
{
    return a.l<b.l;
}
bool cmp2(str a,str b)
{
    return a.t<b.t;
}
void pushup(int x)
{
    T[x].s1=(a[T[x<<1].s1].r>a[T[x<<1|1].s1].r?T[x<<1].s1:T[x<<1|1].s1);
    T[x].s2=(a[T[x<<1].s2].r>a[T[x<<1|1].s2].r?T[x<<1].s2:T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s1=T[x].s2=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        T[x].s1=T[x].s2=0;
        if(a[q].h==0) T[x].s1=T[x].s2=q;
        else if(a[q].h==1) T[x].s1=q;
        else if(a[q].h==2) T[x].s2=q;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
int main()
{
    int Q;
    scanf("%d",&Q);
    while(Q--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            int x1,x2;
            scanf("%d%d%d%d",&x1,&a[i].l,&x2,&a[i].r);
            if(x1==1&&x2==2) a[i].h=0; 
            if(x1==1&&x2==1) a[i].h=1;
            if(x1==2&&x2==2) a[i].h=2;
            a[i].t=i;
        }
        sort(a+1,a+n+1,cmp);
        build(1,1,n);
        int x1=0,x2=0;
        for(int i=1;i<=n;++i)
        {
            x1=T[1].s1,x2=T[1].s2;
            if(a[i].h==0)
            {
                if(a[x1].r>=a[i].r) a[i].h=2;
                else if(a[x2].r>=a[i].r) a[i].h=1;
                else
                {
                    while(a[x1].r>=a[i].l)
                    {
                        a[x1].r=a[i].l-1;
                        add(1,x1);
                        x1=T[1].s1;
                    }
                    while(a[x2].r>=a[i].l)
                    {
                        a[x2].r=a[i].l-1;
                        add(1,x2);
                        x2=T[1].s2;
                    }
                    add(1,i);
                }
            }
            if(a[i].h==1)
            {
                if(a[x1].r>=a[i].l) a[i].l=a[x1].r+1;
                add(1,i);
            }
            if(a[i].h==2)
            {
                if(a[x2].r>=a[i].l) a[i].l=a[x2].r+1;
                add(1,i);
            }
        }
        sort(a+1,a+n+1,cmp2);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i].l<=a[i].r) s+=(a[i].r-a[i].l+1)*((a[i].h==0)+1);
        }
        printf("%d\n",s);
        for(int i=1;i<=n;++i)
        {
            if(a[i].l>a[i].r) printf("0 0 0 0\n");
            else
            {
                if(a[i].h==0) printf("1 %d 2 %d\n",a[i].l,a[i].r);
                if(a[i].h==1) printf("1 %d 1 %d\n",a[i].l,a[i].r);
                if(a[i].h==2) printf("2 %d 2 %d\n",a[i].l,a[i].r);
            }
        }
    }
    return 0;
}