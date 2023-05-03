#include<bits/stdc++.h>
using namespace std;

using pii=pair<int,int>;
using t3i=tuple<int,int,int>;
using t4i=tuple<int,int,int,int>;

mt19937 rng(64);
int random(int l,int r){
    assert(l<=r);
    
    int ans=int(((long long)rng()%(r-l+1))+l);
    assert(l<=ans && ans<=r);
    return ans;
}

vector<int> prob_distr;
void compute_probability_distribution(int H){
    prob_distr.clear();
    for(int i=1;i<=H;i++){
        for(int j=1;j<=H-i+1;j++){
            prob_distr.push_back(i);
        }
    }
}

void generate(int max_N,int max_L,int max_H,int max_s,string filename){
    ofstream out(filename);

    int N=random(1,max_N);
    int L=random(1,max_L);
    int H=random(1,max_H);
    out<<N<<' '<<L<<' '<<H<<'\n';

    compute_probability_distribution(H);
    for(int i=1;i<=L;i++){
        int t=random(1,N);
        int h=prob_distr[random(0,(int)prob_distr.size()-1)];
        int s=random(1,max_s);
        out<<t<<' '<<h<<' '<<s<<'\n';
    }
}

void generate_sub2(int max_N,int max_H,int max_s,string filename){
    ofstream out(filename);

    int N=random(1,max_N);
    int L=N;
    int H=random(1,max_H);
    out<<N<<' '<<L<<' '<<H<<'\n';
    compute_probability_distribution(H);

    vector<t3i> lectures; // {t,h,s}
    for(int i=1;i<=N;i++){
        int h=prob_distr[random(0,(int)prob_distr.size()-1)];
        int s=random(1,max_s);

        lectures.push_back({i,h,s});
    }
    shuffle(lectures.begin(),lectures.end(),rng);

    for(t3i i:lectures){
        int t,h,s;
        tie(t,h,s)=i;
        out<<t<<' '<<h<<' '<<s<<'\n';
    }
}

void generate_sub3(int max_N,int max_H,int max_s,string filename){
    ofstream out(filename);

    int N=random(1,max_N);
    int L=2*N;
    int H=random(1,max_H);
    out<<N<<' '<<L<<' '<<H<<'\n';
    compute_probability_distribution(H);

    vector<t3i> lectures; // {t,h,s}
    for(int i=1;i<=N;i++){
        for(int j=1;j<=2;j++){
            int h=prob_distr[random(0,(int)prob_distr.size()-1)];
            int s=random(1,max_s);

            lectures.push_back({i,h,s});
        }
    }
    shuffle(lectures.begin(),lectures.end(),rng);

    for(t3i i:lectures){
        int t,h,s;
        tie(t,h,s)=i;
        out<<t<<' '<<h<<' '<<s<<'\n';
    }
}

int main(){
    const int sub1_cases=10;
    const int sub2_cases=15;
    const int sub3_cases=20;
    const int sub4_cases=20;
    const int sub5_cases=50;

    t3i sub1={1,1000,1000};
    pii sub2={1000,1000}; // {max_N,max_H}
    pii sub3={500,1000}; // {max_N,max_H}
    t3i sub4={100,100,100};
    t3i sub5={1000,1000,1000};

    // sub1
    for(int i=1;i<=sub1_cases;i++){
        string filename="random_data-sub1-case"+to_string(i)+".in";

        int max_N,max_L,max_H,max_s;
        max_s=(int)pow(10,random(0,9));
        tie(max_N,max_L,max_H)=sub1;

        generate(max_N,max_L,max_H,max_s,filename);
    }

    // sub2
    for(int i=1;i<=sub2_cases;i++){
        string filename="random_data-sub2-case"+to_string(i)+".in";

        int max_N,max_H,max_s;
        max_s=(int)pow(10,random(0,9));
        tie(max_N,max_H)=sub2;

        generate_sub2(max_N,max_H,max_s,filename);
    }

    // sub3
    for(int i=1;i<=sub3_cases;i++){
        string filename="random_data-sub3-case"+to_string(i)+".in";

        int max_N,max_H,max_s;
        max_s=(int)pow(10,random(0,9));
        tie(max_N,max_H)=sub3;

        generate_sub3(max_N,max_H,max_s,filename);
    }

    // sub4
    for(int i=1;i<=sub4_cases;i++){
        string filename="random_data-sub4-case"+to_string(i)+".in";

        int max_N,max_L,max_H,max_s;
        tie(max_N,max_L,max_H)=sub4;
        max_s=(int)pow(10,random(0,9));

        generate(max_N,max_L,max_H,max_s,filename);
    }

    // sub5 (full)
    for(int i=1;i<=sub5_cases;i++){
        string filename="random_data-sub5-case"+to_string(i)+".in";

        int max_N,max_L,max_H,max_s;
        tie(max_N,max_L,max_H)=sub5;
        max_s=(int)pow(10,random(0,9));

        generate(max_N,max_L,max_H,max_s,filename);
    }
}
