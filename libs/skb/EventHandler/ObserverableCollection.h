#pragma once

#include "EventHandler.h"

namespace skb    //means SerKoz Bicycles
{


	/*
	Class is wrapper for std container which emits events when somebody perform action with collection
	(add item, remove item etc).
	Note all comparation operations for collection item will be performed for item adresses. In this way elements are considered equal 
	only if they are in fact one element.
	*/
	template< template<typename, typename> class CollectionType, typename ItemType >
	class ObserverableCollection
	{
		CollectionType<ItemType, std::allocator<ItemType> > _collection;

		class isPointersEqual
		{
			const ItemType& _baseItem;
		public:
			isPointersEqual(const ItemType& baseItem) : _baseItem(baseItem)
			{
			}

			bool operator() (const ItemType& item)
			{
				return &_baseItem == &item;
			}
		};

	public:
		/*
		adds item to the tail of collection;
		WARNING! item from args will be copied and item in the collection will have other adress
		*/
		const ItemType* append(const ItemType& item)
		{
			_collection.push_back(item);
			itemAdded(ItemAddedEventArgs<ItemType>(&_collection.back(), nullptr));
			return &_collection.back();
		}


		const ItemType* append(ItemType&& item)
		{
			_collection.push_back(std::move(item));
			itemAdded(ItemAddedEventArgs<ItemType>(&_collection.back(), nullptr));
			return &_collection.back();
		}

		/*
		insert item before itemAfterInsertion(if itemAfterInsertion is nullptr, insert to the tail of collection);
		WARNING! item from args will be copied and item in the collection will have other adress
		*/
		const ItemType* insert(const ItemType& insertableItem, const ItemType* itemAfterInsertion)
		{
			auto it = std::find_if(_collection.begin(), _collection.end(), isPointersEqual(*itemAfterInsertion));
			_collection.insert(it, insertableItem);
			const ItemType* addedItemPtr = &(*(--it));
			itemAdded(ItemAddedEventArgs<ItemType>(&(*it), itemAfterInsertion));
			return addedItemPtr;
		}

		const ItemType* insert(ItemType&& insertableItem, const ItemType* itemAfterInsertion)
		{
			auto it = std::find_if(_collection.begin(), _collection.end(), isPointersEqual(*itemAfterInsertion));
			_collection.insert(it, std::move(insertableItem));
			const ItemType* addedItemPtr = &(*(--it));
			itemAdded(ItemAddedEventArgs<ItemType>(addedItemPtr, itemAfterInsertion));
			return addedItemPtr;
		}

		/*
		remove item from the collection;
		WARNING! It will remove only item with such adress. 
		*/
		bool remove(const ItemType* removedItem)
		{
			auto it = std::find_if(_collection.begin(), _collection.end(), isPointersEqual(*removedItem));

			if (it == _collection.end())
				return false;

			itemRemoved(ItemRemovedEventArgs<ItemType>(&(*it)));

			_collection.erase(it);
			return true;
		}

		/*
		return pointer to the const std collection 
		*/
		const CollectionType<ItemType, std::allocator<ItemType> >* getItems() const
		{
			return &_collection;
		}

		/*
			return items number
		*/
		size_t size() const
		{
			return _collection.size();
		}

		mutable typename CollectionType<ItemType, std::allocator<ItemType> >::const_iterator it;

		//check situation without startEnumeration call
		const ItemType* nextItem() const
		{
			if (it != _collection.end())
				return &(*(it++));
			return nullptr;
		}

		void startEnumeration() const
		{
			it = _collection.begin();
		}

		mutable skb::EventHandler<const ItemAddedEventArgs<ItemType>& > itemAdded;
		mutable skb::EventHandler<const ItemRemovedEventArgs<ItemType>& > itemRemoved;
	};

	template< template<typename, typename> class CollectionType, typename ItemType >
	class NonCopiableObserverableCollection : public ObserverableCollection<CollectionType, ItemType>
	{
		NonCopiableObserverableCollection(const NonCopiableObserverableCollection&);
		NonCopiableObserverableCollection(const NonCopiableObserverableCollection&&);
		void operator =(NonCopiableObserverableCollection);
	public:
		NonCopiableObserverableCollection()
		{}
	};
}

