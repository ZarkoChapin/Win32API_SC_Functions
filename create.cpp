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

    // Prompt the user for the service name
    string serviceName;
    cout << "Enter the service name to create: ";
    cin >> serviceName;

    // Create the service, you will need to change the binary path based on your system
    SC_HANDLE service = CreateServiceA(
        scm,                       // handle to service control manager
        serviceName.c_str(),       // name of service
        serviceName.c_str(),       // display name
        SERVICE_ALL_ACCESS,        // access rights
        SERVICE_WIN32_OWN_PROCESS, // service type
        SERVICE_AUTO_START,        // start type
        SERVICE_ERROR_NORMAL,      // error control type
        "C:\\",                    // binary path
        NULL,                      // no load order group
        NULL,                      // no tag identifier
        NULL,                      // no dependencies
        NULL,                      // LocalSystem account
        NULL                       // no password
    );

    // Check if the service was created successfully or if one already exists, if unsuccessful, print the error code
    if (service == NULL)
    {
        DWORD error = GetLastError();
        if (error == ERROR_SERVICE_EXISTS)
        {
            cout << "The service already exists." << endl;
        }
        else
        {
            cout << "Failed to create the service. Error code: " << error << endl;
        }
        CloseServiceHandle(scm);
        return 1;
    }

    cout << "Service " << serviceName << " has been created." << endl;

    // Close handles and exit
    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    return 0;
}
