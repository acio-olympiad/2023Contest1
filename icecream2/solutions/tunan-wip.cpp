#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> pii;

int N, M, P;
int a[100005];
int depth[100005], seen[100005], ind[100005];
vector<int> pre;
vector<pii> graph[100005];

void dfs(int x, int d) {
    if (seen[x]) return;
    seen[x] = 1;
    ind[x] = (int)pre.size();
    depth[x] = d;
    pre.push_back(x);
    for (auto& [c, w] : graph[x]) {
        dfs(c, d+w);
    }
}

int main() {
    cin >> N >> M >> P;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    for (int i = 0; i < P; i++) {
        cin >> a[i];
    }
    dfs(1, 0);
}
