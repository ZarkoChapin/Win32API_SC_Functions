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
        cout << "Failed to open service control manager: " << GetLastError() << endl;
        return 1;
    }

    // Prompt the user to enter the service name
    string serviceName;
    cout << "Enter the name of the service to change failure action: ";
    getline(cin, serviceName);

    // Open the service
    SC_HANDLE service = OpenServiceA(scm, serviceName.c_str(), SERVICE_ALL_ACCESS);
    if (service == NULL)
    {
        cout << "Failed to open service. Error Code: " << GetLastError() << endl;
        CloseServiceHandle(scm);
        return 1;
    }

    // Prompt the user to select the failure action
    int failureAction;
    cout << "Select the failure action:" << endl;
    cout << "1. Restart the service" << endl;
    cout << "2. Run a command" << endl;
    cout << "3. Reboot the computer" << endl;
    cin >> failureAction;

    // Configure the failure actions
    SERVICE_FAILURE_ACTIONS failureActions = {0};
    failureActions.dwResetPeriod = 60; // Reset the failure counter after 60 seconds

    switch (failureAction)
    {
    case 1:                          // Restart the service
        failureActions.cActions = 1; // Take 1 action on failure
        SC_ACTION restartAction;
        restartAction.Type = SC_ACTION_RESTART; // Restart the service
        restartAction.Delay = 5000;             // Wait 5 seconds before restarting
        failureActions.lpsaActions = &restartAction;
        break;

    case 2:                          // Run a command
        failureActions.cActions = 1; // Take 1 action on failure
                                     // Replace "C:\\path\\to\\command.exe" with the command you want to run
        failureActions.lpCommand = (LPWSTR) "C:\\path\\to\\command.exe";
        break;

    case 3:                          // Reboot the computer
        failureActions.cActions = 1; // Take 1 action on failure
        SC_ACTION rebootAction;
        rebootAction.Type = SC_ACTION_REBOOT; // Reboot the computer
        rebootAction.Delay = 5000;            // Wait 5 seconds before rebooting
        failureActions.lpsaActions = &rebootAction;
        break;

    default:
        cout << "Invalid failure action selected." << endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }

    if (!ChangeServiceConfig2(service, SERVICE_CONFIG_FAILURE_ACTIONS, &failureActions))
    {
        cout << "Failed to change service failure actions: " << GetLastError() << endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scm);
        return 1;
    }

    cout << "Service failure actions changed successfully." << endl;

    // Cleanup
    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    return 0;
}