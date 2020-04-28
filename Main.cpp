#include "Main.h"
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include <tchar.h>

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	LPCTSTR lpzClass = NAME;
	if (!RegMyWindowClass(hInstance, lpzClass))
		return 1;
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	int x = screen_rect.right / 2 - 150;
	int y = screen_rect.bottom / 2 - 75;
	HWND hWnd = CreateWindow(lpzClass, NAME, WS_POPUP, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (!hWnd) return 2;
	LPDIRECT3D9 pD3D;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		UnregisterClass(lpzClass, hInstance);
	}

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0) {
		pD3D->Release();
		UnregisterClass(lpzClass, hInstance);
		return 0;
	}

	ImGui_ImplDX9_Init(hWnd, g_pd3dDevice);

	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxCompotenLen = 0;
	DWORD fileSystemFlags = 0;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		ImGui_ImplDX9_NewFrame();

		DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		static bool open = true;

		if (!open) ExitProcess(0);

		ImGui::Begin(NAME_LOADER, &open, ImVec2(400, 250), 1.0f, dwFlag); 
		{
			if (ImGui::Button("Check Hwid"))
			{
				if (GetVolumeInformation(
					_T("C:\\"),
					volumeName,
					ARRAYSIZE(volumeName),
					&serialNumber,
					&maxCompotenLen,
					&fileSystemFlags,
					fileSystemName,
					ARRAYSIZE(fileSystemName)))
				{

					DWORD acceptedSerial = here you put hwid that you got with the hwid grabber;
					if (serialNumber == acceptedSerial)
					{
						cout << "You have become the long boi but how are he do it" << endl;
					}
					else
					{
						cout << "Not Registered" << endl;
						Sleep(4000);
						return 0;
					}
				}
			}
		}
		ImGui::End();

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			g_pd3dDevice->EndScene();
		}
		g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}
	ImGui_ImplDX9_Shutdown();
	if (g_pd3dDevice) g_pd3dDevice->Release();
	if (pD3D) pD3D->Release();
	UnregisterClass(NAME, hInstance);
	return 0;
}