#include <bits/stdc++.h>
using namespace std;

int N, m, global_deadline;
struct MSG {
	int type;
	int user;
	int time;
	int deadline;
};

bool check_deadline(MSG &msg, int cur_time) 
{
    return (cur_time + msg.time <= min(msg.deadline, global_deadline));
}

vector<vector<int> > greedy_initial(map<int, vector<MSG> > &messages)
{
    vector<vector<int> > distribution(m);
    vector<int> core(10001, -1);
    vector<int> ucm(10001, 0);

    vector<vector<int> > cur_messages(201);
    for (auto it = messages.begin(); it != messages.end(); ++it)
    {
        int user = it->first;
        int cur_msg_type = (it->second)[ucm[user]].type;

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
                MSG msg = messages[user][ucm[user]++];
                distribution[c].push_back(msg.user);
                if (core[msg.user] == -1)
                {
                    core[msg.user] = c;
                }

                if (ucm[user] == messages[user].size())
                {
                    continue;
                } else 
                {
                    MSG next_msg = messages[user][ucm[user]];
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

int score(vector<vector<int> > &distribution, map<int, vector<MSG> > &messages)
{
    int affinity_score = 0;
    int capability_score = 0;

    // user current message index
    vector<int> ucm(10001, 0);
    vector<int> total_time(m, 0);

    for (int i = 0; i < m; i++)
    {
        if (distribution[i].size() == 0) {
            continue;
        } 

        int prev_usr = distribution[i][0];
        MSG prev_msg = messages[prev_usr][ucm[prev_usr]++];
        capability_score += check_deadline(prev_msg, total_time[i]);
        total_time[i] += prev_msg.time;

        for (int j = 1; j < distribution[i].size(); j++)
        {
            int cur_usr = distribution[i][j];
            MSG cur_msg = messages[cur_usr][ucm[cur_usr]++];

            capability_score += check_deadline(cur_msg, total_time[i]);
            total_time[i] += cur_msg.time;

            affinity_score += (cur_msg.type == prev_msg.type);

            prev_msg = cur_msg; 
        }
    }

    return (affinity_score + capability_score) * 1e7 / (2 * N);
}

double get_random_number(double i,double j) //This function generates a random number between 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution (i,j);
    //cout<<"returning "<<(double(distribution(generator)))<<"\n";
    return double(distribution(generator));
    
}

double get_probability(int difference,double temperature) //This function finds the probability of how bad the new solution is
{
    return exp(-1*difference/temperature);
}

int main() 
{
    cin >> N >> m >> global_deadline;

    map<int, vector<MSG> > messages;
    for (int i = 0; i < N; i++)
    {
		MSG msg;
        cin >> msg.type >> msg.user >> msg.time >> msg.deadline;
		messages[msg.user].push_back(msg);
	}

    // vector<vector<int> > distribution = {
    //     {1, 3, 1},
    //     {2, 2}
    // };

    vector<vector<int> > distribution = greedy_initial(messages);
    vector<vector<int> > next_distribution(distribution);
    vector<vector<int> > final_distribution(distribution);

    int cur_score = score(next_distribution, messages);
    int best_score = score(next_distribution, messages);

    double temperature,coolingRate=0.8,absoluteTemperature=1e4,probability;

    // temperature=99999999999999999999999999999999999999999.0; //Initial Temperature
    temperature=99999999.0; //Initial Temperature
    //temperature=DBL_MAX;
    //cout<<"doing rs "<<rs<<"\n";
    while(temperature > absoluteTemperature) 
    {
        // int random_operation = int(get_random_number(0, 2));
        int random_operation = 0; 

        if (random_operation == 0)
        {
            // swap two users in core sequence
            int core = int(get_random_number(0, m));
            int pos1 = int(get_random_number(0, distribution[core].size()));
            int pos2 = int(get_random_number(0, distribution[core].size()));
            while (pos2 == pos1) 
            {
                pos2 = int(get_random_number(0, distribution[core].size()));
            }

            swap(distribution[core][pos1], distribution[core][pos2]);
        } else {
            // swap two core assignments
        }
        
        int new_score = score(distribution, messages);

        int difference = cur_score - new_score;
        
        if(difference < 0 or (difference > 0 and get_probability(difference,temperature) > get_random_number(0,1)))
        {
            next_distribution = distribution;
            cur_score = new_score + difference;
            // temperature=temperature*coolingRate;
        }

        if (cur_score > best_score)
        {
            final_distribution = distribution;
            best_score = cur_score;
        }
        
        temperature=temperature*coolingRate;
    }


    vector<int> ucm(10001, 0);
    for(int i = 0; i < m; ++i)
    {
        cout << final_distribution[i].size();
        for(int j = 0; j < final_distribution[i].size(); ++j)
        {
            int user = final_distribution[i][j];
            MSG msg = messages[user][ucm[user]++];
            cout << ' ' << msg.type << ' ' << msg.user;
        }
        cout << endl;
    }

    // cout << score(distribution, messages) << endl;
    return 0;
}