/* winprocess.c — Process creation on Windows using CreateProcess() */
#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu) — creating child...\n", GetCurrentProcessId());

    if (!CreateProcess(
            "C:\\Windows\\System32\\notepad.exe",
            NULL, NULL, NULL, FALSE, 0, NULL, NULL,
            &si, &pi))
    {
        fprintf(stderr, "CreateProcess failed (error %lu).\n", GetLastError());
        return 1;
    }

    printf("Child process created!\n");
    printf("  Child PID:       %lu\n", pi.dwProcessId);
    printf("  Child Thread ID: %lu\n", pi.dwThreadId);
    printf("Parent: sleeping 60 seconds — do your screenshots NOW!\n");
    printf(">>> Open Task Manager and second CMD now! <<<\n");

    /* Sleep 60 seconds so you have time to take screenshots */
    Sleep(60000);

    printf("Parent: now waiting for child (notepad) to exit...\n");
    printf(">>> Close notepad to finish! <<<\n");

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent: child has exited. Cleaning up.\n");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}