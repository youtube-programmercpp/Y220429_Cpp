#include <stdlib.h>
#include <memory>
void g() ;
void f()
{
	char* const p1 = new char [128];//���s����� std::bad_alloc ��O
	g();//�����ŗ�O������������ delete [] p1; �����s����Ȃ� --- leak ����
	delete [] p1;
}
int main()
{
	f();
}
