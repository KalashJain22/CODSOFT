#include<iostream>
#include<vector>
#include <fstream>
#include <sstream>
#include<unordered_map>

using namespace std;

const size_t MAX_TASKS = 10; //Maximum tasks
const string FILE_NAME = "tasks.txt"; //File name

//For maintain the users of to-do-list
unordered_map<string, vector<pair<string, bool>>> users;

//For read and use of tasks from the file
void load_tasks_from_file() {
    ifstream file(FILE_NAME);

    if(!file.is_open()) {
        return;
    }

    string line;
    while(getline(file, line)) { 
        istringstream iss(line); //Makes every line into String Stream format
        string username, task;
        bool completed;
        if(getline(iss, username, '|') && getline(iss, task, '|') && iss >> completed) {
            users[username].push_back({task, completed}); 
        }
    }

    file.close();
}

//For save input of tasks in the file
void save_tasks_to_file() {
    ofstream file(FILE_NAME);

    for (const auto& user : users) {
        for (const auto& task : user.second) {
            file << user.first << '|' << task.first << '|' << task.second << '\n';
        }
    }
    
    file.close();
}

void add_task(string username, string task) {
    if(MAX_TASKS <= users[username].size()) {
        cout<< "\nSorry, maximum 10 tasks per user are allowed." << endl;
        return;
    }
    users[username].push_back({task, false});
}

void view_task(string username) {
    if(users[username].empty()) {
        cout<< "\nCurrently there are no task in the list, please add a new task." << endl;
    } else {
        cout<<endl;
        for(size_t i = 0; i < users[username].size(); i++) {
            cout<< i+1 << ". Task: " << users[username][i].first << " - Status: " 
            << (users[username][i].second ? "Completed" : "Pending ") << endl;
        }
    }
}

void mark_completed(string username, size_t task_num) {
    if(task_num <= 0 || users[username].size() < task_num) {
        cout<< "\nInvalid, task number." << endl;
    } else if(users[username][task_num-1].second) {
        cout<< "\nGiven task number is already completed." << endl;
    } else {
        users[username][task_num-1].second = true;
        cout<< "\nTask successfully mark as completed." << endl;
    }
}

void delete_task(string username,  size_t task_num) {
    if(task_num <= 0 || users[username].size() < task_num) {
        cout<< "\nInvalid, task number." << endl;
    } else {
        users[username].erase(users[username].begin() + task_num - 1);
        cout<< "\nTask successfully deleted." << endl;
    }
}

int main() {
    load_tasks_from_file();

    string username;
    int choice;
    string task;
    size_t task_num;
    
    cout<< "\n\t*** Welcome to To Do List Manager ***" <<endl;
    cout<< "\nEnter your Username: ";
    getline(cin, username);

    do {
        cout<< "\n1. Add new Task" << endl;
        cout<< "2. View all Tasks" << endl;
        cout<< "3. Marks Task as Completed" << endl;
        cout<< "4. Delete a Task" << endl;
        cout<< "5. Exit" << endl;
        cout<< "Enter your choice: ";
        cin>> choice;

        if(choice == 5) {
            cout<< "\n\tThank You !!!" << endl;
            break;
        } 

        cin.ignore(); //Ignore the new line character

        switch (choice)
        {
        case 1: cout<< "Enter the task that you want to add: ";
                getline(cin, task);
                add_task(username, task);
            break;
        case 2: view_task(username);
            break;
        case 3: cout<< "Enter the task number that you want to mark as completed: ";
                cin>> task_num;
                mark_completed(username, task_num);
            break;
        case 4: cout<< "enter the task number that you want to delete: ";
                cin>> task_num;
                delete_task(username, task_num);
            break;
        
        default: cout<<"\nInvalid choice, Please try again." << endl;
            break;
        }
    } while(true);

    save_tasks_to_file();
}
