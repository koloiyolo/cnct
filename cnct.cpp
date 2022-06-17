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
        string path = ".keys";
        string output;
        int i = 0;
        for (const auto & entry : fs::directory_iterator(path)){
        output = entry.path();
        output.replace(0,6, "");
        cout<<++i<<". "<<output<<endl;
        }
    }
    
    void keysManagement(){
        int choice;
        string tmp, tmp2, command;
        cout<<"1. Set permissions\n2. Rename\n Your choice: "<<endl;
        cin>>choice;
        switch (choice)
        {
            case 0:
            break;
            case 1:
                keyList();
                command = "sudo chmod 600 ";
                cout<<"Please enter full key name: ";
                cin.ignore();
                getline(cin, tmp);
                command += tmp;
                cout<<command<<endl;
                //system(command.c_str()); sudo todo
            break;
            case 2:
                keyList();
                command = "mv .keys/";
                cin.ignore();
                cout<<"Please enter key name: ";
                getline(cin, tmp);
                cout<<"Please eneter new key name: ";
                getline(cin, tmp2);
                command = command+tmp+" .keys/"+tmp2;
                system(command.c_str());
                for(auto &c:connections){
                    if(c.key.compare(tmp)){
                        c.key=tmp2;
                    }
                }
            break;
            case 3:
            break;
            default:
            cout<<"Wrong option, try again."<<endl;
            keysManagement();
            break;
        }
        
    }
};

void menu(){
    Functions f;
    f.des();
    int choice;
    int tmp;
    cout<<"1. Connect to a server\n2. Connection list\n3. Key list\n4. Key management\n5. Add connection\n";
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
            f.keysManagement();
        break;

    }
}


int main(){
    menu();
    return 0;
}
