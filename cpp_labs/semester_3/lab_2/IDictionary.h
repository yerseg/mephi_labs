#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include "ArraySequence.h"
#include "ListSequence.h"

#define Q 2
#define P 3

template <typename TKey, typename TElem>
class IDictionary {
protected:
	struct KeyValue {
		TElem value;
		TKey key;
		const bool operator == (const KeyValue &kv) {
			return this->value == kv.value && this->key == kv.key;
		}
		const bool operator != (const KeyValue &kv) {
			return !(this->key == kv.key && this->value == kv.value);
		}
		friend ostream& operator << (ostream &s, KeyValue &kv) {
			s << '{' << kv.key << " : " << kv.value << '}';
			return s;
		}
	};
	ArraySequence<TKey> keys;
	int count;
	int capacity;
	ListSequence<KeyValue> * ptr;
	void ReBuild();

public:
	IDictionary();
	~IDictionary();
	int GetCount();
	int GetCapacity();
	TElem Get(TKey key);
	bool ContainsKey(TKey key);
	void Add(TKey key, TElem element);
	void Remove(TKey key);
	void printAll();
};

template <typename TKey, typename TElem>
IDictionary<TKey, TElem>::IDictionary() {
	this->count = 0;
	this->capacity = 1;
	this->ptr = new ListSequence<KeyValue> [1];
}

template <typename TKey, typename TElem>
IDictionary<TKey, TElem>::~IDictionary() {
	delete[] this->ptr;
}

template <typename TKey, typename TElem>
void IDictionary<TKey, TElem>::ReBuild() {
	if (this->capacity == this->count) {
		int new_capacity = this->capacity * Q + 1;
		ListSequence<KeyValue> * ptr1 = new ListSequence<KeyValue>[new_capacity];
		for (int i = 0; i < this->capacity; i++) {
			for (int k = 0; k < ptr[i].GetLength(); k++) {
				KeyValue kv;
				kv.key = this->ptr[i].Get(k).key;
				kv.value = this->ptr[i].Get(k).value;

				std::hash<TKey> hash_fn;
				size_t hash = hash_fn(kv.key);
				int index = hash % new_capacity;

				ptr1[index].Append(kv);
			}
		}

		delete[] this->ptr;

		this->ptr = ptr1;
		this->capacity = new_capacity;
	}
	else if (this->count <= this->capacity / P) {
		int new_capacity = this->capacity / Q + 1;
		ListSequence<KeyValue> * ptr1 = new ListSequence<KeyValue>[new_capacity];
		for (int i = 0; i < this->capacity; i++) {
			for (int k = 0; k < ptr[i].GetLength(); k++) {
				KeyValue kv;
				kv.key = this->ptr[i].Get(k).key;
				kv.value = this->ptr[i].Get(k).value;

				std::hash<TKey> hash_fn;
				size_t hash = hash_fn(kv.key);
				int index = hash % new_capacity;

				ptr1[index].Append(kv);
			}
		}
		delete[] this->ptr;
		this->ptr = ptr1;
		this->capacity = new_capacity;
	}
	else
		;
}

template <typename TKey, typename TElem>
int IDictionary<TKey, TElem>::GetCount() {
	return this->count;
}

template <typename TKey, typename TElem>
int IDictionary<TKey, TElem>::GetCapacity() {
	return this->capacity;
}

template <typename TKey, typename TElem>
void IDictionary<TKey, TElem>::Add(TKey key, TElem element) {
	ReBuild();
	KeyValue kv;
	kv.key = key; kv.value = element;
	if (ContainsKey(key)) throw KeyUsedException<TKey>(key);
	std::hash<TKey> hash_fn;
	size_t hash = hash_fn(kv.key);
	int index = hash % this->capacity;
	this->ptr[index].Append(kv);
	this->keys.Append(key);
	this->count++;
}

template <typename TKey, typename TElem>
TElem IDictionary<TKey, TElem>::Get(TKey key) {
	std::hash<TKey> hash_fn;
	size_t hash = hash_fn(key);
	int index = hash % this->capacity;
	if (ContainsKey(key)) {
		for (int k = 0; k < this->ptr[index].GetLength(); k++) {
			if (this->ptr[index].Get(k).key == key)
				return this->ptr[index].Get(k).value;
		}
	}
	else
		throw KeyIsNotExistException<TKey>(key);
}

template <typename TKey, typename TElem>
bool IDictionary<TKey, TElem>::ContainsKey(TKey key) {
	for (int i = 0; i < this->keys.GetLength(); i++) {
		if (key == keys.Get(i))
			return true;
	}
	return false;
}

template <typename TKey, typename TElem>
void IDictionary<TKey, TElem>::Remove(TKey key) {
	std::hash<TKey> hash_fn;
	size_t hash = hash_fn(key);
	int index = hash % this->capacity;
	if (ContainsKey(key)) {
		for (int k = 0; k < this->ptr[index].GetLength(); k++) {
			if (this->ptr[index].Get(k).key == key)
				this->ptr[index].Remove(this->ptr[index].Get(k));
		}
		this->keys.Remove(key);
		this->count--;
		ReBuild();
	}
	else
		throw KeyIsNotExistException<TKey>(key);
}

template <typename TKey, typename TElem>
void IDictionary<TKey, TElem>::printAll() {
	for (int j = 0; j < this->capacity; j++) {
		if (this->ptr[j].GetLength() != 0) {
			cout << endl << "___________________BACKET #" << j << "___________________" << endl;
			this->ptr[j].printAll();
		}
	}
}

#endif /* IDICTIONARY_H */