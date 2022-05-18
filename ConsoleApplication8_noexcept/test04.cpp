struct sample {
	sample(sample&& r) noexcept
	{
	}
	sample& operator=(sample&& r) noexcept
	{
		return *this;
	}
	sample() 
	{
	}
};
int main()
{
	sample x;
}

