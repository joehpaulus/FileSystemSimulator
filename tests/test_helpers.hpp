#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>

#include <array>

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);

string test_touch(string* fileName, int len); // test the core functionality: touch 
string test_mkdir(string* dirName, int len);  
string test_ls(string* fileName, int fileLen, string* dirName, int dirLen); 
string test_pwd(string* fileName, int fileLen, string* dirName, int dirLen);
string test_tree(string* fileName, int fileLen, string* dirName, int dirLen); 
string test_edit(string* path, string* newValue, int len, string* fileName, int fileLen, string* dirName, int dirLen);
string test_cat(string* path, int len, string* fileName, int fileLen, string* dirName, int dirLen); 
// string test_stat(string* path, int len, string* fileName, int fileLen, string* dirName, int dirLen); 
string test_cd(string* dirPath, int len, string* fileName, int fileLen, string* dirName, int dirLen); 
string test_rm(string* path, string* flag, int len, int len2, string* fileName, int fileLen, string* dirName, int dirLen);
string test_mv(string* originPath, string* destPath, int len, string* fileName, int fileLen, string* dirName, int dirLen);
#endif // TEST_H__
