module;

#include <string>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

export module Object;

export namespace cave
{
	class Object
	{
	public:
		FORCEINLINE friend bool operator==(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator!=(const Object& lhs, const Object& rhs);
		FORCEINLINE friend bool operator<(const Object& lhs, const Object& rhs);

		virtual ~Object();

		FORCEINLINE uint32_t GetGUID() const;
		FORCEINLINE bool IsValid() const;

		FORCEINLINE const std::string& GetName() const;

	protected:
		Object();
		Object(std::string& name);
		Object(const char* name);
		Object(const Object& other);
		Object(Object&& other) noexcept;

		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

	private:
		static uint32_t mNextGUID;
		/*Object's unique ID.*/
		uint32_t mGUID = 0;

		const std::string mName;
	};

	uint32_t Object::mNextGUID = 1;

	Object::Object()
		: mName()
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(std::string& name)
		: mName(name)
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const char* name)
		: mName(name)
	{
		assert((name != nullptr) & (mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const Object& other)
		: mName(other.GetName())
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::Object(Object&& other) noexcept
		: mName(other.GetName())
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::~Object()
	{
		assert(IsValid());
		mGUID = 0;
	}

	Object& Object::operator=(const Object& other)
	{
		assert(GetGUID() != other.GetGUID());

		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		assert(GetGUID() != other.GetGUID());

		return *this;
	}

	FORCEINLINE bool operator==(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() == rhs.GetGUID();
	}

	FORCEINLINE bool operator!=(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() != rhs.GetGUID();
	}

	FORCEINLINE bool operator<(const Object& lhs, const Object& rhs)
	{
		return lhs.GetGUID() < rhs.GetGUID();
	}

	FORCEINLINE uint32_t Object::GetGUID() const
	{
		assert(IsValid());
		return mGUID;
	}

	FORCEINLINE bool Object::IsValid() const
	{
		return mGUID == 0 ? false : true;
	}

	FORCEINLINE const std::string& Object::GetName() const
	{
		assert(IsValid());
		return mName;
	}
}