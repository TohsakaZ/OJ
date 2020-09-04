
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <sstream>

using namespace std;

vector<string> article[100];
map<string, set<pair<int, int> > > vocabulary;

void cout_end()
{
    cout << "==========" << endl;
}

void cout_serperate()
{
    cout << "----------" << endl;
}

void cout_not_found()
{
    cout << "Sorry, I found nothing." << endl;
}

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    string empty;
    int article_number = 0;
    cin >> article_number;
    getline(cin, empty);

    int count = 0;
    while (count<article_number)
    {
        string templine;
        while (getline(cin, templine) && templine!="**********")
        {
            article[count].push_back(templine);
            for (int i = 0; i < templine.length();i++)
            {
                if (!((templine[i]>='A' && templine[i] <='Z') || (templine[i]>='a' && templine[i]<='z')))
                {
                    templine[i] = ' ';
                }
            }
            stringstream line_split(templine);
            string word;
            while (line_split >> word)
            {
                transform(word.begin(), word.end(), word.begin(),::tolower);
                vocabulary[word].insert(make_pair(count, article[count].size() - 1));
            }
        }
        count++;
    }
    int query_number = 0;
    cin >> query_number;
    getline(cin, empty);
    count = 0;
    while (count < query_number)
    {
        string query_templine;
        getline(cin, query_templine);
        stringstream line_split(query_templine);
        string word1, word2;
        if (query_templine.find("AND") != -1)
        {
            string temp;
            line_split >> word1 >> temp >> word2;
            if (vocabulary.count(word1)==0 || vocabulary.count(word2)==0)
            {
                cout_not_found();
            }
            else
            {
                set<int> article_list1,article_list2;
                map<int, set<int> > article_index;
                for (auto item: vocabulary[word1])
                {
                    article_list1.insert(item.first);
                    article_index[item.first].insert(item.second);
                }
                for (auto item: vocabulary[word2])
                {
                    article_list2.insert(item.first);
                    article_index[item.first].insert(item.second);
                }
                set<int> list_common;
                set_intersection(article_list1.begin(), article_list1.end(), article_list2.begin(), article_list2.end(), inserter(list_common,list_common.begin()));
                if (list_common.size()==0){
                    cout_not_found();
                }
                else{
                    for (auto article_id:list_common)
                    {
                        if (article_id!=*list_common.begin())
                        {
                            cout_serperate();
                        }

                        for (auto item:article_index[article_id])
                        {
                            cout << article[article_id][item]<< endl;
                        }
                    }
                }
            }
            cout_end();
        }
        else if (query_templine.find("OR")!=-1)
        {
            string temp;
            line_split >> word1 >> temp >> word2;
 
            if (vocabulary.count(word1)==0 && vocabulary.count(word2)==0)
            {
                cout_not_found();
            }
            else
            {
                set<int> article_list;
                map<int, set<int> > article_index;
                if (vocabulary.count(word1)!=0){
                    for (auto item: vocabulary[word1])
                    {
                        article_list.insert(item.first);
                        article_index[item.first].insert(item.second);
                    }
                }
                if (vocabulary.count(word2)!=0){
                    for (auto item: vocabulary[word2])
                    {
                        article_list.insert(item.first);
                        article_index[item.first].insert(item.second);
                    }
                }
                if (article_list.size()==0){
                    cout_not_found();
                }
                else{
                    for (auto article_id:article_list)
                    {
                        if (article_id!=*article_list.begin())
                        {
                            cout_serperate();
                        }
                        for (auto line_id :article_index[article_id])
                        {
                            cout << article[article_id][line_id]<< endl;
                        }
                    }
                }
            }
            cout_end();
        }
        else if (query_templine.find("NOT")!=-1)
        {
            line_split >> word1 >> word2;
            set<int> article_idx;
            for (int i = 0; i < article_number;i++)
            {
                article_idx.insert(i);
            }
            if (vocabulary.count(word2)!=0)
            {
                for (auto item:vocabulary[word2])
                {
                    article_idx.erase(item.first);
                }
            }
            if (article_idx.size()==0)
            {
                cout_not_found();
            }
            else{
                for (auto article_id:article_idx)
                {
                    if (article_id != *article_idx.begin())
                    {
                        cout_serperate();
                    }
                    for (auto line:article[article_id] )
                    {
                        cout << line << endl;
                    }
                }
            }

            cout_end();
        }
        else
        {
            line_split >> word1;
            if (vocabulary.count(word1) == 0)
            {
                cout_not_found();
                cout_end();
            }
            else
            {
                int pre_article_id = -1;
                for (auto item : vocabulary[word1])
                {
                    if (pre_article_id!=-1 && item.first!=pre_article_id)
                    {
                        cout_serperate();
                    }
                    pre_article_id = item.first;
                    cout << article[item.first][item.second] << endl;
                }
                cout_end();
            }
        }
        count++;
    }
}