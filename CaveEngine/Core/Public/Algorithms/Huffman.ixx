/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <unordered_map>

#include "CoreGlobals.h"
#include "Debug/Log.h"
#include "Memory/MemoryPool.h"

export module Huffman;

import Array;
import Memory;
import Stack;
import String;

namespace cave
{
	export class HuffmanNode final
	{
	public:
		constexpr HuffmanNode(size_t frequency);
		constexpr HuffmanNode(size_t frequency, char character);
		constexpr HuffmanNode(const HuffmanNode& other) = delete;
		constexpr HuffmanNode(HuffmanNode&& other) = delete;
		~HuffmanNode() = default;

		static void DestroyTree(HuffmanNode* root, MemoryPool& pool);

		constexpr HuffmanNode& operator=(const HuffmanNode& other) = delete;
		constexpr HuffmanNode& operator=(HuffmanNode&& other) = delete;

		constexpr bool IsLeaf() const;
		constexpr size_t GetFrequency() const;
		constexpr void SetFrequency(size_t frenquency);
		constexpr char GetCharacter() const;
		constexpr const HuffmanNode* GetLeft() const;
		constexpr const HuffmanNode* GetRight() const;
		constexpr void SetRight(HuffmanNode* right);
		static constexpr void AddParent(HuffmanNode* root, HuffmanNode* parent);
		static constexpr void AddParent(HuffmanNode* leftChild, HuffmanNode* rightChild, HuffmanNode* parent);
		static constexpr void AddNode(HuffmanNode* root, HuffmanNode* node);

		static HuffmanNode* CreateHuffmanTreeMalloc(const String& message, MemoryPool& pool);
		static String EncodeMessage(const std::unordered_map<char, String>& charToBits, const String& message);
		static std::unordered_map<char, String> GetHuffmanTable(const HuffmanNode* const tree);
	private:
		static void quicksortCharacterCount(Array<std::pair<char, size_t>>& outCharacterCount);
		static void quicksortCharacterCountRecursive(Array<std::pair<char, size_t>>& outCharacterCount, size_t leftIndex, size_t rightIndex);
		static size_t partitionCharacterCountRecursive(Array<std::pair<char, size_t>>& outCharacterCount, size_t leftIndex, size_t rightIndex);
		static void destroyTreeRecursive(HuffmanNode* node, MemoryPool& pool);
		static constexpr void addNodeRecursive(HuffmanNode* root, HuffmanNode* node);

		static void getHuffmanTableRecursive(const HuffmanNode* const tree, std::unordered_map<char, String>& outTable, String& code);

		size_t mFrequency = 0u;
		char mCharacter = '\0';
		HuffmanNode* mLeft = nullptr;
		HuffmanNode* mRight = nullptr;
	};

	constexpr HuffmanNode::HuffmanNode(size_t frequency)
		: mFrequency(frequency)
		, mCharacter('\0')
		, mLeft(nullptr)
		, mRight(nullptr)
	{
	}

	constexpr HuffmanNode::HuffmanNode(size_t frequency, char character)
		: mFrequency(frequency)
		, mCharacter(character)
		, mLeft(nullptr)
		, mRight(nullptr)
	{
	}

	void HuffmanNode::DestroyTree(HuffmanNode* root, MemoryPool& pool)
	{
		destroyTreeRecursive(root, pool);
	}

	void HuffmanNode::destroyTreeRecursive(HuffmanNode* node, MemoryPool& pool)
	{
		HuffmanNode* left = node->mLeft;
		HuffmanNode* right = node->mRight;

		if (left != nullptr)
		{
			destroyTreeRecursive(left, pool);
		}

		if (right != nullptr)
		{
			destroyTreeRecursive(right, pool);
		}

		pool.Deallocate(node, sizeof(HuffmanNode));
	}

	constexpr bool HuffmanNode::IsLeaf() const
	{
		return mLeft == nullptr && mRight == nullptr;
	}

	constexpr size_t HuffmanNode::GetFrequency() const
	{
		return mFrequency;
	}

	constexpr void HuffmanNode::SetFrequency(size_t frenquency)
	{
		mFrequency = frenquency;
	}

	constexpr char HuffmanNode::GetCharacter() const
	{
		return mCharacter;
	}

	constexpr const HuffmanNode* HuffmanNode::GetLeft() const
	{
		return mLeft;
	}

	constexpr const HuffmanNode* HuffmanNode::GetRight() const
	{
		return mRight;
	}

	constexpr void HuffmanNode::SetRight(HuffmanNode* right)
	{
		assert(mRight == nullptr);
		mRight = right;
	}

	constexpr void HuffmanNode::AddNode(HuffmanNode* root, HuffmanNode* node)
	{
		addNodeRecursive(root, node);
	}

	constexpr void HuffmanNode::addNodeRecursive(HuffmanNode* root, HuffmanNode* node)
	{
		if (root->mFrequency <= node->mFrequency)
		{
			if (root->mRight == nullptr)
			{
				root->mRight = node;
			}
			else
			{
				addNodeRecursive(root->mLeft, node);
			}
		}
		else
		{
			if (root->mLeft == nullptr)
			{
				root->mLeft = node;
			}
			else
			{
				addNodeRecursive(root->mLeft, node);
			}
		}
	}

	constexpr void HuffmanNode::AddParent(HuffmanNode* root, HuffmanNode* parent)
	{
		HuffmanNode::AddNode(parent, root);
	}

	constexpr void HuffmanNode::AddParent(HuffmanNode* leftChild, HuffmanNode* rightChild, HuffmanNode* parent)
	{
		HuffmanNode::AddNode(parent, leftChild);
		//HuffmanNode::AddNode(parent, rightChild);
		parent->SetRight(rightChild);
	}

	HuffmanNode* HuffmanNode::CreateHuffmanTreeMalloc(const String& message, MemoryPool& pool)
	{
		std::unordered_map<char, size_t> table;

		for (size_t i = 0; i < message.GetLength(); ++i)
		{
			if (table.contains(message[i]))
			{
				table.at(message[i]) = table.at(message[i]) + 1;
			}
			else
			{
				table.insert_or_assign(message[i], 1);
			}
		}
		Array<std::pair<char, size_t>> charCount;
		charCount.SetCapacity(table.size());
		for (const auto& iter : table)
		{
			charCount.InsertBack(iter);
		}
		quicksortCharacterCount(charCount);

		HuffmanNode* root = nullptr;
		for (size_t i = 0; i < charCount.GetSize(); ++i)
		{
			HuffmanNode* node = reinterpret_cast<HuffmanNode*>(pool.Allocate(sizeof(HuffmanNode)));
			new(node) HuffmanNode(charCount[i].second, charCount[i].first);

			if (root == nullptr)
			{
				root = node;
			}
			else if (root->IsLeaf())
			{
				HuffmanNode* newRoot = reinterpret_cast<HuffmanNode*>(pool.Allocate(sizeof(HuffmanNode)));
				new(newRoot) HuffmanNode(root->GetFrequency() + node->GetFrequency());
				HuffmanNode::AddParent(root, node, newRoot);
				root = newRoot;
			}
			else
			{
				HuffmanNode* newRoot = reinterpret_cast<HuffmanNode*>(pool.Allocate(sizeof(HuffmanNode)));
				new(newRoot) HuffmanNode(root->GetFrequency() + node->GetFrequency());
				HuffmanNode::AddParent(root, node, newRoot);
				root = newRoot;
			}
		}

		return root;
	}

	void SetBit(size_t n, void* ptr, size_t size)
	{
		assert(n < size);

		uint8_t remainder = static_cast<uint8_t>(n % 8);

		size_t quotient = n / 8;
		*(reinterpret_cast<uint8_t*>(ptr) + quotient) |= 1u << remainder;
	}

	uint8_t GetBit(size_t n, void* ptr, size_t size)
	{
		assert(n < size);

		uint8_t remainder = static_cast<uint8_t>(n % 8);

		size_t quotient = n / 8;
		return *(reinterpret_cast<uint8_t*>(ptr) + quotient) >> remainder & 1u;
	}

	String HuffmanNode::EncodeMessage(const std::unordered_map<char, String>& charToBits, const String& message)
	{
		String encodedMessage;

		for (size_t i = 0; i < message.GetLength(); ++i)
		{
			encodedMessage.Append(charToBits.at(message[i]));
		}

		return std::move(encodedMessage);
	}

	std::unordered_map<char, String> HuffmanNode::GetHuffmanTable(const HuffmanNode* const tree)
	{
		std::unordered_map<char, String> charToBits;
		if (tree->IsLeaf())
		{
			String code("0");
			charToBits.insert_or_assign(tree->mCharacter, code);
		}
		else
		{
			String code;

			if (tree->mLeft != nullptr)
			{
				code.PushBack('0');
				getHuffmanTableRecursive(tree->mLeft, charToBits, code);
			}

			if (tree->mRight != nullptr)
			{
				code.PushBack('1');
				getHuffmanTableRecursive(tree->mRight, charToBits, code);
			}
		}

		return charToBits;
	}

	void HuffmanNode::getHuffmanTableRecursive(const HuffmanNode* const tree, std::unordered_map<char, String>& outCharToBits, String& code)
	{
		if (tree->IsLeaf())
		{
			outCharToBits.insert_or_assign(tree->mCharacter, code);
		}
		else
		{
			if (tree->mLeft != nullptr)
			{
				code.PushBack('0');
				getHuffmanTableRecursive(tree->mLeft, outCharToBits, code);
			}

			if (tree->mRight != nullptr)
			{
				code.PushBack('1');
				getHuffmanTableRecursive(tree->mRight, outCharToBits, code);
			}
		}

		code.PopBack();
	}

	void HuffmanNode::quicksortCharacterCount(Array<std::pair<char, size_t>>& outCharacterCount)
	{
		quicksortCharacterCountRecursive(outCharacterCount, 0, outCharacterCount.GetSize() - 1);
	}

	void HuffmanNode::quicksortCharacterCountRecursive(Array<std::pair<char, size_t>>& outCharacterCount, size_t leftIndex, size_t rightIndex)
	{
		if (leftIndex >= rightIndex) {
			return;
		}

		size_t pivotIndex = partitionCharacterCountRecursive(outCharacterCount, leftIndex, rightIndex);

		quicksortCharacterCountRecursive(outCharacterCount, leftIndex, pivotIndex);
		quicksortCharacterCountRecursive(outCharacterCount, pivotIndex + 1, rightIndex);
	}

	size_t HuffmanNode::partitionCharacterCountRecursive(Array<std::pair<char, size_t>>& outCharacterCount, size_t leftIndex, size_t rightIndex)
	{
		size_t i = leftIndex - 1;
		size_t j = rightIndex + 1;

		while (true) {
			do {
				++i;
			} while (outCharacterCount[i].second < outCharacterCount[leftIndex].second);

			do {
				--j;
			} while (outCharacterCount[j].second > outCharacterCount[leftIndex].second);

			if (i >= j) {
				return j;
			}

			std::pair<char, size_t> temp = outCharacterCount[i];
			outCharacterCount[i] = outCharacterCount[j];
			outCharacterCount[j] = temp;
		}
	}
#ifdef CAVE_BUILD_DEBUG
	namespace HuffmanTest
	{
		export void Main();

		void Main()
		{
			{
				String message = "banana*bab";

				HuffmanNode* node = HuffmanNode::CreateHuffmanTreeMalloc(message, gCoreMemoryPool);
				std::unordered_map<char, String> charToBits = HuffmanNode::GetHuffmanTable(node);
				String encodedMeessage = HuffmanNode::EncodeMessage(charToBits, message);

				LOGDF(eLogChannel::CORE, "Original Message: %s", message.GetCString());
				LOGDF(eLogChannel::CORE, "Encoded Message: %s", encodedMeessage.GetCString());

				HuffmanNode::DestroyTree(node, gCoreMemoryPool);
			}
		}
	}
#endif
}
