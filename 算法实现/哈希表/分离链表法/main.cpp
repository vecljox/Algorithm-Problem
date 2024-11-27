#include "SeparateChaining.h"
#include <iostream>
#include <string>

int main()
{
    // 创建一个哈希表，初始大小为101
    HashTable<std::string> hashTable(101);

    // 插入一些元素
    hashTable.insert("apple");
    hashTable.insert("banana");
    hashTable.insert("cherry");

    // 查找元素
    std::cout << "Contains 'apple': " << (hashTable.contains("apple") ? "true" : "false") << std::endl;
    std::cout << "Contains 'banana': " << (hashTable.contains("banana") ? "true" : "false") << std::endl;
    std::cout << "Contains 'grape': " << (hashTable.contains("grape") ? "true" : "false") << std::endl;

    // 删除元素
    hashTable.remove("banana");
    std::cout << "Contains 'banana' after removal: " << (hashTable.contains("banana") ? "true" : "false") << std::endl;

    // 再次插入删除的元素
    hashTable.insert("banana");

    // 测试清空哈希表
    hashTable.makeEmpty();
    std::cout << "Contains 'apple' after makeEmpty: " << (hashTable.contains("apple") ? "true" : "false") << std::endl;

    return 0;
}
