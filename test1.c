int f()
{
	int x;
	x = 7777;
	*(&x + 2) = f;
	printf ("this is f\n");
	return x;
}

int main()
{
	f();
	return 0;
}
