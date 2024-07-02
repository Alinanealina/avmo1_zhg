#include <iostream>
using namespace std;
const int N = 4, M = 5;
class s_fract {
	friend bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f);
protected:
	int a, b;
public:
	s_fract(int x, int y);
	void print();
	void sum(s_fract fr1, s_fract fr2);
	void diff(s_fract fr1, s_fract fr2);
	void mult(s_fract fr1, s_fract fr2);
	void div(s_fract fr1, s_fract fr2);
	void red();
	bool eq0();
};
s_fract::s_fract(int x = 0, int y = 1)
{
	if (y > 0)
	{
		a = x;
		b = y;
		red();
	}
	else if (y < 0)
	{
		a = -x;
		b = -y;
		red();
	}
	else
	{
		a = 0;
		b = 0;
	}
}
void s_fract::print()
{
	if ((b != 0) && (b != 1))
		cout << a << "/" << b;
	else if ((b != 0) && (b == 1))
		cout << a;
	else
		cout << INFINITY;
}
void s_fract::sum(s_fract fr1, s_fract fr2)
{
	s_fract obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	if (fr1.b < fr2.b)
	{
		obm = fr1;
		fr1 = fr2;
		fr2 = obm;
	}

	if (fr1.b == fr2.b)
	{
		a = fr1.a + fr2.a;
		b = fr1.b;
	}
	else if (fr1.b % fr2.b != 0)
	{
		a = fr1.a * fr2.b + fr2.a * fr1.b;
		b = fr1.b * fr2.b;
	}
	else if (fr1.b % fr2.b == 0)
	{
		a = fr1.a + fr2.a * (fr1.b / fr2.b);
		b = fr1.b;
	}
	if (eq0())
		b = 1;
	red();
}
void s_fract::diff(s_fract fr1, s_fract fr2)
{
	fr2.a *= -1;
	sum(fr1, fr2);
}
void s_fract::mult(s_fract fr1, s_fract fr2)
{
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	a = fr1.a * fr2.a;
	b = fr1.b * fr2.b;
	if (eq0())
		b = 1;
	red();
}
void s_fract::div(s_fract fr1, s_fract fr2)
{
	int obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	obm = fr2.a;
	fr2.a = fr2.b;
	fr2.b = obm;
	if (fr2.b < 0)
	{
		fr2.a *= -1;
		fr2.b *= -1;
	}
	mult(fr1, fr2);
}
void s_fract::red()
{
	int x, y, obm;
	if ((a == 0) || (b == 0))
		return;
	for (x = abs(a), y = abs(b); x != y; y -= x)
	{
		if (x > y)
		{
			obm = x;
			x = y;
			y = obm;
		}
	}
	a /= x;
	b /= x;
}
bool s_fract::eq0()
{
	if ((a == 0) && (b != 0))
		return true;
	else
		return false;
}



bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f = false)
{
	int t;
	if ((fr1.b == 0) || (fr2.b == 0))
		return false;

	if (f)
	{
		fr1.a = abs(fr1.a);
		fr2.a = abs(fr2.a);
	}

	if (((fr1.b > fr2.b) && (fr1.b % fr2.b != 0)) || ((fr1.b <= fr2.b) && (fr2.b % fr1.b != 0)))
	{
		t = fr1.b;
		fr1.a *= fr2.b;
		fr1.b *= fr2.b;
		fr2.a *= t;
		fr2.b *= t;
	}
	else if ((fr1.b > fr2.b) && (fr1.b % fr2.b == 0))
	{
		fr2.a *= (fr1.b / fr2.b);
		fr2.b = fr1.b;
	}
	else if ((fr1.b <= fr2.b) && (fr2.b % fr1.b == 0))
	{
		fr1.a *= (fr2.b / fr1.b);
		fr1.b = fr2.b;
	}

	if (fr1.a > fr2.a)
		return true;
	else
		return false;
}

void print_m(s_fract A[N][M + 1])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= M; j++)
		{
			cout << "\t";
			A[i][j].print();
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	bool fl;
	int i, j, k, j2, f[N] = { 0 };
	s_fract A[N][M + 1] =
	{
		/*s_fract(1), s_fract(1), s_fract(0), s_fract(1),			// 1
		s_fract(0), s_fract(0), s_fract(0), s_fract(1),
		s_fract(1), s_fract(1), s_fract(1), s_fract(1),

		s_fract(1), s_fract(1), s_fract(0), s_fract(0),			// 2
		s_fract(0), s_fract(1), s_fract(1), s_fract(0),
		s_fract(0), s_fract(0), s_fract(0), s_fract(0),

		s_fract(1), s_fract(1), s_fract(0), s_fract(1),			// 1a
		s_fract(1), s_fract(1), s_fract(0), s_fract(2),
		s_fract(1), s_fract(1), s_fract(1), s_fract(1),

		s_fract(1), s_fract(1), s_fract(1),			// 3
		s_fract(0), s_fract(1), s_fract(0),

		s_fract(1), s_fract(1), s_fract(1), s_fract(1),			// 4
		s_fract(0), s_fract(0), s_fract(1), s_fract(2),
		s_fract(0), s_fract(1), s_fract(1), s_fract(3),

		s_fract(0), s_fract(2), s_fract(1), s_fract(1),			// 5
		s_fract(1), s_fract(1), s_fract(1), s_fract(3),
		s_fract(0), s_fract(1), s_fract(1), s_fract(1),*/



		/*s_fract(2), s_fract(-3), s_fract(5), s_fract(7), s_fract(1),
		s_fract(4), s_fract(-6), s_fract(2), s_fract(3), s_fract(2),
		s_fract(2), s_fract(-3), s_fract(-11), s_fract(-15), s_fract(1),

		s_fract(4), s_fract(-17), s_fract(-6), s_fract(-5), s_fract(-17),
		s_fract(43), s_fract(24), s_fract(-1), s_fract(3), s_fract(28),
		s_fract(0), s_fract(1), s_fract(2), s_fract(1), s_fract(9),
		s_fract(2), s_fract(1), s_fract(0), s_fract(0), s_fract(1),

		s_fract(1), s_fract(3), s_fract(0), s_fract(1),
		s_fract(2), s_fract(0), s_fract(-3), s_fract(2),*/

		s_fract(2), s_fract(-1), s_fract(1), s_fract(2), s_fract(3), s_fract(2),
		s_fract(6), s_fract(-3), s_fract(2), s_fract(4), s_fract(5), s_fract(3),
		s_fract(6), s_fract(-3), s_fract(4), s_fract(8), s_fract(13), s_fract(9),
		s_fract(4), s_fract(-2), s_fract(1), s_fract(1), s_fract(2), s_fract(1),
	}, X[M], t, t2;
	print_m(A);

	for (i = 0; i < N; i++)
	{
		cout << "\n " << i << " строка:";

		fl = false;
		for (j2 = i; j2 < M; j2++)
		{
			for (j = i; j < N; j++)
			{
				if (!A[j][j2].eq0())
				{
					fl = true;
					break;
				}
			}
			if (fl)
				break;
		}
		if (j2 == M)
		{
			if (!A[i][M].eq0())
			{
				cout << "\n______________________\n Решений нет.";
				return 0;
			}
		}

		for (j = i + 1, k = i; j < N; j++)
		{
			if (fr1_gr_fr2(A[j][j2], A[k][j2], true))
				k = j;
		}
		if (k != i)
		{
			for (j = 0; j <= M; j++)
			{
				t = A[i][j];
				A[i][j] = A[k][j];
				A[k][j] = t;
			}
			cout << "\n (обмен строк)\n ~";
			print_m(A);
		}

		t = A[i][j2];
		for (j = 0; j <= M; j++)
			A[i][j].div(A[i][j], t);
		cout << "\n (1 в диагонали)\n ~";
		print_m(A);

		for (j = 0; j < N; j++)
		{
			if ((i == j) || (A[j][j2].eq0()))
				continue;
			t.diff(s_fract(0), A[j][j2]);
			for (k = 0; k <= M; k++)
			{
				t2.mult(t, A[i][k]);
				A[j][k].sum(A[j][k], t2);
			}
		}
		cout << "\n (нули)\n ~";
		print_m(A);
	}



	cout << "______________________" << endl;
	for (i = 0, k = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (!A[i][j].eq0())
				f[i]++;
		}
	}
	for (i = 0, k = 0; i < N; i++)
	{
		if (f[i] > 0)
			X[k++] = A[i][M];
	}

	if (k == M)
	{
		for (i = 0; i < M; i++)
		{
			cout << "\nx" << i << " = ";
			X[i].print();
		}
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			if (f[i] != 0)
			{
				for (j = 0; j < M; j++)
				{
					if (!A[i][j].eq0())
						break;
				}
				cout << "\nx" << j << " = ";
				X[i].print();
			}
			if (f[i] > 1)
			{
				for (j = M - 1; f[i] > 1; j--)
				{
					if (A[i][j].eq0())
						continue;

					if (fr1_gr_fr2(A[i][j], s_fract(0)))
						cout << " - ";
					else
					{
						A[i][j].mult(A[i][j], s_fract(-1));
						cout << " + ";
					}
					A[i][j].print();
					cout << "(x" << j << ")";
					f[i]--;
				}
			}
		}
	}
	return 0;
}