template<int x>struct Sample;

template<>struct Sample<1> {
	int a;
	int b;
};
template<>struct Sample<2> {
	int a;
	int b;
	int c;
};
int main()
{
	Sample<1> alpha;
	Sample<2> beta;
}
