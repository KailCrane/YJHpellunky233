#pragma once
#include "yaScene.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		std::list<GameObject* > titleObjs;
		std::list<GameObject* > menuselObjs;
		std::list<GameObject* > charselObjs;

		enum MenuState
		{
			TitleScreen,
			MenuSelect,
			CharSelect
		};
		MenuState menuState;
	};
}
