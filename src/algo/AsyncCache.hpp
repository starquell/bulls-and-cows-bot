#pragma once

#include <map>
#include <mutex>

namespace game::algo {

    template <typename Key,
              typename Value>
    class AsyncCache {

    private:
        explicit AsyncCache() = default;

    public:
        AsyncCache(const AsyncCache &) = delete;
        AsyncCache(AsyncCache &&) = delete;

        AsyncCache& operator= (const AsyncCache&) = delete;
        AsyncCache& operator= (AsyncCache&&) = delete;

        static auto get() -> AsyncCache&
        {
            static AsyncCache _instance;
            return _instance;
        }

        auto operator[](const Key& key) ->  Value&
        {
            std::lock_guard guard {_mut};
            return _map[key];
        }

        auto contains(const Key& key) const -> bool
        {
            std::lock_guard guard {_mut};
            return _map.contains(key);
        }

    private:
        std::map<Key, Value> _map;
        mutable std::mutex _mut;
    };
}



