#include <iostream>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <map>
#include <set>
using namespace std;
class clock_time
{
public:
    clock_time():
        minutes(0)
    {}
    clock_time(int hour):
        minutes(hour*60)
    {}
    clock_time operator+(int Minutes) const
    {
        clock_time new_time;
        new_time.minutes = this->minutes + Minutes;
        return new_time;
    }
    bool operator<(const clock_time & Other) const
    {
        return this->minutes < Other.minutes;
    }
    bool operator<=(const clock_time& Other) const{
        return this->minutes <= Other.minutes;
    }
    bool operator==(const clock_time& Other) const{
        return this->minutes == Other.minutes;
    }
    string str_format(){
        int hour = minutes / 60;
        int min = minutes - hour * 60;
        stringstream k;
        k << hour << ":" << setw(2) << setfill('0') << min;
        return k.str();
    }
    int minutes;
};

struct cmp 
{
    bool operator()(const clock_time& a,const clock_time& b){
    return a.minutes > b.minutes;
    }
};

class person_record
{
public:
    int oerpate_id;
    int recover_id;
    clock_time operate_beg;
    clock_time operate_end;
    clock_time recover_beg;
    clock_time recover_end;
};
int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int num_operate, num_recover, beg_time, transport_time, preprare_operate, prepare_recover, num_patient;
    int cnt=0;
    while (cin >> num_operate >> num_recover >> beg_time >> transport_time >> preprare_operate >> prepare_recover >> num_patient)
    {
        vector< pair<int, int> > person_info;
        vector<string> person_list;
        queue<int> person_prepare_list;
        for (int i = 0; i < num_patient;i++){
            string person_name;
            cin >> person_name;
            person_prepare_list.push(i);
            person_list.push_back(person_name);
            int operate_time,recover_time;
            cin >> operate_time >> recover_time;
            person_info.push_back(make_pair(operate_time,recover_time));
        }
        clock_time current_time(beg_time);
        vector<clock_time> operate_time_info(num_operate);
        vector<int> operate_name(num_operate,-1);
        vector<bool> operate_working(num_operate, false);
        vector<clock_time> recover_time_info(num_recover);
        vector<int> recover_name(num_recover,-1);
        vector<bool> recover_working(num_recover, false);

        vector<person_record> record(num_patient);
        priority_queue<clock_time, vector<clock_time>, cmp> time_pool;
        time_pool.push(current_time);
        clock_time pre_time;
        pre_time.minutes = -1;
        while (!time_pool.empty())
        {
            current_time = time_pool.top();
            time_pool.pop();
            if (current_time == pre_time){
                continue;
            }
            pre_time = current_time;

            // make sure all avilabe recover bed
            queue<int> wait_for_recover;
            // get the person finish operating and all avliable operate room
            for (int i = 0; i < num_operate;i++){
                if (operate_time_info[i] <= current_time && operate_working[i]){
                    operate_working[i] = false;
                    if (operate_name[i] !=-1)
                    {
                        operate_working[i] = true;
                        operate_time_info[i] = current_time + preprare_operate;
                        wait_for_recover.push(operate_name[i]);
                        operate_name[i] = -1;
                        time_pool.push(operate_time_info[i]);
                    }
               }
                if (!operate_working[i] && !person_prepare_list.empty()){
                    operate_working[i] = true;
                    int person_id = person_prepare_list.front();
                    person_prepare_list.pop();
                    record[person_id].oerpate_id= i + 1;
                    record[person_id].operate_beg = current_time;
                    record[person_id].operate_end = current_time + person_info[person_id].first;
                    operate_time_info[i] = record[person_id].operate_end;
                    operate_name[i] = person_id;
                    time_pool.push(record[person_id].operate_end);
                }
            }
            // get all availabe recover bed and move to recover
            for (int i = 0; i < num_recover; i++)
            {
                if (recover_time_info[i] <= current_time && recover_working[i]){
                    recover_working[i] = false;
                    if (recover_name[i] !=-1){
                        recover_working[i] = true;
                        recover_time_info[i] = current_time + prepare_recover;
                        recover_name[i] = -1;
                        time_pool.push(recover_time_info[i]);
                    }
               }
                if (!recover_working[i] && !wait_for_recover.empty()){
                    recover_working[i] = true;
                    // move wait to the bed room;
                    int person_id= wait_for_recover.front();
                    wait_for_recover.pop();
                    record[person_id].recover_id = i + 1;
                    record[person_id].recover_beg = current_time + transport_time;
                    record[person_id].recover_end = current_time + transport_time + person_info[person_id].second;
                    recover_time_info[i] = record[person_id].recover_end;
                    recover_name[i] = person_id;
                    time_pool.push(record[person_id].recover_end);
                }
            }
        }
        cout << " Patient          Operating Room          Recovery Room" <<endl;
        cout << " #  Name     Room#  Begin   End      Bed#  Begin    End" << endl;
        cout << " ------------------------------------------------------" << endl;
        clock_time beg;
        beg.minutes = INT_MAX;
        clock_time end;
        map<int,int> room_table;
        map<int,int> bed_table;
        for (int i=0;i < person_list.size() ;i++){
            string person_name = person_list[i];
            person_record& record_person = record[i];
            beg = min(record_person.operate_beg, beg);
            end = max(record_person.recover_end, end);
            room_table[record_person.oerpate_id]+= record_person.operate_end.minutes - record_person.operate_beg.minutes;
            bed_table[record_person.recover_id]+= record_person.recover_end.minutes - record_person.recover_beg.minutes;
            printf("%2d  %-9s%3d   %5s   %5s     %2d   %5s   %5s\n",i+1,person_name.c_str(),record_person.oerpate_id,record_person.operate_beg.str_format().c_str(),
                record_person.operate_end.str_format().c_str(),record_person.recover_id,record_person.recover_beg.str_format().c_str(),
                record_person.recover_end.str_format().c_str());
        }
        double total_minutes = (end.minutes-beg.minutes)/100.0;

        cout << endl;
        cout << "Facility Utilization" << endl;
        cout << "Type  # Minutes  % Used" << endl;
        cout << "-------------------------" << endl;
        for (int i =0;i<num_operate;i++){
            if (num_patient==0){
                printf("%-5s%2d%8d   %5.2f\n","Room",i+1,room_table[i+1],0.0);
            }
            else{
                printf("%-5s%2d%8d   %5.2f\n","Room",i+1,room_table[i+1],room_table[i+1]/total_minutes);
            }
       }
        for (int i =0;i<num_recover;i++){
            if (num_patient==0){
                printf("%-5s%2d%8d   % 5.2lf\n","Bed",i+1,bed_table[i+1],0.0);
            }
            else{
                printf("%-5s%2d%8d   %5.2lf\n","Bed",i+1,bed_table[i+1],bed_table[i+1]/total_minutes);
            }
        }
        cout << endl;
    }
}