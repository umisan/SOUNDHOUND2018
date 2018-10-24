#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <queue>

using namespace std;

typedef long long int ll;
typedef pair<ll, int> P;

int main()
{
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  vector<vector<P>> graph_yen(n);
  vector<vector<P>> graph_sunuke(n);
  for(int i = 0; i < m; i++)
  {
    int u, v, a, b;
    cin >> u >> v >> a >> b;
    //円の無向グラフの構成
    graph_yen[u - 1].push_back({a, v - 1});
    graph_yen[v - 1].push_back({a, u - 1});
    //スヌケの無向グラフの構成
    graph_sunuke[u - 1].push_back({b, v - 1});
    graph_sunuke[v - 1].push_back({b, u - 1});
  }

  //グラフダンプ関数
  auto dump = [n](vector<vector<P>> &graph){
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < graph[i].size(); j++)
      {
        cout << graph[i][j].second << " ";
      }
      cout << endl;
    }
  };

  //ダイクストラ
  auto dijkstra = [n](vector<vector<P>> &graph, int s, int t){
    //到達済みフラグと結果
    vector<bool> flag(n, false);
    vector<ll> result(n, -1);
    //優先度付きキュー
    priority_queue<P, vector<P>, greater<P>> q;
    //初期化
    result[s] = 0;
    q.push({0, s});
    //メインアルゴリズム
    while(!q.empty())
    {
      const P current = q.top();
      if(!flag[current.second])
      {
        flag[current.second] = true;
      }else{
        q.pop();
      }
      for(int i = 0; i < graph[current.second].size(); i++)
      {
        const P target = graph[current.second][i];
        ll temp_len = result[current.second] + target.first;
        if(result[target.second] == -1 || temp_len < result[target.second])
        {
          result[target.second] = temp_len;
          flag[target.second] = true;
          q.push({temp_len, target.second});
        }
      }
    }
    return result;
  };
  vector<ll> result_yen = dijkstra(graph_yen, s - 1, t  - 1);
  vector<ll> result_sunuke = dijkstra(graph_sunuke, t - 1, s  - 1);
  vector<ll> optimal_sunuke(n + 1, 0);
  for(int i = n - 1; i >= 0; i--)
  {
    ll rest = 1000000000000000 - (result_yen[i] + result_sunuke[i]);
    optimal_sunuke[i] = max(optimal_sunuke[i + 1], rest);
  }
  for(int i = 0; i < n; i++)
  {
    cout << optimal_sunuke[i] << endl;
  }
	return 0;
}
