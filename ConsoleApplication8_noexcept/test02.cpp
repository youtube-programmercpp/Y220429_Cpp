#include <stdlib.h>

void f();
int main()
{
	void* const p1 = malloc(128);
	if (p1) {
		void* const p2 = malloc(128);
		if (p2) {
			f();
			//p1 と p2 を使う処理
			free(p2);
		}
		free(p1);
	}
}
