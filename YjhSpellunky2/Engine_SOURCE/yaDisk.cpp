#include"yaDisk.h"


namespace ya
{
	Disk::Disk()
		:speed(0.0f),
		isTurn(false),
		isComplete(false)
	{

	}
	Disk::~Disk()
	{

	}
	void Disk::Initalize()
	{
		GameObject::Initalize();
		init_rot =  this->GetComponent<Transform>()->GetRotation();
		speed = 1.0f;
	}
	void Disk::Update()
	{
		GameObject::Update();
		if (!this->IsDead())
		{
			if (isTurn == true)
			{
				Vector3 curr_tr = this->GetComponent<Transform>()->GetRotation();
				Vector3 changed_tr = Vector3(curr_tr.x, curr_tr.y, curr_tr.z += speed * Time::DeltaTime());
				this->GetComponent<Transform>()->SetRotation(changed_tr);
			}
		}
	}
	void Disk::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}
	void Disk::Render()
	{
		GameObject::Render();
	}

	void Disk::Turn()
	{
		isTurn = true;
		/*Time::DeltaTime() * 10;*/
	}
}