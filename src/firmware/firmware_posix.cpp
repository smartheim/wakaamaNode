#include "object_firmware.hpp"
#include "lwm2m_connect.h"

#ifdef LWM2M_FIRMWARE_UPGRADES

#if (defined(_WIN32) || defined(__unix__))
#include <iostream>
#include <fstream>
using namespace std;
static string executableFilename;
#endif

#ifdef _WIN32
#include <windows.h>

void startup(const char* lpApplicationName) {
   // additional information
   STARTUPINFO si;
   PROCESS_INFORMATION pi;

   // set the size of the structures
   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);
   ZeroMemory( &pi, sizeof(pi) );

  // start the program up
  CreateProcess( lpApplicationName,   // the path
    (string(lpApplicationName)+" oldexe="+to_string(parent_pid)).c_str(),        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory
    &si,            // Pointer to STARTUPINFO structure
    &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
#endif

#if defined(__unix__)

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
void startup(const char* lpApplicationName) {
    pid_t parent_pid;
    pid_t child_pid;
    // so the child can send a signal to the parent if needed
    parent_pid = getpid();

    child_pid = fork();
    switch( child_pid )
    {
      case -1:
         perror( "[fork-exec-test] fork failed" );
         exit( EXIT_FAILURE );
         break;

      case 0:
         // the program should receive its own command as argv[0]
         execlp( lpApplicationName, string("oldexe="+to_string(parent_pid)).c_str(), NULL );
         // should't return
         perror( "[fork-exec-test] exec failed" );
         exit( EXIT_FAILURE );
         break;

      default:
         // no errors
         break;
    }
}

#endif

#if (defined(_WIN32) || defined(__unix__))

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void writeNewFirmware(DynArray<uint8_t*>& firmware) {
    string newname = "new." + executableFilename;
    ofstream fout(newname, ofstream::trunc);
    if (!fout.is_open()) {
        cerr << "Cannot open file for writing " << newname << endl;
        return;
    }
    fout.write((const char*)firmware.data, firmware.len);
    fout.close();
}

void executeFirmwareUpdate(uint8_t*, int) {
    string newname = "new." + executableFilename;
    if (!exists(newname)) return;

    if (exists("old."+executableFilename)) {
        remove(("old."+executableFilename).c_str());
    }
    if (rename(executableFilename.c_str(), ("old."+executableFilename).c_str())) {
        cerr << "Cannot move old executable " << executableFilename << endl;
        return;
    }
    if (rename(newname.c_str(), executableFilename.c_str())) {
        cerr << "Cannot move " << newname << " to " << executableFilename << endl;
        return;
    }

    firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_SUCCESS;
    firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);

    startup(executableFilename.c_str());
    sigset_t sigset{};
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGKILL);
    siginfo_t info;
    timespec t;
    t.tv_nsec=1000*500;
    int s = sigtimedwait(&sigset,&info,&t);
    if (s==SIGKILL){
        cout << "Update completed"<<endl;
        exit(0);
    } else if (s==EINTR) {
        cout << "Updated process didn't report back in time"<<endl;
    } else {
        cerr << "Error with sigtimedwait " << info.si_errno<<endl;
    }
}

// Initalize the KnownObjects::id5::object
class InitModule {
public:
    InitModule() {
        firmwareObjectInstance.Package = writeNewFirmware;
        firmwareObjectInstance.Update = executeFirmwareUpdate;
        firmwareObjectInstance.FirmwareUpdateProtocolSupport = UPDATE_PROTOCOL_COAP;
        firmwareObjectInstance.FirmwareUpdateDeliveryMethod = UPDATE_DELIVERY_PUSH;
        firmwareObjectInstance.PkgVersion.copy(LWM2M_APP_VERSION);
        firmwareObjectInstance.State=exists("new." + executableFilename) ? UPDATE_STATE_DOWNLOADED :UPDATE_STATE_IDLE;
        firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_IDLE;
    }
};
static InitModule initModule;

void checkIsUpdated(int argc, char** argv) {
   executableFilename = argv[0];
   firmwareObjectInstance.PkgName.copy(argv[0]);

   int pid = -1;
   for (int i=0;i<argc;++i){
       auto arg = std::string(argv[i]);
       if (arg.find("oldexe=")!=std::string::npos) {
           arg = arg.substr(arg.find("="));
           pid = std::stoi(arg);
           break;
       }
   }
   if (pid != -1) {
        kill(pid, SIGKILL);
        cout << "Wait for old executable to terminate: " << pid << endl;
        usleep(200*1000);
   }
}
#endif

#endif
