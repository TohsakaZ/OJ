#include <iostream>
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

class operating_person
{
public:
    operating_person(string name,int operate_id,clock_time next_t):
        name(name),
        next_t(next_t),
        operate_id(operate_id)
    {}

    bool operator<(const operating_person& Other) const{
        return next_t < Other.next_t || (next_t == Other.next_t and operate_id <Other.operate_id);
    }
    string name;
    clock_time next_t;
    int operate_id;
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
    string templine;
    while (getline(cin,templine)){
        int num_operate,num_recover,beg_time,transport_time,preprare_operate,prepare_recover,num_patient;
        stringstream line_split(templine);
        line_split >> num_operate >> num_recover >> beg_time >> transport_time >> preprare_operate >> prepare_recover >> num_patient;
        map<string,pair<int,int> > person_info;
        vector<string> person_list;
        queue<string> person_prepare_list; 
        while (num_patient--){
            string person_name;
            cin >> person_name;
            person_prepare_list.push(person_name);
            person_list.push_back(person_name);
            int operate_time,recover_time;
            cin >> operate_time >> recover_time;
            person_info[person_name]=make_pair(operate_time,recover_time);
        }
        clock_time current_time(beg_time);
        vector<operating_person> operate_list; // time for person(operate+transport)
        map<int,clock_time> recover_time_info;
        map<int,clock_time> operate_time_info; // time for bed(oeprate+ prepare)
        map<string,person_record> record;

        while (!person_prepare_list.empty() || !operate_list.empty())
        {
            //cout << "current time is " << current_time.str_format() << endl;
            // get the next time;
            clock_time jump_time;
            jump_time.minutes=INT_MAX;
            // make sure all avilabe recover bed
            set<int> avalible_recover_bed;
            for (int i=1;i<= num_recover;i++){
                if (recover_time_info[i] < current_time){
                    avalible_recover_bed.insert(i);
                }
            }

            set<operating_person> wait;
            // get the person finish operating
            for (auto iter =operate_list.begin() ;iter != operate_list.end();){
                if (iter->next_t == current_time){
                    wait.insert(*iter);
                    iter = operate_list.erase(iter);
                    continue;
                }
                else{
                    jump_time = min(jump_time,iter->next_t);
                    iter++;
                    continue;
                }
            }

            // move to the recover
            auto recover_bed_iter = avalible_recover_bed.begin();
            for (auto person_item:wait){
                int recover_bed = *recover_bed_iter;
                recover_bed_iter++;
                record[person_item.name].recover_id = recover_bed;
                record[person_item.name].recover_beg = current_time;
                record[person_item.name].recover_end = current_time+person_info[person_item.name].second;
                recover_time_info[recover_bed] = record[person_item.name].recover_end+prepare_recover;
            }

            // get the avalible operate bed;
            set<int> avalible_operate_bed;
            for (int i = 1;i<=num_operate ;i++){
                if (operate_time_info[i] <= current_time){
                    avalible_operate_bed.insert(i);
                }
                else{
                    jump_time = min(jump_time,operate_time_info[i]);
                }
            }
            // move to operate
            auto operate_iter= avalible_operate_bed.begin();
            while (operate_iter!=avalible_operate_bed.end() && !person_prepare_list.empty()){
                auto person_name = person_prepare_list.front();
                person_prepare_list.pop();
                record[person_name].oerpate_id = *operate_iter;
                record[person_name].operate_beg = current_time;
                record[person_name].operate_end = current_time + person_info[person_name].first;
                operate_time_info[*operate_iter] = record[person_name].operate_end+preprare_operate;
                operate_list.push_back(operating_person(person_name,*operate_iter,record[person_name].operate_end+transport_time));

                jump_time=min(jump_time,operate_time_info[*operate_iter]);
                jump_time=min(jump_time,operate_list[operate_list.size()-1].next_t);

                operate_iter++;
            }

            current_time = jump_time;
        }
        cout << " Patient          Operating Room          Recovery Room" <<endl;
        cout << " #  Name     Room#  Begin   End      Bed#  Begin    End" << endl;
        cout << " ------------------------------------------------------" << endl;
        clock_time beg(beg_time);
        clock_time end;
        map<int,int> room_table;
        map<int,int> bed_table;
        for (int i=0;i < person_list.size() ;i++){
            string person_name = person_list[i];
            end = max(record[person_name].recover_end,end);
            room_table[record[person_name].oerpate_id]+= record[person_name].operate_end.minutes - record[person_name].operate_beg.minutes;
            bed_table[record[person_name].recover_id]+= record[person_name].recover_end.minutes - record[person_name].recover_beg.minutes;
            cout << setiosflags(ios::right) <<setw(2) << i+1 << setw(2) << "";
            cout << setw(9) << setiosflags(ios::left) << person_name 
                 << setw(3) << setiosflags(ios::left) << record[person_name].oerpate_id  <<setw(2) << ""
                 << setw(1) << "" << setw(5) << record[person_name].operate_beg.str_format() << setw(3) << ""
                 << setw(5) << record[person_name].operate_end.str_format() << setw(5) << ""
                 << setw(2) << setiosflags(ios::right) << record[person_name].recover_id << setw(3) << ""
                 << setw(5) << record[person_name].recover_beg.str_format() << setw(3) << "" 
                 << setw(5) << record[person_name].recover_end.str_format() << endl;
             
        }
        double total_minutes = (end.minutes-beg.minutes)/100.0;

        cout << endl;
        cout << "Facility Utilization" << endl;
        cout << "Type  # Minutes  % Used" << endl;
        cout << "-------------------------" << endl;
        for (int i =0;i<num_operate;i++){
            cout << setw(4) << "Room"  << setw(1) << ""
                 << setw(2) << setiosflags(ios::right) << i+1
                 << setw(8) << room_table[i+1]
                 << setw(3) << "" 
                 << setw(5) << setiosflags(ios::fixed) << setprecision(2) << room_table[i+1]/total_minutes 
                 << endl;
        }
        for (int i =0;i<num_recover;i++){
            cout << setw(3) << "Bed"  << setw(2) << ""
                 << setw(2) << setiosflags(ios::right) << i+1
                 << setw(8) << bed_table[i+1]
                 << setw(3) << "" 
                 << setw(5) << setiosflags(ios::fixed) << setprecision(2) << bed_table[i+1]/total_minutes 
                 << endl;
        }

    }



}