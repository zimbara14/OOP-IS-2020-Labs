//
//  newBackUp.cpp
//  newBackUp
//
//  Created by Sara Nikolić
//

#include "newBackUp.hpp"
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <list>


// --- FILE ---
File::File(){}

File::File(std::string name){
    std::ifstream in(name, std::ifstream::ate);
    if(!in) throw std::runtime_error("Error! Could not find the file within the function File::File().\n");
    this->Path = name.substr(0, (name.find_last_of('/')) + 1);
    this->Name = name.substr(name.find_last_of('/') + 1);
    this->timeF = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() - std::chrono::minutes(5)); // supposing the File is the one only connected to the BackUP, not the real life !!! everything's a lie. u r in the matrix.
    this->sizeFile = in.tellg();
}

File::~File(){}

std::string File::getNameF(){
    return this->Name;
}

std::string File::getPathF(){
    return this->Path;
}

long long File::getSizeF(){
    return sizeFile;
}
 
long long File::getSizeFile(){
    std::string extension = getNameF().substr(getNameF().find_last_of('.'));
    std::string name;
    if(getNameF().find('_') != std::string::npos) name = getNameF().substr(0, getNameF().find('_'));
    else name = getNameF().substr(0, getNameF().find_last_of('.'));;
    std::ifstream in(getPathF()+name+extension, std::ifstream::ate);
    if(!in) throw std::runtime_error("Error! Could not find the file within the function File::getSizeF().\n");
    return in.tellg();
}

std::string File::getCharTimeF(){
    return ctime(&timeF);
}

time_t File::getTimeF(){
    return this->timeF;
}

void File::setSizeF(long long size){
    this->sizeFile = size;
}

void File::setNameF(std::string n){
    this->Name = n;
}

void File::setTimeF(time_t time){
    this->timeF = time;
}

void File::setPathF(std::string s){
    this->Path = s;
}

// --- RESTORE POINT ---
int RestorePoint::ID = 0;

RestorePoint::~RestorePoint() = default;

void RestorePoint::deleteFile(const std::string& file){
    filesRestorePoints.erase(std::remove_if(filesRestorePoints.begin(), filesRestorePoints.end(), [&file](File& ele)->bool
    {
        return ele.getNameF().substr(0, ele.getNameF().find_last_of('_')) == file;
    }), filesRestorePoints.end());
}

bool RestorePoint::findFile(const std::string& nameF) const{
    for(auto i : filesRestorePoints){
        if(i.getNameF().substr(0, i.getNameF().find_first_of('_')) == nameF) return true;
    }
    return false;
}

RestorePoint* RestorePoint::getParentRP() const{
    return parentRP;
}

File RestorePoint::getFile(const std::string& nameF) const{
    for(auto i : filesRestorePoints){
        if(i.getNameF().substr(0, i.getNameF().find_first_of('_')) == nameF) return i;
    }
    throw std::runtime_error("Error! Could not get the file within the function RestorePoint::getFile().\n");
}

std::string RestorePoint::getNameRP() const{
    return nameRP;
}

std::vector<File> RestorePoint::getFilesRP() const{
    return this->filesRestorePoints;
}

int RestorePoint::getIDRP(){
    return thisID;
}

void RestorePoint::printAll(){
    for(auto& i : filesRestorePoints) std::cout << i.getNameF() << " ";
    std::cout << std::endl;
}

long long RestorePoint::getSizeRP(){
    long long size = 0;
    for(auto f : filesRestorePoints) size += f.getSizeF();
    return size;
}

time_t RestorePoint::getTimeRP(){
    return timeRP;
}

Full::Full(RestorePoint* par){
    this->parentRP = par;
    this->nameRP = "full";
    this->thisID = ++ID;
    auto newTime = std::chrono::minutes(thisID);
    this->timeRP = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + newTime);
}

void Full::addFileRP(File f){
    if(f.getNameF().find_first_of('_') == std::string::npos){
        std::string newName = f.getNameF().substr(0, f.getNameF().find_last_of('.')) + "_" + std::to_string(thisID);
        std::string extension = f.getNameF().substr(f.getNameF().find_last_of('.'));
        f.setNameF(newName + extension);
    } else{
        std::string newName = f.getNameF().substr(0, f.getNameF().find_first_of('_') + 1) + std::to_string(thisID);
        std::string extension = f.getNameF().substr(f.getNameF().find_last_of('.'));
        f.setNameF(newName + extension);
    }
    filesRestorePoints.push_back(f);
}

long long Full::setSize(const RestorePoint *rp, const std::string name){
    for(auto f : filesRestorePoints) if(f.getNameF().substr(0, f.getNameF().find_first_of('_')) == name) return f.getSizeF();
    return 0;
}

Incremental::Incremental(RestorePoint* par){
    this->parentRP = par;
    this->nameRP = "delta";
    this->thisID = ++ID;
    auto newTime = std::chrono::minutes(thisID);
    this->timeRP = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + newTime);
}

void Incremental::addFileRP(File f){
    if(f.getNameF().find_first_of('_') == std::string::npos){
        std::string newName = f.getNameF().substr(0, f.getNameF().find_last_of('.')) + "_" + std::to_string(thisID);
        std::string extension = f.getNameF().substr(f.getNameF().find_last_of('.'));
        f.setNameF(newName + extension);
    } else{
        std::string newName = f.getNameF().substr(0, f.getNameF().find_first_of('_') + 1) +  std::to_string(thisID);
        std::string extension = f.getNameF().substr(f.getNameF().find_last_of('.'));
        f.setNameF(newName + extension);
    }
    std::string newName = f.getNameF().substr(0, f.getNameF().find_last_of('_'));
    long long size = setSize(parentRP, newName);
    f.setSizeF(abs(f.getSizeFile() - size)); // this is so-called delta
    if(f.getSizeF() != 0) filesRestorePoints.push_back(f);
}

long long Incremental::setSize(const RestorePoint* rp, const std::string name){
    if(!rp) return 0;
    if(!rp->findFile(name)) return setSize(rp->getParentRP(), name);
    if(rp->getNameRP() == "full") return rp->getFile(name).getSizeF();
    else return rp->getFile(name).getSizeFile() + setSize(rp->getParentRP(), name);
}

// --- BACKUP ---
BackUp::BackUp(){
    this->creationTimeBU = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void BackUp::addFileToBackUp(const std::string& name){
    std::ifstream infile(name);
    if(!infile.good()) throw std::runtime_error("Error! File does not exist within the function BackUp::addFileToBackUp().\n");
    File f(name);
    filesForBackup.push_back(f);
}

void BackUp::deleteFileFromBackUp(const std::string &File){
    bool flag = false;
    for(auto f : filesForBackup){
        std::string newName = f.getNameF().substr(0, f.getNameF().find('.'));
        if(newName == File) {flag = true; break;}
    }
    if(!flag) throw std::runtime_error("Error! File with this name does not exist within the function BackUp::deleteFileFromBackUp().\n");
    filesForBackup.erase(std::remove_if(filesForBackup.begin(), filesForBackup.end(), [&File](class File& ele)->bool
    {
        return ele.getNameF().substr(0, ele.getNameF().find('.')) == File;
    }), filesForBackup.end());
    for(auto f : restorePointList) f->deleteFile(File);
}

void BackUp::makeRP(const std::string& typeRP){
    RestorePoint* last;
    if(restorePointList.empty()) last = nullptr;
    else last = restorePointList.back();
    if(typeRP == "full"){
        RestorePoint* rp = new Full(last);
        for(File& f : filesForBackup){
            rp->addFileRP(f);
        }
        restorePointList.push_back(rp);
    } else if(typeRP == "delta"){
        RestorePoint* rp = new Incremental(last);
        for(File& f : filesForBackup){
            rp->addFileRP(f);
        }
        restorePointList.push_back(rp);
    } else {
        throw std::runtime_error("Error! Cannot create Restore point of the given type within the function BackUp::makeRP().\n");
    }
}

std::vector<RestorePoint*> BackUp::getRPList(){
    return restorePointList;
}

void BackUp::printAll(){
    std::cout << "Content of the BackUp:\n";
    for(auto& i : restorePointList) {std::cout << i->getNameRP() << " restore point with the ID " << i->getIDRP() << " contains:\n"; i->printAll(); }
    std::cout << std::endl;
}

long long BackUp::getSizeRPs(){
    long long size = 0;
    for(auto rp : restorePointList) size += rp->getSizeRP();
    return size;
}

void BackUp::limiting(const IDeleteAlgorithmCreator& limiter) {
    int deletion = limiter.limit(restorePointList);
    std::vector<File> temp;
    bool flag = false;
    for(int i = 0; i < deletion; ++i){
        temp = restorePointList[i]->getFilesRP();
        if(restorePointList[i]->getNameRP() == "full"){
//            if(flag)
            for(auto f : temp){
                std::string newName = f.getNameF().substr(0, f.getNameF().find('_'));
                this->deleteFileFromBackUp(newName);
            }
        }
        
    }
    restorePointList.erase(restorePointList.begin(), restorePointList.begin() + deletion);
}

// --- ALGORITHMS SAVE ---
std::string ISaveAlgorithmCreator::getPath(){
    return this->pathSave;
}
void ISaveAlgorithmCreator::setPath(std::string path){
    this->pathSave = path;
}

void SeparateAlgorithm::saveFiles(BackUp b){
    bool flag;
    for(auto it : b.getRPList()){
        std::string nameRP = it->getNameRP();
        flag = false;
        for(auto f : it->getFilesRP()){
            std::string newFileName = f.getNameF().substr(0, f.getNameF().find_first_of('.'));
            std::ofstream log(pathSave + "FolderOfSeparateFiles2/" + newFileName + ".log");
            if(!log.good()) throw std::runtime_error("Stupid!\n");
            if(!flag) log << "Restore point of type: " << it->getNameRP() << " with the ID: " << it->getIDRP() << ".\n";
            flag = true;
            log << "Filename: " << f.getNameF() << std::endl;
            log << "Size of the file: " << f.getSizeF() << std::endl;
            log << "Creation date and time: " << f.getCharTimeF() << std::endl;
            log.close();
        }
    }
    std::cout << "Files saved into separate files " << pathSave << "FolderOfSeparateFiles2/ within the function SeparateAlgorithm::saveFiles().\n";
}

void CommonAlgorithm::saveFiles(BackUp b){
    std::ofstream log(pathSave + "new_archive2.log");
    for(auto it : b.getRPList()){
        std::string nameRP = it->getNameRP();
        for(auto f : it->getFilesRP()){
            log << "Folder is contained within restore point of type: " << it->getNameRP() << " with the ID: " << it->getIDRP() << ".\n";
            log << "Filename: " << f.getNameF() << std::endl;
            log << "Size of the file: " << f.getSizeF() << std::endl;
            log << "Creation date and time: " << f.getCharTimeF() << std::endl;
        }
    }
    log.close();
    std::cout << "Files saved into an archive " << pathSave << "new_archive2.log within the function CommonAlgorithm::saveFiles().\n";
}

// --- ALGORITHMS DELETE ---

IDeleteAlgorithmCreator IDeleteAlgorithmCreator::or_(IDeleteAlgorithmCreator& other) {
    auto new_limiter = [&](const std::vector<RestorePoint*>& rps) -> int {return std::max(limit(rps), other.limit(rps));};
    return IDeleteAlgorithmCreator(new_limiter);
}

IDeleteAlgorithmCreator IDeleteAlgorithmCreator::and_(IDeleteAlgorithmCreator& other) {
    auto new_limiter = [&](const std::vector<RestorePoint*>& rps) -> int {return std::min(limit(rps), other.limit(rps));};
    return IDeleteAlgorithmCreator(new_limiter);
}

int IDeleteAlgorithmCreator::limit(const std::vector<RestorePoint*>& rps) const {
    return limit_(rps);
}

long long SizeAlg::size_limiter(long long lim, const std::vector<RestorePoint*>& restorePoints) {
    long long max_num = 0;
    long long i = restorePoints.size() - 1;
    for(; i >=0; i--) {
        max_num += restorePoints[i]->getSizeRP();
        if(max_num > lim) break;
    }
    return i + 1;
}

int SizeAlg::limit(const std::vector<RestorePoint*>& rps) const {
    return (int)size_limiter(sizeLim_, rps);
}

int DateAlg::date_limiter(time_t lim, const std::vector<RestorePoint*>& restorePoints) {
    int answ = 0;
    for( const auto & rp : restorePoints) {
        if(rp->getTimeRP() < lim) // make this func
            answ++;
    }
    return answ;
}

int DateAlg::limit(const std::vector<RestorePoint*>& rps) const {
    return date_limiter(timeLim_, rps);
}

int LengthAlg::length_limiter(size_t lim, const std::vector<RestorePoint*>& restorePoints) {
    return restorePoints.size() <= lim ? 0 : restorePoints.size() - lim;
}

int LengthAlg::limit(const std::vector<RestorePoint*>& rps) const {
    return length_limiter(lengthLim_, rps);
}

// --- SYSTEM UTIL ---
SystemUtility::SystemUtility(int ID){
    this->IDBackUp = ID;
}

void SystemUtility::filesToBackUp(std::vector<std::string> listOFFiles){
    for(auto& i : listOFFiles){
        general.addFileToBackUp(i);
    }
    std::cout << "Created backup of file(s) within function SystemUtility::filesToBackUp().\n";
}

void SystemUtility::MakeRestorePoint(const std::string& typeRP){
    general.makeRP(typeRP);
}

void SystemUtility::saveRPs(const std::string& str){
    if(str == "archive"){
        ISaveAlgorithmCreator* alg = new CommonAlgorithm();
        alg->setPath("/Users/zimbara/Desktop/");
        alg->saveFiles(general);
    } else if(str == "folders"){
        ISaveAlgorithmCreator* alg = new SeparateAlgorithm();
        alg->setPath("/Users/zimbara/Desktop/");
        alg->saveFiles(general);
    } else throw std::runtime_error("Error! Algorithm does not yet exist within the function SystemUtility::saveRPs().\n");
}

void SystemUtility::print(){
    general.printAll();
}

void SystemUtility::deleteFile(const std::string &name){
    general.deleteFileFromBackUp(name);
}

void SystemUtility::addFile(std::string name){
    general.addFileToBackUp(name);
}

void SystemUtility::writeToFile(const std::string &name){
    std::ofstream in(name, std::ios_base::app);
    if(!in.good()) throw std::runtime_error("Error! Could not open the file within the function SystemUtility::writeToFile().\n");
    in << "Just a string.\n";
    in.close();
}

IDeleteAlgorithmCreator* SystemUtility::pickAlg(const std::string &name1){
    IDeleteAlgorithmCreator* ret;
    if(name1 == "size"){
        long long size;
        std::cout << "Please input the control quantity.\n";
        std::cin >> size;
        ret = new LengthAlg(size);
    } else if(name1 == "length"){
        size_t size;
        std::cout << "Please input the control size.\n";
        std::cin >> size;
        ret = new SizeAlg(size);
    } else if(name1 == "date"){
        auto t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + std::chrono::minutes(3)); // changing the time limit
        ret = new DateAlg(t_c);
    } else ret = nullptr;
    if (ret) return ret;
    else throw std::runtime_error("Error! \n");
}

void SystemUtility::controlRPs(const std::string& name1) {
    IDeleteAlgorithmCreator* res;
    if(name1 != "hybrid"){
        res = pickAlg(name1);
        if(!res) throw std::runtime_error("Error! Algorithm does not yet exist within the function SystemUtility::controlRPs().\n");
    } else {
        int n;
        std::cout << "How many algorithms would you like to use?\n";
        std::cin >> n;
        std::string alg;
        IDeleteAlgorithmCreator* another, another2;
        if(n == 0) throw std::runtime_error("Error! NaN within the function SystemUtility::controlRPs().\n");
        while(n--){
            std::cout << "Input the name of the algorithm:\n";
            std::cin >> alg;
            another = pickAlg(alg);
            another2 = another->and_(*another); // or or_
        }
        res = &another2;
    }
    if(!res) throw std::runtime_error("Error! Algorithm does not yet exist within the function SystemUtility::controlRPs().\n");
    general.limiting(*res);
}
