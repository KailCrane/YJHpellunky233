#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Rigidbody : public Component
	{
	public:

		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void ChangeGravityScale();
		void GravityOn() { isGravity = true; }
		void GravityOff() { isGravity = false; }

	private:

		Vector3 gravity_direction;
		float gravity_scale;
		bool isGravity;
	};
}