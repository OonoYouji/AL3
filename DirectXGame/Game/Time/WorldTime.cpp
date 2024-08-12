#include <WorldTime.h>

#include  <ImGuiManager.h>

void WorldTime::ImGuiDebug() {
#ifdef _DEBUG

	if (!ImGui::Begin("world time setting")) {
		ImGui::End();
		return;
	}

	ImGui::Spacing();
	ImGui::Text("delta time  : %f", deltaTime_);

	ImGui::Spacing();
	ImGui::Text("attenuation : %f", attenuation_);

	ImGui::Spacing();
	ImGui::Text("frame time  : %f", FrameTime());

	ImGui::End();

#endif // _DEBUG
}
