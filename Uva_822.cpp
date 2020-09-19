#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;


class job_topic
{
public:
    int beg_time;
    int task_num;
    int interval_time;
    int proc_time;
    queue<int> table;
};

class person
{
public:
    int id;
    int level_num;
    int last_work_time;
    int finish_time;
    vector<int>  jobs;
    bool operator< (const person& Other)
    {
        return (last_work_time < Other.last_work_time || (last_work_time==Other.last_work_time && id < Other.id));
    }
};

int main()
{
    //ifstream input("input.txt");
    //cin.rdbuf(input.rdbuf());

    int case_nubmer=0;
    int count =0;
    string empty;
    while (cin >> case_nubmer  && case_nubmer !=0){
        getline(cin,empty);
        count++;
        int current_minute=INT_MAX;
        // map_task_info
        // get all task info
        map<int,job_topic> job_info;
        while (case_nubmer--){
            string templine;
            getline(cin,templine);
            stringstream line_split(templine);         
            int job_id,task_num,beg_time,proc_time,interval_time;
            line_split >> job_id;
            job_info[job_id]=job_topic();
            line_split >> job_info[job_id].task_num >> job_info[job_id].beg_time >> job_info[job_id].proc_time >> job_info[job_id].interval_time;
            current_minute = min(current_minute,job_info[job_id].beg_time);

            // add job
            task_num = job_info[job_id].task_num;
            beg_time = job_info[job_id].beg_time;
            while (task_num--){
                job_info[job_id].table.push(beg_time);
                beg_time+=job_info[job_id].interval_time;
            }
        }


        int person_number= 0;
        cin >> person_number;
        vector<person> person_list;
        while (person_number--){
            person k;
            int person_id,task_num;
            cin >> k.id >> k.level_num;
            task_num = k.level_num;
            while (task_num--){
                int job_id;
                cin >> job_id;
                k.jobs.push_back(job_id); 
            }
            person_list.push_back(k);
        }

        int total_minutes = 0;
        int job_number=job_info.size();
        while (job_number){
            int jump_time = INT_MAX;
            sort(person_list.begin(),person_list.end());
            for (auto& person_item : person_list){
                if (person_item.finish_time > current_minute){
                }
                else{
                    int next_time=INT_MAX;
                    for (int level_i = 0;level_i < person_item.level_num;level_i++){
                        int job_id = person_item.jobs[level_i];
                        if (job_info[job_id].table.empty()){
                            continue;
                        }
                        if (job_info[job_id].table.front() > current_minute){
                            next_time = min(next_time,job_info[job_id].table.front());
                            continue;
                        }
                        next_time = min(next_time,job_info[job_id].table.front());
                        // get job 
                        if (job_info[job_id].table.front() <= current_minute){
                            job_info[job_id].table.pop(); 
                            if (job_info[job_id].table.empty()){
                                job_number--;
                            }
                            person_item.last_work_time = current_minute;
                            next_time = current_minute + job_info[job_id].proc_time;
                            total_minutes = max(total_minutes,next_time);
                            break;
                        }
                    }
                    person_item.finish_time = next_time;
                }
                jump_time = min(jump_time,person_item.finish_time);
            }
            current_minute = jump_time;
        }
    
        cout << "Scenario "<< count << ": All requests are serviced within " << total_minutes << " minutes." << endl;
    }

}