#pragma once

#include "yaGameObject.h"

namespace ya

{
	class BoardNScroll : public GameObject
	{
	public:

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetObj(GameObject* _board,
					GameObject* _left_Scroll,
					GameObject* _right_Scroll)
					{board = _board;
					left_Scroll = _left_Scroll;
					right_Scroll = _right_Scroll;}

		void Active() { isActive = true; }
		void Complete() { isComplete = true; }



	private:
		void Move();



		GameObject* board;
		GameObject* left_Scroll;
		GameObject* right_Scroll;

		bool isActive;
		bool isComplete;

		float down_move_dist;
		float side_move_dist;

		float board_move_speed;

		Vector3 init_board_pos;
		Vector3 init_left_scroll_pos;
		Vector3 init_right_scroll_pos;
 
		enum ActPhase
		{
			DownMove,
			SideMove
		};
		ActPhase actphase;

	};
}

