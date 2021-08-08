/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <unordered_map>
#include <vector>

#include "CoreTypes.h"

#include "Assertion/Assert.h"
#include "Debug/Log.h"

export module Trie;

import String;

namespace cave
{
	export template <typename T>
	class TrieNode final
	{
	public:
		constexpr explicit TrieNode(const T& data);
		constexpr explicit TrieNode(const T& data, bool bIsEnd);
		constexpr TrieNode(const TrieNode& other);
		constexpr TrieNode(const TrieNode& other, bool bIsEnd);
		constexpr TrieNode(TrieNode&& other);
		constexpr TrieNode(TrieNode&& other, bool bIsEnd);
		constexpr TrieNode& operator=(const TrieNode& other);
		constexpr TrieNode& operator=(TrieNode&& other);
		~TrieNode() = default;

		constexpr const T& GetData() const;
		constexpr bool IsEnd() const;
		constexpr std::unordered_map<T, TrieNode>& GetChildren();
		constexpr const std::unordered_map<T, TrieNode>& GetChildren() const;

		constexpr void AddChild(TrieNode&& node);
		constexpr TrieNode& GetChild(const T& data);
		constexpr bool RemoveChild(const T& data);
	private:
		T mData;
		bool mbIsEnd;
		//TArray<TrieNode*> mChildren;
		std::unordered_map<T, TrieNode> mChildren;
	};

	template <typename T>
	constexpr TrieNode<T>::TrieNode(const T& data)
		: TrieNode(data, false)
	{
	}

	template <typename T>
	constexpr TrieNode<T>::TrieNode(const T& data, bool bIsEnd)
		: mData(data)
		, mbIsEnd(bIsEnd)
		, mChildren(std::unordered_map<T, TrieNode>())
	{
	}

	template <typename T>
	constexpr TrieNode<T>::TrieNode(const TrieNode& other)
		: TrieNode(other, other.mbIsEnd)
	{
	}

	template <typename T>
	constexpr TrieNode<T>::TrieNode(const TrieNode& other, bool bIsEnd)
		: mData(other.mData)
		, mbIsEnd(bIsEnd)
		, mChildren(other.mChildren)
	{
	}

	template <typename T>
	constexpr TrieNode<T>::TrieNode(TrieNode&& other)
		: TrieNode(std::move(other), other.mbIsEnd)
	{
	}

	template <typename T>
	constexpr TrieNode<T>::TrieNode(TrieNode&& other, bool bIsEnd)
		: mData(std::move(other.mData))
		, mbIsEnd(bIsEnd)
		, mChildren(std::move(other.mChildren))
	{
	}

	template <typename T>
	constexpr TrieNode<T>& TrieNode<T>::operator=(const TrieNode& other)
	{
		if (this != &other)
		{
			mData = other.mData;
			mbIsEnd = other.mbIsEnd;
			mChildren = other.mChildren;
		}

		return *this;
	}

	template <typename T>
	constexpr TrieNode<T>& TrieNode<T>::operator=(TrieNode&& other)
	{
		if (this != &other)
		{
			mData = std::move(other.mData);
			mbIsEnd = other.mbIsEnd;
			mChildren = std::move(other.mChildren);
		}

		return *this;
	}

	template <typename T>
	constexpr const T& TrieNode<T>::GetData() const
	{
		return mData;
	}

	template <typename T>
	constexpr bool TrieNode<T>::IsEnd() const
	{
		return mbIsEnd;
	}

	template <typename T>
	constexpr std::unordered_map<T, TrieNode<T>>& TrieNode<T>::GetChildren()
	{
		return mChildren;
	}

	template <typename T>
	constexpr const std::unordered_map<T, TrieNode<T>>& TrieNode<T>::GetChildren() const
	{
		return mChildren;
	}

	template <typename T>
	constexpr void TrieNode<T>::AddChild(TrieNode&& node)
	{
		//mChildren[node.mData] = std::move(node);
		mChildren.insert({ node.mData, std::move(node) });
	}

	template <typename T>
	constexpr TrieNode<T>& TrieNode<T>::GetChild(const T& data)
	{
		assert(mChildren.contains(data));

		return mChildren.at(data);
	}

	template <typename T>
	constexpr bool TrieNode<T>::RemoveChild(const T& data)
	{
		if (!mChildren.contains(data))
		{
			return false;
		}

		mChildren.remove(data);

		return true;
	}

#ifdef CAVE_BUILD_DEBUG
	export namespace TrieTest
	{
		void Main();

		void PrintRecursive(const TrieNode<char>& node, String str)
		{
			str.PushBack(node.GetData());

			if (node.IsEnd())
			{
				LOGDF(cave::eLogChannel::CORE_CONTAINER, "WORD: %s", str.GetCString());
			}

			for (const std::pair<const char, cave::TrieNode<char>>& pair : node.GetChildren())
			{
				PrintRecursive(pair.second, str);
			}
		}

		void Main()
		{
			std::vector<TrieNode<char>> trieNodes;
			trieNodes.reserve(2);

			trieNodes.push_back(TrieNode<char>('a', true));
			{
				trieNodes[0].AddChild(TrieNode<char>('a'));
				{
					trieNodes[0].GetChild('a').AddChild(TrieNode<char>('h', true));
				}
				trieNodes[0].AddChild(TrieNode<char>('b'));
				{
					trieNodes[0].GetChild('b').AddChild(TrieNode<char>('a'));
					{
						trieNodes[0].GetChild('b').GetChild('a').AddChild(TrieNode<char>('c'));
						{
							trieNodes[0].GetChild('b').GetChild('a').GetChild('c').AddChild(TrieNode<char>('k', true));
							trieNodes[0].GetChild('b').GetChild('a').GetChild('c').AddChild(TrieNode<char>('u'));
							{
								trieNodes[0].GetChild('b').GetChild('a').GetChild('c').GetChild('u').AddChild(TrieNode<char>('s', true));
							}
						}
						trieNodes[0].GetChild('b').GetChild('a').AddChild(TrieNode<char>('n'));
						{
							trieNodes[0].GetChild('b').GetChild('a').GetChild('n').AddChild(TrieNode<char>('d'));
							{
								trieNodes[0].GetChild('b').GetChild('a').GetChild('n').GetChild('d').AddChild(TrieNode<char>('o'));
								{
									trieNodes[0].GetChild('b').GetChild('a').GetChild('n').GetChild('d').GetChild('o').AddChild(TrieNode<char>('n', true));
								}
							}
						}
					}
					trieNodes[0].GetChild('b').AddChild(TrieNode<char>('l'));
					{
						trieNodes[0].GetChild('b').GetChild('l').AddChild(TrieNode<char>('e', true));
						trieNodes[0].GetChild('b').GetChild('l').AddChild(TrieNode<char>('y', true));
					}
				}
			}

			trieNodes.push_back(TrieNode<char>('b', true));
			{
				trieNodes[1].AddChild(TrieNode<char>('a', true));
				{
					trieNodes[1].GetChild('a').AddChild(TrieNode<char>('b'));
					{
						trieNodes[1].GetChild('a').GetChild('b').AddChild(TrieNode<char>('b'));
						{
							trieNodes[1].GetChild('a').GetChild('b').GetChild('b').AddChild(TrieNode<char>('l'));
							{
								trieNodes[1].GetChild('a').GetChild('b').GetChild('b').GetChild('l').AddChild(TrieNode<char>('e', true));
							}
						}
					}
				}
			}

			for (const TrieNode<char>& root : trieNodes)
			{
				String word;
				PrintRecursive(root, word);
			}
		}
	}
#endif
}