#ifndef TASK_H
#define TASK_H

#include <utility>

template <typename T>
class Task {
    private:
        static int nextId;
        int id;
        int startTime;
        int duration;
        int endTime;
        T item;
    
    public:
        Task(int startTime, int duration, T item) {
            this->startTime = startTime;
            this->duration = duration;
            endTime = startTime + duration;
            this->item = std::move(item);
            this->id = nextId++;
        }

        Task() {
            this->id = nextId++;
        }

        template <typename Executor>
        void execute(Executor& executor) {
            item->execute(executor);
        }

};

template <typename T>
int Task<T>::nextId = 1;



#endif
