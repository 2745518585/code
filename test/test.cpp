#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 505 , Q = 3e5 + 5 , INF = 1e9;
int n , q , a[N] , b[N] , w[N][N] , ans[Q];
int f[N][N][4] , L[N][N] , R[N][N] , id1[N] , id2[N];
struct Qu{int lx , rx , ly , ry , id;};
void chk(int &x , const int &y){x = max(x , y);}
void Work(int n , int m , bool ed , bool tp)
{
	if(!ed)
	{
		f[1][1][0] = f[1][1][1] = f[1][1][2] = f[1][1][3] = -INF;
		if(!tp)f[1][1][1] = -b[id2[1]]; else f[1][1][2] = -a[id1[1]];
	}
	else f[1][1][0] = f[1][1][1] = f[1][1][2] = -INF , f[1][1][3] = w[id1[1]][id2[1]] - a[id1[1]] - b[id2[1]];
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 + (i == 1) ; j <= m ; j++)
		{
			f[i][j][0] = f[i][j][1] = f[i][j][2] = f[i][j][3] = -INF;
			if(i > 1)
			{
				chk(f[i][j][0] , max(f[i - 1][j][0] , f[i - 1][j][2]));
				chk(f[i][j][1] , max(f[i - 1][j][1] , f[i - 1][j][3]));
			}
			if(j > 1)
			{
				chk(f[i][j][0] , max(f[i][j - 1][0] , f[i][j - 1][1]));
				chk(f[i][j][2] , max(f[i][j - 1][2] , f[i][j - 1][3]));
			}
			if(ed || !tp || j > 1)chk(f[i][j][1] , f[i][j][0] - b[id2[j]]); 
			if(ed || tp || i > 1)chk(f[i][j][2] , f[i][j][0] - a[id1[i]]);
			if(ed || (!tp && i > 1) || (tp && j > 1))
				f[i][j][3] = w[id1[i]][id2[j]] + max(f[i][j][2] - b[id2[j]] , f[i][j][1] - a[id1[i]]);
		}
	}
	// cerr << "\tWork { ";
	// for(int i = 1 ; i <= n ; i++)cerr << id1[i] << ",";
	// cerr << "\b} { ";
	// for(int i = 1 ; i <= m ; i++)cerr << id2[i] << ",";
	// cerr << "\b}\n";
	// for(int i = 1 ; i <= n ; i++)
	// 	for(int j = 1 ; j <= m ; j++)
	// 		cerr << "\t  " << i << ',' << j << ":" << f[i][j][0] << "," << f[i][j][1] << "," << f[i][j][2] << "," << f[i][j][3] << "\n";
}
void Calc(int lx , int rx , int ly , int ry , vector<Qu>&qu)
{
	if(lx > rx || ly > ry || qu.empty())return ;
	vector<Qu>ql , qr , qm;
	// cerr << "Calc " << lx << ',' << rx << "; " << ly << ',' << ry << "; {";
	// for(auto &p : qu)cerr << p.id << ",";
	// cerr << "\b}\n";
	if((rx - lx) >= (ry - ly))
	{
		int mid = (lx + rx) >> 1; 
		for(auto &p : qu)
		{
			if(p.rx < mid)ql.push_back(p);
			else if(p.lx > mid)qr.push_back(p);
			else qm.push_back(p);
		}
		for(int i = ly ; i <= ry ; i++)
		{
			// cerr << "  I = " << i << ":\n";
			for(int ed : {0 , 1})
			{
				// cerr << "    ed = " << ed << "\n";
				for(int j = mid ; j >= lx ; j--)id1[mid + 1 - j] = j;
				for(int j = i ; j >= ly ; j--)id2[i - j + 1] = j;
				Work(mid + 1 - lx , i - ly + 1 , ed , 0);
				for(int j = mid ; j >= lx ; j--)
					for(int k = i ; k >= ly ; k--)
					{
						L[j][k] = -INF; for(int t : {0 , 1 , 2 , 3})
						chk(L[j][k] , f[mid + 1 - j][i - k + 1][t]);
					}
				for(int j = mid ; j <= rx ; j++)id1[j - mid + 1] = j;
				for(int j = i ; j <= ry ; j++)id2[j - i + 1] = j;
				Work(rx - mid + 1 , ry - i + 1 , ed , 0);
				for(int j = mid ; j <= rx ; j++)
					for(int k = i ; k <= ry ; k++)
					{
						R[j][k] = -INF; for(int t : {0 , 1 , 2 , 3})
						chk(R[j][k] , f[j - mid + 1][k - i + 1][t]);
					}
				for(auto [l , r , x , y , id] : qm)
				{
					if(i < x || i > y)continue ;
					// cerr << "\tans[" << id << "]:" << L[l][x] << "+" << R[r][y] << "+" << ed * (-w[mid][i] + a[mid]) + b[i] << "\n";
					ans[id] = max(ans[id] , L[l][x] + R[r][y] + ed * (-w[mid][i] + a[mid]) + b[i]);
				}
			}
		}
		Calc(lx , mid - 1 , ly , ry , ql);
		Calc(mid + 1 , rx , ly , ry , qr);
	}
	else
	{
		int mid = (ly + ry) >> 1; 
		for(auto &p : qu)
		{
			if(p.ry < mid)ql.push_back(p);
			else if(p.ly > mid)qr.push_back(p);
			else qm.push_back(p);
		}
		for(int i = lx ; i <= rx ; i++)
		{
			// cerr << "  I = " << i << ":\n";
			for(int ed : {0 , 1})
			{
				// cerr << "    ed = " << ed << "\n";
				for(int j = mid ; j >= ly ; j--)id2[mid + 1 - j] = j;
				for(int j = i ; j >= lx ; j--)id1[i - j + 1] = j;
				Work(i - lx + 1 , mid + 1 - ly , ed , 1);
				for(int j = mid ; j >= ly ; j--)
					for(int k = i ; k >= lx ; k--)
					{
						L[j][k] = -INF; for(int t : {0 , 1 , 2 , 3})
						chk(L[j][k] , f[i - k + 1][mid + 1 - j][t]);
					}
				for(int j = mid ; j <= ry ; j++)id2[j - mid + 1] = j;
				for(int j = i ; j <= rx ; j++)id1[j - i + 1] = j;
				Work(rx - i + 1 , ry - mid + 1 , ed , 1);
				for(int j = mid ; j <= ry ; j++)
					for(int k = i ; k <= rx ; k++)
					{
						R[j][k] = -INF; for(int t : {0 , 1 , 2 , 3})
						chk(R[j][k] , f[k - i + 1][j - mid + 1][t]);
					}
				for(auto [l , r , x , y , id] : qm)
				{
					if(i < l || i > r)continue ;
					// cerr << "\tans[" << id << "]:" << L[l][x] << "+" << R[r][y] << "+" << ed * (-w[mid][i] + a[mid]) + b[i] << "\n";
					ans[id] = max(ans[id] , L[x][l] + R[y][r] + ed * (-w[i][mid] + b[mid]) + a[i]);
				}
			}
		}
		Calc(lx , rx , ly , mid - 1 , ql);
		Calc(lx , rx , mid + 1 , ry , qr);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	cin >> n >> q;
	for(int i = 1 ; i <= n ; i++)cin >> a[i];
	for(int i = 1 ; i <= n ; i++)cin >> b[i];
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			cin >> w[i][j];
	vector<Qu>qu(q);
	for(int i = 0 ; i < q ; i++)
		cin >> qu[i].lx >> qu[i].rx >> qu[i].ly >> qu[i].ry , qu[i].id = i + 1;
	Calc(1 , n , 1 , n , qu);
	for(int i = 1 ; i <= q ; i++)cout << ans[i] << "\n";
	return 0;
}