/*
** EPITECH PROJECT, 2026
** Blackbox
** File description:
** SafeQueue
*/

#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <optional>

namespace blackbox
{

    /**
    * @brief A thread-safe queue.
    * @tparam T The type of elements stored in the queue.
    **/
    template <typename T>
    class SafeQueue
    {
        public:

            SafeQueue() = default;
            ~SafeQueue() = default;

            /**
            * @brief Push an element to the back of the queue.
            * @param value The element to push.
            **/
            void push(const T &value)
            {
                {
                    std::lock_guard<std::mutex> lock(_mutex);
                    _queue.push(value);
                }
                _condition.notify_one();
            }

            /**
            * @brief Pop an element from the front of the queue.
            * @return The popped element.
            **/
            std::optional<T> pop()
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _condition.wait(lock, [this] {
                    return !_queue.empty() || _stop;
                });

                if (_stop && _queue.empty())
                   return std::nullopt;
    
                T value = std::move(_queue.front());
                _queue.pop();
                return value;
            }

            /**
            * @brief Check if the queue is empty.
            * @return True if the queue is empty, false otherwise.
            **/
            bool empty() const
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _queue.empty();
            }

            /**
            * @brief Stop the queue and notify all waiting threads.
            **/
            void stop()
            {
                {
                    std::lock_guard<std::mutex> lock(_mutex);
                    _stop = true;
                }
                _condition.notify_all();
            }

        private:
            mutable std::mutex _mutex;
            std::queue<T> _queue;
            std::condition_variable _condition;
            bool _stop = false;
        };
}
