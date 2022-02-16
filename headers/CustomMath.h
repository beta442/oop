template <typename Type1, typename Type2>
Type1 ipow(Type1 a, Type2 ex)
{
	if (0 == ex)
		return 1;
	else
	{
		Type1 z = a;
		Type1 y = 1;
		while (1)
		{
			if (ex & 1)
				y *= z;
			ex /= 2;
			if (0 == ex)
				break;
			z *= z;
		}
		return y;
	}
}
