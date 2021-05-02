export module Component;

namespace cave
{
	export class Component
	{
	public:
		enum class eType : unsigned char
		{
			NONE,
			INPUT,
			PHTSICS,
			AUDIO,
			VECTOR,
		};

		explicit Component() noexcept :
			mType(eType::NONE)
		{

		}

		explicit Component(eType newType) noexcept :
			mType(newType)
		{

		}

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;

		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


		__forceinline eType GetType() const noexcept
		{
			return mType;
		}

	private:
		eType mType;
	};
}