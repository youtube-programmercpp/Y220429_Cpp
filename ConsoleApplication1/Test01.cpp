#include <map>
#include <string>
#include <iostream>
int main()
{
	std::map<std::string, int> m;

	//�f�[�^�̒ǉ�
	m["zero" ] = 0;
	m["one"  ] = 1;
	m["two"  ] = 2;
	m["three"] = 3;
	//�f�[�^�̈����o��
	auto it = m.find("four");
	if (it == m.end()) {
		//�Y������
		std::cout << "�Y���Ȃ�\n";
	}
	else {
		//�Y������
		std::cout << it->second << '\n';

	}


}
