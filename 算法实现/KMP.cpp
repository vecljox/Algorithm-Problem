视频讲解：https://www.bilibili.com/video/BV18k4y1m7Ar/?spm_id_from=333.337.search-card.all.click&vd_source=bcb9b8ebc5b9cb280e0f82d40bbf59a0
文字讲解：https://yuhi.xyz/post/KMP-%E7%AE%97%E6%B3%95%E8%AF%A6%E8%A7%A3/

S：主串
P：模式串
时间复杂度：O(|S|+|P|)
空间复杂度：O(|P|)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class KMP {
public:
	// 方法：查找所有匹配位置
	vector<int> findAllOccurrences(string s, string p) {
		vector<int> result;
		int m = s.size(), n = p.size();

		// if (n == 0) {
		// 	// 如果模式串为空，根据需求决定返回什么。
		// 	// 这里我们返回所有可能的起始位置。
		// 	for (int i = 0; i <= m; ++i) {
		// 		result.push_back(i);
		// 	}
		// 	return result;
		// }

		// 构建部分匹配表（next 数组）
		vector<int> next(n, 0);
		for (int i = 1, j = 0; i < n; ++i) {
			while (j > 0 && p[i] != p[j])
				j = next[j - 1];
			if (p[i] == p[j])
				++j;
			next[i] = j;
		}

		// 进行字符串匹配
		for (int i = 0, j = 0; i < m; ++i) {
			while (j > 0 && s[i] != p[j])
				j = next[j - 1];
			if (s[i] == p[j])
				++j;
			if (j == n) {
				// 匹配成功后的逻辑
				result.push_back(i - n + 1);
				// 继续查找下一个匹配，使用 next[j-1] 以避免遗漏可能的重叠匹配
				j = next[j - 1];
			}
		}

		return result;
	}
};

// 辅助函数，用于测试单个用例
void testFindAllOccurrences(const string& haystack, const string& needle, const vector<int>& expected) {
	KMP kmp;
	vector<int> result = kmp.findAllOccurrences(haystack, needle);

	// 打印测试用例
	cout << "Haystack: \"" << haystack << "\", Needle: \"" << needle << "\"\n";
	cout << "Expected: [";
	for (size_t i = 0; i < expected.size(); ++i) {
		cout << expected[i];
		if (i != expected.size() - 1) cout << ", ";
	}
	cout << "], Got: [";
	for (size_t i = 0; i < result.size(); ++i) {
		cout << result[i];
		if (i != result.size() - 1) cout << ", ";
	}
	cout << "]";

	// 比较结果
	if (result == expected) {
		cout << " --> Pass\n";
	}
	else {
		cout << " --> Fail\n";
	}
	cout << "-----------------------------\n";
}

int main() {
	// 测试用例1：普通匹配
	testFindAllOccurrences("hello", "ll", { 2 });

	// 测试用例2：needle 不存在
	testFindAllOccurrences("aaaaa", "bba", {});

	// 测试用例3：needle 为空字符串
	// 根据实现，我们返回所有可能的起始位置
	testFindAllOccurrences("anystring", "", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	// 测试用例4：haystack 为空字符串
	testFindAllOccurrences("", "a", {});

	// 测试用例5：haystack 和 needle 相同
	testFindAllOccurrences("abc", "abc", { 0 });

	// 测试用例6：haystack 中有多个匹配的位置
	testFindAllOccurrences("ababababca", "abababca", { 2 });

	// 测试用例7：匹配在字符串末尾
	testFindAllOccurrences("abcde", "de", { 3 });

	// 测试用例8：匹配在字符串开始
	testFindAllOccurrences("abcdef", "abc", { 0 });

	// 测试用例9：部分匹配但最终不匹配
	testFindAllOccurrences("ababcababaad", "ababaac", {});

	// 测试用例10：整个 haystack 是重复的字符
	testFindAllOccurrences("aaaaaa", "aaa", { 0, 1, 2, 3 });

	// 测试用例11：重叠匹配
	testFindAllOccurrences("aaaaa", "aa", { 0, 1, 2, 3 });

	// 测试用例12：包含特殊字符
	testFindAllOccurrences("a!a!a!a!", "!a!", { 1, 3, 5 });

	// 测试用例13：模式串大于主串
	testFindAllOccurrences("short", "longerpattern", {});

	// 测试用例14：模式串在主串中多次重复但不重叠
	testFindAllOccurrences("abcabcabc", "abc", { 0, 3, 6 });

	// 测试用例15：模式串为整个主串的多个重复
	testFindAllOccurrences("ababab", "abab", { 0, 2 });

	return 0;
}
