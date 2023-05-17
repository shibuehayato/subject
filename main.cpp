#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>


const char kWindowTitle[] = "LE2B_17_シブエハヤト_タイトル";

struct Vector2
{
	float x;
	float y;
};

// 壁
Vector2 WallSt = { -300.0f,-200.0f };
Vector2 WallEn = { 300.0f,200.0f };

// 垂直ベクトル
Vector2 vertical;

Vector2 v = { WallEn.x - WallSt.x, WallEn.y - WallSt.y };

// 動く方向を表す
int MoveX = 0;
int MoveY = 0;

// 速度ベクトル
Vector2 velocity;

// 反射ベクトル
Vector2 Reflection;

// 垂直ベクトルと逆速度ベクトルの内積
float InnerProductX;
float InnerProductY;
float InnerProduct;

// 座標をずらす
Vector2 ScrCoordinates = { 600.0f,300.0f };
Vector2 ScrCoordinates2 = { 600.0f,300.0f };

// 壁の座標をずらす
Vector2 ScrWallSt;
Vector2 ScrWallEn;

// 垂直ベクトルの座標をずらす
Vector2 ScrVertical;

// 速度ベクトルの座標をずらす
Vector2 ScrVelocity;

// 反射ベクトルの座標をずらす
Vector2 ScrReflection;

// 衝突点
Vector2 CollisionP;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	vertical.x = v.y;
	vertical.y = -v.x;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_LEFT])
		{
		 	ScrCoordinates.x -= 3;
			ScrCoordinates.y -= 2;
		}
		if (keys[DIK_RIGHT])
		{
			ScrCoordinates.x += 3;
			ScrCoordinates.y += 2;
		}

		Novice::GetMousePosition(&MoveX, &MoveY);

		// 速度ベクトル
		velocity.x = -1 * (MoveX - ScrCoordinates.x);
		velocity.y = -1 * (MoveY - ScrCoordinates.y);

		ScrVelocity.x = velocity.x + ScrCoordinates.x;
		ScrVelocity.y = velocity.y + ScrCoordinates.y;

		ScrWallSt.x = WallSt.x + ScrCoordinates2.x;
		ScrWallSt.y = WallSt.y + ScrCoordinates2.y;
		ScrWallEn.x = WallEn.x + ScrCoordinates2.x;
		ScrWallEn.y = WallEn.y + ScrCoordinates2.y;

		// 正規化
		float length = sqrt(vertical.x * vertical.x + vertical.y * vertical.y);
		// 正規化後のベクトル
		float newX = vertical.x;
		float newY = vertical.y;
		if (length != 0.0f)
		{
			newX = vertical.x / length;
			newY = vertical.y / length;
		}

		ScrVertical.x = newX + ScrCoordinates.x;
		ScrVertical.y = newY + ScrCoordinates.y;

		// 垂直ベクトルと速度ベクトル内積を求める
		InnerProductX = newX * (-1 * (velocity.x));
		InnerProductY = newY * (-1 * (velocity.y));
		InnerProduct = InnerProductX + InnerProductY;

		Reflection.x = InnerProduct * 2 * newX + velocity.x;
		Reflection.y = InnerProduct * 2 * newY + velocity.y;

		ScrReflection.x = Reflection.x + ScrCoordinates.x;
		ScrReflection.y = Reflection.y + ScrCoordinates.y;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 壁
		Novice::DrawLine(ScrWallSt.x, ScrWallSt.y, ScrWallEn.x, ScrWallEn.y, RED);
		// 垂直ベクトル
		Novice::DrawLine(ScrCoordinates.x, ScrCoordinates.y, ScrVertical.x, ScrVertical.y, BLUE);
		// 進行ベクトル
		Novice::DrawLine(MoveX, MoveY, ScrCoordinates.x, ScrCoordinates.y, WHITE);
		// 速度ベクトル
		Novice::DrawLine(ScrCoordinates.x, ScrCoordinates.y, ScrVelocity.x, ScrVelocity.y, GREEN);
		// 反射ベクトル
		Novice::DrawLine(ScrCoordinates.x, ScrCoordinates.y, ScrReflection.x, ScrReflection.y, BLACK);

		///
		/// ↑描画処理ここまで
		//

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
