
#define PLUGIN_NAME_LONG			"scaling_flag_remover_ae"	



void ListenerThing(F4SE::MessagingInterface::Message* a_thing)
{
	if (a_thing->type == F4SE::MessagingInterface::kGameDataReady) {
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
		}
		else {
			REX::INFO("Unable to access DataHandler! Nothing will be changed...");
		}
	}
}



extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface * f4se, F4SE::PluginInfo * info)
{

	REX::INFO("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion = F4SE::PluginInfo::kVersion;
	info->name = PLUGIN_NAME_LONG;		
	info->version = 1;		


	const auto ver = f4se->RuntimeVersion();
	if (ver < F4SE::RUNTIME_1_11_221) {
		REX::INFO("unsupported runtime v{}", ver.string());
		return false;
	}


	REX::INFO("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}


extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface * a_f4se)
{
	F4SE::Init(a_f4se);

	F4SE::GetMessagingInterface()->RegisterListener(ListenerThing);

	return true;
}