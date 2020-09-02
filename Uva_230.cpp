#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Book
{
public:
    Book() : title(""), author(""){};
    Book(string title, string author) : title(title), author(author){};
    string title;
    string author;

    bool operator<(const Book &Other)const;
};

bool Book::operator<(const Book& Other) const
{
    return (this->author < Other.author || (this->author == Other.author and this->title < Other.title));
}

int main()
{
    ifstream fin;
    fin.open("input.txt");
    cin.rdbuf(fin.rdbuf());

    string buffer;
    map<string, Book> book_table;
    map<Book, bool> book_list;
    while (getline(cin,buffer) and buffer != "END")
    {
        Book newbook;
        int beg_loc = buffer.find('"');
        int end_loc = buffer.find('"', beg_loc + 1);
        newbook.title = buffer.substr(beg_loc, end_loc - beg_loc + 1);
        newbook.author= buffer.substr(end_loc + 5);
        book_list[newbook] = true;
        book_table[newbook.title] = newbook;
    }

    //priority_queue<Book> return_list;
    set<Book> return_list;
    while (getline(cin, buffer) and buffer != "END")
    {
        string oper =buffer.substr(0,6);
        if (oper=="BORROW"){
            string title = buffer.substr(7);
            book_list[book_table[title]] = false;
        }
        else if (oper=="RETURN"){
            string title = buffer.substr(7);
            //return_list.push(book_table[title]);
            return_list.insert(book_table[title]);
        }
        else if (oper=="SHELVE"){
            for (auto return_iter = return_list.begin(); return_iter != return_list.end(); return_iter++){
                Book return_book = *return_iter;
                auto iter = book_list.find(return_book);
                while (iter != book_list.begin() and !iter->second)
                {
                    iter--;
                }
                if (iter->second){
                    cout << "Put " << return_book.title << " after " << iter->first.title << endl;
                }
                else{
                    cout << "Put " << return_book.title << " first" << endl;
                }
                book_list[return_book] = true;
                //return_list.pop();
            }
            cout << "END" << endl;
            return_list.clear();
        }
    }
}