#pragma once

#include "yaPlayerScript.h"
#include "yaGameObject.h"
#include "yaScript.h"
#include "yaRope.h"

namespace ya
{
	class RopeScript :public Script
	{
	public:
		RopeScript();
		~RopeScript();


		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		//Start��
		//ó�� ������ ������ * Y��ŭ �ö󰡰�
		//�� �ö󰡸� Next���� ]
		//÷�� �����޸� �����̰� �� �ö󰡸� ���� ��ȣ ALLIVE
		// �̹��� �ݴ�� *Y��ŭ �������� ��
		// ���� ���� ���������� NEXT�� ���ڸ��� ACTIVE();
		// �������� �����ϸ� ���� Ǯ���� �ִ� ��� 
		// 
		//��Ž

		//���ൿ�� ������ �������� �����ϱ� ���ؼ�
		void SetNext(Rope* next){next_chain = next;}
		void SetPrev(Rope* prev){prev_chain = prev;}

		void Throw(Vector3 pos);

		enum State
		{
			Start,
			End,
			Middle
		};
		State state;

	private:
		Rope* prev_chain;
		Rope* next_chain;
		Vector3 start_pos;
		bool isThrow;
	};
};

