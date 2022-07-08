#include "stdafx.h"
#include "render.h"
#include "SDK.hpp"
#include <string>
#include <time.h>
#include <chrono>
using namespace std;

ImFont* gameFont = NULL;
static int page = 0;
ImColor mainColor = ImColor( 54, 54, 54, 255 );


VOID testlog( LPCSTR text, ... ) {

	va_list( args );
	va_start( args, text );

	CHAR wbuffer [ 256 ] = { };
	vsprintf_s( wbuffer, text, args );

	va_end( args );

	std::string buffer = ( "[apex-legends] " ) + std::string( wbuffer );

	OutputDebugStringA( buffer.c_str( ) );
}
POINT screenMidle{ 1920 / 2, 1080 / 2 };

//Respawn001
bool aiming = false;
int entNUm = 64;
int bone_NUM = 5;
ImColor black = ImColor(0, 0, 0, 255);
void total_cheat_loop( )
{
	ImColor cesp_color;
	RGBA* esp_color;
	Entity* local_entity = get_localEntity();
	if (!local_entity) return;
	bool tmp_thirdperson = false;
	if (local_entity->health() != 0)
	{
		if (setting::rc::norecoil == true)
		{
			Vector view_angles = local_entity->view_angles();
			Vector punchAngle = local_entity->aim_punch();

			Vector newAngle = view_angles + (old_aimpunch - punchAngle) * (setting::rc::rcs / 100.f);;

			newAngle.Normalize();

			local_entity->set_view_angles(newAngle);
			old_aimpunch = punchAngle;
		}

		if (setting::therdperson == true)
		{

			*(int*)(dwbase + OFFSET_THIRDPERSON) = 1;
			*(int*)(local_entity + OFFSET_THIRDPERSON_SV) = 1;
		}
		else if (setting::therdperson != true && tmp_thirdperson)
		{
			*(int*)(dwbase + OFFSET_THIRDPERSON) = -1;
			*(int*)(local_entity + OFFSET_THIRDPERSON_SV) = 0;
			tmp_thirdperson = false;
		}
	}

	if (setting::dummys == true)
		entNUm = 17000;
	else entNUm = 64;

	for (int i = 0; i < entNUm; i++)
	{
		uint64_t worldEnt = *(uint64_t*)(dwbase + OFFSET_EntityLIST);
		if (worldEnt == NULL) continue;

		Entity* entity = get_entiy(i);
		if (!entity) continue;
		if (entity == local_entity) continue;
		//if (entity->team_num() != 97) continue;
		//if (entity->team_num() == local_entity->team_num()) continue;
		if (entity->health() == 0) continue;

		
			if (setting::esp::glow == true)
				entity->start_glowing(1000);
			else
				entity->stop_glowing();


		//esp
		{
			Vector localOrigen = local_entity->base_position();
			int shild = entity->shield();
			int health = entity->health();
			int totallENThealth = health + shild;

			Vector entityHead = entity->bone_position(8);
			Vector entityOrigen = entity->base_position();

			Vector2D S_localOrigen;

			Vector2D S_entityHead;
			Vector2D S_entityOrigen;

			world_to_screen(localOrigen, S_localOrigen);

			world_to_screen(entityHead, S_entityHead);
			world_to_screen(entityOrigen, S_entityOrigen);

			if (S_entityHead.x == 0 || S_entityHead.y == 0) continue;
			if (S_entityOrigen.x == 0 || S_entityOrigen.y == 0) continue;

			float hight = S_entityHead.DistTo(S_entityOrigen);
			float width = hight / 2.f;
			int dist = ToMeters(localOrigen.DistTo(entityOrigen));

			if (dist >= setting::esp::distMax) continue;

			Vector2D topLeft = Vector2D(S_entityHead.x - width / 2, S_entityHead.y - hight);
			Vector2D bottomRight = Vector2D(S_entityHead.x + width / 2, S_entityHead.y);
			float boxMiddle = S_entityOrigen.x - (width / 2.0f);

			if (setting::esp::Box == true)
			{
				DrawRect(S_entityHead.x - (width / 2), S_entityHead.y, width, hight, &allcol.BoxEsp, 3);
			}

			if (setting::esp::cornerBox == true)
			{
				DrawCornerBox(S_entityHead.x - (width / 2), S_entityHead.y, width, hight, 3, &allcol.DistEsp);
			}

			if (setting::esp::Healthbare == true)
			{
				//health_bar((S_entityHead.x - (width / 2)) - 3, S_entityHead.y, 2, hight, totallENThealth);
				SeerHealth(S_entityHead.x, S_entityHead.y - 15, shild, entity->max_shield(), entity->armor_type(), health);
			}

			if (setting::esp::name == true)
			{
				//draw_text(S_entityHead.x, S_entityHead.y + 3, &allcol.NameEsp, entity->name().c_str());
			}

			if (setting::esp::dist == true)
			{
				draw_text(S_entityOrigen.x, S_entityOrigen.y, &allcol.DistEsp, E("%f."), std::to_string(dist).c_str());
			}

			if (setting::esp::line == true)
			{
				DrawLine(S_entityOrigen.x, S_entityOrigen.y, S_localOrigen.x, S_localOrigen.y, &allcol.LineEsp, 3);
			}

			if (setting::esp::skeliton == true)
			{
				HitBoxManager HitBoxs;
				world_to_screen(HitBoxPos(0, entity, entityOrigen), HitBoxs.ScreenHeadBone);
				world_to_screen(HitBoxPos(1, entity, entityOrigen), HitBoxs.ScreenNeckBone);
				world_to_screen(HitBoxPos(2, entity, entityOrigen), HitBoxs.ScreenChestBone);
				world_to_screen(HitBoxPos(3, entity, entityOrigen), HitBoxs.ScreenWaistBone);
				world_to_screen(HitBoxPos(4, entity, entityOrigen), HitBoxs.ScreenBotmBone);
				world_to_screen(HitBoxPos(6, entity, entityOrigen), HitBoxs.ScreenLeftshoulderBone);
				world_to_screen(HitBoxPos(7, entity, entityOrigen), HitBoxs.ScreenLeftelbowBone);
				world_to_screen(HitBoxPos(8, entity, entityOrigen), HitBoxs.ScreenLeftHandBone);
				world_to_screen(HitBoxPos(9, entity, entityOrigen), HitBoxs.ScreenRightshoulderBone);
				world_to_screen(HitBoxPos(10, entity, entityOrigen), HitBoxs.ScreenRightelbowBone);
				world_to_screen(HitBoxPos(11, entity, entityOrigen), HitBoxs.ScreenRightHandBone);
				world_to_screen(HitBoxPos(12, entity, entityOrigen), HitBoxs.ScreenLeftThighsBone);
				world_to_screen(HitBoxPos(13, entity, entityOrigen), HitBoxs.ScreenLeftkneesBone);
				world_to_screen(HitBoxPos(14, entity, entityOrigen), HitBoxs.ScreenLeftlegBone);
				world_to_screen(HitBoxPos(16, entity, entityOrigen), HitBoxs.ScreenRightThighsBone);
				world_to_screen(HitBoxPos(17, entity, entityOrigen), HitBoxs.ScreenRightkneesBone);
				world_to_screen(HitBoxPos(18, entity, entityOrigen), HitBoxs.ScreenRightlegBone);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenHeadBone.x, HitBoxs.ScreenHeadBone.y), ImVec2(HitBoxs.ScreenNeckBone.x, HitBoxs.ScreenNeckBone.y), black, setting::esp::skelThikness);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenNeckBone.x, HitBoxs.ScreenNeckBone.y), ImVec2(HitBoxs.ScreenLeftshoulderBone.x, HitBoxs.ScreenLeftshoulderBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenLeftshoulderBone.x, HitBoxs.ScreenLeftshoulderBone.y), ImVec2(HitBoxs.ScreenLeftelbowBone.x, HitBoxs.ScreenLeftelbowBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenLeftelbowBone.x, HitBoxs.ScreenLeftelbowBone.y), ImVec2(HitBoxs.ScreenLeftHandBone.x, HitBoxs.ScreenLeftHandBone.y), black, setting::esp::skelThikness);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenNeckBone.x, HitBoxs.ScreenNeckBone.y), ImVec2(HitBoxs.ScreenRightshoulderBone.x, HitBoxs.ScreenRightshoulderBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenRightshoulderBone.x, HitBoxs.ScreenRightshoulderBone.y), ImVec2(HitBoxs.ScreenRightelbowBone.x, HitBoxs.ScreenRightelbowBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenRightelbowBone.x, HitBoxs.ScreenRightelbowBone.y), ImVec2(HitBoxs.ScreenRightHandBone.x, HitBoxs.ScreenRightHandBone.y), black, setting::esp::skelThikness);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenNeckBone.x, HitBoxs.ScreenNeckBone.y), ImVec2(HitBoxs.ScreenChestBone.x, HitBoxs.ScreenChestBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenChestBone.x, HitBoxs.ScreenChestBone.y), ImVec2(HitBoxs.ScreenWaistBone.x, HitBoxs.ScreenWaistBone.y), black, setting::esp::skelThikness);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenWaistBone.x, HitBoxs.ScreenWaistBone.y), ImVec2(HitBoxs.ScreenLeftThighsBone.x, HitBoxs.ScreenLeftThighsBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenLeftThighsBone.x, HitBoxs.ScreenLeftThighsBone.y), ImVec2(HitBoxs.ScreenLeftkneesBone.x, HitBoxs.ScreenLeftkneesBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenLeftkneesBone.x, HitBoxs.ScreenLeftkneesBone.y), ImVec2(HitBoxs.ScreenLeftlegBone.x, HitBoxs.ScreenLeftlegBone.y), black, setting::esp::skelThikness);

				DrawLineButBetter(ImVec2(HitBoxs.ScreenWaistBone.x, HitBoxs.ScreenWaistBone.y), ImVec2(HitBoxs.ScreenRightThighsBone.x, HitBoxs.ScreenRightThighsBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenRightThighsBone.x, HitBoxs.ScreenRightThighsBone.y), ImVec2(HitBoxs.ScreenRightkneesBone.x, HitBoxs.ScreenRightkneesBone.y), black, setting::esp::skelThikness);
				DrawLineButBetter(ImVec2(HitBoxs.ScreenRightkneesBone.x, HitBoxs.ScreenRightkneesBone.y), ImVec2(HitBoxs.ScreenRightlegBone.x, HitBoxs.ScreenRightlegBone.y), black, setting::esp::skelThikness);

				DrawCircleFilled(HitBoxs.ScreenHeadBone.x, HitBoxs.ScreenHeadBone.y, 2, black);

				DrawCircleFilled(HitBoxs.ScreenLeftHandBone.x, HitBoxs.ScreenLeftHandBone.y, 2, black);

				DrawCircleFilled(HitBoxs.ScreenRightHandBone.x, HitBoxs.ScreenRightHandBone.y, 2, black);

				DrawCircleFilled(HitBoxs.ScreenLeftlegBone.x, HitBoxs.ScreenLeftlegBone.y, 2, black);

				DrawCircleFilled(HitBoxs.ScreenRightlegBone.x, HitBoxs.ScreenRightlegBone.y, 2, black);


			}
		}
	}
}

void aimbot()
{
	if (setting::aimbot::drawFOV == true)
	{
		draw_circle(screenMidle.x, screenMidle.y, setting::aimbot::aimbot_fov, &allcol.FOV, 69);
	}
	Entity* local_entity = get_localEntity();

	for (int i = 0; i < entNUm; i++)
	{		uint64_t worldEnt = *(uint64_t*)(dwbase + OFFSET_EntityLIST);
		if (worldEnt == NULL) continue;

		Entity* entity = get_entiy(i);
		if (!entity) continue;
		if (entity == local_entity) continue;
		//if (entity->team_num() != 97) continue;
		//if (entity->team_num() == local_entity->team_num()) continue;
		if (entity->health() == 0) continue;

		Vector pos = entity->bone_position(setting::aimbot::aimBone);
		Vector2D pos_screan;
		world_to_screen(pos, pos_screan);
		if (check_in_fov(pos_screan, setting::aimbot::aimbot_fov) == true)
		{
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos_screan.x, pos_screan.y), ImVec2(screenMidle.x, screenMidle.y), ImColor(255, 0, 0, 255), 2);

			if (getKeyDown(VK_RBUTTON))
				local_entity->Q_set_view_angles(CalculateBestBoneAim(local_entity,i,setting::aimbot::aimbot_fov));
		}
		else continue;
	}
}
#include <thread>
//Respawn001
__declspec(dllexport) HRESULT PresentHook(IDXGISwapChain *swapChain, UINT syncInterval, UINT flags) {
	if (!device) {
		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID *>(&device));
		device->GetImmediateContext(&immediateContext);

		ID3D11Texture2D *renderTarget = nullptr;
		swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID *>(&renderTarget));
		device->CreateRenderTargetView(renderTarget, nullptr, &renderTargetView);
		renderTarget->Release();

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc(&desc);

		oriWndProc = ( WNDPROC )SetWindowLongPtr( desc.OutputWindow, GWLP_WNDPROC, ( LONG_PTR )WndProc );

		ImGui::GetIO( ).Fonts->AddFontDefault( ); 
		ImFontConfig font_cfg;
		font_cfg.GlyphExtraSpacing.x = 1.2;
		//gameFont = ImGui::GetIO( ).Fonts->AddFontFromMemoryTTF( TTSquaresCondensedBold, 14, 14, &font_cfg );
		gameFont = ImGui::GetIO( ).Fonts->AddFontDefault( );
		ImGui::GetIO( ).Fonts->AddFontDefault( );
		ImGui_ImplDX11_Init(desc.OutputWindow, device, immediateContext);
		ImGui_ImplDX11_CreateDeviceObjects();

		ImGuiStyle* style = &ImGui::GetStyle( );

		style->WindowPadding = ImVec2( 15, 15 );
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2( 5, 5 );
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2( 12, 8 );
		style->ItemInnerSpacing = ImVec2( 8, 6 );
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors [ ImGuiCol_Text ] = ImVec4( 0.80f, 0.80f, 0.83f, 1.00f );
		style->Colors [ ImGuiCol_TextDisabled ] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
		style->Colors [ ImGuiCol_WindowBg ] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
		style->Colors [ ImGuiCol_ChildWindowBg ] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
		//style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors [ ImGuiCol_Border ] = ImVec4( 0.80f, 0.80f, 0.83f, 0.88f );
		style->Colors [ ImGuiCol_BorderShadow ] = ImVec4( 0.92f, 0.91f, 0.88f, 0.00f );
		style->Colors [ ImGuiCol_FrameBg ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_FrameBgHovered ] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
		style->Colors [ ImGuiCol_FrameBgActive ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_TitleBg ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_TitleBgCollapsed ] = ImVec4( 1.00f, 0.98f, 0.95f, 0.75f );
		style->Colors [ ImGuiCol_TitleBgActive ] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
		style->Colors [ ImGuiCol_MenuBarBg ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_ScrollbarBg ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
		style->Colors [ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
		style->Colors [ ImGuiCol_PopupBg ] = ImVec4( 0.19f, 0.18f, 0.21f, 1.00f );
		style->Colors [ ImGuiCol_CheckMark ] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
		style->Colors [ ImGuiCol_SliderGrab ] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
		style->Colors [ ImGuiCol_SliderGrabActive ] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
		style->Colors [ ImGuiCol_Button ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_ButtonHovered ] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
		style->Colors [ ImGuiCol_ButtonActive ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_Header ] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
		style->Colors [ ImGuiCol_HeaderHovered ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_HeaderActive ] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
		style->Colors [ ImGuiCol_Column ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_ColumnHovered ] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
		style->Colors [ ImGuiCol_ColumnActive ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_ResizeGrip ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
		style->Colors [ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
		style->Colors [ ImGuiCol_ResizeGripActive ] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
		style->Colors [ ImGuiCol_CloseButton ] = ImVec4( 0.40f, 0.39f, 0.38f, 0.16f );
		style->Colors [ ImGuiCol_CloseButtonHovered ] = ImVec4( 0.40f, 0.39f, 0.38f, 0.39f );
		style->Colors [ ImGuiCol_CloseButtonActive ] = ImVec4( 0.40f, 0.39f, 0.38f, 1.00f );
		style->Colors [ ImGuiCol_PlotLines ] = ImVec4( 0.40f, 0.39f, 0.38f, 0.63f );
		style->Colors [ ImGuiCol_PlotLinesHovered ] = ImVec4( 0.25f, 1.00f, 0.00f, 1.00f );
		style->Colors [ ImGuiCol_PlotHistogram ] = ImVec4( 0.40f, 0.39f, 0.38f, 0.63f );
		style->Colors [ ImGuiCol_PlotHistogramHovered ] = ImVec4( 0.25f, 1.00f, 0.00f, 1.00f );
		style->Colors [ ImGuiCol_TextSelectedBg ] = ImVec4( 0.25f, 1.00f, 0.00f, 0.43f );
		style->Colors [ ImGuiCol_ModalWindowDarkening ] = ImVec4( 1.00f, 0.98f, 0.95f, 0.73f );

	}

	immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

	auto &window = BeginScene();
	DrawOutlinedText( gameFont, ImVec2( 5, 5 ), 13.0f, ImColor( 255, 255, 255 ), false, E( "%.8f" ), ImGui::GetIO( ).Framerate );
	if (!engine::is_lobby()) total_cheat_loop();

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	if (setting::aimbot::aimbot == true)
		aimbot();
	if ( show_menu )
	{
		ImGui::SetNextWindowSize( ImVec2( 680 , 550 ) );
		ImGui::Begin( E( "APEX LEGENDS INTERNAL TEST - By: Camoryy88 " ), 0, ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse );

		ImGui::Checkbox(E("Box"), &setting::esp::Box);
		ImGui::Checkbox(E("CornerBox"), &setting::esp::cornerBox);
		ImGui::Checkbox(E("Dist"), &setting::esp::dist);
		ImGui::Checkbox(E("glow"), &setting::esp::glow);
		ImGui::Checkbox(E("Health Bar"), &setting::esp::Healthbare);
		ImGui::Checkbox(E("Line"), &setting::esp::line);
		ImGui::Checkbox(E("Skeliton"), &setting::esp::skeliton);
		//ImGui::Checkbox(E("Name"), &setting::esp::name);
	

		ImGui::Spacing();
		ImGui::SliderFloat(E("Max esp dist"), &setting::esp::distMax, 10.f, 1000.f);

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		
		//ImGui::Checkbox(E("No spread"), &setting::rc::nospread);
		ImGui::Spacing();
		ImGui::Checkbox(E("No recoil"), &setting::rc::norecoil);
		ImGui::SliderFloat(E("rsc"), &setting::rc::rcs, 1.f, 100.f);

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();


		//ImGui::Checkbox(E("triger bot"), &setting::aimbot::trigerBot);
		ImGui::Checkbox(E("aim bot"), &setting::aimbot::aimbot);
		ImGui::Checkbox(E("vis check"), &setting::aimbot::vis);
		ImGui::Checkbox(E("Draw fov"), &setting::aimbot::drawFOV);
		
		ImGui::Spacing();
		ImGui::SliderFloat(E("Aimbot fov (both)"), &setting::aimbot::aimbot_fov, 10.f, 2000.f);
		ImGui::SliderInt(E("Max dist (both)"), &setting::aimbot::distMax, 10.f, 1000.f);
		ImGui::SliderFloat(E("Aimbot smoothness"), &setting::aimbot::aimbot_smoothing, 2.f, 20.f);

		ImGui::Spacing();
		ImGui::Separator();		
		ImGui::Spacing();

		ImGui::Checkbox(E("dummy check"), &setting::dummys);
		ImGui::Checkbox(E("3D persone"), &setting::therdperson);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (engine::is_lobby() == true)
			ImGui::TextColored(ImVec4(0, 255, 255, 255), E(" [ you are in lobby ] "));
		else
			ImGui::TextColored(ImVec4(255,0,0,255), E(" [ you are in a game ] "));
		ImGui::End( );


	}
	EndScene(window);

	return PresentOriginal(swapChain, syncInterval, flags);
}

__declspec(dllexport) HRESULT ResizeHook(IDXGISwapChain *swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

ImGuiWindow &BeginScene() {
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin(E("##scene" ), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar );

	auto &io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}

VOID EndScene(ImGuiWindow &window) {
	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::Render();
}

VOID Main() {
	NtGetAsyncKeyState = ( LPFN_MBA )LI_FN( GetProcAddress )( LI_FN( GetModuleHandleA )( E( "win32u.dll" ) ), E( "NtUserGetAsyncKeyState" ) );
	//InjectMouseInput = reinterpret_cast< InjectMouseInput_t >( GetProcAddress( LoadLibraryA( "user32.dll" ), "InjectMouseInput" ) );


	IDXGISwapChain      *swapChain    = nullptr;
	ID3D11Device        *device       = nullptr;
	ID3D11DeviceContext *context      = nullptr;
	auto                 featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd           = { 0 };
	sd.BufferCount                    = 1;
	sd.BufferDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage                    = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags                          = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow                   = GetForegroundWindow();
	sd.SampleDesc.Count               = 1;
	sd.Windowed                       = TRUE;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBox(0, E( L"Failed to create D3D11 device and swap chain" ), E( L"Failure" ), MB_ICONERROR );
		return;
	}

	auto table = *reinterpret_cast<PVOID **>(swapChain);
	auto present = table[8];
	auto resize = table[13];

	context->Release();
	device->Release();
	swapChain->Release();

	MH_Initialize();

	MH_CreateHook(present, PresentHook, reinterpret_cast<PVOID *>(&PresentOriginal));
	MH_EnableHook(present);

	MH_CreateHook(resize, ResizeHook, reinterpret_cast<PVOID *>(&ResizeOriginal));
	MH_EnableHook(resize);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		Main();
	}

	return TRUE;
}


//C:\Users\Camle\OneDrive\Desktop\HyperVisor - Injector - main\HyperVisor - Injector - main\rwx1.dll

//Respawn001