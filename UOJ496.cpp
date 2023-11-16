#include<cstdio>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int N=1000001;
int n,fa[N],l[N];
bool h[N];
struct str
{
    int l,r;
}a[N];
vector<pair<int,int>> e;
queue<int> Q;
map<pair<int,int>,int> Map;
pair<int,int> mp(int x,int y)
{
    return make_pair(min(x,y),max(x,y));
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d",&n);
    if(n==3)
    {
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;++i) a[i].l=i-1,a[i].r=i+1;
    a[1].l=n,a[n].r=1;
    for(int i=1;i<=n;++i)
    {
        Map[mp(i,a[i].r)]=0;
    }
    for(int i=1;i<=n-3;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        Map[mp(x,y)]=Map[mp(y,x)]=0;
        if(a[x].l==a[y].r) Q.push(a[x].l);
        else if(a[x].r==a[y].l) Q.push(a[x].r);
    }
    for(int p=1;p<=n-4;++p)
    {
        while(h[Q.front()]) Q.pop();
        int k=Q.front();
        Q.pop();
        h[k]=true;
        int z1=Map[mp(k,a[k].l)],z2=Map[mp(k,a[k].r)];
        if(z1==0&&z2==0)
        {
            Map[mp(a[k].l,a[k].r)]=k;
        }
        else if(z1!=0&&z2!=0)
        {
            e.push_back(mp(z1,k));
            e.push_back(mp(z2,k));
            Map[mp(k,a[k].l)]=Map[mp(k,a[k].r)]=0;
            Map[mp(a[k].l,a[k].r)]=k;
        }
        else if(z1!=0)
        {
            e.push_back(mp(k,a[k].l));
            e.push_back(mp(z1,a[k].l));
        }
        else if(z2!=0)
        {
            e.push_back(mp(k,a[k].r));
            e.push_back(mp(z2,a[k].r));
        }
        a[a[k].l].r=a[k].r;
        a[a[k].r].l=a[k].l;
        if(Map.count(mp(a[k].r,a[a[k].l].l))) Q.push(a[k].l);
        if(Map.count(mp(a[k].l,a[a[k].r].r))) Q.push(a[k].r);
    }
    while(h[Q.front()]) Q.pop();
    int x1=Q.front(),x2=a[x1].r,x3=a[x2].r,x4=a[x3].r;
    int z1=Map[mp(x1,x2)],z2=Map[mp(x2,x3)],z3=Map[mp(x3,x4)],z4=Map[mp(x4,x1)];
    // printf("%d %d %d %d\n",x1,x2,x3,x4);
    // printf("%d %d %d %d\n",z1,z2,z3,z4);
    for(int p=0;p<=(1<<9)-1;++p)
    {
        vector<pair<int,int>> e2;
        int i1=(p&1)!=0,i2=(p&2)!=0,i3=(p&4)!=0,i4=(p&8)!=0,i5=(p&16)!=0,j1=(p&32)!=0,j2=(p&64)!=0,j3=(p&128)!=0,j4=(p&256)!=0;
        if(i1+i2+i3+i4+i5!=3) continue;
        for(int i=1;i<=4;++i) fa[i]=i,l[i]=0;
        if(i1) fa[find(1)]=find(2),++l[1],++l[2],e2.push_back(mp(x1,x2));
        if(i2) fa[find(2)]=find(3),++l[2],++l[3],e2.push_back(mp(x2,x3));
        if(i3) fa[find(3)]=find(4),++l[3],++l[4],e2.push_back(mp(x3,x4));
        if(i4) fa[find(4)]=find(1),++l[4],++l[1],e2.push_back(mp(x4,x1));
        if(i5) fa[find(2)]=find(4),++l[2],++l[4],e2.push_back(mp(x2,x4));
        if(find(2)!=find(1)||find(3)!=find(1)||find(4)!=find(1)) continue;
        if(z1)
        {
            if(j1) ++l[1],e2.push_back(mp(z1,x1));
            else ++l[2],e2.push_back(mp(z1,x2));
        }
        if(z2)
        {
            if(j2) ++l[2],e2.push_back(mp(z2,x2));
            else ++l[3],e2.push_back(mp(z2,x3));
        }
        if(z3)
        {
            if(j3) ++l[3],e2.push_back(mp(z3,x3));
            else ++l[4],e2.push_back(mp(z3,x4));
        }
        if(z4)
        {
            if(j4) ++l[4],e2.push_back(mp(z4,x4));
            else ++l[1],e2.push_back(mp(z4,x1));
        }
        if(l[1]==2||l[2]==2||l[3]==2||l[4]==2) continue;
        for(auto i:e) printf("%d %d\n",i.first,i.second);
        for(auto i:e2) printf("%d %d\n",i.first,i.second);
        return 0;
    }
    printf("-1");
    return 0;
}