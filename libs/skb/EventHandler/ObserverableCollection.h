#pragma once

#include <memory>

#include "EventHandler.h"


namespace skb    //means SerKoz Bicycles
{


	/*
	Class is wrapper for any sequence stl container. Wrapper emits events when somebody perform action with collection
	(add item, remove item etc).
	Class encapsulates stl container but users can get usual stl iterator and work with it.
	*/
	template< template<typename, typename> class CollectionType, typename ItemType >
	class ObserverableCollection
	{
		typedef typename CollectionType<ItemType, std::allocator<ItemType> >::const_iterator const_iterator;
		typedef typename CollectionType<ItemType, std::allocator<ItemType> >::iterator iterator;

		CollectionType<ItemType, std::allocator<ItemType> > _collection;

	public:

		/*
		return items number
		*/
		size_t size() const
		{
			return _collection.size();
		}

		const_iterator begin() const
		{
			return _collection.begin();
		}

		iterator begin()
		{
			return _collection.begin();
		}

		const_iterator end() const
		{
			return _collection.end();
		}

		iterator end()
		{
			return _collection.end();
		}

		const ItemType& front() const
		{
			return _collection.front();
		}

		ItemType& front()
		{
			return _collection.front();
		}

		const ItemType& back() const
		{
			return _collection.back();
		}

		ItemType& back()
		{
			return _collection.back();
		}

		/*
		adds item to the tail of collection;
		*/
		void push_back(const ItemType& item)
		{
			_collection.push_back(item);
			itemAdded(ItemAddedEventArgs<ItemType>(_collection.back()));
		}


		void push_back(ItemType&& item)
		{
			_collection.push_back(std::move(item));
			itemAdded(ItemAddedEventArgs<ItemType>(_collection.back()));
		}


		iterator insert(const_iterator pos, const ItemType& value)
		{
			auto it = _collection.insert(pos, value);
			itemAdded(ItemAddedEventArgs<ItemType>(*it));
			return it;
		}

		iterator insert(const_iterator pos, ItemType&& value)
		{
			auto it = _collection.insert(pos, std::move(value));
			itemAdded(ItemAddedEventArgs<ItemType>(*it));
			return it;
		}


		/*
		// Return iterator of next item after deleted item (like stl erase)
		*/
		iterator erase(const_iterator pos)
		{
			itemRemoved(ItemRemovedEventArgs<ItemType>(*pos));
			return _collection.erase(pos);
		}

		///*
		//return pointer to the const std collection 
		//*/
		//const CollectionType<ItemType, std::allocator<ItemType> >* getItems() const
		//{
		//	return _collection.get();
		//}


		//ObserverableCollection() : 	_collection(new CollectionType<ItemType, std::allocator<ItemType> >())
		//{

		//}

		////очень вероятно, что можно было не писать всю эту байду вручную, ведь у классов контейнеров есть кон-р копирования пермещением
		////так что можно наверно было оставить _collection членом по значеню
		////TODO поэкспериментировать с к-рами копирования перемещением коллекций
		//ObserverableCollection(const ObserverableCollection& other) : ObserverableCollection()
		//{
		//	auto ptr = new CollectionType<ItemType, std::allocator<ItemType> > (other._collection.get())
		//		_collection.reset(ptr);
		//}

		//ObserverableCollection& operator= (const ObserverableCollection& other)
		//{
		//	ObserverableCollection temp(other);
		//	swap(*this, other);
		//}


		//ObserverableCollection(ObserverableCollection&& other)
		//{
		//	this->_collection = std::move(other._collection);
		//}

		//ObserverableCollection& operator= (ObserverableCollection&& other)
		//{
		//	ObserverableCollection temp(std::move(other));
		//	swap(*this, temp);
		//}

		//friend void swap(ObserverableCollection& one, ObserverableCollection& other)
		//{
		//	one._collection.swap(other._collection);
		//}

		mutable skb::EventHandler<const ItemAddedEventArgs<ItemType>& > itemAdded;
		mutable skb::EventHandler<const ItemRemovedEventArgs<ItemType>& > itemRemoved;
	};
}

