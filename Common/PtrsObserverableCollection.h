#pragma once 

#include "ObserverableCollection.h"
#include <algorithm>

namespace skb
{
	template< template<typename, typename> class CollectionType, typename ItemType >
	class PtrsObserverableCollection : public ObserverableCollection<CollectionType, std::unique_ptr<ItemType> >
	{
	public:
		iterator find(const ItemType* requiredItem)
		{
			auto it = std::find_if(_collection.begin(), _collection.end(), [&] (std::unique_ptr<ItemType>& item) { 
				return item.get() == requiredItem; 
			}); 

			if (it == _collection.end())
			{
				//TODO errors collector 
				throw std::logic_error("PtrsObserverableCollection.find: specified item is abscent in collection");
			}
		}
	};
}