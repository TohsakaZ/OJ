#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

const string empty_prefix="   ";

class item
{
public:
    item():name(""),exist(false){};
    item(string n):name(n),exist(false){};

    string name;
    int count;
    bool exist;
    bool explicity_install;

    vector<item*> depend;
 
    int support_num;

    bool operator<(const item& Other){
        if (!Other.exist || this->exist && this->count < Other.count ){
            return true;
        }
        else
        {
            return false;
        }
        
    }
    bool install(bool explicy){
        if (exist){
            return false;
        }
        exist=true;
        support_num=0;
        explicity_install=explicy;
        
        for (auto i:depend){
            if (!i->exist) {
                i->install(false);
            }
            i->support_num+=1;
        }

        count = item::install_count++;
        cout << empty_prefix <<  "Installing "<< name << endl;
        return true;
    }

    bool uninstall(bool expliciy){
        if (support_num !=  0 ){
            return false;
        }
        if (!exist){
            cout << empty_prefix << name << " is not installed." << endl;
            return true;
        }

        queue<item*> q;
        q.push(this);
        while (!q.empty()){
            item* now = q.front(); q.pop();
            now->exist =false;
            cout << empty_prefix << "Removing " << now->name << endl;
            for (auto i:now->depend){
                i->support_num-=1;
                if (i->support_num==0 && !i->explicity_install){
                    q.push(i);
                }
            }
        }
        return true;
    }

    static int install_count;
    static map<string,item*> item_list;
    static void list_exist(){
        vector<item> list;
        for (auto iter =item_list.begin();iter!=item_list.end();iter++){
            if (iter->second->exist){
                list.push_back(*iter->second);
            }
        }
        sort(list.begin(),list.end());
        for (auto& i : list){
            cout << empty_prefix <<  i.name << endl;
        }
    }

    static item* insert(string name){
        if (item_list.count(name)==0){
            item_list[name] = new item(name);
        }
        return item_list[name];
    }
    static void clear(){
        for (auto i : item::item_list){
            delete i.second;
        }
        item_list.clear();
    }
};

int item::install_count=0;
map<string,item*> item::item_list;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    string templine;
    while (getline(cin,templine)){
        cout << templine << endl; 
        stringstream temp_split(templine);
        temp_split >> templine;
        if (templine=="END"){
            item::clear();            
            continue;
        }
        else if (templine == "DEPEND"){
            temp_split >> templine;
            auto item1 = item::insert(templine);
            while (temp_split >> templine){
                item1->depend.push_back(item::insert(templine));
            }
        }
        else if (templine == "INSTALL"){
            temp_split >> templine;
            auto i = item::insert(templine);
            if (!i->install(true)){
                cout << empty_prefix << i->name << " " << "is already installed." << endl;
            }
        }
        else if (templine == "REMOVE"){
            temp_split >> templine;
            auto i = item::insert(templine);
            if (!i->uninstall(true)){
                cout << empty_prefix << i->name << " " << "is still needed." << endl;
            }
        }
        else if (templine == "LIST"){
            item::list_exist();
        }
    }

}