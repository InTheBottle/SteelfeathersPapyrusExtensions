#include "Papyrus/Papyrus.h"

static void MessageEventCallback(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		SECTION_SEPARATOR;
		logger::info("Finished startup tasks, enjoy your game!"sv);
		break;
	default:
		break;
	}
}

SKSEPluginInfo(
	.Version = Plugin::VERSION,
	.Name = Plugin::NAME,
	.Author = "Steelfeathers"sv,
	.RuntimeCompatibility = SKSE::VersionIndependence::AddressLibrary
)

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	SECTION_SEPARATOR;
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
	logger::info("Author: Steelfeathers"sv);
	logger::info("Runtime: {} ({})"sv, REL::Module::get().version().string(), REL::Module::IsVR() ? "VR"sv : REL::Module::IsAE() ? "AE"sv : "SE"sv);
	SECTION_SEPARATOR;

	logger::info("Performing startup tasks..."sv);

	// if (!Settings::INI::Read()) {
	//	SKSE::stl::report_and_fail("Failed to load INI settings. Check the log for more information."sv);
	//}
	SECTION_SEPARATOR;

	SKSE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);
	SECTION_SEPARATOR;

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(&MessageEventCallback);

	return true;
}

void GetFormByID() {
	auto* sweetroll = RE::TESForm::LookupByID(0x64B3D);
	logger::info("Form Name: {}", sweetroll->GetName());
}
