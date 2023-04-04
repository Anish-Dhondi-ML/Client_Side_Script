#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Employee{
  private:    
  int id = 0;    
  string first_name;    
  string last_name;    
  ROLE role;
  public:    
  Employee(int empid, string fname, string lname, ROLE r)    
  {        
    id = empid;        
    first_name = fname;        
    last_name = lname;        
    role = r;    
  }    
  virtual void print_data();
};
class Manager : public Employee{
  public:    
  Manager(int empid, string fname, string lname) : Employee(empid, fname, lname, MANAGER) {}    
  nominate_team_for_training(vector *group, Training *ptr);    
  void add_group(Employee *emp)    
  {        
    group.push_back(emp);    
  };    
  virtual void print_data();
  private:    
  vector<Employee *> group;
};
void Manager::print_data()
{    
  Employee::print_data();    
  for (auto emp : group)    
  {        emp->print_data();    
  }
}
void Employee::print_data()
{    
  cout << "ID:" << id << endl;    
  cout << "Name:" << first_name << " " << last_name << endl;    
  cout << "Role:" << (role == MANAGER ? "Manager":"Employee") << endl;
}
int main()
{    
  Employee *emp1 = new Employee(1, "Anne", "Vaysettes", EMPLOYEE);    
  Employee *emp2 = new Employee(2, "Alain", "Gr", EMPLOYEE);    
  Manager *manager = new Manager(3, "Pattric", "Lacaroux");    
  manager->add_group(emp1);    
  manager->add_group(emp2);    
  manager->print_data();    
  return 0;
}
