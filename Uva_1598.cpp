#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <map>
#include <set>

using namespace std;



class buy_trade
{
public:
    buy_trade(int size,int price,int number):
        size(size),
        price(price),
        number(number)
    {
    }
    int price=0;
    int size=0;
    int number=0;

    bool operator < (const buy_trade& Other) const{
        return (price < Other.price || (price == Other.price && number > Other.number));
    }
};

class sell_trade 
{
public:
    sell_trade(int size,int price,int number):
        size(size),
        price(price),
        number(number)
    {
    }
    int price=0;
    int size=0;
    int number=0;

    bool operator < (const sell_trade& Other) const{
        return (price > Other.price || (price == Other.price && number > Other.number));
    }
};




int main()
{
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());
    //ofstream fout("output.txt");
    //cout.rdbuf(fout.rdbuf());
    int cnt = 0;
    int number_message=0;
    while (cin >> number_message){
        if (cnt!=0){
            cout << endl;
        }
        cnt++;
        string temp;
        getline(cin, temp);
        vector<int> size_list;
        vector<pair<int, string> > type_list;
        set<int> unvalid_map;
        priority_queue<buy_trade> buy_list;
        priority_queue<sell_trade> sell_list;
        map<int, int> buy_table;
        map<int, int> sell_table;
        for (int i = 0; i < number_message; i++)
        {
            string templine;
            getline(cin, templine);
            stringstream line_split(templine);
            string key_word;
            line_split >> key_word;
            if (key_word == "BUY"){
                int size,price;
                line_split >> size >> price;
                while (size > 0){
                    while (!sell_list.empty() and unvalid_map.count(sell_list.top().number)!=0 ){
                        sell_list.pop();
                    }
                    if (sell_list.empty() || price < sell_list.top().price){
                        break;
                    }
                       
                    auto top_trade = sell_list.top();
                    sell_list.pop();
                    int common_size = min(size, top_trade.size);
                    cout << "TRADE " << common_size << " " << top_trade.price << endl;
                    size -= common_size;
                    top_trade.size -= common_size;
                    sell_table[top_trade.price] -= common_size;
                    size_list[top_trade.number-1]-=common_size;
                    if (top_trade.size > 0)
                    {
                        sell_list.push(top_trade);
                    }
                }
                if (size > 0){
                    buy_list.push(buy_trade(size, price, i + 1));
                    buy_table[price] += size;
                }
                size_list.push_back(size);
                type_list.push_back(make_pair(price, "BUY"));
            }
            else if (key_word == "SELL"){
                int size, price;
                line_split >> size >> price;
                while (size > 0 ){
                    while (!buy_list.empty() and unvalid_map.count(buy_list.top().number)!=0){
                        buy_list.pop();
                    }
                    if (buy_list.empty() || price > buy_list.top().price){
                        break;
                    }

                    auto top_trade = buy_list.top();
                    buy_list.pop();
                    int common_size = min(size, top_trade.size);
                    cout << "TRADE " << common_size << " " << top_trade.price << endl;
                    size -= common_size;
                    top_trade.size -= common_size;
                    buy_table[top_trade.price] -= common_size;
                    size_list[top_trade.number - 1] -= common_size;
                    if (top_trade.size > 0)
                    {
                        buy_list.push(top_trade);
                    }
                }
                if (size >0){
                    sell_list.push(sell_trade(size, price, i + 1));
                    sell_table[price] += size;
                }
                size_list.push_back(size);
                type_list.push_back(make_pair(price, "SELL"));
            }
            else if (key_word == "CANCEL"){
                int number;
                line_split >> number;
                unvalid_map.insert(number);
                size_list.push_back(-1);
                type_list.push_back(make_pair(-1, "NONE"));
                if (size_list[number-1] > 0){
                    if (type_list[number-1].second == "BUY"){
                        buy_table[type_list[number - 1].first] -= size_list[number - 1];
                    }
                    else if(type_list[number-1].second == "SELL"){
                        sell_table[type_list[number - 1].first] -= size_list[number - 1];
                    }
                    size_list[number - 1] = 0;
                }
            }

            // count sum;
            cout << "QUOTE ";
            int bie_size = 0, bie_price = 0;
            while (!buy_list.empty() && unvalid_map.count(buy_list.top().number)!=0){
                buy_list.pop();
            }
            if (!buy_list.empty()){
                bie_price = buy_list.top().price;
                bie_size = buy_table[bie_price];
            }
            cout << bie_size << " " << bie_price;
            cout << " - ";

            int ask_size = 0, ask_price = 99999;
            while (!sell_list.empty() && unvalid_map.count(sell_list.top().number) != 0)
            {
                sell_list.pop();
            }
            if (!sell_list.empty()){
                ask_price = sell_list.top().price;
                ask_size = sell_table[ask_price];
            }
            cout << ask_size << " " << ask_price << endl;
        }
        string empty_line;
        //getline(cin,empty_line);
    }

}