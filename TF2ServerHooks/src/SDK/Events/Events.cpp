#include "Events.h"

void CEventListener::Initialize()
{
	std::vector<const char*> vEvents = { 
		
	};

	for (auto szEvent : vEvents)
	{
		I::GameEventManager->AddListener(this, szEvent, false);

		if (!I::GameEventManager->FindListener(this, szEvent))
			SDK::Output("Amalgam", std::format("Failed to add listener: {}", szEvent).c_str(), { 255, 150, 175, 255 });
	}
}

void CEventListener::Unload()
{
	I::GameEventManager->RemoveListener(this);
}

void CEventListener::FireGameEvent(IGameEvent* pEvent)
{
	if (!pEvent)
		return;

	//auto pLocal = H::Entities.GetLocal();
	//auto uHash = FNV1A::Hash32(pEvent->GetName());

	return;
}