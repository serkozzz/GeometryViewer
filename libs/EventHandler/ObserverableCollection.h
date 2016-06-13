#pragma once

#include "EventHandler.h"

namespace skb    //means SerKoz Bicycles
{
	template< template<typename, typename> class CollectionType, typename ItemType >
	class ObserverableCollection
	{
		CollectionType<ItemType, std::allocator<ItemType> > _collection;
	public:

		void append(const ItemType* item)
		{

		}
		void insert(const ItemType* insertableItem, const ItemType* itemBeforeInsertion);
		bool remove(const ItemType* item);
		const CollectionType<ItemType, std::allocator<ItemType> >* getItems() const;


		skb::EventHandler<const ItemType*> pointAdded;
		skb::EventHandler<const ItemType*> pointRemoved;
	};
}