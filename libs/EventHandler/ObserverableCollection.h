#pragma once

#include "EventHandler.h"

namespace skb    //means SerKoz Bicycles
{
	template< template<typename, typename> class CollectionType, typename ItemType >
	class ObserverableCollection
	{
		CollectionType<ItemType, std::allocator<ItemType> > _collection;
	public:

		void append(const ItemType& item)
		{
			const ItemType* lastItem = (_collection.size() == 0) ? nullptr : &_collection.back(); 
			_collection.push_back(item);
			pointAdded(ItemAddedEventArgs<ItemType>(&_collection.back(), lastItem));
		}


		void insert(const ItemType* insertableItem, const ItemType* itemBeforeInsertion);


		bool remove(const ItemType* removedItem)
		{
			auto it = std::find_if(_collection.begin(), _collection.end(), [&removedItem] (const ItemType& item) {
				return removedItem == &item;
			});
			if (it == _collection.end())
				return false;

			pointRemoved(ItemRemovedEventArgs<ItemType>(&(*it)));

			_collection.erase(it);
			return true;
		}

		const CollectionType<ItemType, std::allocator<ItemType> >* getItems() const
		{
			return &_collection;
		}


		skb::EventHandler<const ItemAddedEventArgs<ItemType>& > pointAdded;
		skb::EventHandler<const ItemRemovedEventArgs<ItemType>& > pointRemoved;
	};
}