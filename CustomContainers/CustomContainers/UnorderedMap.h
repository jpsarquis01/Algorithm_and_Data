#pragma once
#include <vector>
#include <functional>

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
    struct KeyValuePair
    {
        KeyType key;
        ValueType value;
    };
public:
    UnorderedMap(std::size_t initialBucketSize = 8, double load factor = 0.75)
        :mBucketCount(initialBucketSize)
        , mLoadFactorThreshold(load factor)
        , mCount(0)
    {
        // in case we set it to 0
        mBucketCount = std::max(initialBucketSize, 1);
		mTable.resize(mBucketCount);
    }
    
    // delete copy and move constructor
    // prevents duplicationg data or losing content
	UnorderedMap(const UnorderedMap&) = delete;
	UnorderedMap(const UnorderedMap&&) = delete;
	UnorderedMap& operator=(const UnorderedMap&) = delete;
	UnorderedMap& operator=(const UnorderedMap&&) = delete;

    void Insert(const KeyType& key, const ValueType& value)
    {
		std::size_t index = GetTableIndex(key);
		// check if we already have the key in the table
		for (KeyValuePair& kv : mTable[index])
		{
			if (kv.key == key)
			{
                // if so, update the value and return
				kv.value = value;
				return;
			}
		}

        // otherwise add the new key and value 
		KeyValuePair& kv = mTable[index].emplace_back();
		kv.key = key;
		kv.value = value;
		++mCount;
		
		if ((double)mCount / (double)mBucketCount > mLoadFactorThreshold)
		{
            Rehash();
		}
    }

    bool Find(const KeyType& key, ValueType& outValue) const
    {
		std::size_t index = GetTableIndex(key);
        for (const KeyValuePair& kv : mTable[index])
        {
            if (kv.key == key)
            {
				outValue = kv.value;
				return true;
            }
        }
		return false;
    }

	bool Has(const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		for (const KeyValuePair& kv : mTable[index])
		{
			if (kv.key == key)
			{
				return true;
			}
		}
		return false;
	}

    bool Remove(const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);
		std::vector<KeyValuePair>& bucket = mTable[index];
		for (auto iter = bucket.begin(); iter != bucket.end(); ++iter)
		{
			if (iter->key == key)
			{
				bucket.erase(iter);
				--mCount;
				return true;
			}
		}
		return false;
    }

	std::size_t GetCount() const
	{
		return mCount;
	}

	void Clear()
	{
		for (std::vector<KeyValuePair>& bucket : mTable)
		{
			bucket.clear();
		}
		mTable.clear();
		mCount = 0;
	}

	// data accessors
	ValueType& operator[](const KeyType& key)
	{
		std::size_t index = GetTableIndex(key);
		for (KeyValuePair& kv : mTable[index])
		{
			if (kv.key == key)
			{
				return kv.value;
			}
		}
		KeyValuePair& kv = mTable[index].emplace_back();
		kv.key = key;
		kv.value = mDefault;
		++mCount;
		return kv.value;
	}

	// mMyMap["Vancouver"] = cool
	// mMyMap.Insert("Vancouver", cool);

	const ValueType& operator[](const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		for (const KeyValuePair& kv : mTable[index])
		{
			if (kv.key == key)
			{
				return kv.value;
			}
		}
		return mDefault;
	}

private:
    ValueType mDefault;
    // Table is main vector, "Bucket" is vector of objects using same index
    std::vector<std::vector<KeyValuePair>> mTable;
    // max indices the table can use to store individual values 
    std::size_t mBucketCount = 0;
	// total number od items in the table
    std::size_t mCount = 0;
	// how many items in the bucket before we need to resize the table
    double mLoadFactorThreshold = 1.0;
    // dynamic hash function, gives a hash value form whatever we use as a key
	std::hash<KeyType> mHashFunction;
    
    // gives the index in the table that the item will be placed
    std::size_t GetTableIndex(const KeyType& key) const
    {
		return mHashFunction(key) % mBucketCount;
    }

    void Rehash()
    {
		std::size_t newBucketCount = mBucketCount * 2;
		std::vector<std::vector<KeyValuePair>> newTable;
		newTable.resize(newBucketCount);

		// Set it first so we can reuse "GetTableIndex"
		mBucketCount = newBucketCount;
		for (std::vector<KeyValuePair>& bucket : mTable)
		{
			for (KeyValuePair& kv : bucket)
			{
				std::size_t index = GetTableIndex(kv.key);
				newTable[index].push_back(kv);
			}
			bucket.clear();
		}
		mTable.clear();
		// swap the new table with the old one
		mTable.swap(newTable);
    }
};