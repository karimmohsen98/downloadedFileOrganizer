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

    wcout << L"Enter the full path to the PDF folder where you want them to be saved: " << endl;
    wstring pdfFolderPath;
    std::getline(wcin,pdfFolderPath);


}


