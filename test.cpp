#include<bits/stdc++.h>
#include<iomanip>
#include<stdlib.h>
#include<unistd.h>
#include<filesystem>
using namespace std;

vector<vector<int>> exploits_used;
string pName;

int score=0;

class sys_c{
public:
    vector<pair<string, bool>> vul;
    vector<sys_c*> adjSys;

    int sysN;

    sys_c(int n) {
        sysN=n;
    }

    void setVul(vector<pair<string, bool>>& p) {
        vul=p;
    }

    bool exploit(int i) {
        ofstream out;
        out.open(pName+".txt", ios::app);

        if(vul[i].second) cout << "Hacked\n";
        else cout << "Failed\n";

        exploits_used.push_back({sysN, i, (vul[i].second)?1:0});
        string tmp=to_string(sysN)+", "+to_string(i)+", "+to_string((vul[i].second)?1:0)+"\n";
        out << tmp;
        out.close();

        return vul[i].second;
    }

    void setAdjSys(vector<sys_c*>& v) {
        adjSys=v;
    }

    void show_adjSys() {
        for(auto x:adjSys) cout << x->sysN << " ";
        cout << endl;
    }

    void showVul() {
        for(int i=0; i<vul.size(); i++) cout << i << ": " << vul[i].first << endl; 
    }
};

// Systems
int n=20;
sys_c s0(0);
sys_c s1(1);
sys_c s2(2);
sys_c s3(3);
sys_c s4(4);
sys_c s5(5);
sys_c s6(6);
sys_c s7(7);
sys_c s8(8);
sys_c s9(9);
sys_c s10(10);
sys_c s11(11);
sys_c s12(12);
sys_c s13(13);
sys_c s14(14);
sys_c s15(15);
sys_c s16(16);
sys_c s17(17);
sys_c s18(18);
sys_c s19(19);
sys_c s20(20);

sys_c* arr[21]={&s0, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11, &s12, &s13, &s14, &s15, &s16, &s17, &s18, &s19, &s20};

void help_cmd() {
    cout << "Commands available: \n";
    cout << 1 << ": nmap\n";
    cout << 2 << ": nmap -sL all\n";
    cout << 3 << ": logout\n";
    cout << 4 << ": use_exploit\n";
    cout << 5 << ": chat\n";
    cout << 6 << ": help\n";  
    cout << 7 << ": show_exploits_used\n";
}

void showExploits() {
    for(auto exp:exploits_used) {
        cout << "%d-%d:%d\n", exp[0], exp[1], exp[2];
    }

    return;
}

void chat() {
    if(pName=="player1") {
        ifstream file("player2.txt");
        string str, file_contents;

        while(getline(file, str)) {
            file_contents+=str;
            file_contents.push_back('\n');
        }

        cout << file_contents << endl;

        file.close();
    }

    if(pName=="player2") {
        ifstream file("player1.txt");
        string str, file_contents;

        while(getline(file, str)) {
            file_contents+=str;
            file_contents.push_back('\n');
        }

        cout << file_contents << endl;

        file.close();
    }
}

namespace fs=std::filesystem;

void ls(int sn) {
    cout << "Available files: \n";
    string path="C:/Users/HP/OneDrive/Desktop/Codes/hackit/files/s ("+to_string(sn)+")/";
    
    int cnt=0;
    for(const auto &entry:fs::directory_iterator(path)) {
        cnt++;
        cout << entry.path() << endl;
    }

    if(cnt==0) return;

    cout << "Choose one file to copy: ";
    string fname;
    cin >> fname;

    ifstream infile(path+"/"+fname+".txt");
    if(infile.good()) {
        string sLine;
        getline(infile, sLine);

        if(sLine=="bingo") score+=100;
        else score-=100;

        cout << sLine << endl;
    }
}

// 1: nmap, 2: nmap -sL all, 3: logout, 4: use_exploit, 5: chat, 6: help, 7: get_exploits_used, 8: ls

void util() {
    stack<sys_c*> s;
    s.push(&s0);

    int x;
    for(int i=0; i<10; i++) {
        cout << "Enter command: ";
        cin >> x;

        if(x==1) {
            vector<sys_c*> as=s.top()->adjSys;
            
            if(s.top()->adjSys.size()==0) {
                cout << "No system available\n";
                continue;
            }

            cout << "Available systems: \n";
            s.top()->show_adjSys();

            cout << "Enter one system to attack: ";
            int y;
            cin >> y;

            arr[y]->showVul();
            cout << "Enter one vulnerability to attack: ";
            int i;
            cin >> i;
            
            if(arr[y]->exploit(i)) {
                s.push(arr[y]);
                ls(y);
            }
            
        } else if(x==2) {
            s.top()->show_adjSys();
        } else if(x==3) {
            s.pop();
        } else if(x==4) {
            s.top()->showVul();
            int i;
            cout << "Enter vulnerability to attack: ";
            cin >> i;
            s.top()->exploit(i);
        } else if(x==5) {
            chat();
        } else if(x==6) {
            help_cmd();
        } else if(x==7) {
            showExploits();
        } else {

        }
    }
}

int main() {
    // timer();

    cout << "Enter player1 or player2: ";
    cin >> pName;

    stack<sys_c*> s;
    s.push(&s1);
    s.push(&s2);
    s.push(&s3);
    s.push(&s4);
    s.push(&s5);
    s.push(&s6);
    s.push(&s7);
    s.push(&s8);
    s.push(&s9);
    s.push(&s10);
    s.push(&s11);
    s.push(&s12);
    s.push(&s13);
    s.push(&s14);
    s.push(&s15);
    s.push(&s16);
    s.push(&s17);
    s.push(&s18);
    s.push(&s19);
    s.push(&s20);

    vector<pair<string, bool>> temp;
    temp.push_back({"sql_injection", false});
    temp.push_back({"DDoS_attack", true});
    temp.push_back({"drown_attack", true});
    temp.push_back({"brute_force", false});
    temp.push_back({"directory_harvest", true});

    while(!s.empty()) {
        s.top()->setVul(temp);
        s.pop();
    }

    vector<sys_c*> v1={&s1, &s2, &s3, &s4};
    vector<sys_c*> v2={&s5, &s6, &s7, &s8};
    vector<sys_c*> v3={&s9, &s10, &s11, &s12};
    vector<sys_c*> v4={&s13, &s14, &s15, &s16};
    vector<sys_c*> v5={&s17, &s18, &s19, &s20};

    s0.setAdjSys(v1);
    s1.setAdjSys(v2);
    s2.setAdjSys(v3);
    s3.setAdjSys(v4);
    s4.setAdjSys(v5);

    cout << "Commands available: \n";
    cout << 1 << ": nmap\n";
    cout << 2 << ": nmap -sL all\n";
    cout << 3 << ": logout\n";
    cout << 4 << ": use_exploit\n";
    cout << 5 << ": chat\n";
    cout << 6 << ": help\n";
    cout << 7 << ": show_exploits_used\n";

    util();

    cout << "Your score is " << score << endl;

    return 0;
}