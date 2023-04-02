#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <sstream>

using namespace std;

// Define the Employee message structure
struct Employee {
    int id;
    string name;
    vector<string> trainings;
};

// Convert an Employee object to a string message format
string employee_to_message(Employee emp) {
    stringstream ss;
    ss << emp.id << "," << emp.name << ",";
    for (string training : emp.trainings) {
        ss << training << ";";
    }
    return ss.str();
}

// Convert a string message to an Employee object
Employee message_to_employee(string message) {
    Employee emp;
    stringstream ss(message);
    string field;

    // Parse the message into fields
    getline(ss, field, ',');
    emp.id = stoi(field);
    getline(ss, emp.name, ',');
    while (getline(ss, field, ';')) {
        emp.trainings.push_back(field);
    }

    return emp;
}

int main() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    // Prompt user to enter the IP address and port number of the server
    string server_ip_address;
    cout << "Enter the IP address of the server: ";
    getline(cin, server_ip_address);
    cout << "Enter the port number of the server: ";
    cin >> portno;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Get server information using gethostbyname
    server = gethostbyname(server_ip_address.c_str());
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // Set up the server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    // Prompt user to enter an Employee object to send to the server
    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter employee name: ";
    getline(cin, emp.name);
    string training;
    do {
        cout << "Enter training (or enter nothing to stop): ";
        getline(cin, training);
        if (training.length() > 0) {
            emp.trainings.push_back(training);
        }
    } while (training.length() > 0);

    // Convert the Employee object to a message and send it to the server
    string message = employee_to_message(emp);
    n = write(sockfd, message.c_str(), message.length());
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    // Read the server's response
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    if (strncmp(buffer, "ERROR", 5) == 0) {
cout << "Server responded with an error: " << buffer << endl;
} else {
// Convert the server's response to an Employee object and print it
Employee emp = message_to_employee(string(buffer));
cout << "Employee received from server:" << endl;
cout << "ID: " << emp.id << endl;
cout << "Name: " << emp.name << endl;
cout << "Trainings: ";
for (string training : emp.trainings) {
cout << training << ", ";
}
cout << endl;
}

// Close the socket and exit
close(sockfd);
return 0;
}






