#pragma once
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	class Disk : public GameObject
	{
	public:
		Disk();
		virtual ~Disk();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void Turn();
	private:

		bool isTurn;
		bool isComplete;
		float speed;
		Vector3 init_rot;
	};
}

