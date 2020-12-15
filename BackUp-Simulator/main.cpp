//
//  main.cpp
//  newBackUp
//
//  Created by Sara Nikolić
//

#include <iostream>
#include "newBackUp.hpp"

int main() {
    try{
/*
        OPTIONS:
 
        - su.filesToBackUp(); // argument: vector of strings, where strings are paths to actual files
        - su.MakeRestorePoint(); // argument: "full" or "delta"
        - su.addFile(); // argument: path to actual file
        - su.deleteFile(); // argument: filename
        - su.writeToFile(); // argument: path to actual file
        - su.saveRPs(); // argument: "folders" or "archive"
        - su.controlRPs(); // arguments(3): date, length, size, or "" (note that first argument must not be an empty string! also, date is changed internally within the function SystemUtility::pickAlg()
        - su.print(); // no argument needed
 
        NOTES:
        Concerning time: files only keep a record of the time of their creation, whereas the time of creation of Restore points depends on their ID.
 */
        SystemUtility su(1);
        std::string f1 = "/Users/zimbara/Desktop/fileOne.txt";
        std::string f2 = "/Users/zimbara/Desktop/fileTwo.txt";
        std::string f3 = "/Users/zimbara/Desktop/fileThree.txt";
        std::string f4 = "/Users/zimbara/Desktop/fileFour.txt";
        std::vector<std::string> files;
        files.push_back(f1);
        files.push_back(f2);
        files.push_back(f3);
        files.push_back(f4);
        su.filesToBackUp(files);
        su.MakeRestorePoint("full");
        su.writeToFile(f1);
        su.deleteFile("fileTwo");
        su.MakeRestorePoint("delta");
        su.writeToFile(f3);
        su.MakeRestorePoint("delta");
        su.addFile(f2);
        su.MakeRestorePoint("delta");
//        su.saveRPs("folders");
        su.saveRPs("archive");
        su.controlRPs("hybrid"); // hybrid
        su.print();
    } catch(const std::runtime_error& e){
        std::cout << "Runtime error occurred...\n" << e.what() << "\n";
    }
    
    
    
    return 0;
}
