export module formats.mvt.cache;

import std;

import core.bitmap;

namespace mvt::cache
{
	export template<typename Key, typename Value>
	class Cache
	{
		constexpr static size_t MaxCacheSize = 20;

		std::vector< Key > mCache;

//		std::unordered_map<Key, std::unique_ptr<Value> > mCacheMap;
		std::unordered_map<Key, std::shared_ptr<Value> > mCacheMap;

	public:
		Cache() {}

		bool HasItem(const Key& key) const
		{
			return mCacheMap.find(key) != mCacheMap.end();
		}

		std::shared_ptr<Value> GetItem(const Key& key)
		{
			std::shared_ptr<Value> item {};

			auto it = mCacheMap.find(key);
			if (it != mCacheMap.end())
			{
				item = it->second;

				auto it = std::find(begin(mCache), end(mCache), key);
				if (it != end(mCache))
				{
					mCache.erase(it);
					mCache.push_back(key);
				}
			}

			return item;
		}

		void AddItem(const Key& key, std::shared_ptr<Value> item)
		{
			mCache.emplace_back(key);
			mCacheMap[key] = std::move(item);

			if (mCache.size() > MaxCacheSize)
			{
				const auto& oldestKey = mCache.front();
				mCacheMap.erase(oldestKey);
				mCache.erase(mCache.begin());
			}
		}
	};

	/*
	using BitmapCache = Cache<std::string, core::bitmap::Bitmap>;

	void Test(void)
	{
		BitmapCache cache;

		auto bitmap = std::make_unique<core::bitmap::Bitmap>();
		auto bitmap2 = std::make_unique<core::bitmap::Bitmap>();

		cache.AddItem("test", bitmap);
		cache.AddItem("test2", bitmap2);

		cache.GetItem("test");
		cache.GetItem("test3");

		int i{};
	}
	*/
};
