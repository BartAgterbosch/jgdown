#include <stdio.h>
#include <windows.h>

int main() {
    FILE *tunnelNamesBuffer;
    char tunnelNames[4096] = "\0";
    char *tunnelName;
    char x64Path[512] = "\0";
    char x86Path[512] = "\0";
    char wireguardPath[512] = "\0";
    char showIntf[512] = "\0";

    snprintf(x64Path, sizeof(x64Path), "%s\\Program Files\\Wireguard\\wg.exe", getenv("SystemDrive"));
    snprintf(x86Path, sizeof(x86Path), "%s\\Program Files (x86)\\Wireguard\\wg.exe", getenv("SystemDrive"));
    
    if ((GetFileAttributes(x64Path) != INVALID_FILE_ATTRIBUTES) && !(GetFileAttributes(x64Path) & FILE_ATTRIBUTE_DIRECTORY)) {
        //Build command with path
        snprintf(showIntf, sizeof(showIntf), "\"%s\" show interfaces", x64Path);

        //Get active tunnels
        tunnelNamesBuffer = popen(showIntf, "r");
        if (fgets(tunnelNames, sizeof(tunnelNames), tunnelNamesBuffer) != NULL) {
            tunnelNames[strcspn(tunnelNames, "\r\n")] = ' ';
        }
        pclose(tunnelNamesBuffer);

        //Set wireguard.exe path
        snprintf(wireguardPath, sizeof(wireguardPath), "%s\\Program Files\\Wireguard\\wireguard.exe", getenv("SystemDrive"));
    } else if ((GetFileAttributes(x86Path) != INVALID_FILE_ATTRIBUTES) && !(GetFileAttributes(x86Path) & FILE_ATTRIBUTE_DIRECTORY)) {
        //Build command with path
        snprintf(showIntf, sizeof(showIntf), "\"%s\" show interfaces", x86Path);

        //Get active tunnels
        tunnelNamesBuffer = popen(showIntf, "r");
        if (fgets(tunnelNames, sizeof(tunnelNames), tunnelNamesBuffer) != NULL) {
            tunnelNames[strcspn(tunnelNames, "\r\n")] = ' ';
        }
        pclose(tunnelNamesBuffer);

        //Set wireguard.exe path
        snprintf(wireguardPath, sizeof(wireguardPath), "%s\\Program Files (x86)\\Wireguard\\wireguard.exe", getenv("SystemDrive"));
    } else {
        printf("Please (re)install Wireguard on your systemdrive.");
        return 1;
    }
    
    //Split on spaces and build array with tunnel names
    tunnelName = strtok(tunnelNames, " ");

    while (tunnelName != NULL) {
        //Avoid NordVpn tunnel from being pulled down
        if (strcmp(tunnelName, "NordLynx") != 0) {
            //Build full command dynamically each time
            char tunnelDownCommand[512];
            snprintf(tunnelDownCommand, sizeof(tunnelDownCommand), "\"%s\" /uninstalltunnelservice %s", wireguardPath, tunnelName);

            //Pull down tunnel
            system(tunnelDownCommand);
        }
        tunnelName = strtok(NULL, " ");
    }
    return 0;
}