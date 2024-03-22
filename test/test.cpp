#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+500;

int n,k,a[N],st[3][N][19],b[N],ans=1e9+7,lg[N];
vector<int>p[N];

int findnum(int ty,int l,int r)
{
    int w=a[l];
    for(int i=lg[n]-1;i>=0;i--)if(l+(1<<i)-1<=n&&st[ty][l][i]<=r&&st[ty][l][i])
    {
        // cout<<ty<<' '<<l<<' '<<i<<' '<<st[ty][l][i]<<'\n';
        l=st[ty][l][i];
    }
    return l;
}

int num(int ty,int l,int r)
{
    return abs(a[l]-a[findnum(ty,l,r)]);
}

int sol(int a,int b,int len)
{
    int l=max(a,b),r=n,ans=1e9+7;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(num(1,a,mid)+num(2,b,mid)>=len)r=mid-1,ans=mid;
        else l=mid+1;
    }
    return ans;
}

int rsol(int ty,int l,int k)
{
    for(int i=lg[n]-1;i>=0;i--)if(l+(1<<i)-1<=n&&st[ty][l][i]<=n&&st[ty][l][i]&&(1<<i)<=k)
    {
        // cout<<ty<<' '<<l<<' '<<i<<' '<<st[ty][l][i]<<'\n';
        l=st[ty][l][i],k-=(1<<i);
    }
    return k?1e9+7:l;
}

int solve(int l,int r,int len)
{
    int to=max(l,r);
    int w=upper_bound(p[a[to]].begin(),p[a[to]].end(),to)-p[a[to]].begin();
    if(w>=p[a[to]].size())
    {
        if(l>r)return rsol(1,l,len);
        return rsol(2,r,len);
    }
    w=p[a[to]][w];
    if(l<r)l=w;else r=w;len--;
    // cout<<"FFFIIINNNDDD   "<<l<<' '<<r<<' '<<w<<' '<<len<<'\n';
    return sol(l,r,len);
}

int solve(int A,int B,int posa,int posb)
{
    int ll=min(posa,posb),len=k-2;
    if(posa<posb)
    {
        int to=findnum(1,posa,posb-1);
        len-=a[to]-a[posa];posa=to;
    }
    else
    {
        int to=findnum(2,posb,posa-1);
        len-=a[posb]-a[to];posb=to;
    }
    if(len<=0)return max(posa,posb)-ll;
    if(a[posa]>=a[posb])return sol(posa,posb,len)-ll;
    if(a[posa]+1==a[posb])
    {
        int ans=1e9+7;
        if(posa>posb)
        {
            ans=rsol(1,posa,len);
            posb=upper_bound(p[a[posa]].begin(),p[a[posa]].end(),posa)-p[a[posa]].begin();
            if(posb>=p[a[posa]].size())return ans-ll;posb=p[a[posa]][posb];
        }
        else
        {
            ans=rsol(2,posb,len);
            posa=upper_bound(p[a[posb]].begin(),p[a[posb]].end(),posb)-p[a[posb]].begin();
            if(posa>=p[a[posb]].size())return ans-ll;posa=p[a[posb]][posa];
        }
        return min(ans,sol(posa,posb,len-1))-ll;
    }
    int l=max(posa,posb),r=n,pos=n+1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(a[findnum(1,posa,mid)]<a[findnum(2,posb,mid)])l=mid+1,pos=mid;
        else r=mid-1;
    }
    if(pos>=n)return 1e9+7;
    int to;
    to=findnum(1,posa,pos);len-=a[to]-a[posa];posa=to;
    to=findnum(2,posb,pos);len-=a[posb]-a[to];posb=to;
    // cout<<A<<' '<<B<<' '<<posa<<' '<<posb<<' '<<pos<<'\n';
    // cout<<min(solve(posa,pos+1,len-1),solve(pos+1,posb,len-1))-ll<<'\n';
    // cout<<solve(posa,pos+1,len-1)<<'\n';
    // cout<<findnum(1,posa,5)<<' '<<findnum(2,posb,5)<<'\n';
    // cout<<st[1][1][0]<<' '<<st[2][2][0]<<'\n';
    // cout<<"find "<<A<<' '<<B<<' '<<posa<<' '<<posb<<' '<<pos<<' '<<len<<'\n';
    // exit(0);
    return min(solve(posa,pos+1,len-1),solve(pos+1,posb,len-1))-ll;
}

main()
{
    // freopen("in.txt","r",stdin);
    // n=k=2e5;
    // cout<<n<<' '<<k<<'\n';
    // for(int i=1;i<n;i++)cout<<n-i<<' ';cout<<n;
    // return 0;
    cin>>n>>k;
    if(k&1){cout<<-1;return 0;}
    for(int i=1;i<=n+1;i++)b[i]=n+1,lg[i]=lg[i>>1]+1;b[0]=n+1;
    for(int i=1;i<=n;i++)cin>>a[i],p[a[i]].push_back(i);
    for(int i=n;i>=1;i--)st[1][i][0]=b[a[i]+1],st[2][i][0]=b[a[i]-1],b[a[i]]=i;
    for(int i=1;(1<<i)<=n;i++)st[1][n+1][i]=st[2][n+1][i]=n+1;
    for(int j=1;(1<<j)<=n;j++)
    for(int i=1;i+(1<<j)-1<=n;i++)
    st[1][i][j]=st[1][st[1][i][j-1]][j-1],st[2][i][j]=st[2][st[2][i][j-1]][j-1];
    for(int i=1;i<=n;i++)
    {
        // cout<<i<<'\n';
        int A=a[i],B=a[i]+(k/2)-1;
        int posb=upper_bound(p[B].begin(),p[B].end(),i)-p[B].begin(),t=posb;
        if(posb<p[B].size())posb=p[B][posb],ans=min(ans,solve(A,B,i,posb));
        if(t+1<p[B].size()&&num(1,i,posb)==k/2-1)ans=min(ans,sol(p[B][t],p[B][t+1],k/2-1)-i);
        // cout<<A<<' '<<B<<' '<<i<<' '<<p[B][posb]<<'\n';
        A=a[i]-(k/2)+1,B=a[i];
        if(A<1)continue;
        int posa=upper_bound(p[A].begin(),p[A].end(),i)-p[A].begin();t=posa;
        // cout<<A<<' '<<B<<'\n'<<i<<' '<<p[A][posa]<<'\n';
        if(posa<p[A].size())posa=p[A][posa],ans=min(ans,solve(A,B,posa,i));
        // cout<<p[A][t+1]<<' '<<p[A][t]<<' '<<k/2-1<<' '<<sol(p[A][t+1],p[A][t],k/2-1)<<'\n';
        if(t+1<p[A].size()&&num(2,i,posa)==k/2-1)ans=min(ans,sol(p[A][t+1],p[A][t],k/2-1)-i);
    }
    if(ans>=n)ans=-1;cout<<ans;
}