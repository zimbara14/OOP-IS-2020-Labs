//
//  newBackUp.hpp
//  newBackUp
//
//  Created by Sara Nikolić
//

#ifndef newBackUp_hpp
#define newBackUp_hpp

#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <utility>

// --- FILE ---
class File{
    std::string Path;
    std::string Name;
    long long sizeFile;
    time_t timeF;
public:
    File(std::string name);
    File();
    ~File();
    
    std::string getNameF();
    std::string getPathF();
    long long getSizeF();
    long long getSizeFile();
    std::string getCharTimeF();
    time_t getTimeF();
    
    void setSizeF(long long size);
    void setTimeF(time_t time);
    void setNameF(std::string s);
    void setPathF(std::string s);
};

// --- RESTORE POINT ---
class RestorePoint{
protected:
    static int ID;
    int thisID;
    std::string nameRP;
    std::vector<File> filesRestorePoints;
    RestorePoint* parentRP;
   ~RestorePoint();
    time_t timeRP;
    virtual long long setSize(const RestorePoint* rp, const std::string name) = 0;
public:
    std::string getNameRP() const;
    int getIDRP();
    time_t getTimeRP();
    RestorePoint* getParentRP() const;
    virtual void addFileRP(File file) = 0;
    void deleteFile(const std::string& nameF);
    bool findFile(const std::string& nameF) const;
    File getFile(const std::string& nameF) const;
    std::vector<File> getFilesRP() const;
    void printAll();
    long long getSizeRP();
};

class Full : public RestorePoint {
    long long setSize(const RestorePoint* rp, const std::string name) override;
public:
    Full(RestorePoint* par);
    void addFileRP(File file) override;
};

class Incremental : public RestorePoint {
    long long setSize(const RestorePoint* rp, const std::string name) override;
public:
    Incremental(RestorePoint* par);
    void addFileRP(File file) override;
};

// --- DELETE ALGS --- 
class IDeleteAlgorithmCreator{
private:
    std::function<int(const std::vector<RestorePoint*>&)> limit_;
public:
    IDeleteAlgorithmCreator() = default;
    explicit IDeleteAlgorithmCreator(std::function<int(const std::vector<RestorePoint*>&)> limit) : limit_(std::move(limit)) {}
    IDeleteAlgorithmCreator or_(IDeleteAlgorithmCreator& other);
    IDeleteAlgorithmCreator and_(IDeleteAlgorithmCreator& other);
    virtual int limit(const std::vector<RestorePoint*>& rps) const;
};

class SizeAlg : public IDeleteAlgorithmCreator{
private:
    long long sizeLim_;
public:
    explicit SizeAlg(long long sizeLim) : sizeLim_(sizeLim) {}
    static long long size_limiter(long long lim, const std::vector<RestorePoint*>& restorePoints);
    int limit(const std::vector<RestorePoint*>& rps) const override;
};

class DateAlg : public IDeleteAlgorithmCreator{
private:
    time_t timeLim_;
public:
    explicit DateAlg(time_t timeLim) : timeLim_(timeLim) {}
    static int date_limiter(time_t lim, const std::vector<RestorePoint*>& restorePoints);
    int limit(const std::vector<RestorePoint*>& rps) const override;
};

class LengthAlg : public IDeleteAlgorithmCreator{
private:
    size_t lengthLim_;
public:
    explicit LengthAlg(size_t lengthLim) : lengthLim_(lengthLim) {}
    static int length_limiter(size_t lim, const std::vector<RestorePoint*>& restorePoints);
    int limit(const std::vector<RestorePoint*>& rps) const override;
};

// --- BACKUP ---
class BackUp{
private:
    time_t creationTimeBU;
    long long sizeBackUp;
    std::vector<RestorePoint*> restorePointList;
    std::vector<File> filesForBackup;
public:
    BackUp();
    void addFileToBackUp(const std::string& File);
    void deleteFileFromBackUp(const std::string& File);
    std::vector<RestorePoint*> getRPList();
    void printAll();
    void makeRP(const std::string& typeRP);
    long long getSizeRPs();
    void limiting(const IDeleteAlgorithmCreator& limiter);
};

// --- ALGORITHMS ---
class ISaveAlgorithmCreator{
public:
    std::string pathSave;
    std::string getPath();
    void setPath(std::string path);
    virtual void saveFiles(BackUp b) = 0;
};

class SeparateAlgorithm : public ISaveAlgorithmCreator{
public:
    void saveFiles(BackUp b) override;
};

class CommonAlgorithm : public ISaveAlgorithmCreator{
public:
    void saveFiles(BackUp b) override;
};

// --- SYSTEM UTIL ---
class SystemUtility {
    BackUp general;
    int IDBackUp;
public:
    SystemUtility(int ID);
    void filesToBackUp(std::vector<std::string> listOFFiles);
    void MakeRestorePoint(const std::string& typeRP);
    void saveRPs(const std::string& str);
    void print();
    void deleteFile(const std::string& name);
    void addFile(std::string name);
    void writeToFile(const std::string& name);
    IDeleteAlgorithmCreator* pickAlg(const std::string& name1);
    void controlRPs(const std::string& name1);
};


#endif /* newBackUp_hpp */
