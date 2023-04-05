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

    // Get the service name from the user
    string serviceName;
    cout << "Enter the name of the service to start: ";
    cin >> serviceName;

    // Open the service
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_ALL_ACCESS);
    if (service == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Start the service
    if (!StartServiceA(service, 0, NULL))
    {
        cout << "Error starting service: " << GetLastError() << endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }

    cout << serviceName << " started successfully." << endl;

    // Close handles and exit
    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    return 0;
}