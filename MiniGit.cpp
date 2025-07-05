#include "MiniGit.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdio>

MiniGit::MiniGit() {
    curBranch = "main";
    latestCommit = "";
}

std::string MiniGit::generateHash() {
    std::stringstream ss;
    ss << std::time(0);
    return ss.str();
}

void MiniGit::copyFile(const std::string& src, const std::string& dest) {
    std::ifstream in(src);
    std::ofstream out(".minigit/" + dest);
    std::string line;
    while (getline(in, line)) {
        out << line << '\n';
    }
}

void MiniGit::initRepo() {
    system("mkdir .minigit");
    branches[curBranch] = "";
    std::cout << "Repository initialized\n";
}

void MiniGit::addFile(const std::string& filename) {
    std::ifstream test(filename);
    if (!test) {
        std::cout << "File does not exist\n";
        return;
    }
    stagingArea.push_back(filename);
    std::cout << filename << " added to staging\n";
}

void MiniGit::makeCommit(const std::string& msg) {
    std::string hash = generateHash();
    Commit c;
    c.hash = hash;
    c.message = msg;
    c.parentHash = latestCommit;

    for (auto& fname : stagingArea) {
        std::string version = fname + "_" + hash.substr(0, 5);
        copyFile(fname, version);
        c.files[fname] = version;
    }

    commitHistory[hash] = c;
    latestCommit = hash;
    branches[curBranch] = hash;
    stagingArea.clear();

    std::cout << "Commit done: " << hash << "\n";
}

void MiniGit::showLog() {
    std::string h = latestCommit;
    while (h != "") {
        Commit& c = commitHistory[h];
        std::cout << "Commit: " << h << " - " << c.message << "\n";
        h = c.parentHash;
    }
}

void MiniGit::createBranch(const std::string& name) {
    if (branches.count(name)) {
        std::cout << "Branch already exists\n";
        return;
    }
    branches[name] = latestCommit;
    std::cout << "Branch " << name << " created\n";
}

void MiniGit::switchTo(const std::string& target) {
    if (branches.count(target)) {
        curBranch = target;
        latestCommit = branches[target];
        std::cout << "Switched to branch: " << target << "\n";
    } else if (commitHistory.count(target)) {
        latestCommit = target;
        std::cout << "Checked out commit: " << target << "\n";
    } else {
        std::cout << "Not found\n";
    }
}

void MiniGit::mergeBranch(const std::string& name) {
    if (!branches.count(name)) {
        std::cout << "Branch not found\n";
        return;
    }

    std::string other = branches[name];
    Commit merged = commitHistory[latestCommit];

    for (auto& file : commitHistory[other].files) {
        merged.files[file.first] = file.second;
    }

    std::string hash = generateHash();
    merged.hash = hash;
    merged.message = "Merge with " + name;
    merged.parentHash = latestCommit;

    commitHistory[hash] = merged;
    latestCommit = hash;
    branches[curBranch] = hash;

    std::cout << "Merged " << name << " into " << curBranch << "\n";
}

void MiniGit::diffFiles(const std::string& f1, const std::string& f2) {
    std::ifstream a(f1), b(f2);
    std::string la, lb;
    int line = 1;
    while (getline(a, la) && getline(b, lb)) {
        if (la != lb)
            std::cout << "Line " << line << ": " << la << " != " << lb << "\n";
        line++;
    }
}
