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

    // Prompt the user to enter the name of the service to query
    string serviceName;
    cout << "Enter the name of the service to query: ";
    getline(cin, serviceName);

    // Open the service
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_QUERY_CONFIG);
    if (service == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Query the service description
    DWORD bytesNeeded = 0;
    if (QueryServiceConfig2A(service, SERVICE_CONFIG_DESCRIPTION, NULL, 0, &bytesNeeded))
    {
        cout << "Service description: (none)" << endl;
    }
    else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)

    // Query the service configuration for memory allocation
    {
        LPQUERY_SERVICE_CONFIGA serviceConfig = (LPQUERY_SERVICE_CONFIGA)LocalAlloc(LPTR, bytesNeeded);
        if (serviceConfig == NULL)
        {
            cout << "Error: Failed to allocate memory for service configuration" << endl;
            CloseServiceHandle(service);
            CloseServiceHandle(scm);
            return 1;
        }

        // Query the service configuration and print the description of that service
        if (QueryServiceConfig2A(service, SERVICE_CONFIG_DESCRIPTION, (LPBYTE)serviceConfig, bytesNeeded, &bytesNeeded))
        {
            LPSERVICE_DESCRIPTIONA serviceDescription = (LPSERVICE_DESCRIPTIONA)serviceConfig;
            if (serviceDescription != NULL && serviceDescription->lpDescription != NULL && serviceDescription->lpDescription[0] != '\0')
            {
                cout << "Service description: " << serviceDescription->lpDescription << endl;
            }
            else
            {
                cout << "Service description: (none)" << endl;
            }
        }
        else
        {
            cout << "Error: Could not get the service configuration" << endl;
        }

        LocalFree(serviceConfig);
    }
    else
    {
        cout << "Error: Could not get the size of the service configuration" << endl;
    }

    // Close handles and exit
    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    return 0;
}
