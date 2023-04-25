#include "yaFadeEffect.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaConstantBuffer.h"
#include "yaRenderer.h"
#include "yaTime.h"

extern ya::Application application;

namespace ya
{
	FadeEffect::FadeEffect()
		: IsActive(false)
		, IsReady(false)
		, fade_state(eFadeState::Ready)
		, add_time(0.0f)
		, duration(0.5f)
		, ratio(1.0f)
		, fade_type(eFadeType::Fade_In)
	{
	}
	FadeEffect::~FadeEffect()
	{
	}

	void FadeEffect::Initalize()
	{
	}
	void FadeEffect::Update()
	{
		if (IsActive)
		{
			add_time += Time::DeltaTime();

			if (add_time >= duration)
			{
				IsActive = false;
				fade_state = eFadeState::Complete;
				add_time = 0.0f;
			}
		}

		/*if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::I) && false == mIsActive
			&& 0.9 <= mRatio)
		{
			mIsComplete = false;
			mIsActive = true;
			mType = Fade_In;
		}
		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::O) && false == mIsActive
			&& 0.1 >= mRatio)
		{
			mIsComplete = false;
			mIsActive = true;
			mType = Fade_Out;
		}*/
	}

	void FadeEffect::FadeIn()
	{
		IsActive = true;
		fade_state = eFadeState::Processing;
		fade_type = Fade_In;
	}
	void FadeEffect::FadeOut()
	{
		IsActive = true;
		fade_state = eFadeState::Processing;
		fade_type = Fade_Out;
	}


	void FadeEffect::FixedUpdate()
	{
		if (!IsActive)
			return;

		// alpha test
		if (ratio > 0.5f)
			int a = 0;

		if (eFadeType::Fade_Out == fade_type)
		{
			ratio = (add_time / duration);
		}
		else if (eFadeType::Fade_In == fade_type)
		{
			ratio = 1 - (add_time / duration);
		}


		// Constant buffer
		ConstantBuffer* FadeCB = renderer::constantBuffers[(UINT)eCBType::Fade];

	/*	renderer::FadeCB data;
		data.alpha = ratio;*/

		//FadeCB->Bind(&data);
		//FadeCB->SetPipline(eShaderStage::VS);
		//FadeCB->SetPipline(eShaderStage::PS);
	}
	void FadeEffect::Render()
	{
	}
}