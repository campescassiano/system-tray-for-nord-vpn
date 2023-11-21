#include "NordVPN.hpp"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>

NordVPN::NordVPN() : connected_(false) {
    std::string nordVPNPath = "/usr/bin/" + kNordVPNBinary;
    bool        exists      = std::filesystem::exists(nordVPNPath);
    if (!exists)
        std::cerr << "The " << kNordVPNBinary << " was not found" << std::endl;

    connected_ = NordVPN::IsConnected();
}

NordVPN::~NordVPN() {
    if (!NordVPN::IsConnected()) return;

    NordVPN::SetAction(NordVPNAction::Disconnect);

    if (NordVPN::IsConnected())
        std::cerr << "Could not disconnect" << std::endl;
}

bool NordVPN::IsConnected(void) {
    std::string command = kNordVPNBinary + " " + "status";

    FILE *pipe = popen(command.c_str(), "r");

    if (!pipe) {
        std::cerr << "Error opening pipe to command " << command << std::endl;
        return false;
    }

    constexpr int BUFFER_SIZE = 128;
    char          buffer[BUFFER_SIZE];

    std::string result;
    while (fgets(buffer, BUFFER_SIZE, pipe) != nullptr) {
        char *str = strstr(buffer, "Status: ");
        if (str == nullptr) continue;

        str += strlen("Status: ");

        char *endl = strstr(str, "\n");
        if (endl) *endl = '\0';

        if (strstr(str, "Connected"))
            connected_ = true;
        else
            connected_ = false;
    }

    if (pclose(pipe) == -1) {
        std::cerr << "Error closing the pipe to command" << std::endl;
        return false;
    }

    return connected_;
}

void NordVPN::Toggle(void) {
    if (NordVPN::IsConnected())
        NordVPN::SetAction(NordVPNAction::Disconnect);
    else
        NordVPN::SetAction(NordVPNAction::Connect);
}

void NordVPN::SetAction(NordVPNAction action) {
    std::string command =
        kNordVPNBinary + " " +
        ((action == NordVPNAction::Connect) ? "connect" : "disconnect");

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
        std::cerr << "Error opening pipe to command " << command << std::endl;

    connected_ = NordVPN::IsConnected();

    if (pclose(pipe) == -1)
        std::cerr << "Error closing the pipe to command" << std::endl;
}
