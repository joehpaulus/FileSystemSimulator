#include <gtest/gtest.h>
#include "test_helpers.hpp"
#include "../code_1/fileSim.hpp"

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName)
{
    std::string line, out;
    ifstream A;
    A.open(fileName);
    if (!A)
    {
        throw std::runtime_error("could not open file: " + fileName);
    }
    while (getline(A, line))
    {
        out = out + line + "\n";
    }
    return out;
}

// helpers
bool validateArgs(std::string command, std::vector<string> &args)
{
    // Validates the number of args for a command

    if (command == "rm")
    {
        if (args.size() != 2 && args.size() != 3)
        {
            cout << "rm requires 1 or 2 arguments!" << endl;
            return false;
        }
        return true;
    }

    std::vector<std::string>::size_type desiredArgs;
    if (command == "ls" || command == "tree" || command == "pwd")
    {
        desiredArgs = 0;
    }
    else if (command == "touch" || command == "mkdir" || command == "cd" || command == "stat" || command == "cat" || command == "search")
    {
        desiredArgs = 1;
    }
    else
    {
        desiredArgs = 2;
    }
    if (args.size() != desiredArgs + 1)
    {
        cout << command << " requires " << desiredArgs << " arguments, but you passed " << args.size() - 1 << endl;
        return false;
    }
    return true;
}

int handleCommand(std::string command, std::vector<std::string> &args, FileSim *fs)
{
    // Verify we have passed the correct number of arguments
    if (!validateArgs(command, args))
    {
        return 1;
    }

    // Resolve the command with the appropriate function
    if (command == "touch")
    {
        return fs->touch(args.at(1));
    }
    else if (command == "edit")
    {
        return fs->edit(args.at(1), args.at(2));
    }
    else if (command == "mkdir")
    {
        return fs->mkdir(args.at(1));
    }
    else if (command == "ls")
    {
        fs->ls();
    }
    else if (command == "tree")
    {
        fs->tree();
    }
    else if (command == "rm")
    {
        bool recursive = false;
        if (args.size() == 3)
        {
            if (args.at(2) == "-r")
            {
                recursive = true;
            }
            else
            {
                cout << "rm: Invalid flag " << args.at(2) << endl;
                return 1;
            }
        }
        return fs->rm(args.at(1), recursive);
    }
    else if (command == "cd")
    {
        return fs->cd(args.at(1));
    }
    else if (command == "mv")
    {
        return fs->mv(args.at(1), args.at(2));
    }
    else if (command == "pwd")
    {
        fs->pwd();
    }
    else if (command == "stat")
    {
        return fs->stat(args.at(1));
    }
    else if (command == "cat")
    {
        return fs->cat(args.at(1));
    }
    else if (command == "search")
    {
        // TODO
    }
    else
    {
        cout << "Invalid command. Use `help` to get a list of valid commands." << endl;
        return 1;
    }
    return 0;
}

void addFiles(vector<string> &args, string *fileName, int fileLen, FileSim &fs)
{
    args.push_back("touch");
    for (int i = 0; i < fileLen; i++)
    {
        args.push_back(fileName[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }
}

void addDirectories(vector<string> &args, string *dirName, int dirLen, FileSim &fs)
{
    args.push_back("mkdir");
    for (int i = 0; i < dirLen; i++)
    {
        args.push_back(dirName[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }
}

// SEVERAL TEST FUNCTIONS HERE
string test_touch(string *fileName, int len)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    args.push_back("touch");
    for (int i = 0; i < len; i++)
    {
        cout << "Creating file: " << fileName[i] << endl;
        args.push_back(fileName[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_mkdir(string *dirName, int len)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    args.push_back("mkdir");
    for (int i = 0; i < len; i++)
    {
        cout << "Creating directory: " << dirName[i] << endl;
        args.push_back(dirName[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_ls(string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("ls");
    handleCommand(args.front(), args, &fs);

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_pwd(string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("pwd");
    handleCommand(args.front(), args, &fs);

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_tree(string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("tree");
    handleCommand(args.front(), args, &fs);

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_edit(string *path, string *newValue, int len, string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(50);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("edit");
    for (int i = 0; i < len; i++)
    {
        cout << "Editing file: " << path[i] << endl;
        args.push_back(path[i]);
        args.push_back(newValue[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_cat(string *path, int len, string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("cat");
    for (int i = 0; i < len; i++)
    {
        cout << "File content of: " << path[i] << endl;
        args.push_back(path[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}

/*
string test_stat(string* path, int len, string* fileName, int fileLen, string* dirName, int dirLen)
{
    testing::internal::CaptureStdout();
    
    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("stat");
    for(int i = 0;i<len;i++)
    {
        cout << "Stats of: " << path[i] << endl;
        args.push_back(path[i]); 
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}
*/

string test_cd(string *dirPath, int len, string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(5);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("cd");
    for (int i = 0; i < len; i++)
    {
        cout << "Changing directory to: " << dirPath[i] << endl;
        args.push_back(dirPath[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_rm(string *path, string *flag, int len, int len2, string *fileName, int fileLen, string *dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(50);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("rm");
    for (int i = 0; i < len; i++)
    {
        cout << "Removing: " << path[i] << endl;
        args.push_back(path[i]);
        if (i < len2)
        {
            args.push_back(flag[i]);
        }
        handleCommand(args.front(), args, &fs);
        args.pop_back();
        if (i < len2)
        {
            args.pop_back();
        }
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_mv(string* originPath, string* destPath, int len, string* fileName, int fileLen, string* dirName, int dirLen)
{
    testing::internal::CaptureStdout();

    // Test code here
    FileSim fs(50);
    vector<string> args;
    addFiles(args, fileName, fileLen, fs);

    args.clear();
    addDirectories(args, dirName, dirLen, fs);

    args.clear();
    args.push_back("mv");
    for (int i = 0; i < len; i++)
    {
        cout << "Moving from: " << originPath[i] << " to " << destPath[i] << endl;
        args.push_back(originPath[i]);
        args.push_back(destPath[i]);
        handleCommand(args.front(), args, &fs);
        args.pop_back();
        args.pop_back();
    }

    string output = testing::internal::GetCapturedStdout();
    return output;
}
