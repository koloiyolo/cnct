#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Functions
{
     //string 1 is IP, string 2 is key file
    vector<pair<string, string>> connections; 
    public:
    void showConnections(){
    }
    void connect(int i){
    }
};

void menu(){
    Functions f;
    int choice;
    int tmp;
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
            f.connect(tmp);
        break;

    }
}


int main(){
    menu();
    return 0;
}