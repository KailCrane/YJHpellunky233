#pragma once
#include "yaScene.h"
#include "yaDisk.h"
#include "yaTime.h"
#include "yaArrow.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void DiskMove();
		void DiskTurn();

		void SnakeMove();


		void MenuUp();
		void MenuDown();

		void SpearAnim();

		void BoardMove();

		void UnfoldScroll();

		void DoorMove();



		//// 메뉴 선택 애니메이션 작동
		//void MenuSelectAnim();
		//// 메뉴 선택 애니메이션 스킵
		//void MenuSelectAnimSkip();

	private:
		

		GameObject* fadeScr;

		enum PageState
		{
			TitleScreen,
			MenuApearAnim,
			MenuSelect,
			CharSelect
		};

		PageState pageState;

		GameObject* bgObj;
		GameObject* bggalObj;
		// 돌아가는 원판
		
		GameObject* disk_L_obj;
		GameObject* disk_R_obj;

		std::vector<GameObject*> menu_select_objs;



		float turn_speed;
		float move_speed;

		bool isDiskMoveActive;
		bool isDiskMoveDone;

		bool isDiskTurnActive;
		bool isDiskTurnDone;

		bool isHeadMoveActive;
		bool isHeadMoveDone;

		Vector3 init_pos;
		Vector3 init_rot;

		float  move_done_dist;
		float head_move_dist;


		GameObject* select_bar_L;
		GameObject* select_bar_R;

		float spear_move_speed;
		bool isSpearMoveDone;
		GameObject* stone_head_obj;
		GameObject* snake_head_obj;

		enum MenuSpearState
		{
			forward,
			backward
		};

		std::vector<GameObject*> menu_select_bars;

		MenuSpearState menuSpearState;

		float spear_move_dist;

		int menu_num;
		int prev_menu_num;

		std::vector<GameObject*> char_select_objs;

		GameObject* upboard;
		GameObject* downboard;
		bool isBoardMoveActive;
		bool isBoardMoveDone;
		
		float board_move_dist;
		float board_move_speed;
		
		Vector3 init_Board_pos;


		GameObject* scroll_L;
		GameObject* scroll_R;
		
		GameObject* scrollMiddle;

		bool isScrollMoveActive;
		bool isScrollMoveDone;
		float scroll_move_dist;
		float scroll_move_speed;
		
		Vector3 init_Scroll_pos;


		Arrow* left_arrow;
		Arrow* right_arrow;

		bool isDoorMoveActive;
		bool isDoorMoveDone;

		GameObject* door_obj;
		GameObject* z_button;

		float door_move_speed;
		float door_move_dist;

		Vector3 init_door_pos;

		/*GameObject* right_arrow;
		GameObject* left_arrow;

		float arrow_move_dist;
		float arrow_move_speed;
		bool isArrowRepeat;

		float arrow_select_dist;
		float arrow_move_speed;*/
		

	};
}
