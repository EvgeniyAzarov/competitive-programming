#include <bits/stdc++.h>

using namespace std;

struct MSG {
	int type;
	int user;
	int time;
	int deadline;
};

int compute_score(vector<vector<MSG> > &distribution, int global_deadline) 
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

vector<int> determine_msgs_order(int cur_time, vector<int> &msg_users, map<int, queue<MSG> > &messages)
{
    int m = msg_users.size();
    vector<int> new_order;
    vector<int> out_time_msgs;
    
    for (int i = 0; i < m; i++)
    {
        MSG msg = messages[msg_users[i]].front();

        if (cur_time + msg.time <= msg.deadline)
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

int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> core(10001, -1);
    vector<int> user_execution_time(10001, 0);
    vector<int> core_execution_time(m, 0);

    vector<vector<MSG> > cur_distribution(m);
    vector<vector<MSG> > distribution(m);

    vector<pair<int, int> > total(m);
    for (size_t i = 0; i < m; i++) total[i] = make_pair(i, 0);

    map<int, queue<MSG> > messages_global;
    map<int, queue<MSG> > messages;

    for (int i = 0; i < n; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages_global[msg.user].push(msg);
        user_execution_time[msg.user] += msg.time;
	}

    // Assign cores, but not randomly
    for (int i = 0; i < 10001; i++)
    {
        if (user_execution_time[i] == 0) continue;

        int least_loaded = distance(core_execution_time.begin(), 
            min_element(core_execution_time.begin(), core_execution_time.end()));

        core[i] = least_loaded;
        core_execution_time[least_loaded] += user_execution_time[i]; 
    }

    // random_device rnd_device;
    // // Specify the engine and distribution.
    // mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    // uniform_int_distribution<int> dist {0, m-1};
    
    // auto gen = [&dist, &mersenne_engine](){
    //                return dist(mersenne_engine);
    //            };

    int max_score = 0;
    for (int i = 0; i < 1; i++)
    {
        messages = messages_global;

        // generate(core.begin(), core.end(), gen);
        for (int j = 0; j < m; j++) cur_distribution[j].clear();

        vector<vector<vector<int> > > core_cur_msgs(m, vector<vector<int> >(201));
        for (auto it = messages.begin(); it != messages.end(); ++it)
        {
            int user = it->first;
            int cur_msg_type = it->second.front().type;

            core_cur_msgs[core[user]][cur_msg_type].push_back(user);
        }

        int max_max_set;
        do {
            max_max_set = 0;

            // sort(total.begin(), total.end(), [](const auto &lhs, const auto &rhs) {
            //     return lhs.second < rhs.second;
            // });

            for (auto &core_info : total) 
            {
                int cn = core_info.first;

                int max_set = 0;
                int max_set_type = 0;
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

                vector<int> ordered_msgs = determine_msgs_order(core_info.second, core_cur_msgs[cn][max_set_type], messages);

                for (int user : ordered_msgs)
                {
                    MSG msg = messages[user].front();
                    messages[user].pop();
                    cur_distribution[cn].push_back(msg);
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

        int score = compute_score(cur_distribution, c);

        if (score > max_score)
        {
            distribution = cur_distribution;
            max_score = score;
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

    // cout << "Score: " << compute_score(distribution, c) << endl;
    return 0;
}

