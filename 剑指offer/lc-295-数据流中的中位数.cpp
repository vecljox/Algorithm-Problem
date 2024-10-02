//大堆和小堆
class MedianFinder {
public:
    priority_queue<int> queMax;
    priority_queue<int, vector<int>, greater<int>> queMin;
    MedianFinder() {
        queMax.push(INT_MIN);
        queMin.push(INT_MAX);
    }

    void addNum(int num) {
        if (num <= queMin.top()) {
            queMax.push(num);
            if (queMax.size() == queMin.size() + 2) {
                queMin.push(queMax.top());
                queMax.pop();
            }
        } else {
            queMin.push(num);
            if (queMin.size() > queMax.size()) {
                queMax.push(queMin.top());
                queMin.pop();
            }
        }
    }

    double findMedian() {
        if (queMax.size() == queMin.size())
            return double(queMax.top() + queMin.top()) / 2;

        return queMax.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */


// 有序集合
class MedianFinderB {
    multiset<int> nums;
    multiset<int>::iterator left;
    multiset<int>::iterator right;

public:
    MedianFinder() {}

    void addNum(int num) {
        int n = nums.size();
        nums.insert(num);
        if (!n) {
            left = nums.begin();
            right = nums.begin();
        } else if (n & 1) {
            if (num >= *right)
                ++right;
            else
                --left;
        } else {
            if (num >= *left && num < *right) {
                ++left;
                --right;
            } else if (num >= *right)
                ++left;

            else
                --right;
        }
    }

    double findMedian() { return (*left + *right) / 2.0; }
};
