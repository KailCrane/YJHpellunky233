#include "yaBoardNScroll.h"
#include "yaTime.h"
namespace ya
{
	void BoardNScroll::Initialize()
	{
		GameObject::Initialize();
	}
	void BoardNScroll::Update()
	{
		GameObject::Update();
	}
	void BoardNScroll::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}
	void BoardNScroll::Render()
	{
		GameObject::Render();
	}

	void BoardNScroll::Move()
	{
		if (actphase = DownMove)
		{
			Vector3 curr_board_pos = board->GetComponent<Transform>()->GetPosition();
			Vector3 fixed_board_pos = Vector3(curr_board_pos.x, curr_board_pos.y - board_move_speed * Time::DeltaTime(), curr_board_pos.z);
			board->GetComponent<Transform>()->SetPosition(fixed_board_pos);

			Vector3 curr_left_scroll_pos = board->GetComponent<Transform>()->GetPosition();
			Vector3 fixed_left_scroll_pos = Vector3(curr_left_scroll_pos.x, curr_left_scroll_pos.y - board_move_speed * Time::DeltaTime(), curr_left_scroll_pos.z);
			board->GetComponent<Transform>()->SetPosition(fixed_board_pos);

			Vector3 curr_right_scroll_pos = board->GetComponent<Transform>()->GetPosition();
			Vector3 fixed_right_scroll_pos = Vector3(curr_right_scroll_pos.x, curr_right_scroll_pos.y - board_move_speed * Time::DeltaTime(), curr_right_scroll_pos.z);
			board->GetComponent<Transform>()->SetPosition(fixed_right_scroll_pos);

			if (init_board_pos.y - curr_board_pos.y < down_move_dist)
			{
				actphase = SideMove;
			}
		}
		if (actphase = SideMove)
		{

		}
	}




}