#include <iostream>
#include <cstring>
#include <winsock2.h>

using namespace std;

// Define the message types
enum MessageType {
    REGISTER_REQUEST,
    REGISTER_RESPONSE,
    NOMINATE_REQUEST,
    REQUEST_APPROVAL_IN_PROGRESS_RESPONSE
};

// Define the message structures
struct RegisterRequest {
    int employeeID;
    char role[20];
};

struct RegisterResponse {
    int employeeID;
    char nominatedTrainings[1024];
    char completedTrainings[1024];
    char rejectedTrainings[1024];
};

struct NominateRequest {
    int employeeID;
    char trainingName[20];
    int trainingID;
};

struct RequestApprovalInProgressResponse {
    char message[1024];
};

// Define the message handler class
class MessageHandler {
public:
    MessageHandler(SOCKET sock) : m_sock(sock) {}
    void SendRegisterRequest(int employeeID, const char* role) {
        RegisterRequest request;
        request.employeeID = employeeID;
        strncpy_s(request.role, role, sizeof(request.role));
        SendMessage(REGISTER_REQUEST, &request, sizeof(request));
    }
    void ReceiveRegisterResponse(RegisterResponse& response) {
        ReceiveMessage(REGISTER_RESPONSE, &response, sizeof(response));
    }
    void SendNominateRequest(int employeeID, const char* trainingName, int trainingID) {
        NominateRequest request;
        request.employeeID = employeeID;
        strncpy_s(request.trainingName, trainingName, sizeof(request.trainingName));
        request.trainingID = trainingID;
        SendMessage(NOMINATE_REQUEST, &request, sizeof(request));
    }
    void ReceiveRequestApprovalInProgressResponse(RequestApprovalInProgressResponse& response) {
        ReceiveMessage(REQUEST_APPROVAL_IN_PROGRESS_RESPONSE, &response, sizeof(response));
    }
private:
    SOCKET m_sock;
    void SendMessage(MessageType messageType, const void* message, size_t size) {
        send(m_sock, (const char*)&messageType, sizeof(messageType), 0);
        send(m_sock, (const char*)message, size, 0);
    }
    void ReceiveMessage(MessageType expectedMessageType, void* message, size_t size) {
        MessageType messageType;
        recv(m_sock, (char*)&messageType, sizeof(messageType), 0);
        if (messageType != expectedMessageType) {
            throw runtime_error("Received unexpected message type");
        }
        recv(m_sock, (char*)message, size, 0);
    }
};

int main() {
    // Initialize the Winsock library
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed: " << iResult << endl;
        return 1;
    }

    // Connect to the server using sockets
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Replace with the port number of your server
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Replace with the IP address of your server
    connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    // Create a message handler for the socket
    MessageHandler messageHandler(sock);

    // Send a register request message to the server
    messageHandler.SendRegisterRequest(123, "Manager");

    // Receive a register response message from the server
    RegisterResponse registerResponse;
    messageHandler.ReceiveRegisterResponse(registerResponse);

   
