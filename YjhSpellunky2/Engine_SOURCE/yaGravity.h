#pragma once
#include "yaComponent.h"

using namespace ya::math;

namespace ya
{
	class Gravity : public Component
	{

	public :

		Gravity();
		virtual ~Gravity();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		void OnDrop();


		void OffDrop();


		void Drop();

	private:

		//떨어지는 최대 속도
		//땅에 붙어있는가 아닌가를 받아와야겠네
		// bool을 이용하여 on off
		float maxSpeed;
		bool isDrop;
		Transform* tr;
	};



}
