#pragma once
#include "yaComponent.h"
#include "yaGameObject.h"

using namespace ya::math;

namespace ya
{
	class Gravity : public Component
	{

	public :

		Gravity();
		virtual ~Gravity();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		void GravityOn() { isGravity = true; }
		void GravityOff() { isGravity = false; }
		bool GetIsGravity() { return isGravity; }
		void Reset() { velocity = 0.0f; force_power = 0.0f; }

		void AddForce(Vector2 direction);


	private:

		//�������� �ִ� �ӵ�
		//���� �پ��ִ°� �ƴѰ��� �޾ƿ;߰ڳ�
		// bool�� �̿��Ͽ� on off
		float velocity;
		float max_velocity;
		float acc;
		bool isGravity;
		float force_power;
		float max_power;
	};
}

