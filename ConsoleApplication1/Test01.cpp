#include <map>
#include <string>
#include <iostream>
int main()
{
	std::map<std::string, int> m;

	//データの追加
	m["zero" ] = 0;
	m["one"  ] = 1;
	m["two"  ] = 2;
	m["three"] = 3;
	//データの引き出し
	auto it = m.find("four");
	if (it == m.end()) {
		//該当無し
		std::cout << "該当なし\n";
	}
	else {
		//該当あり
		std::cout << it->second << '\n';

	}


}
