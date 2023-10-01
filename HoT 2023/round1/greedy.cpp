#include <bits/stdc++.h>

using namespace std;

struct MSG {
	int type;
	int user;
	int time;
	int deadline;
};

int compute_score(vector<vector<MSG> > &distribution) 
{
    int affinity_score = 0;
    int capability_score = 0;

    for (int i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].empty())
        {
            continue;
        } else if (distribution[i].size() == 1) {
            MSG* cur_msg = &distribution[i][0];
            if ((*cur_msg).time <= (*cur_msg).deadline) capability_score++;
        } else {
            MSG* prev_msg = &distribution[i][0];
            int t = (*prev_msg).time;
            if (t <= (*prev_msg).deadline) capability_score++;

            for (int j = 1; j < distribution[i].size(); j++)
            {
                MSG* cur_msg = &distribution[i][j];
                t += (*cur_msg).time;

                if ((*cur_msg).type == (*prev_msg).type) affinity_score++;

                if (t <= (*cur_msg).deadline) capability_score++;
            }
        }
    }

    return affinity_score + capability_score;
}

bool affinity_point(MSG &msg, vector<vector<MSG> > &distribution, int core)
{
    if (distribution[core].empty()) return 0;
    
    MSG &msg_prev = distribution[core].back();
    return (msg.type == msg_prev.type);
}

bool capability_point(MSG &msg, vector<int> &total, int global_deadline, int core)
{
    return (total[core] + msg.time <= min(msg.deadline, global_deadline));
}

void place_task(int user, vector<int> &core, int cn, map<int, queue<MSG> > &messages, vector<vector<MSG> > &distribution)
{
    if (core[user] == -1)
    {
        core[user] = cn;
    }
    
    distribution[core[user]].push_back(messages[user].front());
    messages[user].pop();
    if (messages[user].empty())
    {
        messages.erase(user);
    }
}

int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> core(10001, -1);
    vector<int> total(m, 0);
    map<int, queue<MSG> > messages;
    vector<vector<MSG> > distribution(m);

    for (int i = 0; i < n; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages[msg.user].push(msg);
	}

    const int N_PRIOR = 10;
    vector<MSG> priorities(N_PRIOR);
    vector<int> assigned_cores(N_PRIOR);

    bool placed = true;
    while (placed) {
        placed = false;

        if (messages.empty()) break;

        for (const auto &it : messages)
        {
            if (it.second.empty()) continue;

            MSG msg = (it.second).front();

            if (core[msg.user] != -1)
            {
                bool ap = affinity_point(msg, distribution, core[msg.user]);
                bool cp = capability_point(msg, total, c, core[msg.user]);

                if (ap && cp) {
                    priorities[0] = msg;
                    assigned_cores[0] = core[msg.user];
                    break;
                } else if (ap) {
                    priorities[1] = msg;
                    assigned_cores[1] = core[msg.user];
                    break;
                } else if (cp) {
                    priorities[6] = msg;
                    assigned_cores[6] = core[msg.user];
                    break;
                } else {
                    priorities[8] = msg;
                    assigned_cores[8] = core[msg.user];
                }
            } else {
                bool stop_loop = false;
                for (int i = 0; i < m; i++)
                {
                    bool ap = affinity_point(msg, distribution, i);
                    bool cp = capability_point(msg, total, c, i);

                    if (ap && cp) {
                        priorities[1] = msg;
                        assigned_cores[1] = i;
                        stop_loop = true;
                        break;
                    } else if (ap) {
                        priorities[3] = msg;
                        assigned_cores[3] = i;
                        stop_loop = true;
                        break;
                    } else if (cp) {
                        priorities[7] = msg;
                        assigned_cores[7] = i;
                    } else {
                        priorities[9] = msg;
                        assigned_cores[9] = i;
                    }
                }
                if (stop_loop) break;
            }
        } 

        for (int p = 0; p < N_PRIOR; p++)
        {
            if (priorities[p].type == 0) continue;
            
            place_task(priorities[p].user, core, assigned_cores[p], messages, distribution);
            priorities[p].type = 0;
            placed = true;
            break;
        }
    } 
       

    for(int i = 0; i < m; ++i)
    {
        cout << distribution[i].size();
        for(int j = 0; j < distribution[i].size(); ++j)
        {
            cout << ' ' << distribution[i][j].type << ' ' << distribution[i][j].user;
        }
        cout << endl;
    }

    // cout << "Score: " << compute_score(distribution) << endl;
    return 0;
}

