#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
const string PREFIX = "     ";

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());
    // reading all mta infomation
    string line;
    map<string, set<string> > MTA_info;
    while (getline(cin, line) && line != "*")
    {
        //cout << line << endl;
        stringstream linestream(line);
        string temp, MTA_name;
        int number;
        linestream >> temp >> MTA_name >> number;
        for (int i = 0; i < number;i++)
        {
            string name;
            linestream >> name;
            MTA_info[MTA_name].insert(name);
        }
    }


    // process  send mail
    string templine;
    while (cin >> templine && templine != "*")
    {
        set<string> receiver_table;
        vector<string> mta_order;
        map<string, vector<string> > recevier_info;
        string sender, send_mta;
        int idx = templine.find("@");
        sender = templine.substr(0, idx);
        send_mta = templine.substr(idx + 1);

        // get receiver
        while (cin >> templine && templine != "*")
        {
            string rec_mta, receiver;
            int idx = templine.find("@");
            receiver = templine.substr(0, idx);
            rec_mta = templine.substr(idx + 1);
            if (recevier_info.count(rec_mta) == 0)
            {
                mta_order.push_back(rec_mta);
            }

            if (receiver_table.count(templine) == 0)
            {
                recevier_info[rec_mta].push_back(receiver);
                receiver_table.insert(templine);
            }
        }

        // get message
        // skip * line
        getline(cin, templine);
        vector<string> infomation;
        while (getline(cin, templine) && templine != "*")
        {
            infomation.push_back(templine);
        }
        //cout << "infomation line number:" << infomation.size() << endl;

        // printout
        for (auto mta : mta_order)
        {
            cout << "Connection between " << send_mta << " and " << mta << endl;
            cout << PREFIX << "HELO " << send_mta << endl;
            cout << PREFIX << 250 << endl;
            cout << PREFIX << "MAIL FROM:<" << sender + "@" + send_mta << ">" << endl;
            cout << PREFIX << 250 << endl;
            int valid_user = 0;
            for (auto receiver : recevier_info[mta])
            {
                cout << PREFIX << "RCPT TO:<" << receiver + "@" + mta << ">" << endl;
                if (MTA_info[mta].count(receiver) == 0)
                {
                    cout << PREFIX << 550 << endl;
                }
                else
                {
                    valid_user++;
                    cout << PREFIX << 250 << endl;
                }
            }
            if (valid_user > 0)
            {
                cout << PREFIX << "DATA" << endl;
                cout << PREFIX << 354 << endl;
                for (auto message : infomation)
                {
                    cout << PREFIX << message << endl;
                }
                cout << PREFIX << "." << endl;
                cout << PREFIX << 250 << endl;
            }
            cout << PREFIX << "QUIT" << endl;
            cout << PREFIX << 221 << endl;
        }
    }
}