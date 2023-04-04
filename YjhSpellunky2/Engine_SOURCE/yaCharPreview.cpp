#include "yaCharPreview.h"
#include "yaAnimator.h"
#include "yaTime.h"
namespace ya
{
	CharPreview::CharPreview()
		:isChangeMoveActive(false)
	{
	}
	CharPreview::~CharPreview()
	{
	}
	void CharPreview::Initalize()
	{
		Animator* animator = this->GetComponent<Animator>();
		
		animator->Play(L"Move",true);

		GameObject::Initalize();
	}
	void CharPreview::Update()
	{
		GameObject::Update();
		if(isChangeMoveActive)
		{
			ChangeMove();
		}
	}
	void CharPreview::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void CharPreview::Render()
	{
		GameObject::Render();
	}


	void CharPreview::ChangeMove()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 curr_pos = tr->GetPosition();
		Vector3 fixed_pos;

		Animator* animator = this->GetComponent<Animator>();
		
		if (curr_playingAnim != Move)
		{
			animator->Play(L"Move",true);
		}
		curr_playingAnim = Move;
		switch (direction)
		{
		case ya::CharPreview::None:
			return;
			break;
		case ya::CharPreview::Left:

			fixed_pos = Vector3(curr_pos.x - move_speed * Time::DeltaTime(), curr_pos.y , curr_pos.z);
			tr->SetPosition(fixed_pos);
			if (tr->GetPosition().x <= objective_pos.x)
			{
				animator->Play(L"Idle", false);
				isChangeMoveActive = false;
			}
			break;
		case ya::CharPreview::Right:
			fixed_pos = Vector3(curr_pos.x + move_speed * Time::DeltaTime(), curr_pos.y, curr_pos.z);
			tr->SetPosition(fixed_pos);
			if (tr->GetPosition().x >= objective_pos.x)
			{
				animator->Play(L"Idle", false);
				curr_playingAnim = Idle;
				isChangeMoveActive = false;
			}
			break;
		}
	}
}