#include <string>
#include <vector>
#include <iostream>

using namespace std;

class User{
private:
    string name;
    string phone;
    int loginState; //0 = out, 1= login
    static inline int id;
    vector<User> contact;

public:
    User(){
        id = 0;
    }

    User(int id, string name, string phone): name(name), phone(phone) {
        User::id = id;
        loginState = 1;
    }

    User(string name, string phone): name(name), phone(phone) {
        id++;
        loginState = 1;
        contact = vector<User>();
    }

    void addContactPrompt(){
        string name, phone;
        cout << "Add new contact name: ";
        cin >> name;
        cout << "Add " << name << " phone: ";
        cin >> phone;
        addContact(User(name, phone));
        cout << endl;
    }

    bool addContact(User user){
        if(user.getId()!=0){
            contact.push_back(user);
            cout << user.name << " is successfully created" << endl;
        }

        else{
            return false;
            cout << "fail to add new contact!" << endl;
        }
        return true;
    }

    void printContact(){
        int i = 1;
        cout << "Contact List" << endl;
        if(contact.size() == 0){
            cout << "No contact found!" << endl;
            return;
        }
        for(auto user: contact){
            cout << i << ". " << user.name << ", " << user.phone << endl;
        }
        cout << endl;
    }

    string getName(){return name;};
    string getPhone(){return phone;};
    int getLoginState(){return loginState;};
    void setLoginState(int state){ loginState = state;};
    static int getId(){return id;};
    static void resetId(){
        id = 0;
    }
};