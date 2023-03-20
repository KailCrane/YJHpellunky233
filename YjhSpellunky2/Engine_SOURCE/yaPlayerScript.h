#pragma once
#include "yaScript.h"


namespace ya
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void StateCheck();
		void AttackEnd();
		void AnimInput();

	private:

		enum PlayerActionState
		{
			Idle,
			Move,
			Jump,
			Attack,
			Burn,
		};

		PlayerActionState actionState;

		enum PlayerHealthState
		{
			Nomal,
			Addicted,
			ElectricShockDead,
			StingDead,
			ChompDead
		};

		bool isAttack;
		bool isMove;
		bool isDaead;

	};
}
