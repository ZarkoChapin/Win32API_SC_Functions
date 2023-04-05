#include <iostream>
#include <windows.h>
#include <winsvc.h>
#include <string>
using namespace std;

int main()
{
    // Open the Service Control Manager
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (scm == NULL)
    {
        cout << "Could not open the Service Control Manager. Error code: " << GetLastError() << endl;
        return 1;
    }

    // Prompt the user for the service name to delete
    string serviceName;
    cout << "Enter the name of the service to delete: ";
    getline(cin, serviceName);

    // Open the service
    SC_HANDLE svc = OpenServiceA(scm, serviceName.c_str(), DELETE);
    if (svc == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Delete the service
    if (DeleteService(svc) == 0)
    {
        DWORD err = GetLastError();
        if (err == ERROR_SERVICE_MARKED_FOR_DELETE)
        {
            cout << "Service " << serviceName << " is already marked for deletion." << endl;
        }
        else
        {
            cout << "Failed to delete service, error " << err << endl;
        }
        CloseServiceHandle(svc);
        CloseServiceHandle(scm);
        return 1;
    }

    // Close handles and exit
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    cout << "Service " << serviceName << " deleted successfully." << endl;

    return 0;
}