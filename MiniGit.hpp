#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <string>
#include <vector>
#include <map>

struct Commit {
    std::string hash;
    std::string message;
    std::map<std::string, std::string> files;
    std::string parentHash;
};

class MiniGit {
private:
    std::map<std::string, Commit> commitHistory;
    std::map<std::string, std::string> branches;
    std::vector<std::string> stagingArea;
    std::string curBranch;
    std::string latestCommit;

    std::string generateHash();
    void copyFile(const std::string& src, const std::string& dest);

public:
    MiniGit();
    void initRepo();
    void addFile(const std::string& filename);
    void makeCommit(const std::string& msg);
    void showLog();
    void createBranch(const std::string& name);
    void switchTo(const std::string& target);
    void mergeBranch(const std::string& name);
    void diffFiles(const std::string& f1, const std::string& f2);
};

#endif
