//
// Created by User on 22/12/2022.
//

#include"stdio.h"
#include"iostream"
#include"conio.h"
#include"winsock2.h"
#include"windows.h"
#include"string"
#pragma comment (lib, "Ws2_32.lib")
using namespace std;


int main(){
    SOCKET sock;
    SOCKADDR_IN address;

    long ok;
    char MESSAGE[1000];
    char MESSAGE2[200];
    WSAData WSD;
    WORD DllVersion;
    DllVersion = MAKEWORD(2,1);
    ok = WSAStartup(DllVersion, &WSD);

    while (true) {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_family = AF_INET;
        address.sin_port = htons(10102);

        connect(sock, (SOCKADDR *) &address, sizeof(address));

        string mood;
        string msg;
        string password;
        cout << "Enter you want to choose " << endl;
        cout << "Press 1 to show each data\nPress 2 to transfer\nPress 3 to withdraw\nPress 4 to save money\nPress 5 to show all data\nPress 6 to exit" << endl;
        cin >> mood;
        const char *t = mood.c_str();
        if (mood == "1") {
            cout << "Please enter name: ";
            cin >> msg;
            const char *s = msg.c_str();
            ok = send(sock, t, 1024, 0);
            ok = send(sock, s, 1025, 0); // for thinking 1 week 1024 => 1025 correct
            cout << "Please enter password: ";
            cin >> password;


            const char *u = password.c_str();

            ok = send(sock, u, 1029, 0);


        } else if (mood == "2") {
            string firstName;
            string secondName;
            string transferAmount;
            cout << "PLease enter first name: ";
            cin >> firstName;
            cout << "PLease enter second name: ";
            cin >> secondName;
            cout << "PLease enter amount ";
            cin >> transferAmount;

            const char *v = firstName.c_str();
            const char *u = secondName.c_str();
            const char *w = transferAmount.c_str();
            ok = send(sock, t, 1024, 0);
            ok = send(sock, v, 1026, 0);
            ok = send(sock, u, 1027, 0);
            ok = send(sock, w, 1028, 0);

        } else if (mood == "3") {
            string withdrawName;
            string withdrawAmount;
            cout << "Please enter name you want to withdraw";
            cin >> withdrawName;
            cout << "Please enter withdraw amount";
            cin >> withdrawAmount;
            const char *u = withdrawName.c_str();
            const char *v = withdrawAmount.c_str();
            ok = send(sock, t, 1024, 0);
            ok = send(sock, u, 1022, 0);
            ok = send(sock, v, 1023, 0);

        } else if (mood == "4") {
            string saveMoneyName;
            string saveMoneyAmount;
            cout << "Please enter name to save money";
            cin >> saveMoneyName;
            cout << "Please enter amount to save money";
            cin >> saveMoneyAmount;
            const char *u = saveMoneyName.c_str();
            const char *v = saveMoneyAmount.c_str();
            ok = send(sock, t, 1024, 0);
            ok = send(sock, u, 1020, 0);
            ok = send(sock, v, 1021, 0);

        }else if (mood == "5"){
            ok = send(sock, t, 1024, 0);
        }else if (mood == "6"){
            exit(0);
        }else{
            continue;
        }

        ok = recv(sock, MESSAGE, 1024, 0);
        string reply;
        reply = MESSAGE;

        cout << "Server says:\t" << reply << endl;



        }

}



