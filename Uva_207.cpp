#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// quality people number
const int QNum = 70;

void read_palyer_info(map<string,vector<int> > & player_info)
{
    // read player infomation
    int player_nubmer = 0;
    cin >> player_nubmer;

    int count = player_nubmer;

    // read all player info
    while (count-- >0)
    {
        char name[20];
        vector<int> score;
        cin.get(name, 20);
        int score_nubmer = 0;
        bool dq_flag = false;
        while (score_nubmer++ < 4 )
        {
            string score_str;
            cin >> score_str;
            if (score_str == "DQ" && score_nubmer < 3)
            {
                dq_flag = true;
                break;
            }
            stringstream temp_dbl(score_str);
            int temp_int ;
            temp_dbl >> temp_int;
            score.push_back(temp_int);
        }
        if (dq_flag)
        {
            continue;
        }
        else
        {
            player_info[string(name, 20)] = score;
        }
    }
 
}

class first
{
public:
    first(string name, double score)
    {
        this->name = name;
        this->score = score;
    };


    bool operator <(const first& Other) const
    {
        return this->score < Other.score;
    };

    bool operator ==(const first& Other) const
    {
        return this->score == Other.score;
    };

    string name;
    double score;

};


void print_result(string name,string place,vector<int> score,double prize = -1)
{
    cout << ios::left << setw(21) << name
         << ios::left << setw(10) << place;

    int sum = 0;
    for (int i = 0; i < 4;i++)
    {
        if (i >= score.size()){
            cout << setw(5) << "";
        }
        else{
            cout << ios::left << setw(5) << score[i];
            sum += score[i];
        }
    }
    if (score.size() <4 ){
        cout << setw(10) << "DQ" ;
    }
    else{
        cout << ios::left << setw(10) << sum;
        if (prize >=0){
            cout << "$"
                 << ios::right << setw(9) << prize ;
        }
    }
    cout << endl;
}

int main()
{
    int case_number;
    cin >> case_number;
    while (case_number-- > 0)
    {
        string blank_temp;
        cin >> blank_temp;

        // read tototal value and percentage
        int total_value;
        cin >> total_value;
        vector<double> percentage(QNum);
        int count = QNum;
        while (count-- > 0)
        {
            cin >> percentage[QNum - count - 1];
        }

        // read player info
        map<string, vector<int> > player_info;
        read_palyer_info(player_info);

        //  First sort 70
        vector<first> first_result; 
        for (auto& info : player_info)
        {
            first_result.push_back(first(info.first, info.second[0] + info.second[1]));
        }
        sort(first_result.begin(), first_result.end());
        double cut_score = first_result[69].score;
        auto cut_iter = upper_bound(first_result.begin(), first_result.end(),first("",cut_score));
        int cut_num = cut_iter - first_result.begin() + 1;

        // second 
        vector<first> second_result;
        vector<string> dq_player;
        sort(second_result.begin(),second_result.end());
        for (int i = 0; i < cut_num;i++)
        {
            string player_name = first_result[i].name;
            if (player_info[player_name].size()<4){
                dq_player.push_back(player_name);
            }
            else{
                double total = 0;
                for (auto score : player_info[player_name])
                {
                    total += score;
                }
                second_result.push_back(first(player_name, total));
            }
        }

        sort(second_result.begin(), second_result.end());
        // compute prize size
        // first prize

        // output final result
        int place_now = 1;
        int prize_now = 1;
        auto player_now = second_result.begin();
        cout << "Player Name          Place     RDJ  RD2  RD3  RD4  TOTAL     Money Won" << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        while (place_now < 70)
        {
            int num_amateuer = 0;
            int num_prize = 0;
            vector<string> amateuer;
            vector<string> prize;
            int marker_now = player_now->score;
            while (player_now->score == marker_now)
            {
                string name = player_now->name;
                if (name[name.length()-1] == '*' )
                {
                    amateuer.push_back(name);
                }
                else{
                    prize.push_back(name);
                }
                player_now++;
            }
            int money = 0;
            // compute total
            for (int i = 0; i < prize.size();i++)
            {
                money += total_value * percentage[prize_now + i];
            }
            money /= prize.size();
            
            // print non-amateure
            string place_str = to_string(place_now);
            if (prize.size() > 1){
                place_str += "T";
            }
            for (int i = 0; i < prize.size(); i++)
            {
                string name = prize[i];
                print_result(name, place_str , player_info[name], money);
            }

            // print amateure
            place_str = to_string(place_now);
            for (int i = 0; i < amateuer.size(); i++)
            {
                string name = amateuer[i];
                print_result(name, place_str, player_info[name]);
            }

            place_now += amateuer.size() + prize.size();
            prize_now += prize.size();
        }

        // cout one blank line
        cout << endl;
    }
}