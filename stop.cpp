#include <iostream>
#include <windows.h>
#include <winsvc.h>
#include <string>
using namespace std;

int main()
{
    // Open the service control manager
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (scm == NULL)
    {
        cout << "Could not open the Service Control Manager. Error code: " << GetLastError() << endl;
        return 1;
    }

    // Prompt the user to enter the service name
    cout << "Enter the name of the service to stop: ";
    string serviceName;
    getline(cin, serviceName);

    // Get a handle to the service
    SC_HANDLE serviceHandle = OpenServiceA(scm, serviceName.c_str(), SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (serviceHandle == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Stop the service
    SERVICE_STATUS serviceStatus;
    if (!ControlService(serviceHandle, SERVICE_CONTROL_STOP, &serviceStatus))
    {
        cout << "Failed to stop the service: " << GetLastError() << endl;
        CloseServiceHandle(serviceHandle);
        CloseServiceHandle(scm);
        return 1;
    }

    // Wait for the service to stop
    while (serviceStatus.dwCurrentState != SERVICE_STOPPED)
    {
        Sleep(serviceStatus.dwWaitHint);
        if (!QueryServiceStatus(serviceHandle, &serviceStatus))
        {
            cout << "Failed to query the service status: " << GetLastError() << endl;
            CloseServiceHandle(serviceHandle);
            CloseServiceHandle(scm);
            return 1;
        }
    }

    cout << "The service " << serviceName << " has been stopped." << endl;

    // Close the handles
    CloseServiceHandle(serviceHandle);
    CloseServiceHandle(scm);

    return 0;
}