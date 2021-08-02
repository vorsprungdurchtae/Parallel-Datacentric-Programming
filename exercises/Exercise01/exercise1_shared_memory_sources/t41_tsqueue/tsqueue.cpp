#include <queue>
#include <mutex>

template <typename T>
class threadsafe_queue
{
    private:
        std::queue<T> data;
        std::mutex mut;
        std::condition_variable cond;

    public:
        threadsafe_queue() {}
        threadsafe_queue(threadsafe_queue const& other)
        {
            std::lock_guard<std::mutex> lk(other.mut);
            data = other.data;
        }

        void push(T new_val)
        {
            std::lock_guard<std::mutex> lk(mut);
            data.push(new_val);
            cond.notify_one();
        }

        void wait_and_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(mut);
            cond.wait(lk, [this]{return !data.empty();} );
            value = data.front();
            data.pop();
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data.empty();
        }
};


int main() {
    return 0;
}
