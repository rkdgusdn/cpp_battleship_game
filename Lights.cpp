#include "stdafx.h"

void MainGame()
{
	//Update
	SceneManager::GetInstance()->CheckChangeScene();
	KeyManager::GetInstance()->Update();
	Time::GetInstance()->Update();
	SceneManager::GetInstance()->GetNowScene()->SceneUpdate(Time::GetInstance()->fDeltaTime);
	CDirect3D::GetInstance()->Render();
	SceneManager::GetInstance()->GetNowScene()->SceneIO();
}

VOID Cleanup()
{
	//Remove
	SceneManager::GetInstance()->RemoveAll();
	BitmapManager::GetInstance()->RemoveAll();
	CDirect3D::GetInstance()->Cleanup();
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		KeyManager::GetInstance()->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        "D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

	//SetCursor(LoadCursor(NULL, IDC_ARROW));
	SetCursor(NULL);
	ShowCursor(FALSE);

    // Create the application's window
    HWND hWnd = CreateWindow( "D3D Tutorial", "2D Game 101",
                              WS_POPUP|WS_EX_TOPMOST, 0, 0, CDirect3D::GetInstance()->dScnX, CDirect3D::GetInstance()->dScnY,
                              NULL, NULL, wc.hInstance, NULL );
	//WS_OVERLAPPEDWINDOW
    // Initialize Direct3D
	if (SUCCEEDED(CDirect3D::GetInstance()->InitD3D(hWnd)))
	{
		//SceneManager::GetInstance()->AddScene("SceneMenu", new SceneMenu);
		//SceneManager::GetInstance()->ChangeScene("SceneMenu", true);
		SceneManager::GetInstance()->AddScene("Opening", new Opening);
		SceneManager::GetInstance()->ChangeScene("Opening", true);

		// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);


		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				MainGame();
		}

	}

    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}



