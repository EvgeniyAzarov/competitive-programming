#include <bits/stdc++.h>

using namespace std;

struct MSG {
	int type;
	int user;
	int time;
	int deadline;
};

int score(vector<vector<MSG> > &distribution, int global_deadline) 
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
            if ((*cur_msg).time < min((*cur_msg).deadline, global_deadline)) capability_score++;
        } else {
            MSG* prev_msg = &distribution[i][0];
            int t = (*prev_msg).time;
            if (t <= min((*prev_msg).deadline, global_deadline)) capability_score++;

            for (int j = 1; j < distribution[i].size(); j++)
            {
                MSG* prev_msg = &distribution[i][j-1];
                MSG* cur_msg = &distribution[i][j];
                t += (*cur_msg).time;

                if ((*cur_msg).type == (*prev_msg).type) affinity_score++;

                if (t <= min((*cur_msg).deadline, global_deadline)) capability_score++;
            }
        }
    }

    return affinity_score + capability_score;
}

vector<int> determine_msgs_order(int cur_time, vector<int> &msg_users, map<int, queue<MSG> > &messages, int global_deadline)
{
    int m = msg_users.size();
    vector<int> new_order;
    vector<int> out_time_msgs;
    
    for (int i = 0; i < m; i++)
    {
        MSG msg = messages[msg_users[i]].front();

        if (cur_time + msg.time <= min(msg.deadline, global_deadline))
        {
            new_order.push_back(msg.user);
            cur_time += msg.time;
        } else {
            out_time_msgs.push_back(msg.user);
        }
    }

    new_order.insert(new_order.end(), out_time_msgs.begin(), out_time_msgs.end());

    return new_order;
}

vector<vector<MSG> > strategy1(map<int, queue<MSG> > messages, int m, int c)
{
    vector<vector<MSG> > distribution(m);
    vector<int> core(10001, -1);

    vector<pair<int, int> > total(m);
    for (size_t i = 0; i < m; i++) total[i] = make_pair(i, 0);
    
    vector<vector<int> > cur_messages(201);
    for (auto it = messages.begin(); it != messages.end(); ++it)
    {
        int user = it->first;
        int cur_msg_type = it->second.front().type;

        cur_messages[cur_msg_type].push_back(user);
    }

    vector<vector<vector<int> > > core_cur_msgs(m, cur_messages);
    
    int max_set = 0;
    int max_set_type = 0;

    int max_max_set = 0;

    do {
        max_max_set = 0;

        sort(total.begin(), total.end(), [](const auto &lhs, const auto &rhs) {
            return lhs.second < rhs.second;
        });

        for (auto &core_info : total) 
        {
            int cn = core_info.first;

            // remove users which are already assigned to other cores
            for (size_t i = 1; i < 201; i++)
            {
                if (core_cur_msgs[cn][i].empty()) continue;

                auto it = core_cur_msgs[cn][i].begin();
                while(it != core_cur_msgs[cn][i].end()) 
                {
                    if (core[*it] != -1 && core[*it] != cn) it = core_cur_msgs[cn][i].erase(it);
                    else it++;
                }
            }

            max_set = 0;
            for (size_t i = 1; i < 201; i++)
            {
                int size = core_cur_msgs[cn][i].size();
                if (size > max_set)
                {
                    max_set=size;
                    max_set_type=i;
                }
            }

            if (max_set == 0) continue;

            vector<int> ordered_msgs = determine_msgs_order(core_info.second, core_cur_msgs[cn][max_set_type], messages, c);

            for (int user : ordered_msgs)
            {
                MSG msg = messages[user].front();
                messages[user].pop();
                distribution[cn].push_back(msg);
                core_info.second += msg.time;

                if (core[msg.user] == -1) core[msg.user] = cn;

                if (messages[user].empty())
                {
                    messages.erase(user);
                    continue;
                } else 
                {
                    MSG next_msg = messages[user].front();
                    core_cur_msgs[cn][next_msg.type].push_back(user);
                }
            }
            core_cur_msgs[cn][max_set_type].clear();
            if (max_set > max_max_set)
            {
                max_max_set = max_set;
            }
            
        }
    } while (max_max_set > 0);

    return distribution;
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

vector<vector<MSG> > strategy2(map<int, queue<MSG> > messages, int m, int c)
{
    vector<vector<MSG> > distribution(m);
    vector<int> core(10001, -1);
    vector<int> total(m);

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

    return distribution;
}

int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    
    map<int, queue<MSG> > messages;
    for (int i = 0; i < n; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages[msg.user].push(msg);
	}

    vector<vector<MSG> > distribution;

    auto distribution1 = strategy1(messages, m, c);
    int score1 = score(distribution1, c);

    auto distribution2 = strategy2(messages, m, c);
    int score2 = score(distribution2, c);

    if (score1 > score2) {
        distribution = distribution1;
    } else {
        distribution = distribution2;
    }

    // Test that strategy1 is working as expected
    distribution = distribution1;

    for(int i = 0; i < m; ++i)
    {
        cout << distribution[i].size();
        for(int j = 0; j < distribution[i].size(); ++j)
        {
            cout << ' ' << distribution[i][j].type << ' ' << distribution[i][j].user;
        }
        cout << endl;
    }

    // cout << "Score: " << score(distribution, c) << endl;
    return 0;
}

