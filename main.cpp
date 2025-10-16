#include <iostream>
#include "user.h"

using namespace std;

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, MAIN_PROMPT};
enum subUserPrompt{USER_VERIFICATION, LOGIN_MENU};
enum featurePrompt{WHOAMI, LIST_CONTACT, ADD_CONTACT, LOGOUT, LOGIN_MENU_PROMPT};

int main() {
    PrimaryPrompt prompt = MAIN_PROMPT;
    subUserPrompt sub_login_prompt = USER_VERIFICATION;
    featurePrompt login_menu_prompt = LOGIN_MENU_PROMPT;
    const string serialname = "user_data.bin";

    //reset static variables to 0
    User::resetId();

    User user;
    //test case
    user = User("test", "123");
    user.setLoginState(0);
    
    //reload from serialized data
    //user = User::deserialize(serialname);
    while (true) {
        switch (prompt) {
            case MAIN_PROMPT:
                cout << "Select an option: " << endl;
                cout << "1. Login" << endl;
                cout << "2. Register" << endl;
                cout << "3. Exit" << endl;
                int choice;
                cin >> choice;
                prompt = static_cast<PrimaryPrompt>(choice - 1);
                break;
            case LOGIN:{
                // login is prompting entering name and phone number to confirmation
                //cout << "Login selected." << endl;
                switch (sub_login_prompt){
                    case USER_VERIFICATION:{
                        string name, phone;
                        cout << "Please enter name and phone number for Login." << endl;
                        cout << "Name: "; cin >> name;
                        cout << "Phone: "; cin >> phone;
                        if ((user.getName() == name) & (phone == user.getPhone())){
                            sub_login_prompt = LOGIN_MENU;
                            user.setLoginState(1);
                        } else{
                            cout << "entered info is not recognized!" << endl;
                        }
                        break;
                    }
                    case LOGIN_MENU:{
                        //check login state
                        switch(login_menu_prompt){
                            case LOGIN_MENU_PROMPT:
                                if(user.getLoginState()==0){
                                    //ask for login
                                    sub_login_prompt = USER_VERIFICATION;
                                    break;
                                }

                                //TODO: Must check user login state
                                cout << "Please select the following" << endl;
                                cout << "1. WHO AM I" << endl;
                                cout << "2. List contact" << endl;
                                cout << "3. Add contact" << endl;
                                cout << "4. Logout" << endl;
                                cin >> choice;
                                login_menu_prompt = static_cast<featurePrompt>(choice - 1);
                                //cout << "promptId: " << login_menu_prompt << endl;
                                break;
                            case WHOAMI:
                                cout << "Name: " << user.getName() << endl;
                                cout << "Phone: " << user.getPhone() << endl;
                                login_menu_prompt = LOGIN_MENU_PROMPT;
                                cout << endl;
                                break;
                            case LIST_CONTACT:
                                user.printContact();
                                login_menu_prompt = LOGIN_MENU_PROMPT;
                                break;
                            case ADD_CONTACT:
                                user.addContactPrompt();
                                login_menu_prompt = LOGIN_MENU_PROMPT;
                                break;
                            case LOGOUT:
                                prompt = MAIN_PROMPT;
                                sub_login_prompt = USER_VERIFICATION;
                                user.setLoginState(0);
                                break;
                        }
                    }
                }
                break;
            }
            case REGISTER:{
                // register ask for the user internal data, then immediately make the current user login
                string name, phone;
                cout << "Please enter name and phone number for registration." << endl;
                cout << "Name: "; cin >> name;
                cout << "Phone: "; cin >> phone;
                user = User(name, phone);
                //after register set the state to LOGIN for the other menu
                prompt = LOGIN;
                sub_login_prompt = LOGIN_MENU;
                user.setLoginState(0);
                cout << "Registration is successful, please login to continue" << endl;
                break;
            }
            case EXIT:
                user.serialize(serialname);
                return 1;
        }
    }

    return 0;
}