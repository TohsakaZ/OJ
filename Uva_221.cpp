#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class building
{
public:
    int id;
    double x;
    double y;
    double width;
    double depth;
    double height;

    double x2()
    {
        return x + width;
    }
};

class lines
{
public:

    lines(double x1,double x2)
    {
        left = x1;
        right = x2;
    }

    void add(double x1,double x2)
    {
        if (x2 <= left && x1 >= right)
        {
            return;
        }

        if (x1 < left)
        {
            x1 = left;
        }
        if ( x2 > right)
        {
            x2 = right;
        }
        if (all_line.size()==0)
        {
            all_line.push_back(make_pair(x1, x2));
        }
        else
        {
            auto iter_begin = all_line.begin();
            while (iter_begin->second < x1 && iter_begin!=all_line.end())
                iter_begin++;
            if (iter_begin == all_line.end())
            {
                all_line.push_back(make_pair(x1, x2));
                return;
            }

            if (iter_begin->first > x1)
            {
                // insert
                iter_begin = all_line.insert(iter_begin, make_pair(x1, x1));
            }
            int beg_id = iter_begin - all_line.begin();

            //now include 
            if (iter_begin->second >= x2){
                return;
            }

            //erase and merge
            for (auto iter = iter_begin + 1; iter != all_line.end();)
            {
                if (iter->first > x2)
                {
                    break;
                }
                else if (iter->second >= x2)
                {
                    x2 = iter->second;
                    iter = all_line.erase(iter);
                    break;
                }
                else
                {
                    iter = all_line.erase(iter);
                    continue;
                }
            }

            all_line[beg_id].second = x2;
        }
    }

    bool is_visible()
    {
        if (all_line.size() ==0 )
        {
            return true;
        }

        if (all_line.size() == 1 && (all_line[0].first>left || all_line[0].second < right) )
        {
            return true;
        }

        if (all_line.size() > 1)
        {
            return true;
        }

        return false;
    }

    vector<pair<double, double> > all_line;
    double left;
    double right;
};

bool compare_building_by_height(const building& left,const building& right)
{
    if (left.height < right.height)
    {
        return true;
    }
    else if (left.height == right.height)
    {
        return left.y > right.y;
    }
    else
    {
        return false;
    }
}

bool compare_building_by_direct(const building& left,const building& right)
{
    return (left.x < right.x || (left.x == right.x && left.y < right.y));
}


building read_buildings()
{
    building newone;
    cin >> newone.x >> newone.y >> newone.width >> newone.depth >> newone.height;
    return newone;
}

int main()
{
    //ifstream fin;
    //fin.open("input");
    //cin.rdbuf(fin.rdbuf());
    int number;
    int count= 0;
    while (cin >> number && number != 0)
    {
        count++;
        // blank line
        if (count>1){
            cout << endl;
        }
        cout << "For map #" << count << ", the visible buildings are numbered as follows:" << endl;
        // reading maps
        vector<building> maps;
        for (int i = 0; i < number; i++)
        {
            maps.push_back(read_buildings());
            maps[maps.size() - 1].id = i + 1;
        }

        // according to height
        vector<building> map_new = maps;
        sort(map_new.begin(), map_new.end(), compare_building_by_height);
        //cout << map_new[0].id << endl;

        vector<building> visible_id;
        for (int i = map_new.size() - 1; i >= 0;i--)
        {
            lines invisble(map_new[i].x,map_new[i].x2());
            for (int j = i + 1; j < map_new.size(); j++)
            {
                // behind building;
                if (map_new[j].y > map_new[i].y)
                {
                    continue;
                }

                // no before the building
                if (map_new[j].x >= map_new[i].x2()
                || map_new[i].x >= map_new[j].x2())
                {
                    continue;
                }

                invisble.add(map_new[j].x, map_new[j].x2());
            }

            if (invisble.is_visible())
            {
                visible_id.push_back(maps[map_new[i].id-1]);
            }
        }

        // sort visible buildings
        sort(visible_id.begin(), visible_id.end(), compare_building_by_direct);

        // print
        for (int i = 0; i < visible_id.size();i++)
        {
            if (i != 0){
                cout << " ";
            }
            cout << visible_id[i].id;
        }
        cout << endl;

    }

}