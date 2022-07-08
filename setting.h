#pragma once


namespace setting
{
	bool hide = true;

	namespace esp
	{
		float distMax = 600;
		bool espSettings = false;
		bool cornerBox = false;
		bool Box = false;
		bool line = false;
		bool Healthbare = false;
		bool name = false;
		bool dist = false;
		bool skeliton = false;

		bool glow = false;
		bool iteamGlow = false;

		int skelThikness = 1;
	}
	
	namespace aimbot
	{
		bool aimAssist = false;
		
		bool aimbot = false;
		int aimBone = 5;
		int distMax = 500.f;
		bool drawFOV = true;
		bool vis = true;
		float aimbot_fov = 90.f;
		float aimbot_smoothing = 150.f;
		int r = 50;

		bool trigerBot = false;
		bool aimbot_smoothing_c = false;
	}

	namespace rc
	{
		bool norecoil = false;
		float rcs = 69.f;

		bool nospread = false;

	}



	namespace misc
	{
		bool third_person = false;
		bool skinChanger_wp = false;
	}

	bool skinchanger = false;
	bool therdperson = false;
	int wp_skin_id = 10;
	int entNum = 64;
	bool dummys = false;
}
