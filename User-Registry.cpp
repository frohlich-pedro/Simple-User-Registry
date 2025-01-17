#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class User {
public:
    string name;
    string email;
    string id;

    User(string name, string email, string id)
        : name(name), email(email), id(id) {}
    ~User() = default;
};

int main(void) {
    vector<User> users = {};

    auto addUser = [&users](string name, string email, string id) {
        if (name.empty()) {
            throw runtime_error("ERROR: Can't create user without name.");
        }

        if (email.empty()) {
            throw runtime_error("ERROR: Can't create user without email.");
        }
        users.push_back(User(name, email, id));
    };

    auto removeUser = [&users](string id) {
        if (id.empty()) {
            throw runtime_error("ERROR: Can't open specified user id.");
        }

        for (auto i = users.begin(); i != users.end(); i++) {
            if (i->id == id) {
                users.erase(i);
                break;
            }
        }
    };

    auto editUser = [&users](string id) {
        if (id.empty()) {
            throw runtime_error("ERROR: Can't open specified user id.");
        }

        for (auto i = users.begin(); i != users.end(); i++) {
            if (i->id == id) {
                string name;
                string email;

                cout << "new name:" << endl;
                cin >> name;
                if (name.empty()) {
                    throw runtime_error("ERROR: Can't create user with empty name.");
                }

                cout << "new email:" << endl;
                cin >> email;
                if (email.empty()) {
                    throw runtime_error("ERROR: Can't create user with empty email.");
                }

                i->name = name;
                i->email = email;
                break;
            }
        }
    };

    auto saveUsersToFile = [&users](string filename) {
        if (filename.empty()) {
            throw runtime_error("ERROR: Can't open file with empty name.");
        }

        if (users.empty()) {
            throw runtime_error("ERROR: No users to add.");
        }

        ofstream file(filename, ios::app);

        for (auto& i : users) {
            file << i.name << ", " << i.email << ", " << i.id << endl;
        }

        file.close();
    };

    while (true) {
        try {
            cout << "Hello! What would you like to do:" << endl 
                << "1. Add new user." << endl
                << "2. Edit existing user." << endl
                << "3. Remove existing user" << endl
                << "4. Save added users to file" << endl
                << "0. Exit Program" << endl;
                
            int action = 0;
            cin >> action;

            switch (action) {
                case 1: {
                    string name;
                    string email;
                    string id;

                    cout << "New user name:" << endl;
                    cin >> name;
                    cout << "New user email:" << endl;
                    cin >> email;
                    cout << "New user id:" << endl;
                    cin >> id;

                    addUser(name, email, id);
                    break;
                }

                case 2: {
                    string id;
                    cout << "User id to edit:" << endl;
                    cin >> id;
                    editUser(id);
                    break;
                }

                case 3: {
                    string id;
                    cout << "User id to remove:" << endl;
                    cin >> id;
                    removeUser(id);
                    break;
                }

                case 4: {
                    string filename;
                    cout << "Filename to save users:" << endl;
                    cin >> filename;
                    saveUsersToFile(filename);
                    break;
                }

                case 0: {
                    cout << "Exiting program..." << endl;
                    return 0;
                }

                default: {
                    cout << "Invalid action. Please try again." << endl;
                    break;
                }
            }

        } catch (runtime_error& error) {
            cerr << error.what() << endl;
        }
    }

    return 0;
}
