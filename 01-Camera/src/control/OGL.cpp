
// Header Files
#include <windows.h>
#include "OGL.h"

// Standard Header files
#include <stdio.h> // for file io functions
#include <stdlib.h> // for exit()

// OpenGL  libraries
#pragma comment(lib,"GLEW32.lib")
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"Sphere.lib")

// OpenGL HEADER FILES
#include <GL/glew.h> // This Must Be Before Including <GL/gl.h>
#include <GL/gl.h>

#include "../view/renderer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Renderer r;
Logger ogl("OGL.log");

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declarations
	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");
	BOOL bDone = FALSE;
	int iRetVal = 0;
	RECT rc;

	ogl.write( "Log file is successfully created.");

	// initialization of WNDCLASSEX structure
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register WNDCLASSEX 
	RegisterClassEx(&wndclass);

	// Get size of Work Area of the window 
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

	// create the window
	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		TEXT("OGL WINDOW"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(rc.right - WINWIDTH) / 2,
		(rc.bottom - WINHEIGHT) / 2,
		WINWIDTH,
		WINHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	r.ghwnd = hwnd;

	// Initialize
	iRetVal = r.initialize();

	if (iRetVal == -1)
	{
		ogl.write(  "Choose Pixel Format Failed\n");
		uninitialize();
	}
	else if (iRetVal == -2)
	{
		ogl.write(  "Set Pixel Format Failed\n");
		uninitialize();
	}
	else if (iRetVal == -3)
	{
		ogl.write(  "Create OpenGL Context Failed\n");
		uninitialize();
	}
	else if (iRetVal == -4)
	{
		ogl.write(  "Making Opengl Context As Current Context Failed\n");
		uninitialize();
	}
	else if (iRetVal == -5)
	{
		ogl.write(  "Create OpenGL glewInit Failed \n");
		uninitialize();
	}
	else
	{
		ogl.write(  "Initialize Success..!\n");
	}


	// show window
	ShowWindow(hwnd, iCmdShow);

	// Foregrounding and focusing the window
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Game Loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (r.gbActiveWindow == TRUE)
			{
				// Render the scene
				r.render();

				// Update the scene
				r.update();

			}
		}
	}


	return((int)msg.wParam);
}



// Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Function declarations
	void ToggleFullscreen(void);
	void resize(int, int);
	void uninitialize(void);

	// code
	switch (iMsg)
	{


	case WM_SETFOCUS:
		r.gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		r.gbActiveWindow = FALSE;
		break;

	case WM_ERASEBKGND:
		break;

	case WM_CHAR:
		
		switch (wParam)
		{
		case 'F':
		case 'f':
			ToggleFullscreen();
			break;


		case 'g':
			r.day = (r.day + 6) % 360;
			break;
		case	'G':
			r.day = (r.day - 6) % 360;
			break;
		case 'Y':
			r.year = (r.year + 3) % 360;
			break;
		case 'y':
			r.year = (r.year - 3) % 360;
			break;
		case 'M':
			r.moonx = (r.moonx + 3) % 360;
			break;
		case 'm':
			r.moonx = (r.moonx - 3) % 360;
			break;

		
		default:
			break;
		}
		break;

	case WM_KEYDOWN:
		r.camera.update(hwnd, iMsg, wParam, lParam);
		switch (wParam)
		{
		case 27:
			DestroyWindow(hwnd);
			break;

		default:
			break;
		}
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_MOUSEMOVE:
		r.camera.update(hwnd, iMsg, wParam, lParam);
	break;
	case WM_DESTROY:
		uninitialize();
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void resize(int width, int height)
{
	// code
	if (height == 0)
		height = 1;  //to avoid divide by 0 in future code
	glViewport(0, 0, width, height);

	r.perspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}



void uninitialize(void)
{
	// Function declarations
	void ToggleFullscreen(void);
	r.s.uninitialize();  //renderer->sphere->uninitialize

	// Code
	if (r.gbFullscreen)
	{
		ToggleFullscreen();
	}

	if (wglGetCurrentContext() == r.ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (r.ghrc)
	{
		wglDeleteContext(r.ghrc);
		r.ghrc = NULL;
	}

	if (r.ghdc)
	{
		ReleaseDC(r.ghwnd, r.ghdc);
		r.ghdc = NULL;
	}

	if (r.ghwnd)
	{
		DestroyWindow(r.ghwnd);
		r.ghwnd = NULL;
	}

}


void ToggleFullscreen(void)
{
	// Variable declarations
	static DWORD dwStyle;
	static WINDOWPLACEMENT wp;
	MONITORINFO mi;


	// Code
	wp.length = sizeof(WINDOWPLACEMENT);

	if (r.gbFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(r.ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(r.ghwnd, &wp) && GetMonitorInfo(MonitorFromWindow(r.ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(r.ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(r.ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			ShowCursor(FALSE);
			r.gbFullscreen = TRUE;
		}
	}
	else
	{
		SetWindowLong(r.ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(r.ghwnd, &wp);
		SetWindowPos(r.ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		r.gbFullscreen = FALSE;
	}
}
