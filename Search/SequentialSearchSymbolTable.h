#pragma once

#include <optional>
#include <memory>

namespace Search
{
	template <typename Key, typename Value>
	class SequentialSearchSymbolTable
	{
	private:
		struct Node
		{
		public:
			Node(const Key &key, const Value &value, std::unique_ptr<Node> next = nullptr)
				: key(key), value(value), next(std::move(next)) {}

			std::unique_ptr<Node> next; // 内存对齐 64 位
			Key key;
			Value value;
		};

	public:
		std::optional<Value> get(const Key &key)
		{
			for (Node *x = head.get(); x != nullptr; x = x->next.get())
			{
				if (key == x->key)
				{
					return x->value;
				}
			}
			return std::nullopt;
		}

		void put(const Key &key, const Value &value)
		{
			for (Node *x = head.get(); x != nullptr; x = x->next.get())
			{
				if (key == x->key)
				{
					x->value = value;

					return;
				}
			}

			head = std::make_unique<Node>(key, value, std::move(head));
		}

		void deletes(const Key &key)
		{
			if (head == nullptr)
				return;

			if (head->key == key)
			{
				head = std::move(head->next);
				return;
			}

			Node *preview = head.get();
			Node *current = preview->next.get();
			while (current != nullptr && current->key != key)
			{
				preview = current;
				current = current->next.get();
			}

			if (current != nullptr)
			{
				preview->next.reset(current->next.release());
			}
		}

		size_t size()
		{
			size_t count = 0;
			for (Node *x = head.get(); x != nullptr; x = x->next.get())
			{
				++count;
			}

			return count;
		}

	private:
		std::unique_ptr<Node> head;
	};
}