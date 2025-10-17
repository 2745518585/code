#include<bits/stdc++.h>
using namespace std;
int n,p[300100],X[300100],f[300100][30],z_;
#define pi pair<int,int>
#define fi first
#define se second
int q[300010];
pi g[300100][30];
int Q(int x,int r){
    int s=0;
    for(int i=20;i>=0;i--)if(f[x][i]<=r)
    s+=(1<<i),x=f[x][i];
    return s;
}
void sol(){
    scanf("%d%d",&n,&z_);
    for(int i=1;i<=n;i++)scanf("%d",&X[i]);
    for(int i=1;i<=n;i++){
        p[i]=max(1,p[i-1]);
        while(p[i]<=n&&X[p[i]]-X[i]<=z_)p[i]++;
        f[i][0]=p[i];
    }
    p[n+1]=f[n+1][0]=n+1;
    for(int j=1;j<=20;j++)for(int i=1;i<=n+1;i++)f[i][j]=f[f[i][j-1]][j-1];
    for(int i=1;i<n;i++){
        int u=i,v=i+1,s=0;
        for(int j=20;j>=0;j--){
            if(f[u][j]!=f[v][j])
            s+=(1<<j),u=f[u][j],v=f[v][j];
        }
        q[i]=f[u][0],g[i][0]=make_pair(q[i],s*2+2);
        u=i+1,v=p[i];
        if(u==v)g[i][0]=make_pair(i+1,1);
        else{
            s=0;
            for(int j=20;j>=0;j--){
                if(f[u][j]!=f[v][j])
                s+=(1<<j),u=f[u][j],v=f[v][j];
            }
            if(g[i][0].se>s*2+3)
            g[i][0]=make_pair(f[u][0],s*2+3);
        }
    }
    q[n]=q[n+1]=n+1;
    g[n][0]=g[n+1][0]=make_pair(n+1,0);
    for(int j=1;j<=20;j++)for(int i=1;i<=n+1;i++)
    g[i][j]=make_pair(g[g[i][j-1].fi][j-1].fi,g[i][j-1].se+g[g[i][j-1].fi][j-1].se);
    int q;scanf("%d",&q);
    for(int i_=1,l,r;i_<=q;i_++){
        scanf("%d%d",&l,&r);
        if(l==r){puts("1");continue;}
        int ans=2,u=l;
        for(int i=20;i>=0;i--)
        if(g[u][i].fi<=r)
        ans+=g[u][i].se,u=g[u][i].fi;
        if(u==r)printf("%d\n",ans-1);
        else{
            ans+=Q(u,r),ans+=Q(u+1,r);
            printf("%d\n",ans);
        }
    }
}
int main(){
    int T;scanf("%d",&T);while(T--)sol();
    return 0;
}