#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct cdata
{
    string name, ip, user, key;
};

class Functions
{
     
    vector<cdata> connections; 
    public:
    
    void des(){
        fstream data;
        string name, ip, user, key;
        data.open("data.txt");
        if(data.is_open()){
            while(data>>name>>ip>>user>>key){
                connections.push_back({name, ip, user, key});
            }
        }else{
            cout<<"Data file doesn't exist"<<endl;
        }
    }
    
    void showConnections(){
        int i = 0;
        for(auto c:connections){
            cout<<++i<<". "<<c.name<<" "<<c.ip<<endl;
        }
    }
    
    void connect(int i){
        string command ="ssh ";
        string key="-i /.keys"+connections[i].key+" ";
        string login = connections[i].user+'@'+connections[i].ip;
        if(connections[i].key==""){
            command +=login;
        }else{
            
            command = command+key+login;
        }
        system(command.c_str());
    }

    void keyList(){
        //system("cd .keys");
        //system("ls -l");
        string path = ".keys";
        for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
    }


    void keysToDir(){}
};

void menu(){
    Functions f;
    f.des();
    int choice;
    int tmp;
    cout<<"1. Connect to a server\n2. Connection list\n3. Key list\n4. Add key to keys directory\n5. Add connection\n";
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
        case 2:
            cout<<"List: "<<endl;
            f.showConnections();
        break;
        case 3:
            f.keyList();
        break;
        case 4:
            system("mkdir a");
        break;

    }
}


int main(){
    menu();
    return 0;
}
