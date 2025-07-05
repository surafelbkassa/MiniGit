#include "MiniGit.hpp"
#include <iostream>

int main() {
    MiniGit mgit;
    std::string cmd;

    std::cout << "MiniGit (student version)\n";

    while (true) {
        std::cout << ">> ";
        std::cin >> cmd;

        if (cmd == "exit") break;
        else if (cmd == "init") mgit.initRepo();
        else if (cmd == "add") {
            std::string file;
            std::cin >> file;
            mgit.addFile(file);
        }
        else if (cmd == "commit") {
            std::cin.ignore();
            std::string msg;
            getline(std::cin, msg);
            mgit.makeCommit(msg);
        }
        else if (cmd == "log") mgit.showLog();
        else if (cmd == "branch") {
            std::string name;
            std::cin >> name;
            mgit.createBranch(name);
        }
        else if (cmd == "checkout") {
            std::string t;
            std::cin >> t;
            mgit.switchTo(t);
        }
        else if (cmd == "merge") {
            std::string name;
            std::cin >> name;
            mgit.mergeBranch(name);
        }
        else if (cmd == "diff") {
            std::string a, b;
            std::cin >> a >> b;
            mgit.diffFiles(a, b);
        }
        else std::cout << "Unknown command\n";
    }

    return 0;
}