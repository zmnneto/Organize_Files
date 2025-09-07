#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <shlobj.h> // Para SHGetKnownFolderPath
#include <knownfolders.h> // Para FOLDERID_Downloads e FOLDERID_Documents
#include <direct.h> // Para _mkdir
#include <algorithm> // Para transform

using namespace std;