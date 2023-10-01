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

vector<vector<MSG> > strategy1(map<int, queue<MSG> > messages, int m)
{
    vector<vector<MSG> > distribution(m);
    vector<int> core(10001, -1);

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
        for (int c = 0; c < m; c++)
        {
            // remove users which are already assigned to other cores
            for (size_t i = 1; i < 201; i++)
            {
                if (core_cur_msgs[c][i].empty()) continue;

                auto it = core_cur_msgs[c][i].begin();
                while(it != core_cur_msgs[c][i].end()) 
                {
                    if (core[*it] != -1 && core[*it] != c) it = core_cur_msgs[c][i].erase(it);
                    else it++;
                }
            }

            max_set = 0;
            for (size_t i = 1; i < 201; i++)
            {
                int size = core_cur_msgs[c][i].size();
                if (size > max_set)
                {
                    max_set=size;
                    max_set_type=i;
                }
            }

            if (max_set == 0) continue;

            for (int user : core_cur_msgs[c][max_set_type])
            {
                MSG msg = messages[user].front();
                messages[user].pop();
                distribution[c].push_back(msg);
                if (core[msg.user] == -1)
                {
                    core[msg.user] = c;
                }
                

                if (messages[user].empty())
                {
                    messages.erase(user);
                    continue;
                } else 
                {
                    MSG next_msg = messages[user].front();
                    core_cur_msgs[c][next_msg.type].push_back(user);
                }
            }
            core_cur_msgs[c][max_set_type].clear();
            if (max_set > max_max_set)
            {
                max_max_set = max_set;
            }
            
        }
    } while (max_max_set > 0);


    return distribution;
}

vector<vector<MSG> > strategy2(map<int, queue<MSG> > messages, int m)
{
    vector<vector<MSG> > distribution(m);
    vector<int> core(10001, -1);

    int total_users = messages.size();

    vector<vector<int> > cur_messages(201);

    for (auto it = messages.begin(); it != messages.end(); ++it)
    {
        int user = it->first;
        int cur_msg_type = it->second.front().type;

        cur_messages[cur_msg_type].push_back(user);
    }

    vector<vector<vector<int> > > core_cur_msgs(m, cur_messages);
    
    int max_max_set = 0;
    int chosen_core;
    int chose_type;

    bool all_cores_assigned = false;
    int assigned_users = 0;
    do {
        max_max_set = 0;
        for (int c = 0; c < m; c++)
        {
            // remove users which are already assigned to other cores
            for (size_t i = 1; i < 201; i++)
            {
                if (core_cur_msgs[c][i].empty()) continue;

                auto it = core_cur_msgs[c][i].begin();
                while(it != core_cur_msgs[c][i].end()) 
                {
                    if (core[*it] != -1 && core[*it] != c) it = core_cur_msgs[c][i].erase(it);
                    else it++;
                }
            }

            int max_set = 0;
            int max_set_type = 0;
            for (size_t i = 1; i < 201; i++)
            {
                int size = core_cur_msgs[c][i].size();
                if (size > max_set)
                {
                    max_set=size;
                    max_set_type=i;
                }
            }

            if (max_set > max_max_set) {
                max_max_set = max_set;
                chosen_core = c;
                chose_type = max_set_type;

                if (all_cores_assigned) break;
            }
        }

        if (max_max_set == 0) break;
        
        for (int user : core_cur_msgs[chosen_core][chose_type])
        {
            MSG msg = messages[user].front();
            messages[user].pop();
            distribution[chosen_core].push_back(msg);
            if (core[msg.user] == -1)
            {
                core[msg.user] = chosen_core;
                assigned_users++;
                if (assigned_users == total_users) all_cores_assigned = true;
            }

            if (messages[user].empty())
            {
                messages.erase(user);
                continue;
            } else 
            {
                MSG next_msg = messages[user].front();
                core_cur_msgs[chosen_core][next_msg.type].push_back(user);
            }
        }
        core_cur_msgs[chosen_core][chose_type].clear();

    } while (max_max_set > 0);

    return distribution;
}

int main()
{
    int n, m, global_deadline;
    cin >> n >> m >> global_deadline;
    
    map<int, queue<MSG> > messages;
    for (int i = 0; i < n; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages[msg.user].push(msg);
	}

    vector<vector<MSG> > distribution;

    auto distribution1 = strategy1(messages, m);
    int score1 = score(distribution1, global_deadline);

    auto distribution2 = strategy2(messages, m);
    int score2 = score(distribution2, global_deadline);

    if (score1 > score2) {
        distribution = distribution1;
    } else {
        distribution = distribution2;
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

    // cout << "Score: " << score(distribution, c) << endl;
    return 0;
}

