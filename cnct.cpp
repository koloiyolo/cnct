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
    void ser()
    {
        ofstream("data.txt");
        fstream data;
        data.open("data.txt");
        for (auto c : connections)
        {
            data << c.name << " " << c.ip << " " << c.user << " " << c.key << endl;
        }
        data.close();
    }
    void des()
    {
        fstream data;
        string name, ip, user, key;
        data.open("data.txt");
        if (data.is_open())
        {
            while (data >> name >> ip >> user >> key)
            {
                connections.push_back({name, ip, user, key});
            }
        }
        else
        {
            cout << "Data file doesn't exist" << endl;
        }
    }

    void showConnections()
    {
        int i = 0;
        for (auto c : connections)
        {
            cout << ++i << ". " << c.name << " " << c.ip << endl;
        }
        cout << "\n";
    }

    void connect(int i)
    {
        string command = "ssh ";
        string key = "-i .keys/" + connections[i].key + " ";
        string login = connections[i].user + '@' + connections[i].ip;
        if (connections[i].key == "")
        {
            command += login;
        }
        else
        {

            command = command + key + login;
        }
        system(command.c_str());
    }

    void keyList()
    {
        string path = ".keys";
        string output;
        int i = 0;
        for (const auto &entry : fs::directory_iterator(path))
        {
            output = entry.path();
            output.replace(0, 6, "");
            cout << ++i << ". " << output << endl;
        }
        cout << "\n";
    }

    void keysManagement()
    {
        int choice;
        string tmp, tmp2, command;
        cout << "1. Set permissions\n2. Rename\n Your choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            break;
        case 1:
            keyList();
            command = "sudo chmod 600 ";
            cout << "Please enter full key name: ";
            cin.ignore();
            getline(cin, tmp);
            command += tmp;
            cout << command << endl;
            // system(command.c_str()); sudo todo
            break;
        case 2:
            keyList();
            command = "mv .keys/";
            cin.ignore();
            cout << "Please enter key name: ";
            getline(cin, tmp);
            cout << "Please eneter new key name: ";
            getline(cin, tmp2);
            command = command + tmp + " .keys/" + tmp2;
            system(command.c_str());
            for (auto &c : connections)
            {
                if (c.key.compare(tmp))
                {
                    c.key = tmp2;
                }
            }
            break;
        case 3:
            break;
        default:
            cout << "Wrong option, try again." << endl;
            keysManagement();
            break;
        }
        cout << "\n";
    }

    void connectManagement()
    {
        int choice;
        cout << "1. Add connection\n2. Remove connection\n";
        cout << "Choice: ";
        cin >> choice;
        string user, ip, key, name;
        switch (choice)
        {
        case 1:
            cin.ignore();
            cout << "What is your user name?: ";
            getline(cin, user);
            cout << "What is IP address of this server?: ";
            getline(cin, ip);
            keyList();
            cout << "What is the name of the private key?: ";
            getline(cin, key);
            cout << "How would you like to name it?: ";
            getline(cin, name);
            if ((user != "") && (ip != ""))
            {
                connections.push_back({name, ip, user, key});
                cout << "Connection created succesfully\n";
            }
            else
            {
                cout << "Wrong data" << endl;
            }
            break;
        case 2:
            showConnections();
            cout<<"Which one you want to remove?\nChoice: ";
            cin>>choice;
            connections.erase(connections.begin()+choice-1);
            break;
        }
        cout << "\n";
    }
};

void menu(Functions &f)
{
    int choice;
    int tmp;
    cout << "1. Connect to a server\n2. Connection list\n3. Key list\n4. Key management\n5. Connection management\n0. Exit\n";
    cout << "Choice: ";
    cin >> choice;
    cout << "\n";
    switch (choice)
    {
    default:
        cout << "Wrong choice, please try again" << endl;
        menu(f);
        break;
    case 0:
        break;
    case 1:
        f.showConnections();
        cout << "Which server you want to connect to?" << endl;
        cout << "Please enter number: ";
        cin >> tmp;
        f.connect(tmp - 1);
        break;
    case 2:
        cout << "List: " << endl;
        f.showConnections();
        menu(f);
        break;
    case 3:
        f.keyList();
        menu(f);
        break;
    case 4:
        f.keysManagement();
        menu(f);
        break;
    case 5:
        f.connectManagement();
        menu(f);
        break;
    }
}

int main()
{
    Functions f;
    f.des();
    menu(f);
    f.ser();
    return 0;
}
