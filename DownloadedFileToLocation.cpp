#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include <filesystem>
#include <ShlObj_core.h> 
#include <string>  
using namespace std;


int main()
{
    char username [UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName((TCHAR*)username, &username_len);

    PWSTR downloadsPath;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &downloadsPath);
    if (SUCCEEDED(result))
    {
		wcout << "Download path: " << downloadsPath << endl;
	}
    else
    {
		wcout << "Error: " << result << endl;
	} 
    wstring downloadsFolderPath(downloadsPath);
    //free the memory allocated by the downloadsPath
    CoTaskMemFree(static_cast<void*>(downloadsPath));

    //get the path from the user
    wcout << L"Enter the full path to the PDF folder where you want them to be saved: " << endl;
    wstring pdfFolderPath;
    getline(wcin,pdfFolderPath);

    wstring pdfExtension = L".pdf";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((downloadsFolderPath + L"\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error finding files in the downloads folder." << endl;
        return 1;
    }

    do {
        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            wstring fileName = findFileData.cFileName;
            size_t pos = fileName.find_last_of(L".");
            if (pos != wstring::npos) {
                wstring fileExtension = fileName.substr(pos);
                if (fileExtension == pdfExtension) {
                    wstring sourcePath = downloadsFolderPath + L"\\" + fileName;
                    wstring destinationPath = pdfFolderPath + L"\\" + fileName;

                    if (MoveFile(sourcePath.c_str(), destinationPath.c_str())) {
                        wcout << L"Moved " << fileName << L" to " << pdfFolderPath << endl;
                    }
                    else {
                        wcerr << L"Error moving " << fileName << L": " << GetLastError() << endl;
                    }
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return 0;
    

}



