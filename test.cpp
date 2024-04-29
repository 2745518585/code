#include<bits/stdc++.h>
using namespace std;
const int N=500;

int n,a[N],b[N],ans=1e9,m,c[N],ro[N],tl[N],tr[N],pos[N],val[N],l,r;
vector<int>sa[N],sb[N];set<int>re;

int find(int x)
{
    return ro[x]==x?x:ro[x]=find(ro[x]);
}

void merge(int x,int y)
{
    ro[find(x)]=find(y);
}

int chk(int l1,int r1,int l2,int r2)
{
    if(l1>l2)swap(l1,l2),swap(r1,r2);
    return r1<r2;
}

int mk(int x,int ty)
{
    if(val[x]&&val[x]!=ty)return 1;
    val[x]=ty;
    pos[x]=ty==1?tl[x]:tr[x];
    return 0;
}

int base()
{
    while(1)
    {
        int f=0;
        for(auto x:re)
        {
            int p1=0,p2=1e9;
            for(int i=l+1;i<x;i++)p1=pos[i]?pos[i]:p1;
            for(int i=m-r;i>x;i--)p2=pos[i]?pos[i]:p2;
            if(p1>tr[x])return 1;
            if(p2<tl[x])return 1;
            if(p1>tl[x]&&p2<tr[x])return 1;
            if(p1>tl[x])val[x]=2,pos[x]=tr[x],f=1;
            if(p2<tr[x])val[x]=1,pos[x]=tl[x],f=1;
            if(f)
            {
                re.erase(x);
                break;
            }
        }
        if(!f)break;
    }
    return 0;
}

int chk()
{
    for(int i=1;i<=m;i++)c[i]=pos[i]=val[i]=0,ro[i]=i;
    for(int i=1;i<=l;i++)c[b[i]]++;
    for(int i=1;i<=n;i++)if(c[i]>=3)return 0;
    for(int i=1;i<=n;i++)c[i]=0;
    for(int i=1;i<=r;i++)c[b[m-i+1]]++;
    for(int i=1;i<=n;i++)if(c[i]>=3)return 0;
    for(int i=1;i<=l;i++)c[b[i]]++;
    re.clear();
    for(int i=1;i<=n;i++)
    {
        vector<int>&p=sb[i],&q=sa[i];
        if(c[i]==0)
        {
            for(int j=0;j<3;j++)pos[p[j]]=q[j];
            continue;
        }
        if(c[i]==1)
        {
            if(p[0]<=l)pos[p[1]]=q[0],pos[p[2]]=q[2];
            else pos[p[0]]=q[0],pos[p[1]]=q[2];
            continue;
        }
        if(c[i]==3)continue;
        if(p[1]<=l)
        {
            pos[p[2]]=q[2];
            continue;
        }
        if(p[1]>=m-r+1)
        {
            pos[p[0]]=q[0];
            continue;
        }
        pos[p[1]]=0;
        tl[p[1]]=p[0],tr[p[1]]=p[2];
    }
    for(int la=0,i=l+1;i<=m-r;i++)
    {
        if(pos[i])
        {
            if(pos[i]<la)return 0;
            la=pos[i];
        }
        else re.insert(i);
    }
    for(auto x:re)for(auto y:re)if(x!=y&&chk(tl[x],tr[x],tl[y],tr[y]))merge(x,y);
    for(auto x:re)tl[x]=sa[b[x]][0],tr[x]=sa[b[x]][2];
    if(base())return 0;
    for(auto x:re)for(auto y:re)if(y>x)
    {
        int l1=tl[x],r1=tr[x],l2=tl[y],r2=tr[y];
        if(l2>r1)continue;
        if(r2<l1)return 0;
        if(r1>r2&&mk(x,1))return 0;
        if(l2<l1&&mk(y,2))return 0;
    }
    if(base())return 0;
    for(auto x:re)if(val[x]&&mk(find(x),val[x]))return 0;
    return 1;
}

main()
{
    cin>>n;m=3*n;
    for(int i=1;i<=m;i++)cin>>a[i],sa[a[i]].push_back(i);
    for(int i=1;i<=m;i++)cin>>b[i],sb[b[i]].push_back(i);
    for(int i=0;i<=m;i++)
    for(int j=0;j+i<=m;j++)if(i+j<ans)
    {
        l=i,r=j;
        if(chk())ans=min(ans,i+j);
    }
    cout<<(ans>m?-1:ans);
}

