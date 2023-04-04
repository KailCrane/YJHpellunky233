#include "yaTitleScene.h"
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
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaFadeEffect.h"
#include "yaCharPreview.h"

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte),
		pageState(TitleScreen),
		turn_speed(0.0f),
		move_speed(0.0f),
		isDiskMoveActive(false),
		isDiskMoveDone(false),
		isSpearMoveDone(true),
		menu_num(0),
		prev_menu_num(0),
		spear_move_speed(0.0f),
		spear_move_dist(0.0f),
		isScrollMoveActive(false),
		isScrollMoveDone(false),
		scroll_move_dist(0.0f),
		board_move_dist(0.0f),
		isDoorMoveDone(false),
		door_move_speed(2.0f),
		door_move_dist(2.0f)
	{


	}
	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initalize()
	{
		// Main Camera Game Object

		turn_speed = 1.0f;
		move_speed = 2.0f;
		move_done_dist = 4.0f;
		head_move_dist = 6.0f;
		spear_move_dist = 5.0f;
		spear_move_speed = 20.0f;
		scroll_move_dist = 3.0f;
		board_move_dist = 4.0f;
		board_move_speed = 8.0f;
#pragma region MainCamera

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
#pragma endregion

#pragma region  "UI Camera"


		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
#pragma endregion

#pragma region MainBg


		//MainBG
		{
			bgObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			bgObj->SetName(L"MenuTitle");
			Transform* bg_tr = bgObj->GetComponent<Transform>();
			bg_tr->SetPosition(Vector3(1.0f, 1.0f, 7.0f));
			bg_tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			SpriteRenderer* mr = bgObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MenuTitleMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion

#pragma region MenuBggal
		{
			bggalObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			bggalObj->SetName(L"MenuBgGal");
			Transform* tr = bggalObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.5f, 0.8f, 6.0f));
			tr->SetScale(Vector3(9.0f, 9.0f, 1.0f));

			SpriteRenderer* mr = bggalObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bggal_material = Resources::Find<Material>(L"MenuTitlegalMaterial");
			mr->SetMaterial(bggal_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}

#pragma endregion

		{
			GameObject* main_dirtObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			main_dirtObj->SetName(L"main_dirt");
			Transform* tr = main_dirtObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -2.0f, 1.0f));
			tr->SetScale(Vector3(10.0f, 2.0f, 1.0f));

			SpriteRenderer* mr = main_dirtObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material>  main_dir_material = Resources::Find<Material>(L"main_dirt_Material");
			mr->SetMaterial(main_dir_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(main_dirtObj);
		}

		{
			GameObject* main_doorbackObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			main_doorbackObj->SetName(L"main_doorback");
			Transform* tr = main_doorbackObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(15.5f, 10.0f, 1.0f));

			SpriteRenderer* mr = main_doorbackObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> main_doorback_material = Resources::Find<Material>(L"main_doorback_Material");
			mr->SetMaterial(main_doorback_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(main_doorbackObj);
		}

		{
			select_bar_L = object::Instantiate<GameObject>(eLayerType::UI, this);
			select_bar_L->SetName(L"selectBarL");
			Transform* tr = select_bar_L->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.5f, 2.0f, 1.0f));
			tr->SetScale(Vector3(2.4f, 0.5f, 1.0f));

			SpriteRenderer* mr = select_bar_L->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"selectBarL_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			menu_select_bars.push_back(select_bar_L);
			//selectBarLObj->Death();
		}

		{
			select_bar_R = object::Instantiate<GameObject>(eLayerType::UI, this);
			select_bar_R->SetName(L"selectBarR");
			Transform* tr = select_bar_R->GetComponent<Transform>();
			tr->SetPosition(Vector3(3.7f, 2.0f, 1.0f));
			tr->SetScale(Vector3(2.4f, 0.5f, 1.0f));

			SpriteRenderer* mr = select_bar_R->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SelectBarR_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_bars.push_back(select_bar_R);
			//selectBarRObj->Death();
		}

		{
			GameObject* optionBar_Obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			optionBar_Obj->SetName(L"optionBar_Bar");
			Transform* tr = optionBar_Obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 0.5f, 1.0f));

			SpriteRenderer* mr = optionBar_Obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"OptionBar_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_bars.push_back(optionBar_Obj);
			//optionBar_Obj->Death();
		}

		{
			GameObject* playBar_Obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			playBar_Obj->SetName(L"playBar");
			Transform* tr = playBar_Obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 2.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 0.5f, 1.0f));

			SpriteRenderer* mr = playBar_Obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayBar_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_bars.push_back(playBar_Obj);
			//playBar_Obj->Death();
		}


		{
			GameObject* playerProfileBar_Obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			playerProfileBar_Obj->SetName(L"playerProfileBar");
			Transform* tr = playerProfileBar_Obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 0.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 0.5f, 1.0f));

			SpriteRenderer* mr = playerProfileBar_Obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerProfileBar_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_bars.push_back(playerProfileBar_Obj);
			//playerProfileBar_Obj->Death();
		}

		{
			GameObject* rankBar_Obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			rankBar_Obj->SetName(L"rankBar");
			Transform* tr = rankBar_Obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -1.0f, 1.0f));
			tr->SetScale(Vector3(1.5f, 0.5f, 1.0f));

			SpriteRenderer* mr = rankBar_Obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> rankBar_material = Resources::Find<Material>(L"RankBar_Material");
			mr->SetMaterial(rankBar_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_bars.push_back(rankBar_Obj);
			//rankBar_Obj->Death();
		}

		{
			snake_head_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			snake_head_obj->SetName(L"SnakeHead");
			Transform* tr = snake_head_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = snake_head_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> snake_head_material = Resources::Find<Material>(L"SnakeHeadMaterial");
			mr->SetMaterial(snake_head_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(snake_head_obj);
		}

		{
			disk_L_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			disk_L_obj->SetName(L"Split_Disk_L");
			Transform* tr = disk_L_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(7.8f, 7.8f, 1.0f));

			SpriteRenderer* mr = disk_L_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> split_disk_L_material = Resources::Find<Material>(L"SplitDisk_L_Material");
			mr->SetMaterial(split_disk_L_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(disk_L_obj);
		}


		{
			disk_R_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			disk_R_obj->SetName(L"Splt_Disk_R");
			Transform* tr = disk_R_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(7.8f, 7.8f, 1.0f));

			SpriteRenderer* mr = disk_R_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> split_disk_R_material = Resources::Find<Material>(L"SplitDisk_R_Material");
			mr->SetMaterial(split_disk_R_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(disk_R_obj);
		}


		{
			stone_head_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			stone_head_obj->SetName(L"StoneHead");
			Transform* tr = stone_head_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(8.5f, 8.5f, 1.0f));

			SpriteRenderer* mr = stone_head_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> stone_head_material = Resources::Find<Material>(L"StoneHeadMaterial");
			mr->SetMaterial(stone_head_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(stone_head_obj);
		}

		{
			GameObject* main_doorframeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			main_doorframeObj->SetName(L"main_doorframe");
			Transform* tr = main_doorframeObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			SpriteRenderer* mr = main_doorframeObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material>  main_doorframe_material = Resources::Find<Material>(L"main_doorframe_Material");
			mr->SetMaterial(main_doorframe_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(main_doorframeObj);
		}

		{
			GameObject* mainfore2ObjL = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainfore2ObjL->SetName(L"mainfore2ObjR");
			Transform* tr = mainfore2ObjL->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(17.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = mainfore2ObjL->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mainfore2ObjL_material = Resources::Find<Material>(L"main_fore_2L_Material");
			mr->SetMaterial(mainfore2ObjL_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(mainfore2ObjL);
		}

		{
			GameObject* mainforeObjL = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainforeObjL->SetName(L"mainforeObjL");
			Transform* tr = mainforeObjL->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(15.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = mainforeObjL->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mainforeObjL_material = Resources::Find<Material>(L"main_foreL_Material");
			mr->SetMaterial(mainforeObjL_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(mainforeObjL);
		}

		{
			GameObject* mainfore2ObjR = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainfore2ObjR->SetName(L"mainfore2ObjR");
			Transform* tr = mainfore2ObjR->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(17.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = mainfore2ObjR->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mainfore2ObjR_material = Resources::Find<Material>(L"main_fore_2R_Material");
			mr->SetMaterial(mainfore2ObjR_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(mainfore2ObjR);
		}

		{
			GameObject* mainforeObjR = object::Instantiate<GameObject>(eLayerType::UI, this);
			mainforeObjR->SetName(L"mainforeObjR");
			Transform* tr = mainforeObjR->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.5f, 1.0f, 1.0f));
			tr->SetScale(Vector3(15.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = mainforeObjR->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mainforeObjR_material = Resources::Find<Material>(L"main_foreR_Material");
			mr->SetMaterial(mainforeObjR_material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			menu_select_objs.push_back(mainforeObjR);
		}

		{
			GameObject* charDoor_frameObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			charDoor_frameObj->SetName(L"CharDoorFrame");
			Transform* tr = charDoor_frameObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.7f, 2.4f, 1.0f));
			tr->SetScale(Vector3(2.4f, 2.0f, 1.0f));

			SpriteRenderer* mr = charDoor_frameObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoorFrame_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(charDoor_frameObj);
		}
#pragma region CharDoorObjs

		{
			GameObject* door_bg = object::Instantiate<GameObject>(eLayerType::UI, this);
			door_bg->SetName(L"DoorBg");
			Transform* tr = door_bg->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.7f, 2.4f, 1.0f));
			tr->SetScale(Vector3(2.6f, 2.3f, 1.0f));

			SpriteRenderer* mr = door_bg->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoorSpace_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(door_bg);
		}

		{
			door_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			door_obj->SetName(L"CharDoor");
			Transform* tr = door_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.7f, 2.4f, 1.0f));
			tr->SetScale(Vector3(2.6f, 2.3f, 1.0f));

			SpriteRenderer* mr = door_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoor_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(door_obj);
			//menu_select_objs.push_back(charDoorObj);
		}

		{
			z_button = object::Instantiate<GameObject>(eLayerType::UI, this);
			z_button->SetName(L"Z_button");
			Transform* tr = z_button->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.74f, 2.4f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = z_button->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Z_Button_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(z_button);

		}


		{
			GameObject* charDoorObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			charDoorObj->SetName(L"CharDoor");
			Transform* tr = charDoorObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-2.7f, -1.0f, 1.0f));
			tr->SetScale(Vector3(2.6f, 2.3f, 1.0f));

			SpriteRenderer* mr = charDoorObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoor_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(charDoorObj);

			//menu_select_objs.push_back(charDoorObj);
		}


		{
			GameObject* charDoorObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			charDoorObj->SetName(L"CharDoor");
			Transform* tr = charDoorObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(4.4f, 2.4f, 1.0f));
			tr->SetScale(Vector3(2.6f, 2.3f, 1.0f));

			SpriteRenderer* mr = charDoorObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoor_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(charDoorObj);

			//menu_select_objs.push_back(charDoorObj);
		}

		{
			GameObject* charDoorObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			charDoorObj->SetName(L"CharDoor");
			Transform* tr = charDoorObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(4.4f, -1.0f, 1.0f));
			tr->SetScale(Vector3(2.6f, 2.3f, 1.0f));

			SpriteRenderer* mr = charDoorObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoor_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(charDoorObj);

			//menu_select_objs.push_back(charDoorObj);
		}

#pragma endregion


		{
			GameObject* menuCharSelObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			menuCharSelObj->SetName(L"MenuCharsel");
			Transform* tr = menuCharSelObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(18.0f, 10.0f, 1.0f));

			SpriteRenderer* mr = menuCharSelObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"MenuCharsel_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			char_select_objs.push_back(menuCharSelObj);

			//menu_select_objs.push_back(charDoor_blockedObj);
		}

		
	
#pragma region Rope

		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -3.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);	
		}


		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -2.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}

		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -1.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}
		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 0.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}

		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}
		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 2.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}
		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 3.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}
		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}

		{
			GameObject* ropeMiddleObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			ropeMiddleObj->SetName(L"RopeMiddle");
			Transform* tr = ropeMiddleObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 5.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* mr = ropeMiddleObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(ropeMiddleObj);

		}
#pragma endregion

		{
			upboard = object::Instantiate<GameObject>(eLayerType::UI, this);
			upboard->SetName(L"Upboard");
			Transform* tr = upboard->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 4.8f, 1.0f));
			tr->SetScale(Vector3(11.0f, 2.0f, 1.0f));

			SpriteRenderer* mr = upboard->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Char_Select_Upboard_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(upboard);

		}


		{
			downboard = object::Instantiate<GameObject>(eLayerType::UI, this);
			downboard->SetName(L"Downboard");
			Transform* tr = downboard->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, -2.9f, 1.0f));
			tr->SetScale(Vector3(11.0f, 2.0f, 1.0f));

			SpriteRenderer* mr = downboard->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Char_Select_Downboard_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(downboard);

		}

			

		{
			scrollMiddle = object::Instantiate<GameObject>(eLayerType::UI, this);
			scrollMiddle->SetName(L"ScrollMiddle");
			Transform* tr = scrollMiddle->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 4.5f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.1f, 1.0f));

			SpriteRenderer* mr = scrollMiddle->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"ScrollMiddle_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(scrollMiddle);

		}

		{
			scroll_L = object::Instantiate<GameObject>(eLayerType::UI, this);
			scroll_L->SetName(L"Scroll_L");
			Transform* tr = scroll_L->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.5f, 4.5f, 1.0f));
			tr->SetScale(Vector3(0.5f, 1.7f, 1.0f));

			SpriteRenderer* mr = scroll_L->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Scroll_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(scroll_L);

		}

		{
			scroll_R = object::Instantiate<GameObject>(eLayerType::UI, this);
			scroll_R->SetName(L"Scroll_R");
			Transform* tr = scroll_R->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.5f, 4.5f, 1.0f));
			tr->SetScale(Vector3(0.5f, 1.7f, 1.0f));

			SpriteRenderer* mr = scroll_R->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"Scroll_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			char_select_objs.push_back(scroll_R);

		}

		{
			right_arrow = object::Instantiate<Arrow>(eLayerType::UI, this);
			right_arrow->SetName(L"RightArrow");
			Transform* tr = right_arrow->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.82f, 2.3f, 1.0f));
			tr->SetScale(Vector3(1.5f, 1.5f, 1.0f));

			right_arrow->InitPostionSet(tr->GetPosition());
			right_arrow->SetDirectRight();
			right_arrow->RepeatOn();
			right_arrow->SetMoveSpeed(1.0f);
			right_arrow->SetMoveDist(0.5f);

			SpriteRenderer* mr = right_arrow->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RightArrow_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			right_arrow->Death();
			//char_select_objs.push_back(right_arrow);

		}
		
		{
			left_arrow = object::Instantiate<Arrow>(eLayerType::UI, this);
			left_arrow->SetName(L"LeftArrow");
			Transform* tr = left_arrow->GetComponent<Transform>();
			tr->SetPosition(Vector3(-3.7f, 2.3f, 1.0f));
			tr->SetScale(Vector3(1.5f, 1.5f, 1.0f));

			left_arrow->InitPostionSet(tr->GetPosition());
			left_arrow->SetDirectLeft();
			left_arrow->RepeatOn();
			left_arrow->SetMoveSpeed(1.0f);
			left_arrow->SetMoveDist(0.5f);

			SpriteRenderer* mr = left_arrow->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"LeftArrow_Material");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			left_arrow->Death();
			//char_select_objs.push_back(right_arrow);

		}
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Player");
			Transform* player_tr = obj->GetComponent<Transform>();

			player_tr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			player_tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Circle);
			collider->SetSize(Vector2(0.1f, 0.1f));

			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Player", L"char_yellow.png");

			animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f);
			animator->Create(L"Move", texture, Vector2(128.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.05f);
			animator->Create(L"Attack", texture, Vector2(0.0f, 512.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f);
			//animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
			//좌측상단좌표,좌측상단으로부터 잘라낼 범위, 발끝, 잘라낸 크기 , 프레임당 지속


			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
		}






		//{
		//	GameObject* charDoor_blockedObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		//	charDoor_blockedObj->SetName(L"CharDoorBlocked");
		//	Transform* tr = charDoor_blockedObj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(1.5f, 1.0f, 1.0f));
		//	tr->SetScale(Vector3(2.0f, 2.0f, 5.0f));

		//	SpriteRenderer* mr = charDoor_blockedObj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Material> material = Resources::Find<Material>(L"CharDoorBlocked_Material");
		//	mr->SetMaterial(material);
		//	std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mr->SetMesh(mesh);

		//	//menu_select_objs.push_back(charDoor_blockedObj);
		//}
	

			
			




		for (int i = 0; i < menu_select_objs.size(); i++)
		{
			menu_select_objs[i]->Death();
		}
		for (int i = 0; i < menu_select_bars.size(); i++)
		{
			menu_select_bars[i]->Death();
		}
		for (int i = 0; i < char_select_objs.size(); i++)
		{
			char_select_objs[i]->Death();
		}
		


#pragma region CharacterSheet

		//GameObject* outfit1 = object::Instantiate<GameObject>(eLayerType::None, this);
		//outfit1->SetName(L"Outfit1");
		//Transform* outfit1_tr = outfit1->GetComponent<Transform>();

		//outfit1_tr->SetPosition(Vector3(2.0f, -0.55f, 5.0f));
		////tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		//outfit1_tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//
		//Animator* animator = outfit1->AddComponent<Animator>();
		//std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"outfit1", L"char_yellow.png");

		//animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f);
		//animator->Create(L"Move", texture, Vector2(128.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.05f);
		////animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
		////좌측상단좌표,좌측상단으로부터 잘라낼 범위, 발끝, 잘라낸 크기 , 프레임당 지속

		//animator->Play(L"Idle", true);

		//SpriteRenderer* mr = outfit1->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Material> outfit1mat = Resources::Find<Material>(L"PlayerMaterial");
		//mr->SetMaterial(outfit1mat);
		//std::shared_ptr<Mesh> outfit1mesh = Resources::Find<Mesh>(L"RectMesh");
		//mr->SetMesh(outfit1mesh);
#pragma endregion 


#pragma region  FadeScreen
		{

			fadeScr = object::Instantiate<GameObject>(eLayerType::UI, this);
			fadeScr->SetName(L"FadeScreen");
			Transform* fadeScr_tr = fadeScr->GetComponent<Transform>();
			fadeScr_tr->SetPosition(Vector3(-2.5f, 0.8f, 1.0f));
			fadeScr_tr->SetScale(Vector3(9.0f, 9.0f, 1.0f));

			SpriteRenderer* fade_mr = fadeScr->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> fade_mateiral = Resources::Find<Material>(L"FadeMaterial");
			fade_mr->SetMaterial(fade_mateiral);
			std::shared_ptr<Mesh> fade_mesh = Resources::Find<Mesh>(L"RectMesh");
			fade_mr->SetMesh(fade_mesh);
		}
#pragma endregion





		//{
			//Player* monster = object::Instantiate<Player>(eLayerType::Monster);
			//monster->SetName(L"MONSTER");
			//Transform* mtr = monster->GetComponent<Transform>();
			//mtr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
			////tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//mtr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			//Collider2D* collider = monster->AddComponent<Collider2D>();
			//collider->SetType(eColliderType::Circle);
			////collider->SetSize(Vector2(1.5f, 1.5f));
		/*	SpriteRenderer* mr = monster->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			//object::DontDestroyOnLoad(monster);
		}*/
		////SMILE RECT CHild
		//GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
		//child->SetName(L"SMILE");
		//Transform* childTr = child->GetComponent<Transform>();
		//childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//childTr->SetParent(tr);
	/*	MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(mesh);*/
		//// HPBAR
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Player);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTR = hpBar->GetComponent<Transform>();
		//hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		//hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));
	/*	SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		hpBar->AddComponent(hpsr);
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);*/


		//stone_disk_obj->Death();
		/*side_frame->Death();
		snake_statue->Death();*/

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::CharacterSelect);
		}

#pragma region InputCtrl



		if (Input::GetKeyDown(eKeyCode::ENTER) || Input::GetKeyDown(eKeyCode::Z))
		{
			if (pageState == PageState(TitleScreen))
			{
				for (int i = 0; i < 10; i++)
				{
					menu_select_objs[i]->Death();
				}

				bgObj->Death();
				bggalObj->Death();

				for (int i = 0; i < menu_select_objs.size(); i++)
				{
					menu_select_objs[i]->Alive();
				}

				isDiskTurnActive = true;

				pageState = PageState(MenuApearAnim);
			}
			if (pageState == PageState(MenuSelect))
			{
				if (isSpearMoveDone && !isBoardMoveDone)
				{
					if (menu_num == 0)
					{
						for (int i = 0; i < menu_select_objs.size(); i++)
						{
							menu_select_objs[i]->Death();
						}
						for (int i = 0; i < menu_select_bars.size(); i++)
						{
							menu_select_bars[i]->Death();
						}
						for (int i = 0; i < char_select_objs.size(); i++)
						{
							char_select_objs[i]->Alive();
						}
						isBoardMoveActive = true;
						isBoardMoveDone = false;
						init_Board_pos = upboard->GetComponent<Transform>()->GetPosition();
						Transform* up_tr = upboard->GetComponent<Transform>();
						Transform* down_tr = downboard->GetComponent<Transform>();
						up_tr->SetPosition(Vector3( up_tr->GetPosition().x, up_tr->GetPosition().y + board_move_dist, up_tr->GetPosition().z));
						down_tr->SetPosition(Vector3(down_tr->GetPosition().x, down_tr->GetPosition().y - board_move_dist, down_tr->GetPosition().z));
						
						Transform* scroll_L_tr = scroll_L->GetComponent<Transform>();
						Transform* scroll_R_tr = scroll_R->GetComponent<Transform>();
						Transform* scroll_middle_tr = scrollMiddle->GetComponent<Transform>();

						scroll_L_tr->SetPosition(Vector3(scroll_L_tr->GetPosition().x, scroll_L_tr->GetPosition().y + board_move_dist, scroll_L_tr->GetPosition().z));
						scroll_R_tr->SetPosition(Vector3(scroll_R_tr->GetPosition().x, scroll_R_tr->GetPosition().y + board_move_dist, scroll_R_tr->GetPosition().z));
						scroll_middle_tr->SetPosition(Vector3(scroll_middle_tr->GetPosition().x, scroll_middle_tr->GetPosition().y+ board_move_dist, scroll_middle_tr->GetPosition().z));


					/*	isScrollMoveActive = true;
						isScrollMoveDone = false;
						init_Scroll_pos = scroll_L->GetComponent<Transform>()->GetPosition();*/
					}
				}
			}


			//페이드 아웃해주고 메인 메뉴 선택을 해주는 UI로
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{

		}

		if (pageState == PageState(MenuSelect))
		{

			if (isSpearMoveDone)
			{
				if (Input::GetKeyDown(eKeyCode::UP))
				{
					MenuUp();
				}

				if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					MenuDown();
				}
				

			}
			else
			{
				SpearAnim();
			}

			if (isScrollMoveDone)
			{
				if (!isDoorMoveDone)
				{
					if (Input::GetKeyDown(eKeyCode::Z))
					{
						isDoorMoveActive = true;
						isDoorMoveDone = false;
						init_door_pos = door_obj->GetComponent<Transform>()->GetPosition();
					}
				}

				/*if (Input::GetKeyDown(eKeyCode::LEFT))
				{

				}

				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{

				}*/
			}
		}

#pragma endregion
		if (isDiskTurnActive)
		{
			DiskTurn();
		}
		if (isDiskMoveActive)
		{
			DiskMove();
		}
		if (isHeadMoveActive)
		{
			SnakeMove();
		}
		if (isBoardMoveActive)
		{
			BoardMove();

		}
		if (isScrollMoveActive)
		{
			UnfoldScroll();
		}

		if (isDoorMoveActive)
		{
			DoorMove();
		}

		/*if (isArrowMoveActive)
		{
			ArrowMove();
		}*/

		Scene::Update();
	}


	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{

	}
	void TitleScene::OnExit()
	{

	}
	void TitleScene::DiskTurn()
	{
		Vector3 left_curr_rot = disk_L_obj->GetComponent<Transform>()->GetRotation();
		Vector3 left_change_rot = Vector3(left_curr_rot.x, left_curr_rot.y, left_curr_rot.z += turn_speed * Time::DeltaTime());
		disk_L_obj->GetComponent<Transform>()->SetRotation(left_change_rot);

		Vector3 right_curr_rot = disk_R_obj->GetComponent<Transform>()->GetRotation();
		Vector3 right_change_rot = Vector3(right_curr_rot.x, right_curr_rot.y, right_curr_rot.z += turn_speed * Time::DeltaTime());
		disk_R_obj->GetComponent<Transform>()->SetRotation(right_change_rot);

		Vector3 head_curr_rot = stone_head_obj->GetComponent<Transform>()->GetRotation();
		Vector3 head_change_rot = Vector3(head_curr_rot.x, head_curr_rot.y, head_curr_rot.z -= turn_speed * Time::DeltaTime());
		stone_head_obj->GetComponent<Transform>()->SetRotation(head_change_rot);


		if (left_curr_rot.z >= 3.15f)
		{
			init_pos = disk_L_obj->GetComponent<Transform>()->GetPosition();
			isDiskTurnDone = true;
			isDiskTurnActive = false;
			isDiskMoveDone = false;
			isDiskMoveActive = true;
		}
	}

	void TitleScene::DiskMove()
	{

		Vector3 left_curr_pos = disk_L_obj->GetComponent<Transform>()->GetPosition();
		disk_L_obj->GetComponent<Transform>()->SetPosition(Vector3(left_curr_pos.x + move_speed * Time::DeltaTime(),
			left_curr_pos.y,
			left_curr_pos.z));

		Vector3 right_curr_pos = disk_R_obj->GetComponent<Transform>()->GetPosition();
		disk_R_obj->GetComponent<Transform>()->SetPosition(Vector3(right_curr_pos.x - move_speed * Time::DeltaTime(),
			right_curr_pos.y,
			right_curr_pos.z));
		if ((left_curr_pos.x - init_pos.x) >= move_done_dist)
		{
			isDiskMoveActive = false;
			isDiskMoveDone = true;
			isHeadMoveActive = true;
			isHeadMoveDone = false;
			init_pos = stone_head_obj->GetComponent<Transform>()->GetPosition();
		}
	}

	void TitleScene::SnakeMove()
	{
		Vector3 stone_head_curr_pos = stone_head_obj->GetComponent<Transform>()->GetPosition();
		stone_head_obj->GetComponent<Transform>()->SetPosition(Vector3(stone_head_curr_pos.x,
			stone_head_curr_pos.y - move_speed * Time::DeltaTime(),
			stone_head_curr_pos.z));

		Vector3 snake_head_curr_pos = snake_head_obj->GetComponent<Transform>()->GetPosition();
		snake_head_obj->GetComponent<Transform>()->SetPosition(Vector3(stone_head_curr_pos.x,
			stone_head_curr_pos.y - move_speed * Time::DeltaTime(),
			stone_head_curr_pos.z));
		if ((init_pos.y - stone_head_curr_pos.y) >= head_move_dist)
		{
			isHeadMoveActive = false;
			isHeadMoveDone = true;
			for (int i = 0; i < menu_select_bars.size(); i++)
			{
				menu_select_bars[i]->Alive();
			}
			pageState = PageState(MenuSelect);
		}
	}

	void TitleScene::MenuUp()
	{
		if (menu_num <= 0)
		{
			return;
		}
		prev_menu_num = menu_num;
		menu_num--;
		isSpearMoveDone = false;

		menuSpearState = MenuSpearState(backward);
	}

	void TitleScene::MenuDown()
	{
		if (menu_num >= 3)
		{
			return;
		}
		//prev_menu_num = menu_num;
		menu_num++;
		isSpearMoveDone = false;
		menuSpearState = MenuSpearState(backward);
	}

	void TitleScene::SpearAnim()
	{
		Transform* tr_L = select_bar_L->GetComponent<Transform>();
		Transform* tr_R = select_bar_R->GetComponent<Transform>();

		Vector3 left_curr_pos = tr_L->GetPosition();
		Vector3 right_curr_pos = tr_R->GetPosition();

		//들어가고 있을때
		if (menuSpearState == MenuSpearState(backward))
		{
			tr_L->SetPosition(Vector3(left_curr_pos.x - spear_move_speed * Time::DeltaTime(), left_curr_pos.y, left_curr_pos.z));
			tr_R->SetPosition(Vector3(right_curr_pos.x + spear_move_speed * Time::DeltaTime(), right_curr_pos.y, right_curr_pos.z));
			if (init_pos.x - left_curr_pos.x >= spear_move_dist)
			{
				menuSpearState = MenuSpearState(forward);
			}
		}
		// 나올때
		if (menuSpearState == MenuSpearState(forward))
		{
			float fixed_y_pos;
			switch (menu_num)
			{
			case 0:
				fixed_y_pos = 2.0f;
				break;
			case 1:
				fixed_y_pos = 1.0f;
				break;
			case 2:
				fixed_y_pos = 0.0f;
				break;
			case 3:
				fixed_y_pos = -1.0f;
				break;
			}

			tr_L->SetPosition(Vector3(left_curr_pos.x + spear_move_speed * Time::DeltaTime(), fixed_y_pos, left_curr_pos.z));
			tr_R->SetPosition(Vector3(right_curr_pos.x - spear_move_speed * Time::DeltaTime(), fixed_y_pos, right_curr_pos.z));

			if (left_curr_pos.x >= -1.5)
			{
				isSpearMoveDone = true;
			}
		}
	}

	void TitleScene::BoardMove()
	{
		Vector3 curr_upboard_pos = upboard->GetComponent<Transform>()->GetPosition();
		upboard->GetComponent<Transform>()->SetPosition(Vector3(curr_upboard_pos.x,
			curr_upboard_pos.y - board_move_speed * Time::DeltaTime(),
			curr_upboard_pos.z));

		Vector3 curr_scroll_L_pos = scroll_L->GetComponent<Transform>()->GetPosition();
		scroll_L->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_L_pos.x,
			curr_scroll_L_pos.y - board_move_speed * Time::DeltaTime(),
			curr_scroll_L_pos.z));
		Vector3 curr_scroll_R_pos = scroll_R->GetComponent<Transform>()->GetPosition();
		scroll_R->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_R_pos.x,
			curr_scroll_R_pos.y - board_move_speed * Time::DeltaTime(),
			curr_scroll_R_pos.z));
		Vector3 curr_scroll_middle_pos = scrollMiddle->GetComponent<Transform>()->GetPosition();
		scrollMiddle->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_middle_pos.x,
			curr_scroll_middle_pos.y - board_move_speed * Time::DeltaTime(),
			curr_scroll_middle_pos.z));

		Vector3 curr_downboard_pos = downboard->GetComponent<Transform>()->GetPosition();
		downboard->GetComponent<Transform>()->SetPosition(Vector3(curr_downboard_pos.x,
			curr_downboard_pos.y + board_move_speed * Time::DeltaTime(),
			curr_downboard_pos.z));


		if (init_Board_pos.y >= curr_upboard_pos.y)
		{
			isBoardMoveActive = false;
			isBoardMoveDone = true;
			isScrollMoveActive = true;
			isScrollMoveDone = false;

			init_Scroll_pos = scroll_L->GetComponent<Transform>()->GetPosition();
		}

	}

	

	void TitleScene::UnfoldScroll()
	{
	
		Vector3 scroll_L_curr_pos = scroll_L->GetComponent<Transform>()->GetPosition();
		scroll_L->GetComponent<Transform>()->SetPosition(Vector3(scroll_L_curr_pos.x - 8 * Time::DeltaTime(),
			scroll_L_curr_pos.y,
			scroll_L_curr_pos.z));

		Vector3 scrollMiddl_curr_scale = scrollMiddle->GetComponent<Transform>()->GetScale();
		scrollMiddle->GetComponent<Transform>()->SetScale(Vector3(scrollMiddl_curr_scale.x + 16 * Time::DeltaTime(),
			scrollMiddl_curr_scale.y,
			scrollMiddl_curr_scale.z));

		Vector3 scroll_R_curr_pos = scroll_R->GetComponent<Transform>()->GetPosition();
		scroll_R->GetComponent<Transform>()->SetPosition(Vector3(scroll_R_curr_pos.x + 8 * Time::DeltaTime(),
			scroll_R_curr_pos.y,
			scroll_R_curr_pos.z));

		if (init_Scroll_pos.x + scroll_L_curr_pos.x <= -scroll_move_dist)
		{
			isScrollMoveActive = false;
			isScrollMoveDone = true;
		}
	}
	void TitleScene::DoorMove()
	{
		Vector3 door_curr_pos = door_obj->GetComponent<Transform>()->GetPosition();
		door_obj->GetComponent<Transform>()->SetPosition(Vector3(door_curr_pos.x ,
																door_curr_pos.y + door_move_speed * Time::DeltaTime(),
																door_curr_pos.z));

		Vector3 z_button_pos = z_button->GetComponent<Transform>()->GetPosition();
		z_button->GetComponent<Transform>()->SetPosition(Vector3(z_button_pos.x,
																z_button_pos.y + door_move_speed * Time::DeltaTime(),
																z_button_pos.z));
		if (init_door_pos.y - door_curr_pos.y <= - door_move_dist)
		{
			isDoorMoveActive = false;           
			isDoorMoveDone = true;
			

			left_arrow->Alive();
			left_arrow->MoveActive();
			right_arrow->Alive();
			right_arrow->MoveActive();
		}
	}
}