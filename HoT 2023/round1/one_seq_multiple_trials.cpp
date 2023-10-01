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



int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> core(10001, -1);
    vector<vector<MSG> > distribution(m);
    vector<int> total(m, 0);

    map<int, queue<MSG> > messages;

    for (int i = 0; i < n; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages[msg.user].push(msg);
	}

    vector<vector<int> > cur_messages(201);

    for (auto it = messages.begin(); it != messages.end(); ++it)
    {
        int user = it->first;
        int cur_msg_type = it->second.front().type;

        cur_messages[cur_msg_type].push_back(user);
    }

    int max_set = 0;
    int max_set_type = 0;

    vector<MSG> init_seq;

    do {
        max_set = 0;
        for (size_t i = 1; i < 201; i++)
        {
            int size = cur_messages[i].size();
            if (size > max_set)
            {
                max_set=size;
                max_set_type=i;
            }
        }

        if (max_set == 0) break;

        for (int user : cur_messages[max_set_type])
        {
            MSG msg = messages[user].front();
            messages[user].pop();
            init_seq.push_back(msg);

            if (messages[user].empty())
            {
                messages.erase(user);
                continue;
            } else 
            {
                MSG next_msg = messages[user].front();
                cur_messages[next_msg.type].push_back(user);
            }
        }
        cur_messages[max_set_type].clear();
    } while (max_set > 0);

    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {0, m-1};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    vector<vector<MSG> > cur_distribution(m);
    int max_score = 0;
    for (int i = 0; i < 200; i++)
    {
        generate(core.begin(), core.end(), gen);

        for (int j = 0; j < m; j++)
        {
            cur_distribution[j].clear();
        }

        for (auto &msg : init_seq)
        {
            cur_distribution[core[msg.user]].push_back(msg);
        }

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

