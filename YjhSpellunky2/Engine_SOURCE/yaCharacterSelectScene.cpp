#include "yaCharacterSelectScene.h"
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
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaCollisionManager.h"


namespace ya
{
	CharacterSelectScene::CharacterSelectScene()
		: Scene(eSceneType::CharacterSelect)
	{
	
	}
	CharacterSelectScene::~CharacterSelectScene()
	{
		

	}
	void CharacterSelectScene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		GameObject* chrselBgObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		chrselBgObj->SetName(L"ChrSelBg");
		Transform* chrselBg_tr = chrselBgObj->GetComponent<Transform>();
		chrselBg_tr->SetPosition(Vector3(1.2f, 1.0f, 6.0f));
		chrselBg_tr->SetScale(Vector3(11.0f, 7.0f, 1.0f));

		SpriteRenderer* mr = chrselBgObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ChrSelMaterial");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		//1.왼쪽 오른쪽 입력시 캐릭터 변경 기능
		//-> 캐릭터 풀과 넘버링
		//-> 내가 현재 선택한 캐릭터
		//-> 선택시 무엇을 전달 해야할까? 캐릭터 넘버링? 넘버링으로 넘겨줄까? 다음 씬에 넘겨줘야하는데
		//2. 

		// 후에 전체대신 캐릭터를 분리 셀렉이 확인될시 정해진 행동 재생
		// 다시한번 fade in out 넣을것
		// 공동 마을 씬을 스킵 할지 고민할것
		// 텍스트박스 기능이 필요


		Scene::Initalize();
	}
	void CharacterSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();

		//정말로 이 캐릭을 선택하지에 대한 마지막 선택이 아닐시

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{

		}
		//정말로 이 캐릭을 선택할지에 대한 선택일시
		if (Input::GetKeyDown(eKeyCode::X))
		{

		}
		if (Input::GetKeyDown(eKeyCode::Z))
		{

		}

		Scene::Update();

	}
	void CharacterSelectScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void CharacterSelectScene::Render()
	{
		Scene::Render();
	}
	void CharacterSelectScene::OnEnter()
	{
	}
	void CharacterSelectScene::OnExit()
	{
	}
}