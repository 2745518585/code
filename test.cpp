#include<bits/stdc++.h>
using namespace std;
const int N=4e5+4;
typedef long long ll;
typedef pair<int,int> pii;
#define fi first
#define se second
int n,m,a[N],c[N];ll s[N];
deque<pair<pii,pair<int,ll> > >dq;
bool used[N];int b[N];
int main(){
	freopen("noip.in","r",stdin);
	freopen("noip.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(~a[i])used[a[i]]=1;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		if(used[i])b[i]=m;
		else ++m,s[m]=s[m-1]+c[i];
	}
	dq.push_back({{0,m},{0,0}});
	for(int i=1,mx=0,pre=0;i<=n;i++){
		if(i>1){
			auto t=dq.back();
			printf("%lld ",t.se.se+s[m]-s[t.fi.se]);
		}
		if(~a[i]){
			if(mx>a[i])continue;mx=a[i];
			int p=b[a[i]];
			if(dq.front().fi.fi-dq.front().se.fi+pre>p)continue;
			for(;;){
				int pos=dq.front().fi.se-dq.front().se.fi+pre;
				if(pos<p)dq.pop_front();
				else{
					auto t=dq.front();dq.pop_front();
					dq.push_front({{t.fi.se-(pos-p),t.fi.se},t.se});
					break;
				}
			}
			auto t=dq.front();
			int fr=t.fi.fi,to=fr-t.se.fi+pre;
			ll W=t.se.se+s[to]-s[fr]+c[a[i]];
			int cur=to;
			for(;!dq.empty();){
				t=dq.front();
				int tm=pre-t.se.fi;
				int L=t.fi.fi+tm,R=t.fi.se+tm;
				if(t.se.se+s[R]-s[R-tm]<=W){dq.pop_front(),cur=R;continue;}
				if(t.se.se+s[L]-s[L-tm]>W)break;
				dq.pop_front();
				int ld=L,rd=R;
				while(rd>ld){
					int md=(ld+rd>>1)+1;
					if(t.se.se+s[md]-s[md-tm]<=W)ld=md;
					else rd=md-1;	
				}
				cur=ld,dq.push_front({{t.fi.se-(R-ld-1),t.fi.se},t.se});break;
			}
			dq.push_front({{p,cur},{pre,W}});
		}else{
			pre++;
			if(dq.front().fi.fi-dq.front().se.fi>0){
				auto t=dq.front();int p=t.fi.fi;
				dq.push_front({{p,p},{pre,t.se.se+s[p+pre-1-t.se.fi]-s[p]}});
			}
			auto t=dq.back();dq.pop_back();
			if(t.fi.fi!=t.fi.se)dq.push_back({{t.fi.fi,t.fi.se-1},t.se});
		}
	}
	auto t=dq.back();
	printf("%lld ",t.se.se+s[m]-s[t.fi.se]);
}

