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

    // Prompt the user for the name of the service and the Start Type they want to set
    string serviceName;
    int startType;

    cout << "Enter the name of the service to change the start type: ";
    cin >> serviceName;

    cout << "Enter the start type (2 = Automatic, 3 = Manual, 4 = Disabled): ";
    cin >> startType;

    // Open the service
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_CHANGE_CONFIG);

    if (!service)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Modify the start type of the service
    BOOL result = ChangeServiceConfigA(service, SERVICE_NO_CHANGE, startType, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    if (!result)
    {
        cout << "Error: Failed to modify the service configuration." << endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }

    // Close handles and exit
    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    cout << "The service start type has been successfully modified." << endl;
    return 0;
}