/* para compilar
* g++ main.cpp -o app.exe -municode -lole32 -luuid -lshlwapi -lcomdlg32 -std=c++17

*/

#include "include.h"

string getDownloadsPath() {
    PWSTR path = nullptr;
    string result;
    //path, flag, token, ppszPath
    if(SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &path))) {
        wstring ws(path);
        CoTaskMemFree(path);
        result = string(ws.begin(), ws.end());
    }
    return result;
}

string getDocumentsPath() {
    PWSTR path = nullptr;
    string result;
    if(SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path))) {
        wstring ws(path);
        CoTaskMemFree(path);
        result = string(ws.begin(), ws.end());
    }
    return result;
}

string getExtension(const string& filename) {
    size_t dot =filename.rfind('.');
    if(dot == string::npos) return "";
    string ext = filename.substr(dot);
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext;
}

void createDirIfNotExists(const string& path) {
    _mkdir(path.c_str());
}

void organizeFiles() {
    string downloads = getDownloadsPath();
    string remapy = getDocumentsPath() + "\\remapy";
    
    createDirIfNotExists(remapy);

    WIN32_FIND_DATAA findData;
    string searchPath = downloads + "\\*";
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if(hFind == INVALID_HANDLE_VALUE) {
        cout << "Err to read Downloads folder." << endl;
        return;
    }
    do {
        string name = findData.cFileName;
        if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        string ext = getExtension(name);
        if(ext.empty()) continue;

        string sourcePath = downloads + "\\" + name;
        string targetDir = remapy + "\\" + ext.substr(1); // Remove o ponto
        createDirIfNotExists(targetDir);
        string destPath = targetDir + "\\" + name;
        
        MoveFileA(sourcePath.c_str(), destPath.c_str());
        cout<<"Moved: " << name << " to " << targetDir << endl;

    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}

int main() {
    CoInitialize(NULL);

    organizeFiles();
    
    cout << "Oganization Done!" << endl;
    cin.get();

    CoUninitialize();
    return 0;
}