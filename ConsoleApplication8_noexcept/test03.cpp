#include <stdlib.h>
#include <memory>
void g() ;
void f()
{
	char* const p1 = new char [128];//失敗すると std::bad_alloc 例外
	g();//ここで例外が投入されると delete [] p1; が実行されない --- leak 発生
	delete [] p1;
}
int main()
{
	f();
}
