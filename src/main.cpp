
void ListenerThing(F4SE::MessagingInterface::Message* a_thing)
{
	
	if (a_thing->type == F4SE::MessagingInterface::kGameDataReady) {

		REX::INFO("Scaling Flag Remover loading...");

		if (auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {
			for (auto currentNPC : dataHandler->GetFormArray<RE::TESNPC>()) {
				if (currentNPC->HasPCLevelMult()) {
					currentNPC->actorData.actorBaseFlags.reset(RE::ACTOR_BASE_DATA::Flag::kPCLevelMult);
					if (currentNPC->actorData.calcLevelMin < currentNPC->actorData.calcLevelMax) {
						currentNPC->actorData.level = currentNPC->actorData.calcLevelMax;
					}
					else {
						currentNPC->actorData.level = currentNPC->actorData.calcLevelMin;
					}
					
				}
			}
			REX::INFO("Scaling Flag Remover completed loading!");
		}
		else {
			REX::INFO("Unable to access DataHandler! Nothing will be changed...");
		}
	}
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{

	F4SE::Init(a_f4se);

	F4SE::GetMessagingInterface()->RegisterListener(ListenerThing);

	return true;
}