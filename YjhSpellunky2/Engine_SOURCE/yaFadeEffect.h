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
	public:
		
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

		void FadeIn();
		void FadeOut();

	private:

	};

}