#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		CharacterSelect,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Bg,
		Map,
		Monster,
		Player,
		UI,

		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Gravity, // ���ϸ� ���� �߷�
		Camera,
		Mesh,
		Collider,
		//Collider2,
		Animator,
		MeshRenerer,
		SpriteRenderer,
		UI,
		//FadeOut,FadeIn
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};


	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimession,
		End
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}