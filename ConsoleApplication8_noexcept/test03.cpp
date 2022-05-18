#include <stdlib.h>
#include <memory>
void g() ;
void f()
{
	char* const p1 = new char [128];//¸”s‚·‚é‚Æ std::bad_alloc —áŠO
	g();//‚±‚±‚Å—áŠO‚ª“Š“ü‚³‚ê‚é‚Æ delete [] p1; ‚ªÀs‚³‚ê‚È‚¢ --- leak ”­¶
	delete [] p1;
}
int main()
{
	f();
}
