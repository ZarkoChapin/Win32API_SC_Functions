#include <iostream>
#include <windows.h>
#include <winsvc.h>
#include <string>
using namespace std;

int main()
{
    // Open the service control manager
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (scm == NULL)
    {
        cout << "Could not open the Service Control Manager. Error code: " << GetLastError() << endl;
        return 1;
    }

    // Get the service name from the user
    string serviceName;
    cout << "Enter the name of the service: ";
    getline(cin, serviceName);

    // Open the service
    SC_HANDLE serviceHandle = OpenServiceA(scm, serviceName.c_str(), SERVICE_QUERY_STATUS);
    if (serviceHandle == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Query the service status
    SERVICE_STATUS serviceStatus;
    if (!QueryServiceStatus(serviceHandle, &serviceStatus))
    {
        cout << "Failed to query service status." << endl;
        CloseServiceHandle(serviceHandle);
        CloseServiceHandle(scm);
        return 1;
    }

    // Print the service status
    cout << "Service \"" << serviceName << "\" is ";

    switch (serviceStatus.dwCurrentState)
    {
    case SERVICE_STOPPED:
        cout << "stopped.";
        break;
    case SERVICE_START_PENDING:
        cout << "starting.";
        break;
    case SERVICE_STOP_PENDING:
        cout << "stopping.";
        break;
    case SERVICE_RUNNING:
        cout << "running.";
        break;
    case SERVICE_CONTINUE_PENDING:
        cout << "continuing.";
        break;
    case SERVICE_PAUSE_PENDING:
        cout << "pausing.";
        break;
    case SERVICE_PAUSED:
        cout << "paused.";
        break;
    default:
        cout << "in an unknown state.";
        break;
    }

    cout << endl;

    // Close handles and exit
    CloseServiceHandle(serviceHandle);
    CloseServiceHandle(scm);
    return 0;
}