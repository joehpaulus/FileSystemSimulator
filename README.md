Aimed to design a file system simulator that mimics a real-world file system. We use a Tree data structure to represent the overall file system, where each node (Inode), corresponds to a file or a directory.

The project is organized into two parts: Core Features (Master Branch) and Efficient Search (search branch).

Below is a through description of the program's functionality.

In the Lifecycle Methods: We have 2 functions:

1. FileSim(int _diskSize) : numCollisions(0)
This is the constructor. It initializes the necessary variables and the Hash table to a size of 5 slots.

2. ~FileSim()
This is the destructor, which takes care of any postprocessing that is required in order to avoid any memory leaks or overflows.

In the Helper Methods: We have the following functions that assist the programs functionality:

1. makeNode(std::string name, bool isDirectory)
This is function takes in 2 arguements, the name of the file or directory and a boolean variable that dictates wether the node is a directory or file : Additionally, this function:
assigns all the new node attributes.
inserts new node linearly.
2. getChild(Inode* parent, std::string name)
This function finds a child within a parent directory using the child's name.
3. pathToNode(std::string path)
Returns the node pointed to by path. path may be...
The special path '..', which returns the parent of the current. directory, or the current directory if there is no parent.
An absolute path in the format /dir1/dir2/... where / is the root and /dir1 is a child directory of the root.
A relative path (a file in the current working directory)
4. nodeToPath(Inode *node)
Returns an absolute path given a node.
5. recursiveDelete(Inode *node)
Goes thru all childs of current node and recursively delete each child node, then deletes the input node.
6. treeHelper(Inode* node, int level)
Recursively print the node's contents. Starting with the current directory, it print the entire descendant subtree of files and subdirectories.
7. timeToString(time_t t)
Converts time t to a string variable.


In the Public API:

1. touch(std::string fileName)
Checks to see if the new file does not cause the total data usage to exceed the disk capacity, in which case does not insert the new Inode and returns an error message to the user. Checks to see if a file by the same name already exists in the current directory, in which case also do not insert the new Inode and return an error message to the user. Otherwise, create a new Inode that is a file type (directory = false). Asks the user to enter the file name.
2. mkdir(std::string dirName)
Creates a new Inode that is a directory type. Inserts the Inode into the current directory. Since even a directory type has a size of 1 byte, the same check for exceeding the disk capacity is performed.
3. ls()
Lists the contents of the current directory, including all the files and subdirectories.
4. pwd()
From the current directory, prints the path to the root.
5. tree()
Using treehelper(), it recursively print the node's contents. Starting with the current directory, it print the entire descendant subtree of files and subdirectories.
6. cat(std::string path)
Asks the user for a file name in the current directory and prints the fileData contents.
7. stat(std::string path)
Asks the user for a file name in the current directory and print all the info from the file including the file size, file type, creation and modified times, and its parent directory.
8. edit(std::string path, std::string newValue)
Asks the user which file to edit (path). Checks if a corresponding Inode exists in the current directory, and only allow editing if it is a file type (i.e. cannot edit a directory Inode type). Asks the user to enter a string (newValue) to override the string in the corresponding fileData Inode member. The new file size is the length of the fileData string size plus one. Ensures that this does not cause the disk capacity to overflow, and updates the corresponding fileSize.
9. cd(std::string dirPath)
Change the directory (to dirPath) by traversing the tree structure and updating the currentDir pointer.
10. rm(std::string path, bool recursive)
Removes file or directory (path) from the current directory. If the user chooses to delete an entire subdirectory, prompt them to ensure that is their intention. Checks if it's recursive/ if it may be removed.
11. mv(std::string originPath, std::string destPath)
This feature can be used to either change the name of an Inode or to change its location. It should take in two strings, which are either the name of the existing file and the new file name, or the absolute path of an existing file and the absolute path of the file’s new location.
12. search(std::string key)
Prompts the user for a search input. The input can either be a file or a directory name. If one or more files with the name exist in the file system, print the path from the root to the given file(s).
13. Quit
Exits the menu loop and quit the program



INSTRUCTIONS TO USING PROGRAM:

1. In your terminal, change the directory to the build folder located within the project.
2. Type "./run_app_1" (without "") and hit Enter.
3. The program will output "Welcome to fileSim! Type help to view commands.".
4. The above commands (Public API) that are available to use can be viewed by typing in help.
5. Choose your command - Valid commands: quit, touch, edit, mkdir, ls, tree, rm, cd, mv, pwd, stat, cat, search.
6. Enter your command into the terminal along with the necessary arguements provided above.
7. Once your are finished with the program, enter "Quit" to exit the menu loop and quit the program.


Additional Hash Table Functionalities:

1. createNode(std::string _key, Inode *_iptr, HashNode *_next)
creates a HashNode to be inserted into the hash table with a: key, iptr, and next->node.
2. hashFunction(string s)
A common hash insertion function that multiplies current hash by prime number (31) and adds ASCII value then modulo to fit in table.
3. searchItem(string key)
Similar to the search(std::string key), but returns the HashNode you are looking for.
4. insertItemLinear(std::string _key, Inode *_iptr)
Inserts item in a linear method into the hash table. (index = (index+1)% tableSize)
5. insertItemQuadratic(std::string _key, Inode *_iptr)
Inserts item in a quadratic method into the hash table. (index = (index + i * i) % tableSize)
6. insertItemChaining(std::string _key, Inode *_iptr)
Inserts item using chaining, adding to a linked list at the index that a collision occured.
7. resizeHashTable()
Resizes the hash table as necessary.
8. resetCollisions()
Sets collission (numCollisions) to 0.
9. getCollisions()
Returns the number of collisions.

Thanks for reading :)
