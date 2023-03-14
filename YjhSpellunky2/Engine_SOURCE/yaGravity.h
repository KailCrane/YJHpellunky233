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

		//�������� �ִ� �ӵ�
		//���� �پ��ִ°� �ƴѰ��� �޾ƿ;߰ڳ�
		// bool�� �̿��Ͽ� on off
		float maxSpeed;
		bool isDrop;
		Transform* tr;
	};



}
