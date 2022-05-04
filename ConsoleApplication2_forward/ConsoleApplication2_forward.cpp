#include "move.h"
#include "forward.h"
int main()
{
	move::test_lambda_copy_capture();
	forward::test_lambda_copy_capture();
#if 0
	move::test_lval();
#endif
	forward::test_lval();
}
