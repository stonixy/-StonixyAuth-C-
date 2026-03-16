#include <iostream>
#include <string>
#include <iomanip>
#include "stonixyauth/stonixyauth.hpp"

const std::string LOCAL_VERSION = "1.0";

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader() {
    std::cout << "========================================" << std::endl;
    std::cout << "          STONIXYAUTH CLIENT            " << std::endl;
    std::cout << "========================================" << std::endl;
}


bool Stonixy::api::init(const std::string& currentVersion) {
    auto res = this->checkApp();
    if (!res.success) {
        std::cout << (skCrypt("[!] Connection to StonixyAuth failed!").decrypt()) << std::endl;
        return false;
    }

    if (res.app.version != currentVersion) {
        std::cout << (skCrypt("[!] Version mismatch detected!").decrypt()) << std::endl;
        std::cout << (skCrypt("    Local:  ").decrypt()) << currentVersion << std::endl;
        std::cout << (skCrypt("    Server: ").decrypt()) << res.app.version << std::endl;
        return false;
    }

    if (res.app.status != (skCrypt("active").decrypt())) {
        std::cout << (skCrypt("[!] Application is currently disabled by developer.").decrypt()) << std::endl;
        return false;
    }

    return true;
}

int main() {

    if (!StonixyAuth.init(LOCAL_VERSION)) {
        std::cin.get();
        return 1;
    }

    while (true) {
        clearScreen();
        printHeader();
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "\nChoose option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string user, pass;
            std::cout << "Username: "; std::cin >> user;
            std::cout << "Password: "; std::cin >> pass;

            std::cout << "[*] Authenticating..." << std::endl;
            auto res = StonixyAuth.login(user, pass);

            if (res.success) {
                clearScreen();
                printHeader();
                std::cout << "SUCCESSFULLY LOGGED IN" << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "Username:  " << res.info.username << std::endl;
                std::cout << "Expires:   " << (res.info.expires_at.empty() ? "Lifetime" : res.info.expires_at) << std::endl;
                std::cout << "Var:       " << res.info.user_var << std::endl;
                std::cout << "HWID:      " << res.info.hwid.substr(0, 15) << "..." << std::endl;
                std::cout << "----------------------------------------" << std::endl;

                if (!res.variables.empty()) {
                    std::cout << "\nServer Variables:" << std::endl;
                    for (auto const& [key, val] : res.variables) {
                        std::cout << " - " << key << ": " << val << std::endl;
                    }
                   
                
                    std::string variable = "your_variable_name"; // Change to any key you have
                    std::cout << "\n[Demo] Fetching '" << variable << "' via getVar: "
                        << StonixyAuth.getVar(variable, skCrypt("Not Found").decrypt()) << std::endl;
                }

                std::cout << "\nPress Enter to logout...";
                std::cin.ignore();
                std::cin.get();
            }
            else {
                std::cout << "[!] Login Error: " << res.message << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
        }
        else if (choice == 2) {
            std::string user, pass, key;
            std::cout << "Username: "; std::cin >> user;
            std::cout << "Password: "; std::cin >> pass;
            std::cout << "License Key: "; std::cin >> key;

            std::cout << "[*] Creating account..." << std::endl;
            auto res = StonixyAuth.registerUser(user, pass, key);

            if (res.success) {
                std::cout << "[+] Registration successful! You can now login." << std::endl;
            }
            else {
                std::cout << "[!] Registration failed: " << res.message << std::endl;
            }
            std::cin.ignore();
            std::cin.get();
        }
        else {
            break;
        }
    }

    return 0;
}
