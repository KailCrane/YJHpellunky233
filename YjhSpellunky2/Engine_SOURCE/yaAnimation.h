#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

namespace ya
{
	using namespace ya::math;
	using namespace ya::graphics;
	
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// ���� ��� ��ǥ
			Vector2 size;		// ������ܺ��� �߶� ���� ������ �ȼ� ����
			Vector2 offset;		// �� ��
			Vector2 atlasSize;  // �ɰ��� ��������Ʈ�� ũ��
			float duration;		// ������ ������ �ð�
			bool reverse;

			Sprite()
				: leftTop(0.0f, 0.0f)
				, size(0.0f, 0.0f)
				, offset(0.0f, 0.0f)
				, atlasSize(0.0f)
				, duration(0.1f)
				, reverse(false)
			{

			}
		};

		Animation();
		virtual ~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration , bool reverse);

		void Reset();

		void BindShader();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }

	private:
		std::shared_ptr<Texture> mAtlas;
		class Animator* mAnimator;
		
		std::wstring mAnimationName;
		std::vector<Sprite> mSpriteSheet; //�ϳ��� ������ ��Ʈ
		int mIndex;
		float mTime;
		bool mbComplete;

	};
}
