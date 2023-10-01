#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> core(10001, -1);
    vector<vector<pair<int, int>>> res(m);
    vector<int> total(m, 0);
    for(int i = 0; i < n; i++)
    {
        int type, user, time, deadline;
        cin >> type >> user >> time >> deadline;
        if(core[user] == -1)
        {
            for(int j = 0; j < m; ++j)
            {
                if(core[user] == -1 || total[j] < total[core[user]])
                {
                    core[user] = j;
                }
            }
        }
        res[core[user]].push_back(pair<int, int>(type, user));
        total[core[user]] += time;
    }
    for(int i = 0; i < m; ++i)
    {
        cout << res[i].size();
        for(int j = 0; j < res[i].size(); ++j)
        {
            cout << ' ' << res[i][j].first << ' ' << res[i][j].second;
        }
        cout << endl;
    }
    return 0;
}
