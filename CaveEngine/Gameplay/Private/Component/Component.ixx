export module Component;

namespace cave
{
	export class Component
	{
	public:
		enum class eType
		{
			NONE,
			POSSESSOR,
			INPUT,
			PHTSICS,
			AUDIO,
			VECTOR,
			EVENT,
		};

		explicit Component() :
			mType(eType::NONE)
		{

		}

		explicit Component(eType newType) :
			mType(newType)
		{

		}

		__forceinline eType GetType()
		{
			return mType;
		}

	private:
		eType mType;
	};
}