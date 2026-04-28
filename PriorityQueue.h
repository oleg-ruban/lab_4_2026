#include <vector>
#include "Student.h"

class PriorityQueue
{
private:
    std::vector<Student> heap;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index].avgGrade > heap[parent].avgGrade)
            {
                // Max-Heap за балом
                std::swap(heap[index], heap[parent]);
                index = parent;
            }
            else break;
        }
    }

    void heapifyDown(int index)
    {
        int maxIndex = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left].avgGrade > heap[maxIndex].avgGrade) maxIndex = left;
        if (right < heap.size() && heap[right].avgGrade > heap[maxIndex].avgGrade) maxIndex = right;

        if (index != maxIndex)
        {
            std::swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    void push(Student s)
    {
        heap.push_back(s);
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    Student top() { return heap[0]; }
    bool empty() { return heap.empty(); }
    size_t size() { return heap.size(); }
};
