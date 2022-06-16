#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct cdata
{
    string name, ip, user, key;
};

class Functions
{
     
    vector<cdata> connections; 

    void des(){
        fstream data;
        data.open("data.txt");
    }
    public:
    void showConnections(){
        int i = 0;
        for(auto c:connections){
            cout<<++i<<". "<<c.name<<endl;
        }
    }
    void connect(int i){
        string command= "ssh ";
        if(connections[i].key=="")
        system(command.c_str());
    }
};

void menu(){
    Functions f;
    int choice;
    int tmp;
    cout<<"1. Connect to a server\n2. Connection list\n3. Key list\n4. Add key to keys folder\n5. Add connection\n";
    cout<<"Choice: ";
    cin>>choice;
    switch(choice){
        default:
        break;
        case 1:
            f.showConnections();
            cout<<"Which server you want to connect to?"<<endl;
            cout<<"Please enter number: ";
            cin>>tmp;
            f.connect(tmp-1);
        break;

    }
}


int main(){
    menu();
    return 0;
}
