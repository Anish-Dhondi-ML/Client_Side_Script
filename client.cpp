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
    void view_trainings() {     }
    void nominate_training(string training) {    }
    void cancel_nomination(string training) {    }
    void approve_training(string training) {    }
    void reject_training(string training) {    }
    void add_training(string training) {     }
    void delete_training(string training) {    }
};

class Trainee : public Employee {
public:
    Trainee(int id, string name) : Employee(id, name) {}
};

class Trainer : public Employee {
public:
    Trainer(int id, string name) : Employee(id, name) {}
    void create_training(string training) {    }
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
