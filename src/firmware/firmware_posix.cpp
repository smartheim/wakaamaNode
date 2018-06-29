/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
typedef int make_iso_compilers_happy; // if not LWIP

#include "wakaama_config.h"

#ifdef LWM2M_FIRMWARE_UPGRADES
#include "lwm2m/firmware.h"
#include "lwm2m/connect.h"

#if (defined(_WIN32) || defined(__unix__))
#include <iostream>
#include <fstream>
using namespace std;
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

void FirmwareUpdate::process() {}

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void writeNewFirmware(Lwm2mObjectInstance* o, DynArray<uint8_t*>& firmware) {
    FirmwareUpdate* fu = static_cast<FirmwareUpdate*>(o);
    string newname = "new." + fu->executableFilename;
    ofstream fout(newname, ofstream::trunc);
    if (!fout.is_open()) {
        cerr << "Cannot open file for writing " << newname << endl;
        return;
    }
    fout.write((const char*)firmware.data, firmware.len);
    fout.close();
}

void executeFirmwareUpdate(Lwm2mObjectInstance* o, lwm2m_context_t* context) {
    FirmwareUpdate* fu = static_cast<FirmwareUpdate*>(o);

    string newname = "new." + fu->executableFilename;
    if (!exists(newname)) return;

    if (exists("old."+fu->executableFilename)) {
        remove(("old."+fu->executableFilename).c_str());
    }
    if (rename(fu->executableFilename.c_str(), ("old."+fu->executableFilename).c_str())) {
        cerr << "Cannot move old executable " << fu->executableFilename << endl;
        return;
    }
    if (rename(newname.c_str(), fu->executableFilename.c_str())) {
        cerr << "Cannot move " << newname << " to " << fu->executableFilename << endl;
        return;
    }

    fu->UpdateResult=UPDATE_RESULT_STATE_SUCCESS;
    fu->firmwareObject.resChanged(context,0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);

    startup(fu->executableFilename.c_str());
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

FirmwareUpdate::FirmwareUpdate(const char* app_version, lwm2m_update_protocol protocol) {
    Package = writeNewFirmware;
    Update = executeFirmwareUpdate;
    FirmwareUpdateProtocolSupport = protocol;
    FirmwareUpdateDeliveryMethod = UPDATE_DELIVERY_PUSHPULL;
    PkgVersion.copy(app_version);
    State = UPDATE_STATE_IDLE;
    UpdateResult=UPDATE_RESULT_STATE_IDLE;
}

void FirmwareUpdate::checkIsUpdated(int argc, char** argv) {
   executableFilename = argv[0];
   const size_t last_slash_idx = executableFilename.find_last_of("\\/");
   if (std::string::npos != last_slash_idx)
       executableFilename.erase(0, last_slash_idx + 1);
   State=exists("new." + executableFilename) ? UPDATE_STATE_DOWNLOADED :UPDATE_STATE_IDLE;
   PkgName.copy(argv[0]);

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
