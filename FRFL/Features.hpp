#include "Include.h"
#include "sdk.hpp"
#include "settings.hpp"
#include "Color.h"
BaseM* player;

namespace Fetures {
	int* iShotsFired;
	Vec3* aimRecoilPunch;
	Vec3 oPunch{ 0,0,0 };
	Vec3* viewAngles;
	float rcs_amount = 1.f;
	void Fov() {
		if (settings::features::fov) {                                       
			if (player->GetLocalPlayer() != NULL) {
				*(int*)(player->GetLocalPlayer() + m_iDefaultFOV) = 160;
			}
			
		}
		
	}
	void Zoom() {
		if (settings::features::zoom)
		{
			if (player->GetLocalPlayer() != NULL)
			{

				if (GetAsyncKeyState(VK_RBUTTON)) {
					*(int*)(player->GetLocalPlayer() + m_iDefaultFOV) = 10;
				}
				else
				{
					*(int*)(player->GetLocalPlayer() + m_iDefaultFOV) = 160;
				}
			}
			
		}
	
		
		
	}
	void Bhop() {
		if (settings::features::bhop) {
			if (player->GetLocalPlayer() != NULL) {
				if (GetAsyncKeyState(VK_SPACE) && player->GetFlag() & (1 << 0)) {
					*(DWORD*)(player->Base() + dwForceJump) = 6;
				}
			}

				
			
		}

		

		
	}
	void AntiFlash() {
		if (player->GetLocalPlayer() != NULL)
		{
			int flash = 0;
			if (settings::features::antiflash) {
				flash = *(int*)(player->GetLocalPlayer() + m_flFlashDuration);
				if (flash > 0)
				{
					*(int*)(player->GetLocalPlayer() + m_flFlashDuration) = 0;
				}
			}
		}
			
		
		
	}
	void ESP() {
		if (player->GetLocalPlayer() != NULL)
		{
			for (int x = 1; x < 32; x++) {
				uintptr_t Entity = *(uintptr_t*)(player->Base() + dwEntityList + x * 0x10);
				if (Entity != NULL) {
					int GlowObjectManager = *(int*)(player->Base() + dwGlowObjectManager);

					int localTeam = *(int*)(player->GetLocalPlayer() + m_iTeamNum);

					int entityTeam = *(int*)(Entity + m_iTeamNum);
					int glowIndex = *(int*)(Entity + m_iGlowIndex);

					if (entityTeam != localTeam) {

						*(float*)(GlowObjectManager + glowIndex * 0x38 + 0x8) = Colors::glow[0];
						*(float*)(GlowObjectManager + glowIndex * 0x38 + 0xC) = Colors::glow[1];
						*(float*)(GlowObjectManager + glowIndex * 0x38 + 0x10) = Colors::glow[2];
						*(float*)(GlowObjectManager + glowIndex * 0x38 + 0x14) = 1.f; // A  
					}
					*(bool*)(GlowObjectManager + glowIndex * 0x38 + 0x28) = true;
				}
			}
		}
		


	}
	void NoRecoil() {
		if (player->GetLocalPlayer() != NULL)
		{
			iShotsFired = (int*)(player->GetLocalPlayer() + m_iShotsFired);
			aimRecoilPunch = (Vec3*)(player->GetLocalPlayer() + m_aimPunchAngle);
			viewAngles = (Vec3*)(*(uintptr_t*)(player->Engine() + dwClientState) + dwClientState_ViewAngles);

			Vec3 punchAngle = *aimRecoilPunch * (rcs_amount * 2);
			if (*iShotsFired > 1 && GetAsyncKeyState(VK_LBUTTON)) {
				Vec3 newAngle = *viewAngles + oPunch - punchAngle;
				newAngle.normalize();

				*viewAngles = newAngle;
			}
			oPunch = punchAngle;
		}
		
	}

}


namespace Start {
	void Start() {
		while (true) {
			Fetures::ESP();
			Fetures::AntiFlash();
			Fetures::Fov();
			Fetures::Zoom();
			Fetures::Bhop();
			Fetures::NoRecoil();
		}
		

	}
}