#pragma once

#include "yaGraphics.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaObject.h"

namespace ya
{

	class FadeEffect
	{
		enum eFadeType
		{
			Fade_In,
			Fade_Out,
		};

		enum eFadeState
		{
			Ready,
			Processing,
			Complete,
			End,
		};

		FadeEffect();
		virtual ~FadeEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void FadeIn();
		void FadeOut();
		eFadeState GetFadeState() { return fade_state; }
		void SetFadeState(eFadeState state) { fade_state = state; }

		bool GetReady() { return IsReady; }
		void SetReady(bool enable) { IsReady = enable; }

	private:
		bool		IsActive;
		bool		IsReady;
		eFadeState	fade_state;
		float		add_time;
		float		duration;
		float		ratio;
		eFadeType	fade_type;
	};
}