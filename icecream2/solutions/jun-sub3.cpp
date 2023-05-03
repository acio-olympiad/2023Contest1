#include <iostream>
#include <vector>
#include <utility>
#define MAXN 100005
#define MAXC 25
#define LL long long
using namespace std;

/*
1. find spanning tree
2. build LCA structure on tree
3. run floyd warshall on critical nodes
4. for each query add in S,T and do
    min k,l: dTree(S,k) + dCrit(k,l) + dTree(l,T)

Complexity: O(M+K^2logN + K^3 + QK^2)
*/

class TreeDistance {
    vector <pair<int,int> > Tadj[MAXN];
    int n, jmp[MAXN][20], depth[MAXN], edgeDepth[MAXN];
    const int MXLOG = 18;
public:
    void addEdge(int u, int v, int w) {
        Tadj[u].push_back({v,w});
        Tadj[v].push_back({u,w});
    }

    void dfs(int u, int prev) {
        jmp[u][0] = prev;
        for (auto e: Tadj[u]) {
            if (e.first == prev) {continue;}
            depth[e.first] = depth[u] + e.second;
            edgeDepth[e.first] = edgeDepth[u] + 1;
            dfs(e.first, u);
        }
    }

    void buildStructure(int n) {
        dfs(1,1);
        for (int i=1; i<=MXLOG; i++) {
            for (int v=1; v<=n; v++) {
                jmp[v][i] = jmp[jmp[v][i-1]][i-1];
            }
        }
    }

    int lca(int a, int b) {

        if (edgeDepth[a] > edgeDepth[b]) {swap(a,b);} // ensure a is shallower
        for (int i=MXLOG; i>=0; i--) { // bring a to same edge depth
            if ((edgeDepth[b] - edgeDepth[a]) & (1<<i)) {
                b = jmp[b][i];
            }
        }

        for (int i=MXLOG; i>=0; i--) {
            if (jmp[a][i] != jmp[b][i]) {
                a = jmp[a][i];
                b = jmp[b][i];
            }
        }
        if (a != b) {
            return jmp[a][0];
        } else {
            return a;
        }
    }

    int dist(int a, int b) {
        //printf("LCA of %d %d is %d\n",a,b,lca(a,b));
        return depth[a] + depth[b] - 2*depth[lca(a,b)];
    }
} Tree;

class DSU {
    int Set[MAXN];
public:
    void Init(int n) {
        for (int i=1; i<=n; i++) {Set[i] = i;}
    }

    int Find(int x) {
        return Set[x] == x ? x : Set[x] = Find(Set[x]);
    }

    void Union(int x, int y) {
        Set[Find(x)] = Set[Find(y)];
    }
} UF;

int N,M,K; // num nodes, num edges, number of nodes on path
int cDist[MAXC][MAXC], critID[MAXN];
vector <pair<int,int> > nonTreeAdj[MAXN];
vector <int> critical;

bool isCritical[MAXN];

int main() {
    scanf("%d %d %d",&N,&M,&K);
    UF.Init(N);

    for (int i=0; i<M; i++) {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        if (UF.Find(u) != UF.Find(v)) {
            Tree.addEdge(u,v,w);
            UF.Union(u,v);
        } else {
            nonTreeAdj[u].push_back({v,w});
            nonTreeAdj[v].push_back({u,w});
            isCritical[u] = isCritical[v] = true;
        }
    }

    Tree.buildStructure(N);

    // compute distances between critical nodes

    // extract critical nodes
    for (int i=1; i <= N; i++) {
        if (isCritical[i]) {
            critID[i] = critical.size();
            critical.push_back(i);
        }
    }

    // initialise critical nodes by Tree distances
    int C = critical.size();
    for (int i=0; i<C; i++) {
        for (int j=0; j<C; j++) {
            if (i != j) {
                cDist[i][j] = Tree.dist(critical[i], critical[j]);
            }
        }
    }

    // relax with non-tree edges
    for (int v: critical) {
        for (auto e: nonTreeAdj[v]) {
            cDist[critID[v]][critID[e.first]] = min(e.second, cDist[critID[v]][critID[e.first]]);
        }
    }


    // use floyd warshall to compute APSP
    for (int k=0; k<C; k++) {
        for (int i=0; i<C; i++) {
            for (int j=0; j<C; j++) {
                cDist[i][j] = min(cDist[i][k]+cDist[k][j], cDist[i][j]);
            }
        }
    }

    //process queries
    int S,T; // start, end
    LL ans = 0;
    scanf("%d",&S);
    for (int i=2; i<=K; i++) {
        scanf("%d",&T);
        int optimal = Tree.dist(S,T);
        for (int c1=0; c1<C; c1++) {
            for (int c2=0; c2<C; c2++) {
                optimal = min(optimal, Tree.dist(S,critical[c1]) + cDist[c1][c2] +
                               Tree.dist(critical[c2], T));
            }
        }
        //printf("%d %d %d\n",S,T,optimal);
        ans += optimal;
        S = T; // move along
    }

    cout << ans << "\n";
}
