#include <Windows.h>
#include "resource1.h"
#include <stdio.h>


void echo(char *str)
{
	MessageBox(NULL,str,TEXT("ÌבÊ¾"),MB_OK);
}

int CALLBACK DialogProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn;       
	char szFile[260];       				  
	HANDLE hf;  
	DWORD fileSize, readSize;
	char *buffer;

	switch (Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
	{
					   switch (wParam)
					   {
					   case ID_NEW:
						   SetDlgItemText(hwnd, IDC_TEXT, "");
						 
						   break;
					   case ID_OPEN:
						 

						  
						   ZeroMemory(&ofn, sizeof(ofn));
						   ofn.lStructSize = sizeof(ofn);
						   ofn.hwndOwner = hwnd;
						   ofn.lpstrFile = szFile;
						  
						   ofn.lpstrFile[0] = '\0';
						   ofn.nMaxFile = sizeof(szFile);
						   ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
						   ofn.nFilterIndex = 1;
						   ofn.lpstrFileTitle = NULL;
						   ofn.nMaxFileTitle = 0;
						   ofn.lpstrInitialDir = NULL;
						   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

						   

						   if (GetOpenFileName(&ofn) == TRUE)
						   {
							  // echo(szFile);
						   
							   hf = CreateFile(ofn.lpstrFile,
							   GENERIC_READ,
							   0,
							   (LPSECURITY_ATTRIBUTES)NULL,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   (HANDLE)NULL);
						   }
						   if (hf == INVALID_HANDLE_VALUE)
						   {
							   echo("open file of no idea\n");
						   }
						   else
						   {
							   fileSize = GetFileSize(hf, NULL); 
							   buffer = (char *)malloc(fileSize + 1);
							   buffer[fileSize] = '\0'; 

							   
							   ReadFile(
								   hf,         
								   buffer,    
								   fileSize,   
								   NULL        
								   );

							   
							   SetDlgItemText(hwnd, IDC_TEXT, buffer);

							   CloseHandle(hf); 
							   free(buffer);   
						   }
						   break;
					   case ID_EXIT:
						   EndDialog(hwnd,0);
						   break;
					   }
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	
	LoadLibrary("RICHED20.DLL");
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DialogProc);
}