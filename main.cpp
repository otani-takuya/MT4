#include <Novice.h>
#include <imgui.h>

const char kWindowTitle[] = "円の追従補間";

struct Vector2 {
	float x;
	float y;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Novice::Initialize(kWindowTitle, 1280, 720);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// =========================
	// 円の設定
	// =========================

	// 赤い円（マウス）
	Vector2 target = { 640.0f, 360.0f };

	// 緑の円（追従する円）
	Vector2 pos = { 640.0f, 360.0f };

	const float radiusA = 12.0f;
	const float radiusB = 20.0f;

	// 追従速度
	float speed = 5.0f;

	// 60fps固定
	const float deltaTime = 1.0f / 60.0f;

	while (Novice::ProcessMessage() == 0) {

		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// ========================================
		// 1. マウス座標を取得
		// ========================================
		int mouseX = 0;
		int mouseY = 0;

		Novice::GetMousePosition(&mouseX, &mouseY);

		target.x = static_cast<float>(mouseX);
		target.y = static_cast<float>(mouseY);

		// ========================================
		// 2. 円Bを円Aへ追従させる
		// pos += (target - pos) * (speed * deltaTime)
		// ========================================
		pos.x += (target.x - pos.x) * (speed * deltaTime);
		pos.y += (target.y - pos.y) * (speed * deltaTime);

		// ========================================
		// 3. ImGui
		// ========================================
		ImGui::Begin("Interpolation Controller");

		ImGui::Text("Target Mouse Position (Red Circle)");
		ImGui::Text("X : %.1f", target.x);
		ImGui::Text("Y : %.1f", target.y);

		ImGui::Separator();

		ImGui::Text("Follow Circle Position");
		ImGui::Text("X : %.1f", pos.x);
		ImGui::Text("Y : %.1f", pos.y);

		ImGui::Separator();

		ImGui::SliderFloat("Speed", &speed, 0.1f, 20.0f);

		ImGui::End();

		// ========================================
		// 4. 描画
		// ========================================

		// 円A：赤色
		Novice::DrawEllipse(
			static_cast<int>(target.x),
			static_cast<int>(target.y),
			static_cast<int>(radiusA),
			static_cast<int>(radiusA),
			0.0f,
			RED,
			kFillModeSolid
		);

		// 円B：緑色
		Novice::DrawEllipse(
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			static_cast<int>(radiusB),
			static_cast<int>(radiusB),
			0.0f,
			GREEN,
			kFillModeSolid
		);

		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();

	return 0;
}