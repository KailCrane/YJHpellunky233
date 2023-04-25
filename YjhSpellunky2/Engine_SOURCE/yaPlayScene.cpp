#include "yaPlayScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaAnimation.h"

namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		//타일맵 추가
		//미리 저장해둔 레벨파일 로드 필요


		//Player RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Player");
			Transform* player_tr = obj->GetComponent<Transform>();

			player_tr->SetPosition(Vector3(2.0f, -0.55f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			player_tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			/*Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Circle);
			collider->SetSize(Vector2(0.1f, 0.1f));*/

			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Player", L"char_yellow.png");

			animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f);
			animator->Create(L"Move", texture, Vector2(128.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.05f);
			animator->Create(L"Attack", texture, Vector2(0.0f, 512.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f);
			//animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
			//좌측상단좌표,좌측상단으로부터 잘라낼 범위, 발끝, 잘라낸 크기 , 프레임당 지속


			animator->Play(L"Move", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>(); }
			//좌측상단좌표,좌측상단으로부터 잘라낼 범위, 발끝, 잘라낸 크기 , 프레임당 지속



#pragma region BG


		GameObject* caveBgObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		caveBgObj->SetName(L"CaveBg");
		Transform* caveBg_tr = caveBgObj->GetComponent<Transform>();
		caveBg_tr->SetPosition(Vector3(0.0f, 1.0f, 6.0f));
		caveBg_tr->SetScale(Vector3(17.0f, 7.0f, 1.0f));

		SpriteRenderer* caveBgmr = caveBgObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CaveBgMaterial");
		caveBgmr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> caveBgmesh = Resources::Find<Mesh>(L"RectMesh");
		caveBgmr->SetMesh(caveBgmesh);

		GameObject* floorObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		floorObj->SetName(L"FloorBg");
		Transform* floor_tr = floorObj->GetComponent<Transform>();
		floor_tr->SetPosition(Vector3(0.0f, 0.6f, 6.0f));
		floor_tr->SetScale(Vector3(15.0f, 5.0f, 1.0f));

		SpriteRenderer* floormr = floorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> floor_mateiral = Resources::Find<Material>(L"level1_floorMaterial");
		floormr->SetMaterial(floor_mateiral);
		std::shared_ptr<Mesh> floor_mesh = Resources::Find<Mesh>(L"RectMesh");
		floormr->SetMesh(floor_mesh);

		GameObject* entranceObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		entranceObj->SetName(L"EntranceBg");
		Transform* entrance_tr = entranceObj->GetComponent<Transform>();
		entrance_tr->SetPosition(Vector3(0.0f, -0.31f, 6.0f));
		entrance_tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

		SpriteRenderer* entrance_mr = entranceObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> entrance_mateiral = Resources::Find<Material>(L"deco_basecamp_entranceMaterial");
		entrance_mr->SetMaterial(entrance_mateiral);
		std::shared_ptr<Mesh> entrance_mesh = Resources::Find<Mesh>(L"RectMesh");
		entrance_mr->SetMesh(entrance_mesh);

		GameObject* uroborosObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		uroborosObj->SetName(L"EntranceBg");
		Transform* uroboros_tr = uroborosObj->GetComponent<Transform>();
		uroboros_tr->SetPosition(Vector3(0.0f, 1.0f, 6.0f));
		uroboros_tr->SetScale(Vector3(1.0f, 0.7f, 1.0f));

		SpriteRenderer* uroboros_mr = uroborosObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> uroboros_mateiral = Resources::Find<Material>(L"deco_basecamp_uroborosMaterial");
		uroboros_mr->SetMaterial(uroboros_mateiral);
		std::shared_ptr<Mesh> uroboros_mesh = Resources::Find<Mesh>(L"RectMesh");
		uroboros_mr->SetMesh(uroboros_mesh);


#pragma endregion

		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{

	}

	void PlayScene::OnExit()
	{

	}

}
