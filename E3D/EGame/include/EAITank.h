#pragma once

#include "ETank.h"

namespace E3D
{
	class EAITank : public ETank
	{
	public:
		virtual ~EAITank() {}
		virtual void onHited();
		virtual void fire();
		virtual void update();
	protected:
		void updateAI();

	protected:
		friend class EGameManager;
		friend class EPlayerController;
		EAITank(const EString &name, const EString &meshName, EGameManager *gameMgr);
	};
}
