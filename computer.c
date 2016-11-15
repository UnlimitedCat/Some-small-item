
#include <windows.h>
#include "resource.h"
#include <stdlib.h>

double num_a, num_b, rlt;
char op;
float word = 0;

BOOL CALLBACK Dlgproc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	char num[30],org[20];
	char text[30], edit[30];
	char tem[30];
	
	switch (Message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
	break;
	case WM_COMMAND:
		if (wParam>=1001&&wParam<=1010||wParam==1016)
	{
			if (word==1)
			{
				SetDlgItemText(hwnd, IDC_EDIT1, " ");
				word = 0;
			}
			memset(num, 0, sizeof(num));
			GetDlgItemText(hwnd, wParam, num, sizeof(num));
			GetDlgItemText(hwnd, IDC_EDIT1, edit, sizeof(edit));
			sprintf(edit, "%s%s",edit, num);
 			SetDlgItemText(hwnd, IDC_EDIT1, edit);
	}
		if (wParam>=1011&&wParam<=1014)
	{
			GetDlgItemText(hwnd,IDC_EDIT1,tem,sizeof(tem));
			num_a = atof(tem);
			GetDlgItemText(hwnd, wParam, org, sizeof(org));
			op = org[0];
			SetDlgItemText(hwnd, IDC_EDIT1, " ");	
	}
		if (wParam == 1017)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, " ");
		}
		switch (wParam)
		{
		case IDOK:
			GetDlgItemText(hwnd, IDC_EDIT1, tem, sizeof(tem));
			num_b = atof(tem);
			
			switch (op)
			{
			case '+':
				rlt = num_a + num_b;
				break;
			case '-':
				rlt = num_a - num_b;
				break;
			case '*':
				rlt = num_a*num_b;
				break;
			case '/':
				rlt = num_a / num_b;
				break;

			}
			
			sprintf(text, "%f", rlt);
			SetDlgItemText(hwnd, IDC_EDIT1, text);
			word = 1;
			break;
		
		default:

			break;

		}
	
		break;
	}
	return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN), NULL, Dlgproc);
	return 0;
}