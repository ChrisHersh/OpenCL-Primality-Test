long power(long a, long n, long mod)
{
	long power = a;
	long result = 1;

	while (n)
	{
		if (n & 1)
			result = (result * power) % mod;
		power = (power * power) % mod;
		n >>= 1;
	}
	return result;
}

int witness(long n, long s, long d, long a)
{
	long x = power(a, d, n);
	long y;

	while (s) {
		y = (x * x) % n;
		if (y == 1 && x != 1 && x != n - 1)
			return 0;
		x = y;
		--s;
	}
	if (y != 1)
		return 0;
	return 1;
}

int is_prime_mr(long n)
{
	if (((!(n & 1)) && n != 2) || (n < 2) || (n % 3 == 0 && n != 3))
		return 0;
	if (n <= 3)
		return 1;

	long d = n / 2;
	long s = 1;
	while (!(d & 1)) {
		d /= 2;
		++s;
	}

	if (n < 1373653)
		return witness(n, s, d, 2) && witness(n, s, d, 3);
	if (n < 9080191)
		return witness(n, s, d, 31) && witness(n, s, d, 73);
	if (n < 4759123141)
		return witness(n, s, d, 2) && witness(n, s, d, 7) && witness(n, s, d, 61);
	if (n < 1122004669633)
		return witness(n, s, d, 2) && witness(n, s, d, 13) && witness(n, s, d, 23) && witness(n, s, d, 1662803);
	if (n < 2152302898747)
		return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
	if (n < 3474749660383)
		return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13);
	return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17);
}

__kernel void duparray(__global long *in, __global long *out )
{
	int id = get_global_id(0);

	// if(id == 1)
	// {
	// 	int i = 0;
	// 	for(i = 0; i <= 200; i++)
	// 	{
	// 		printf("%d\t", in[i]);
	// 	}
	// }

	//printf("%d :: %d :: %d\t\t",id, in[id], is_prime_mr(in[id]));
	out[id] = (is_prime_mr(in[id]) == 0) ? 0 : in[id];
	//printf("%d :: %d :: %d\t\t",id, in[id], is_prime_mr(in[id]));
	//out[id] = in[id];
}
