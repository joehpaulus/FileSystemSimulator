// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>

#include "test_helpers.hpp"
#include "../code_1/fileSim.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestTouch){
    
    
    string result;
    string expected;
    
	int len = 5;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt", "image.txt", "present.txt"};
    result = test_touch(fileNames, len);
    expected = "Creating file: csci2270.txt\nCreating file: project.txt\nCreating file: report.txt\nCreating file: image.txt\nCreating file: present.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len1 = 5;
    string fileNames1[] = {"csci2270.txt", "project.txt", "report.txt", "project.txt", "present.txt"};
    result = test_touch(fileNames1, len1);
    expected = "Creating file: csci2270.txt\nCreating file: project.txt\nCreating file: report.txt\nCreating file: project.txt\nDuplicate name: project.txt\nCreating file: present.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len2 = 6;
    string fileNames2[] = {"csci2270.txt", "project.txt", "report.txt", "image.txt", "present.txt", "apps.txt"};
    result = test_touch(fileNames2, len2);
    expected = "Creating file: csci2270.txt\nCreating file: project.txt\nCreating file: report.txt\nCreating file: image.txt\nCreating file: present.txt\nCreating file: apps.txt\nNo space left on disk!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len3 = 0;
    string fileNames3[len3];
    result = test_touch(fileNames3, len3);
    expected = "";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);

}


TEST_F(test_x, TestMkdir){
    
    
    string result;
    string expected;
    
	int len = 5;
    string dirNames[] = {"csci2270", "project", "report", "image", "present"};
    result = test_mkdir(dirNames, len);
    expected = "Creating directory: csci2270\nCreating directory: project\nCreating directory: report\nCreating directory: image\nCreating directory: present\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len1 = 5;
    string dirNames1[] = {"csci2270", "project", "report", "project", "present"};
    result = test_mkdir(dirNames1, len1);
    expected = "Creating directory: csci2270\nCreating directory: project\nCreating directory: report\nCreating directory: project\nDuplicate name: project\nCreating directory: present\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len2 = 6;
    string dirNames2[] = {"csci2270", "project", "report", "image", "present","app"};
    result = test_mkdir(dirNames2, len2);
    expected = "Creating directory: csci2270\nCreating directory: project\nCreating directory: report\nCreating directory: image\nCreating directory: present\nCreating directory: app\nNo space left on disk!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len3 = 0;
    string dirNames3[len3];
    result = test_mkdir(dirNames3, len3);
    expected = "";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);

}


TEST_F(test_x, TestLs){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
    result = test_ls(fileNames, fileLen, dirNames, dirLen);
    expected = "csci2270.txt\nproject.txt\nreport.txt\nimage\npresent\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);

	int fileLen1 = 0;
	int dirLen1 = 0;
    string fileNames1[fileLen1];
	string dirNames1[dirLen1];
    result = test_ls(fileNames1, fileLen1, dirNames1, dirLen1);
    expected = "";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);

	int fileLen2 = 0;
	int dirLen2 = 2;
    string fileNames2[fileLen2];
	string dirNames2[] = {"image", "present"};
    result = test_ls(fileNames2, fileLen2, dirNames2, dirLen2);
    expected = "image\npresent\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);

	int fileLen3 = 3;
	int dirLen3 = 0;
    string fileNames3[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames3[dirLen3];
    result = test_ls(fileNames3, fileLen3, dirNames3, dirLen3);
    expected = "csci2270.txt\nproject.txt\nreport.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);

}


TEST_F(test_x, TestPwd){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
    result = test_pwd(fileNames, fileLen, dirNames, dirLen);
    expected = "/\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);

	int fileLen1 = 0;
	int dirLen1 = 0;
    string fileNames1[fileLen1];
	string dirNames1[dirLen1];;
    result = test_pwd(fileNames1, fileLen1, dirNames1, dirLen1);
    expected = "/\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);

}


TEST_F(test_x, TestTree){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
    result = test_tree(fileNames, fileLen, dirNames, dirLen);
    expected = " (root)\n- csci2270.txt\n- project.txt\n- report.txt\n- image\n- present\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

	int fileLen1 = 0;
	int dirLen1 = 0;
    string fileNames1[fileLen1];
	string dirNames1[dirLen1];
    result = test_tree(fileNames1, fileLen1, dirNames1, dirLen1);
    expected = " (root)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);

}

TEST_F(test_x, TestEdit){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
	int len = 3;
	string paths[] = {"project.txt", "csci2270.txt", "a.txt"};
	string newValues[] = {"File Simulator Project", "Data Structures", "Letter a"};
    result = test_edit(paths, newValues, len, fileNames, fileLen, dirNames, dirLen);
    expected = "Editing file: project.txt\nEditing file: csci2270.txt\nEditing file: a.txt\nedit: a.txt: No such file or directory\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

	int len1 = 1;
	string paths1[] = {"csci2270.txt","csci2270.txt","csci2270.txt"};
	string newValues1[] = {"File Simulator Project. Data Structures. I have complete this project successfully. I can't imagine I did this. So proud of myself. Excited to learn more data structures.","File Simulator Project.", "Data Structures."};
    result = test_edit(paths1, newValues1, len1, fileNames, fileLen, dirNames, dirLen);
    expected = "Editing file: csci2270.txt\nedit: No more space left on disk\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

	int len2 = 2;
	string paths2[] = {"present", "csci2270.txt"};
	string newValues2[] = {"File Simulator Project", "Data Structures"};
    result = test_edit(paths2, newValues2, len2, fileNames, fileLen, dirNames, dirLen);
    expected = "Editing file: present\nedit: present: Is a directory\nEditing file: csci2270.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

	int len3 = 2;
	string paths3[] = {"csci2270.txt","csci2270.txt"};
	string newValues3[] = {"File Simulator Project.", "Data Structures."};
    result = test_edit(paths3, newValues3, len3, fileNames, fileLen, dirNames, dirLen);
    expected = "Editing file: csci2270.txt\nEditing file: csci2270.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

}


TEST_F(test_x, TestCat){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
	int pathLen = 3;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
	string paths[] = {"project.txt", "present", "oops.txt"};
    result = test_cat(paths, pathLen, fileNames, fileLen, dirNames, dirLen);
    expected = "File content of: project.txt\n\nFile content of: present\ncat: present: Is a directory\nFile content of: oops.txt\ncat: oops.txt: No such file or directory\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}


/*
TEST_F(test_x, TestStat){

}
*/


TEST_F(test_x, TestCd){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
	int pathLen = 4;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
	string paths[] = {"project.txt", "present", "oops.txt", "none"};
    result = test_cd(paths, pathLen, fileNames, fileLen, dirNames, dirLen);
    expected = "Changing directory to: project.txt\ncd: not a directory: project.txt\nChanging directory to: present\nChanging directory to: oops.txt\ncd: no such file or directory: oops.txt\nChanging directory to: none\ncd: no such file or directory: none\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}


TEST_F(test_x, TestRm){
    
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
	int len = 2, len1 = 1;
	string paths[] = {"present", "project.txt"};
	string flags[] = {"-r"};
    result = test_rm(paths, flags, len, len1, fileNames, fileLen, dirNames, dirLen);
    expected = "Removing: present\nRemoving: project.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);

	int len2 = 4, len3 = 0;
	string paths2[] = {"image", "oops.txt", "oops", ".."};
	string flags2[len3];
    result = test_rm(paths2, flags2, len2, len3, fileNames, fileLen, dirNames, dirLen);
    expected = "Removing: image\nrm: image: is a directory\nRemoving: oops.txt\nrm: oops.txt: No such file or directory\nRemoving: oops\nrm: oops: No such file or directory\nRemoving: ..\nrm: '.' and '..' may not be removed\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
}

TEST_F(test_x, TestMv){
    string result;
    string expected;
    
	int fileLen = 3;
	int dirLen = 2;
    string fileNames[] = {"csci2270.txt", "project.txt", "report.txt"};
	string dirNames[] = {"image", "present"};
	int len = 3;
	string oldPaths[] = {"present", "project.txt", "rep.txt"};
	string newPaths[] = {"/present", "temp.txt", "repo.txt"};
    result = test_mv(oldPaths, newPaths, len, fileNames, fileLen, dirNames, dirLen);
    expected = "Moving from: present to /present\nmv: /present: Already exists!\nMoving from: project.txt to temp.txt\nMoving from: rep.txt to repo.txt\nmv: rep.txt: No such file or directory\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);

	int len1=2;
	string oldPaths1[] = {"image", "report.txt"};
	string newPaths1[] = {"/present/image", "rep.txt"};
    result = test_mv(oldPaths1, newPaths1, len1, fileNames, fileLen, dirNames, dirLen);
    expected = "Moving from: image to /present/image\nMoving from: report.txt to rep.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);    

}


void testHashTable(FileSim& fs, HashTableType type) {
    fs.setHashTableType(type);
    fs.resetCollisions();
    for (int i = 0; i < 100; ++i) {
        std::string dirName = "dir" + std::to_string(i);
        std::string fileName = "file" + std::to_string(i);

        fs.mkdir(dirName);
        fs.cd(dirName);
        fs.touch(fileName);
        fs.cd("..");
    }
    std::cout << "Collisions: " << type << fs.getCollisions() << std::endl;
}

TEST(FileSimTest, HashTableCollision_Test)
{
    //made filesim object w table size of 500
    FileSim fs(500);
    cout << "Linear Test" << endl;
    testHashTable(fs, LINEAR_PROBING);
    cout << "Quadratic Test" << endl;
    testHashTable(fs, QUADRATIC_PROBING);
    cout << "Chaining Test" << endl;
    testHashTable(fs, CHAINING);
    //checks table has less than 10 collision to ensure efficiency
    EXPECT_LT(fs.getCollisions(), 10);
    //search for item 
}
