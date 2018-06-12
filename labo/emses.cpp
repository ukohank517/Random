#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
#include <cmath>
#include <complex> // complex<double> a(1.2 , 2.3);// real(): 1.2, imag()2.3
using namespace std;

#define MOD 1000000007
#define ll long long
#define ld long double
#define FOR(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define rep(i,n) FOR(i,0,n)
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rmsame(a) sort(all(a)),a.erase(unique(all(a)), a.end())
#define rmvector(a,b) rep(i,a.size())rep(j,b.size())if(a[i]==b[j]){a.erase(a.begin()+i);i--;break;}
#define pq_pair_tB priority_queue <pair<ll,ll>, vector<pair<ll,ll> > , greater<pair<ll,ll> > > 
#define pq_pair_ts priority_queue <pair<ll,ll> > //第二成分の大きさが関係ない
template<typename X> bool exist(vector<X> vec, X item){return find(all(vec), item)!=vec.end();}
ll gcd(ll a, ll b){if(b==0)return a;return gcd(b,a%b);}
ll lcm(ll a, ll b){return a/gcd(a,b)*b;}

/*
 想定: 周期的境界条件
 */

/***
 変数格納領域
 ***/
#define particleNum 3 //空間内粒子数
#define meshNum 100 //メッシュサイズ100
#define dx 1 //メッシュの間隔
#define dt 0.001
#define timesteps 5000

ld x_particle[particleNum]; //粒子位置
ld v_particle[particleNum]; //粒子速度
ld rho[meshNum] ; //電荷密度
ld E[meshNum] ; //電場
ld V[meshNum] ; //電位

void particleInit();
void xtorho();
void rhotoE();
void vEtonewv();
void xvtonewx();


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    //粒子を設置
    particleInit();

    rep(i, timesteps){
        //電荷密度計算
        xtorho();
        //電場更新
        rhotoE();
        //速度更新
        vEtonewv();
        //位置更新
        xvtonewx();
        
        
        rep(j, particleNum){
            cout << x_particle[j] << " ";
        }
        cout << endl;

    }
    
    //cout << fixed << setprecision(16) << ans << endl;
    return 0;
}


void particleInit(){
    x_particle[0] = 49;
    x_particle[1] = 50;
    x_particle[2] = 58;
}
void xtorho(){
    //rhoの中身を空にする
    rep(i, meshNum) rho[i] = 0.0;
    
    rep(i, particleNum){
        ld position = x_particle[i];
        ll leftgrid = 0;
        ll rightgrid = 0;
        while(position-1.0 > 0.0){
            position -= 1.0;
            leftgrid ++;
        }
        rightgrid = leftgrid + 1;
        
        
        ld ldis = x_particle[i] - (ld)leftgrid;
        ld rdis = (ld)rightgrid - x_particle[i];
        if(rightgrid == meshNum) rightgrid = 0;
        rho[leftgrid] += rdis;
        rho[rightgrid] += ldis;
       }
}

void rhotoE(){
    /*------------------ポアソンよりVを出す-------------------------*/
    while(1){
        ld maxError = 0;
        ld maxV = 0;
        rep(i, meshNum){
            //領域端の点を取り除く
            if(i == 0) continue;
            if(i == meshNum -1) continue;
            
            ld Prev_V = V[i] ; //前回ループのV
            V[i] = 0.5 * (2.0 * rho[i] + V[i+1] + V[i-1]);// 0.5 * (V[i+1]-2V[i]+V[i-1]) = -rho[i]
            maxV = max(V[i] , maxV);
            maxError = max(maxError, abs(Prev_V - V[i]));
        }
        if(maxError/maxV <= 0.0001) break;
    }
    /*VをベースでEを出す*/
    //???????????????????ここの条件により、周期境界になる????????????????????????????????
    rep(i, meshNum){
        if(i == 0) E[i] = (-0.5) * (V[i+1] - V[meshNum-1]);
        else if(i == meshNum -1) E[i] = (-0.5) * (V[0] - V[i-1]);
        else E[i] = (-0.5) * (V[i+1] - V[i-1]);
    }
}

void vEtonewv(){
    rep(i, particleNum){
        //粒子の位置を取り出す。
        ld position = x_particle[i];
        ll leftgrid = 0;
        ll rightgrid = 0;
        while(position-1.0 >= 0.0){
            position -= 1.0;
            leftgrid ++;
        }
        rightgrid = leftgrid + 1;
        ld rdis = x_particle[i] - (ld)leftgrid;
        ld ldis = (ld)rightgrid - x_particle[i];
        if(rightgrid == meshNum) rightgrid = 0;
        
        ld E_particle = (ldis * E[leftgrid]) + (rdis * E[rightgrid]);
        v_particle[i] = v_particle[i] + dt * E_particle;
    }
}

void xvtonewx(){
    rep(i, particleNum){
        x_particle[i] = x_particle[i] + v_particle[i] * dt;
        if(x_particle[i] > meshNum) x_particle[i]-= (ld) meshNum;
        if(x_particle[i] < 0.0) x_particle[i] += (ld) meshNum;
    }
}
