#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <deque>
#include <map>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_number;
    cin >> case_number;
    for (int case_i=0;case_i<case_number;case_i++){
        //string empty_line;
        //getline(cin,empty_line);
        if (case_i > 0){
            cout << endl;
        }
        int num_program,t_program;
        int a[5];
        cin >> num_program >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> t_program;  
        vector< queue<string> >program_state(num_program);
        deque<int> wait_q;
        queue<int> block_q;
        string empty;
        getline(cin,empty);
        for (int i =0;i<num_program;i++){
            wait_q.push_back(i);
            string templine;
            while (getline(cin,templine) && templine!="end") {
                program_state[i].push(templine);
            }
            program_state[i].push(templine);
        }

        map<char,int> v_table;
        bool lock = false;
        while (!wait_q.empty()){
            int id = wait_q.front();
            wait_q.pop_front();
            int left_time = t_program;
            bool add=true;
            while (left_time >0){
                string state = program_state[id].front();
                bool exec=true;
                if (state.find("=")!=string::npos){
                    stringstream line_split(state);                                        
                    char v;
                    string temp;
                    int k;
                    line_split >> v >> temp >> k;
                    v_table[v] = k;
                    left_time -=a[0];
                } 
                else if (state.find("print")!=string::npos){
                    char k = state[state.length()-1];
                    if (v_table.count(k)==0){
                        v_table[k] = 0;
                    }
                    cout << id+1 << ": "  << v_table[k] << endl;
                    left_time -= a[1];
                }
                else if (state.substr(0,4)=="lock"){
                    if (lock){
                        block_q.push(id);
                        add=false;
                        break;
                    }
                    else{
                        lock=true;
                        left_time -=a[2];
                    }
                }
                else if (state.substr(0,6) == "unlock"){
                    lock=false;
                    if (!block_q.empty()){
                        wait_q.push_front(block_q.front());
                        block_q.pop();
                    }
                    left_time -= a[3];
                }
                else if (state.find("end")!=string::npos){
                    add =false;
                    break;
                }
                program_state[id].pop();
            }
            
            if (add){
                wait_q.push_back(id);
            }
        }
    }
}