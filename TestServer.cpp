//
// Created by minthukha25122003@gmail.com on 14/12/2022.
//

#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"conio.h"
#include"Winsock2.h"
#include"Windows.h"
#include <ws2tcpip.h>
#include"string"
#include"ctime"

#pragma comment (lib, "Ws2_32.lib")
using namespace std;


string allName[100];
string allPassword[100];
int allAmount[100];
string allPhNumber[100];
string allAddress[100];
int count = 0;
int result = 0;
int thing = 0;
int current = 0;
int currentIndex = 0;
int receiver = 0;
int currentAmount = 0;

struct Node{
    int data;
    string arr_username;
    string arr_password;

    int arr_amount;
    string arr_ph_Number;
    string arr_address;
    struct Node * left;
    struct Node * right;

};


struct Node * createNode(string username,string password,int amount,string ph_Number,string address) {

    struct Node *new_node = new Node();
    new_node->arr_username = username;
    new_node->arr_password = password;
    new_node->arr_amount = amount;
    new_node->arr_ph_Number = ph_Number;
    new_node->arr_address = address;

    allName[count] = new_node->arr_username;
    allPassword[count] = new_node->arr_password;
    allAmount[count] = new_node->arr_amount;
    allPhNumber[count] =  new_node->arr_ph_Number;
    allAddress[count] =  new_node->arr_address;
    count++;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


struct Node * insertAtNode(struct Node * root,string username,string password,int amount,string ph_Number,string address) {
    if (root == NULL) {
        return createNode(username,password,amount,ph_Number,address);
    }
    if (amount > root->arr_amount) {
        root->left = insertAtNode(root->left, username, password, amount, ph_Number, address);

    }else{
        root->right = insertAtNode(root->right, username, password, amount, ph_Number, address);

    }
    return root;
}


void inorderTravel(struct Node * root){
    if (root != NULL) {
        inorderTravel(root->left);
        printf("%s %s %d %s %s\n", root->arr_username.c_str(), root->arr_password.c_str(), root->arr_amount,
               root->arr_ph_Number.c_str(), root->arr_address.c_str());
        inorderTravel(root->right);
    }

}

int usernameExit(string username){
    for (int i = 0;i < count;i++){
        if (allName[i] == username){
            return i;
        }
    }
    return 1111;
}
void toTransferFun(int current, int receiver, int transferAmount) {
    if (allAmount[current] - 100 > 0) {
        allAmount[current] = allAmount[current] - transferAmount;
        allAmount[receiver] = allAmount[receiver] + transferAmount;

    }
}

string showAllInfo() {
    string allData;
    for (int i = 0;i < count;i++) {
        allData += allName[i] + " " + allPassword[i] + " " + to_string(allAmount[i]) + " " + allPhNumber[i] + " " + allAddress[i] + "\n";
    }
    return allData;



}


void withdrawFun(int current,int withdrawAmount){
    allAmount[current] = allAmount[current]-withdrawAmount;

}

void saveMoneyFun(int current,int saveMoneyAmount) {
    allAmount[current] = allAmount[current] + saveMoneyAmount;

    }


int main() {
    struct Node *root = NULL;
    root = insertAtNode(root, "minthukha", "2512", 3000, "09854142437", "Chin");
    root = insertAtNode(root, "zuezue", "2012", 4000, "092515121", "Mon");
    root = insertAtNode(root, "winhtut", "1234", 7000, "0941852202", "Chin");
    root = insertAtNode(root, "kyawkyaw", "9876", 8000, "0985141111", "Yangon");
    root = insertAtNode(root, "tuntun", "7411", 5000, "09541541241", "Mandalay");
    root = insertAtNode(root, "ayeaye", "8512", 9000, "09572452424", "Sagaing");
    root = insertAtNode(root, "winhtut", "8472", 2000, "09575245244", "Kayin");

    inorderTravel(root);


    SOCKET ConSock;
    SOCKET ListenSock;
    SOCKADDR_IN address;
    int addressSize = sizeof(address);
    long ok;
    char MESSAGE[200];
    char MESSAGE1[200];
    char MESSAGE2[200];
    char MESSAGE3[200];
    char MESSAGE4[200];
    char MESSAGE5[200];
    char MESSAGE6[200];
    char MESSAGE7[200];
    char MESSAGE8[200];
    char MESSAGE9[200];
    WSAData WSD;
    WORD DllVersion;
    DllVersion = MAKEWORD(2, 1);
    ok = WSAStartup(DllVersion, &WSD);

    ConSock = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_family = AF_INET;
    address.sin_port = htons(10102);
    ListenSock = socket(AF_INET, SOCK_STREAM, 0);
    bind(ListenSock, (SOCKADDR *) &address, sizeof(address));

    listen(ListenSock, SOMAXCONN);

    cout << "Sever waiting for connections\n\n";

    while (true) {
        if (ConSock = accept(ListenSock, (SOCKADDR *) &address, &addressSize)) {

            ok = recv(ConSock, MESSAGE, 1024, 0);
            string mood;
            mood = MESSAGE;
            if (mood == "1") {
                ok = recv(ConSock, MESSAGE2, 1025, 0); // 1024 => 1025
                ok = recv(ConSock, MESSAGE9, 1029, 0);
                string reply4;
                reply4 = MESSAGE2;
                string password;
                password = MESSAGE9;

                cout << "Client say:\t" << mood << endl;
                cout << "Client say:\t" << reply4 << endl;
                cout << "Client say:\t" << password << endl;
                current = usernameExit(reply4);
                for (int i = 0; i < count; i++) {
                    if (current != 1111) {
                        if (reply4 == allName[i] && password == allPassword[i]) {
                            // 2 winhtut
                            currentIndex = i;
                            currentAmount = allAmount[i];
                            string reply;
                            reply = "Here you are\n" + allName[i] + " " + allPassword[i] + " " +
                                    to_string(allAmount[i]) +
                                    " " +
                                    allPhNumber[i] + " " + allAddress[i];

                            const char *s = reply.c_str();

                            ok = send(ConSock, s, 1024, 0);

                        } else {
                            thing = 1;
                        }
                    }else{
                       result = 1;
                    }
                }
                if (thing == 1) {
                    string reply2 = "Wrong password";
                    const char *s = reply2.c_str();

                    ok = send(ConSock, s, 1024, 0);
                }

            if (result == 1) {
                string reply2 = "This username doesn't have DataBase!";
                const char *s = reply2.c_str();

                ok = send(ConSock, s, 1024, 0);
            }




                } else if (mood == "2") {
                ok = recv(ConSock, MESSAGE3, 1026, 0);
                string firstName;
                firstName = MESSAGE3;
                ok = recv(ConSock, MESSAGE4, 1027, 0);
                string secondName;
                secondName = MESSAGE4;
                ok = recv(ConSock, MESSAGE5, 1028, 0);
                string transAmount;
                transAmount = MESSAGE5;
                    cout << "Client say:\t" << mood << endl;
                    cout << "Client say:\t" << firstName << endl;
                    cout << "Client say:\t" << secondName << endl;
                    cout << "Client say:\t" << transAmount << endl;
                current = usernameExit(firstName);
                receiver = usernameExit(secondName);
                if (current == 1111 || receiver == 1111) {
                    string reply2 = "Username doesn't have DataBase!";
                    const char *q = reply2.c_str();

                    ok = send(ConSock, q, 1024, 0);
                    continue;
                    }else {
                    if (stoi(transAmount) >= allAmount[current]) {
                        string reply;
                        reply = "Invalid amount";
                        const char *s = reply.c_str();

                        ok = send(ConSock, s, 1024, 0);
                        continue;
                    } else {
                        toTransferFun(current, receiver, stoi(transAmount));
                        std::time_t mytime = std::time(nullptr);
                        string time = std::asctime(std::localtime(&mytime));
                        string reply;
                        reply = "Money successfully transferred  to " + (allName[receiver]) + "\n" +
                                "Transferred Amount is " + transAmount + "\n" +
                                "From " + allName[current] + " To " + allName[receiver] + " " + transAmount + " " +
                                time + allName[current] + " " + allPassword[current] + " " +
                                to_string(allAmount[current]) +
                                " " +
                                allPhNumber[current] + " " + allAddress[current] + "\n" + allName[receiver] + " " +
                                allPassword[receiver] + " " +
                                to_string(allAmount[receiver]) +
                                " " +
                                allPhNumber[receiver] + " " + allAddress[receiver];

                        const char *s = reply.c_str();

                        ok = send(ConSock, s, 1024, 0);
                    }
                }


                }else if (mood == "3"){
                ok = recv(ConSock, MESSAGE1, 1022, 0);
                string withdrawName;
                withdrawName = MESSAGE1;
                ok = recv(ConSock, MESSAGE6, 1023, 0);
                string withdrawAmount2;
                withdrawAmount2 = MESSAGE6;
                cout << "Client say:\t" << mood << endl;
                cout << "Client say:\t" << withdrawName << endl;
                cout << "Client say:\t" << withdrawAmount2 << endl;
                current = usernameExit(withdrawName);
                if (current != 1111) {
                    if (allAmount[current] - 100 > stoi(withdrawAmount2)) {
                        withdrawFun(current, stoi(withdrawAmount2));
                        string reply2;
                        reply2 = allName[current] + " " + allPassword[current] + " " +
                                 to_string(allAmount[current]) +
                                 " " +
                                 allPhNumber[current] + " " + allAddress[current];
                        const char *s = reply2.c_str();
                        ok = send(ConSock, s, 1024, 0);


                    } else {
                        string reply2;
                        reply2 = "Invalid Amount ";
                        const char *s = reply2.c_str();

                        ok = send(ConSock, s, 1024, 0);
                        continue;
                    }
                }else{
                    string reply2;
                    reply2 = "Username doesn't have DataBase!";
                    const char *q = reply2.c_str();

                    ok = send(ConSock, q, 1024, 0);
                }

            }else if (mood == "4") {
                ok = recv(ConSock, MESSAGE7, 1020, 0);
                string saveMoneyName;
                saveMoneyName = MESSAGE7;
                ok = recv(ConSock, MESSAGE8, 1021, 0);
                string saveMoneyAmount;
                saveMoneyAmount = MESSAGE8;
                cout << "Client say:\t" << mood << endl;
                cout << "Client say:\t" << saveMoneyName << endl;
                cout << "Client say:\t" << saveMoneyAmount << endl;
                current = usernameExit(saveMoneyName);
                if (current != 1111) {
                    saveMoneyFun(current, stoi(saveMoneyAmount));
                    string reply2;
                    reply2 = allName[current] + " " + allPassword[current] + " " +
                             to_string(allAmount[current]) +
                             " " +
                             allPhNumber[current] + " " + allAddress[current];
                    const char *s = reply2.c_str();

                    ok = send(ConSock, s, 1024, 0);

                } else {
                    string reply2;
                    reply2 = "Username doesn't have DataBase!";
                    const char *q = reply2.c_str();

                    ok = send(ConSock, q, 1024, 0);
                }
            }else if (mood == "5") {
                string reply2;
                for (int i = 0; i < count; i++) {
                    reply2 = showAllInfo();
                }
                    const char *q = reply2.c_str();

                    ok = send(ConSock, q, 1024, 0);
                }

            }


        }


        return 0;
    }


