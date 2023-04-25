#pragma once

#include "yaGameObject.h"

namespace ya
{
	class CharPreview : public GameObject
	{
	public:
		CharPreview();
		virtual ~CharPreview();
		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void ChangeMove();
		void SetDirectionLeft() { direction = Direction(Left); }
		void SetDirectionRight() { direction = Direction(Right); }

		void MoveToHall();


	private:

		enum Direction
		{
			None,
			Left,
			Right
		};
		Direction direction;

		float move_speed;
		float move_dist;

		Vector3 left_start_pos;
		Vector3 right_start_pos;
		Vector3 objective_pos;

		bool isChangeMoveActive;
		bool isMoveCoplete;

		enum CurrPlayingAnim
		{
			Idle,
			Move,
			Jump,
			Rope
		};
		CurrPlayingAnim curr_playingAnim;
	};

}
