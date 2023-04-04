#include <iostream>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

struct RegisterRequest {
    int employeeID;
    string role;
};

struct RegisterResponse {
    int employeeID;
    vector<string> nominatedTrainings;
    vector<string> completedTrainings;
    vector<string> rejectedTrainings;
};

struct NominateRequest {
    int employeeID;
    string trainingName;
    int trainingID;
};

struct RequestApprovalInProgressResponse {
    string message;
};

int main() {
    // Connect to the server using sockets
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Replace with the port number of your server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the IP address of your server
    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Send a register request message to the server
    RegisterRequest registerRequest;
    registerRequest.employeeID = 123; // Replace with the employee ID of the user
    registerRequest.role = "Manager"; // Replace with the role of the user
    send(sock, &registerRequest, sizeof(registerRequest), 0);

    // Receive a register response message from the server
    RegisterResponse registerResponse;
    recv(sock, &registerResponse, sizeof(registerResponse), 0);

    // Print the nominated trainings received from the server
    cout << "Nominated trainings: ";
    for (const auto& training : registerResponse.nominatedTrainings) {
        cout << training << ", ";
    }
    cout << endl;

    // Send a nominate request message to the server
    NominateRequest nominateRequest;
    nominateRequest.employeeID = registerResponse.employeeID;
    nominateRequest.trainingName = "Advanced Programming"; // Replace with the name of the training
    nominateRequest.trainingID = 456; // Replace with the ID of the training
    send(sock, &nominateRequest, sizeof(nominateRequest), 0);

    // Receive a request approval in progress response message from the server
    RequestApprovalInProgressResponse requestApprovalInProgressResponse;
    recv(sock, &requestApprovalInProgressResponse, sizeof(requestApprovalInProgressResponse), 0);

    // Print the message received from the server
    cout << requestApprovalInProgressResponse.message << endl;

    // Close the socket
    close(sock);

    return 0;
}
