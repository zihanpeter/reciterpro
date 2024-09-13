#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N = 1e5 + 5;
string s1[N], s2[N], s3[N];
char clean[2][10] = {"clear", "cls"};
int cnt, dic[N], num, sysn, mode;
bool del[N], fir[N];

void pause() {
	string t;
    getline(cin, t);
}

bool init() {
    memset(dic, 0, sizeof(dic));
    memset(del, 0, sizeof(del));
    memset(fir, 0, sizeof(fir));
    num = cnt = 0;
    fstream cts;
    cts.open("contents.txt");
    if (cts.is_open()) {
        string str1, str2, str3, mds;
        getline(cts, mds);
        mds == "e.g." ? mode = 1 : mode = 0;
        while (getline(cts, str1)) {
            s1[++cnt] = str1;
            getline(cts, str2);
            s2[cnt] = str2;
            if (mode) {
                getline(cts, str3);
                s3[cnt] = str3;
            }
        }
        cts.close();
    } else {
        cout << "Error: Create \"contents.txt\" to start." << endl;
        pause();
        return true;
    }
    return false;
}

void showC() {
    cout << "Reciter Pro" << endl;
    cout << "Developed by Peter Lu in 2024." << endl << endl;
}

void solve(string s1[], string s2[], int t, int pat) {
    if (init()) return;
    bool run = true;
    int show, cntf = 0;
    string inp;
    system(clean[sysn]);
    bool flag = true;
    while (run) {
        showC();
        if (t == 1) {
            if (pat == 1) cout << "Pattern: Test Spelling" << endl;
            else cout << "Pattern: Test Meaning" << endl;
        } else {
            if (pat == 1) cout << "Pattern: Learn Spelling" << endl;
            else cout << "Pattern: Learn Meaning" << endl;
        }
        cout << cnt - num << " ";
        show = rand() % cnt + 1;
        while (del[show]) show = rand() % cnt + 1;
        cout << t - dic[show] << " ";
        if (!fir[show]) cout << "first time";
        cout << endl;
        if (pat == 2) {
            cout << endl << s2[show] << endl << "Press \"Enter\" to check the meaning.";
			pause();
			cout << endl;
            mode ? cout << s1[show] << endl << s3[show] << endl << '>' : cout << s1[show] << endl << '>';
		} else cout << endl << s2[show] << endl << '>';
        getline(cin, inp);
        if (inp == "exit 0") {
            system(clean[sysn]);
            exit(0);
        } else if (inp == "exit 1") 
            return;
        else if (inp == s1[show] || inp == "y" && pat == 2) {
            ++dic[show];
            if (dic[show] >= t || !fir[show]) {
                del[show] = true;
                ++num;
            }
            fir[show] = true;
        } else {
            dic[show] = 0;
            fir[show] = true;
            if (pat == 1) cout << ' ' << s1[show] << endl;
            else cout << s2[show] << endl;
            if (mode == 1) cout << endl << s3[show] << endl;
            if (t == 1) {
                del[show] = true;
                ++num;
                ++cntf;
            }
            if (pat == 1) pause();
        }
        if (num >= cnt) run = false;
        system(clean[sysn]);
    }
    if (t == 1) {
        cout << "Result: " << cnt - cntf << "/" << cnt << endl;
        if (cntf) {
            cout << "Incorrect Volcabularies:" << endl;
            for (int i = 1; i <= cnt; ++i) if (!dic[i]) cout << s1[i] << " " << s2[i] << endl;
        }
        pause();
        system(clean[sysn]);
    }
    return;
}

void dealSys() {
	fstream sys;
	sys.open("sys.txt");
	string s;
	if (sys.is_open()) {
		getline(sys, s);
		if (s == "Windows") sysn = 1;
		else sysn = 0;
		sys.close();
	} else {
		cout << "Input your system: " << endl << ">";
		getline(cin, s);
		if (s == "Windows") sysn = 1;
		else sysn = 0;
	}
}

int main() {
    srand(time(NULL));
	dealSys();
    string inp;
    while (true) {
        system(clean[sysn]);
        showC();
        cout << ">";
        getline(cin, inp);
        if (inp == "learn s") solve(s1, s2, 2, 1);
        else if (inp == "learn m") solve(s2, s1, 2, 2);
        else if (inp == "test s") solve(s1, s2, 1, 1);
        else if (inp == "test m") solve(s2, s1, 1, 2);
        else if (inp == "exit 0") {
            system(clean[sysn]);
            exit(0);
        }
    }
    return 0;
}
