#pragma once

#include <list>
#include <string>
#include <variant>
#include <unordered_map>

#include <WorldTransform.h>

/// <summary>
/// すべてのゲームオブジェクトの基本となるクラス
/// </summary>
class GameObject {
public:

	GameObject();
	virtual ~GameObject() = default;

public:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void UpdateMatrix();

	const Mat4& GetMatTransform() const;

#pragma region Setter SRT
	void SetPosX(float x) { worldTransform_.translation_.x = x; }
	void SetPosY(float y) { worldTransform_.translation_.y = y; }
	void SetPosZ(float z) { worldTransform_.translation_.z = z; }
	void SetPos(const Vec3f& v) { worldTransform_.translation_ = v; }

	void SetRotateX(float x) { worldTransform_.rotation_.x = x; }
	void SetRotateY(float y) { worldTransform_.rotation_.y = y; }
	void SetRotateZ(float z) { worldTransform_.rotation_.z = z; }
	void SetRotate(const Vec3f& v) { worldTransform_.rotation_ = v; }

	void SetScaleX(float x) { worldTransform_.scale_.x = x; }
	void SetScaleY(float y) { worldTransform_.scale_.y = y; }
	void SetScaleZ(float z) { worldTransform_.scale_.z = z; }
	void SetScale(const Vec3f& v) { worldTransform_.scale_ = v; }
#pragma endregion

#pragma region Getter SRT
	const Vec3f GetPosition() const;
#pragma endregion


#pragma region Parent Child
	void SetParent(GameObject* parent);
	GameObject* GetParent() const;
	void AddChild(GameObject* child);
	const std::list<GameObject*>& GetChilds() const;
#pragma endregion

#pragma region Accesser Tag Name
	void SetTag(const std::string& tag);
	const std::string& GetTag() const;
	void SetName(const std::string& name);
	const std::string& GetName() const;
#pragma endregion

#pragma region JSON 保存 読み込み
	/// ---------------------------------------------------
	/// 変数一個当たりの情報
	/// ---------------------------------------------------
	struct Item final {
		using Pointer = std::variant<int*, float*, Vector3*, bool*, std::string*>;	///- ポインタ
		using Value = std::variant<int, float, Vector3, bool, std::string>;		///- 実体
		std::pair<Pointer, Value> variable;
	};

	/// ---------------------------------------------------
	/// Itemの集合
	/// ---------------------------------------------------
	struct Group final {
		/// <summary>
		/// 値のsetter
		/// </summary>
		/// <param name="key">: itemsへのkey</param>
		/// <param name="value">: itemsへセットする値</param>
		template<typename T>
		void SetPtr(const std::string& key, T* ptr);

		template<typename T>
		void SetValue(const std::string& key, const T& value);

		/// <summary>
		/// 値のGetter
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		template<typename T>
		const T& GetItem(const std::string& key);

		/// <summary>
		/// デバッグ
		/// </summary>
		void ImGuiDebug();

		/// <summary>
		/// Itemの集合
		/// </summary>
		std::unordered_map<std::string, Item> items;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="groupName"></param>
	Group& CreateGroup(const std::string& groupName);


	/// <summary>
	/// jsonに保存
	/// </summary>
	void SaveFile();

	/// <summary>
	/// jsonから読み込み
	/// </summary>
	/// <param name="key"></param>
	/// <param name="filePath"></param>
	void LoadFile(const std::string& key, const std::string& filePath);

	/// <summary>
	/// srtのグループを作る
	/// </summary>
	void CreateWorldTransformGruop();

#pragma endregion

	void ImGuiDebug();

private:
	std::string tag_;	//- グループごとの名前 : Enemyなど
	std::string name_;	//- オブジェクトごとに違う名前 : Enemy1, Enemy2など
protected:

	WorldTransform worldTransform_;

	GameObject* parent_;
	std::list<GameObject*> childs_;

	std::unordered_map<std::string, Group> groups_;

public:

	bool isActive = true;

};