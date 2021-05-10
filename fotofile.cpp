#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include <stdio.h>


using namespace std;


string parseFileName(string Line){
    string outString = Line.substr(34);
    return outString;
}

string parseFileType(string Line){
    string outString = Line.substr(Line.rfind(":") + 2);
    return outString;
}

string parseDirectoryName(string Line){
    string outString = Line.substr((Line.rfind(":") + 2));
    return outString;
}

string getYear(string Line){
    string outString = Line.substr(34,4);
    return outString;
}

string getMonth(string Line){
    string outString = Line.substr(39,2);
    return outString;
}

string getDay(string Line){
    string outString = Line.substr(42,2);
    return outString;
}

string parseDateTaken(string Line){
    string outString = Line.substr(Line.find("'") + 1,Line.rfind("'") - Line.find("'") - 1);
    if (outString.find("0000:00:00 00:00:00") != std::string::npos) {
            outString = "1900:01:01 01:01:01";
        }
    return outString;
}

bool isPicture(string fn){
    string extensions[] = {"jpg","JPG","jpeg","JPEG","ARW","NEF","png","PNG"};
    for ( int i = 0; i < 8; i++ ) {
        if(fn.substr(fn.find_last_of(".") + 1) == extensions[i]) {
            return true;
        }    
    } 
    return false;
}

bool IsPathExist(const std::string &s){
    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
}

bool fileExists(string path){
    fstream localFile;
    localFile.open(path, ios::in);
    if (localFile){
        localFile.close();
        return true;
    }
    else{
        return false;
    }  
 }

int createDirectory(string directory_name){
//
//  this interesting bit of syntax does the first line if sucessful and the second if not
//   
    std::filesystem::create_directory(directory_name)?
    cout << "Created directory " << directory_name << "\n":
    cout << "create_directory() failed" << "\n";

    return EXIT_SUCCESS;
}

/***********************************************************************************************/

int main( int argc, char** argv)
{
    /*
    for (int i = 0; i < argc; ++i)
        cout << "argument = " << argv[i] << "\n";
    */
    argc++;
    
    string sourceDir = argv[1];
    string targetDir = argv[2];

    ifstream infile("/tmp/exiftool.txt");
        if (!infile) {
            cerr << "Input file could not be opened for reading!" << "\n";
            exit(1);
        }

    string fileName, fileType, dirName, inLine, YYYY, MM, DD, slash = "/";

    getline(infile,inLine);
    while (!infile.eof())
     {                   
        if (inLine.find("File Name") != std::string::npos){
            fileName = parseFileName(inLine);   
        }

        if (inLine.find("Directory") != std::string::npos){
            dirName = parseDirectoryName(inLine);           
        }
         
        if (inLine.substr(0,11) == "File Type  "){
            fileType = parseFileType(inLine);           
        }

        if (inLine.find("Date/Time Original") != std::string::npos){
            YYYY = getYear(inLine);
            MM = getMonth(inLine);
            DD = getDay(inLine);           
        }
   
        getline(infile,inLine);
    }

    if (isPicture(fileName)){
               
        targetDir.append(slash);
        targetDir.append(YYYY);
        if (!IsPathExist(targetDir)){
            createDirectory(targetDir);
        }

        targetDir.append(slash);
        targetDir.append(MM);
        if (!IsPathExist(targetDir)){
            createDirectory(targetDir);
        }

        targetDir.append(slash);
        targetDir.append(DD);
        if (!IsPathExist(targetDir)){
            createDirectory(targetDir);
        }

        targetDir.append(slash);
        targetDir.append(fileName);       
        if (!fileExists(targetDir)){
            sourceDir.append(slash);
            sourceDir.append(fileName);
            cout << "    Copying " << targetDir << "\n";
            std::filesystem::copy(sourceDir,targetDir);
        }
        
    }
    infile.close();

    return 0;
}
