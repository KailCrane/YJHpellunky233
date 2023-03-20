#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaRenderer.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"Idle");

		animator->GetCompleteEvent(L"Attack") = std::bind(&PlayerScript::AttackEnd, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		actionState = Idle;
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos.z += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos.z -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN && !isAttack)
		{
			animator->Play(L"Attack", false);
			isAttack = true;
		}

		tr->SetPosition(pos);

		//공격중일때 재공격 금지
		// Attack> Move> Idle
		AnimInput();
	}

	void PlayerScript::AnimInput()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (!isAttack)
		{
			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED
				|| Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED
				|| Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED
				|| Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				if (!isMove)
				{
					isMove = true;
					animator->Play(L"Move", true);
				}
			}
			else
			{
				isMove = false;
				animator->Play(L"Idle", false);
			}
		}
	}
	void PlayerScript::StateCheck()
	{
		actionState = Idle;
	}

	void PlayerScript::AttackEnd()
	{
		isAttack = false;
	}

	void PlayerScript::Render()
	{

	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{

	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{

	}
}