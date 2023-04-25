#include "yaRigidbody.h"
#include "yaGameObject.h"
#include "yaTime.h"


namespace ya
{
	void Rigidbody::Initalize()
	{	 

	}	 
		 
	void Rigidbody::Update()
	{	 
		if (FAILED(this->GetOwner()->GetComponent<Transform>()))
		{
			return;
		}
		if (isGravity)
		{
			Vector3 curr_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 fixed_pos = Vector3(curr_pos.x + gravity_direction.x + gravity_scale * Time::DeltaTime(),
										curr_pos.y + gravity_direction.y + gravity_scale * Time::DeltaTime(),
										curr_pos.z + gravity_direction.z + gravity_scale * Time::DeltaTime());

			//this->GetOwner()->GetComponent<Transform>()->SetPosition();
		}
	}	 
		 
	void Rigidbody::FixedUpdate()
	{	 
	}	 
		 
	void Rigidbody::Render()
	{	 
	}	 
		 
	void Rigidbody::ChangeGravityScale()
	{

	}
}
