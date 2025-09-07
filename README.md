There are .py version and .cpp version, you just need one of this.

The script will organize the downloads folder by default, creating a directory at ../Documents/remapy.

It will automatically recognize whether the directory exists and whether it contains a folder with the file extension to be organized.

Therefore, if there's a .pdf file in downloads and no .pdf folder in remapy, it will automatically create one and transfer the file.

The process uses some older Windows APIs, and you'll need to configure the .json file if you use VS Code. 

On UCRT64, it will be something like:

g++ main.cpp -o remapy.exe -std=c++17 -lshell32 -lole32 -luuid
