#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

class Functions
{
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