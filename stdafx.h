#pragma once

#include <stdio.h>
#include <windows.h>

#include "skCrypter.h"
#include "signature.h"
#include "lazy_importer.h"
#include "setting.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>

#include <MinHook.h>
#pragma comment(lib, "minhook.lib")

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

ImGuiWindow &BeginScene();
VOID EndScene(ImGuiWindow &window);


#define E skCrypt
typedef int ( WINAPI* LPFN_MBA )( DWORD );
static LPFN_MBA NtGetAsyncKeyState;

bool show_menu = true;
WNDPROC oriWndProc = NULL;
extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void unLoad()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
bool isAiming = 0;
LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( NtGetAsyncKeyState( VK_INSERT ) & 1 )
		show_menu = !show_menu;
	if ( NtGetAsyncKeyState( VK_DELETE ) )
	{
		unLoad();
	}
	if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) && show_menu == true )
	{
		return true;
	}
	return CallWindowProc( oriWndProc, hWnd, msg, wParam, lParam );
}

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

HRESULT( *PresentOriginal )( IDXGISwapChain* swapChain, UINT syncInterval, UINT flags ) = nullptr;
HRESULT( *ResizeOriginal )( IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags ) = nullptr;