#include <iostream>
#include <vector>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    vector<string> trainings;
public:
    Employee(int id, string name) : id(id), name(name) {}
    void view_trainings() {
        cout << name << " is nominated/approved for the following trainings:" << endl;
        for (string training : trainings) {
            cout << "- " << training << endl;
        }
    }
    void nominate_training(string training) {
        cout << name << " has nominated " << training << " for approval." << endl;
        trainings.push_back(training);
    }
    void cancel_nomination(string training) {
        for (int i = 0; i < trainings.size(); i++) {
            if (trainings[i] == training) {
                cout << name << " has cancelled the nomination for " << training << "." << endl;
                trainings.erase(trainings.begin() + i);
                return;
            }
        }
        cout << name << " was not nominated for " << training << "." << endl;
    }
    void approve_training(string training) {
        for (int i = 0; i < trainings.size(); i++) {
            if (trainings[i] == training) {
                cout << name << " has approved the nomination for " << training << "." << endl;
                trainings[i] = "Approved: " + trainings[i];
                return;
            }
        }
        cout << name << " was not nominated for " << training << "." << endl;
    }
    void reject_training(string training) {
        for (int i = 0; i < trainings.size(); i++) {
            if (trainings[i] == training) {
                cout << name << " has rejected the nomination for " << training << "." << endl;
                trainings[i] = "Rejected: " + trainings[i];
                return;
            }
        }
        cout << name << " was not nominated for " << training << "." << endl;
    }
    void add_training(string training) {
        cout << name << " has added " << training << " to the list of trainings." << endl;
        trainings.push_back(training);
    }
    void delete_training(string training) {
        for (int i = 0; i < trainings.size(); i++) {
            if (trainings[i] == training) {
                cout << name << " has deleted " << training << " from the list of trainings." << endl;
                trainings.erase(trainings.begin() + i);
                return;
            }
        }
        cout << name << " was not nominated for " << training << "." << endl;
    }
};

class Trainee : public Employee {
public:
    Trainee(int id, string name) : Employee(id, name) {}
};

class Trainer : public Employee {
public:
    Trainer(int id, string name) : Employee(id, name) {}
    void create_training(string training) {
        cout << name << " has created a new training: " << training << endl;
        trainings.push_back(training);
    }
};

class Manager : public Employee {
public:
    Manager(int id, string name) : Employee(id, name) {}
    void view_department_trainings() {
        cout << name << " is viewing trainings for their department:" << endl;
        // logic for viewing trainings for all employees in the department
    }
};

class HR : public Employee {
public:
    HR(int id, string name) : Employee(id, name) {}
};

int main() {
    Trainee t
    t.nominate_training("Training 1");
    Trainer tr(2, "Trainer 1");
    tr.create_training("Training 2");
    Manager m(3, "Manager 1");
    HR hr(4, "HR 1");
    tr.approve_training("Training 1");
    t.view_trainings();
    tr.view_trainings();
    tr.reject_training("Training 1");
    t.view_trainings();
    tr.view_trainings();
    t.add_training("Training 3");
    t.view_trainings();
    t.delete_training("Training 2");
    t.view_trainings();
    m.view_department_trainings();
    return 0;
}
