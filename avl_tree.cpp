

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream> 
#include <map>
#include <sstream>

using namespace std;

int n;
int s;
vector <int> l;
vector <int> r;
vector <int> t;
vector <int> h;
vector <int> b;
vector <int> p;
vector <int> num;
vector <int> numleft;
ifstream in;
ofstream out;
int root;

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int height(int a, int b) {
	int h1, h2;
	if (a == -1) {
		h1 = 0;
	}
	else {
		h1 = h[a] + 1;
	}
	if (b == -1) {
		h2 = 0;
	}
	else {
		h2 = h[b] + 1;
	}
	return max(h1, h2);

}

int balance(int i) {
	int b1, b2;
	if (l[i] == -1) {
		b1 = -1;
	}
	else {
		b1 = h[l[i]];
	}
	if (r[i] == -1) {
		b2 = -1;
	}
	else {
		b2 = h[r[i]];
	}
	return b2 - b1;

}

int left_turn(int root_local) {
	if (b[r[root_local]] == -1) {
		int A = root_local;
		int B = r[root_local];
		int W = l[root_local];
		int C = l[r[root_local]];
		int Z = r[r[root_local]];
		int X = l[l[r[root_local]]];
		int Y = r[l[r[root_local]]];

		num[B] = num[B] - numleft[B] + num[C] - numleft[C];
		numleft[B] = num[C] - numleft[C];
		num[C] = num[root_local];
		num[A] = numleft[A] + numleft[C];
		numleft[C] = numleft[A] + numleft[C] + 1;// Изменили количество потомков

		l[C] = A;
		r[C] = B;
		l[A] = W;
		r[A] = X;
		l[B] = Y;
		r[B] = Z;//Изменили ссылки на детей

		if (X>-1) p[X] = A;
		if (Y>-1) p[Y] = B;
		p[C] = p[A];
		p[A] = C;
		p[B] = C;
		//Изменили ссылки на родителей

		h[A] = height(W, X);
		h[B] = height(Y, Z);
		h[C] = height(A, B);//Изменили высоту

		b[A] = balance(A);
		b[B] = balance(B);
		b[C] = balance(C);// Изменили баланс

		if (p[C] != -1) {
			if (t[p[C]] > t[C]) {
				l[p[C]] = C;
			}
			else {
				r[p[C]] = C;
			}
		} //Поменяли ссылку на локальный корень

		if (root_local == root) {
			root = C;
		}// Если меняем баланс корня, меняем ссылку на корень
		return C;
	}
	else {
		int A = root_local;
		int X = l[root_local];
		int B = r[root_local];
		int Y = l[r[root_local]];
		int Z = r[r[root_local]];

		num[B] = num[root_local];
		num[A] = numleft[A] + numleft[B];// Изменили количество потомков
		numleft[B] = numleft[A] + numleft[B] + 1;


		l[B] = A;
		r[B] = Z;
		l[A] = X;
		r[A] = Y;//Изменили ссылки на детей

		if (Y>-1) p[Y] = A;
		p[B] = p[A];
		p[A] = B;
		// Изменили ссылки на родителей

		h[A] = height(X, Y);
		h[B] = height(A, Z);//Изменили высоту

		b[A] = balance(A);
		b[B] = balance(B); //Изменили баланс

		if (p[B] != -1) {
			if (t[p[B]] > t[B]) {
				l[p[B]] = B;
			}
			else {
				r[p[B]] = B;
			}
		} //Поменяли ссылку на локальный корень


		if (root_local == root) {
			root = B;
		}//Если меняем баланс корня, меняем ссылку на корень
		return B;
	}

}

int right_turn(int root_local) {
	if (b[l[root_local]] == 1) {
		int A = root_local;
		int B = l[root_local];
		int W = r[root_local];
		int C = r[l[root_local]];
		int Z = l[l[root_local]];
		int X = r[r[l[root_local]]];
		int Y = l[r[l[root_local]]];

		int num_root = num[A];
		num[B] = numleft[B] + numleft[C];
		num[A] = num[A] - numleft[A] + num[C] - numleft[C];
		numleft[A] = num[C] - numleft[C];
		num[C] = num_root;
		numleft[C] = numleft[B] + numleft[C] + 1;// Изменили количество потомков

		l[C] = B;
		r[C] = A;
		l[A] = X;
		r[A] = W;
		l[B] = Z;
		r[B] = Y;//Изменили ссылки на детей

		if (X>-1) p[X] = A;
		if (Y>-1) p[Y] = B;
		p[C] = p[A];
		p[A] = C;
		p[B] = C;
		//Изменили ссылки на родителей

		h[B] = height(Z, Y);
		h[A] = height(X, W);
		h[C] = height(B, A);//Изменили высоту

		b[A] = balance(A);
		b[B] = balance(B);
		b[C] = balance(C);// Изменили баланс

		if (p[C] != -1) {
			if (t[p[C]] > t[C]) {
				l[p[C]] = C;
			}
			else {
				r[p[C]] = C;
			}
		} //Поменяли ссылку на локальный корень


		if (root_local == root) {
			root = C;
		}// Если меняем баланс корня, меняем ссылку на корень
		return C;
	}
	else {
		int A = root_local;
		int X = r[root_local];
		int B = l[root_local];
		int Y = r[l[root_local]];
		int Z = l[l[root_local]];

		int num_root = num[A];
		num[A] = num[A] - numleft[A] + num[B] - numleft[B];
		numleft[A] = num[B] - numleft[B];
		num[B] = num_root;// Изменили количество потомков

		l[B] = Z;
		r[B] = A;
		l[A] = Y;
		r[A] = X;//Изменили ссылки на детей

		if (Y>-1) p[Y] = A;
		p[B] = p[A];
		p[A] = B;
		// Изменили ссылки на родителей

		h[A] = height(Y, X);
		h[B] = height(Z, A);//Изменили высоту

		b[A] = balance(A);
		b[B] = balance(B); //Изменили баланс

		if (p[B] != -1) {
			if (t[p[B]] > t[B]) {
				l[p[B]] = B;
			}
			else {
				r[p[B]] = B;
			}
		} //Поменяли ссылку на локальный корень


		if (root_local == root) {
			root = B;
		}//Если меняем баланс корня, меняем ссылку на корень
		return B;
	}

}

void check_tree(int root_local, int temp, char k) {
	h[root_local] = height(l[root_local], r[root_local]);
	b[root_local] = balance(root_local);
	num[root_local] = num[root_local] + temp;
	if (k == 'l') {
		numleft[root_local] = numleft[root_local] + temp;
	}
	if (b[root_local] == -2) {
		root_local = right_turn(root_local);
	}
	if (b[root_local] == 2) {
		root_local = left_turn(root_local);
	}
	if (p[root_local] != -1) {
		if (t[root_local] < t[p[root_local]]) check_tree(p[root_local], temp, 'l');
		else check_tree(p[root_local], temp, 'r');
	}
}

void add_elem(int root_local, int elem) {
	if (s == 0 || root_local == -1 || elem < t[root_local]){
		if (s == 0 || root_local == -1 || l[root_local] == -1) {
			t[n] = elem;
			if (s != 0) l[root_local] = n;
			if (s != 0) p[n] = root_local;
			else p[n] = -1;
			h[n] = 0;
			b[n] = 0;
			l[n] = -1;
			r[n] = -1;
			num[n] = 0;
			numleft[n] = 0;
			if (root_local == -1) {
				root = n;
			}
			if (s != 0) check_tree(root_local, 1, 'l');
			n++;
			s++;
		}
		else {
			add_elem(l[root_local], elem);
		}
	}
	else if (elem > t[root_local]) {
		if (r[root_local] == -1) {
			t[n] = elem;
			r[root_local] = n;
			p[n] = root_local;
			h[n] = 0;
			b[n] = 0;
			l[n] = -1;
			r[n] = -1;
			num[n] = 0;
			numleft[n] = 0;
			n++;
			s++;
			check_tree(root_local, 1, 'r');

		}
		else {
			add_elem(r[root_local], elem);
		}
	}
}

void del_elem(int root_local, int elem) {
	if (elem == t[root_local]) {
		s--;
		if (l[root_local] == -1 && r[root_local] == -1) {
			if (p[root_local] != -1) {
				if (t[root_local] < t[p[root_local]]) {
					l[p[root_local]] = -1;
					check_tree(p[root_local], -1, 'l');
				}
				else  {
					r[p[root_local]] = -1;
					check_tree(p[root_local], -1, 'r');
				}

			}
			else {
				root = -1;

			}

		}
		else if (l[root_local] == -1) {
			t[root_local] = t[r[root_local]];
			r[root_local] = -1;
			num[root_local]--;
			h[root_local] = 0;
			if (p[root_local] != -1) {
				if (t[root_local] < t[p[root_local]]) {
					check_tree(p[root_local], -1, 'l');
				}
				else  {
					check_tree(p[root_local], -1, 'r');
				}

			}
			else {
				root = root_local;
				b[root_local] = balance(root_local);

			}
		}

		else {
			int y = l[root_local];
			char k = 'l';
			while (r[y] > -1) {
				y = r[y];
				k = 'r';
			}
			t[root_local] = t[y];
			if (k == 'l') l[p[y]] = l[y];
			else r[p[y]] = l[y];
			if (l[y] != -1) {
				p[l[y]] = p[y];
			}
			if (p[root_local] == -1) root = root_local;
			check_tree(p[y], -1, k);
		}
	}
	else if (elem < t[root_local] && l[root_local] > -1) {
		del_elem(l[root_local], elem);
	}
	else if (elem > t[root_local] && r[root_local] > -1) {
		del_elem(r[root_local], elem);
	}
}
char find_elem(int root_local, int elem) {
	if (elem == t[root_local]) {
		return 'Y';
	}
	else if (elem < t[root_local] && l[root_local] != -1) {
		find_elem(l[root_local], elem);
	}
	else if (elem > t[root_local] && r[root_local] != -1) {
		find_elem(r[root_local], elem);
	}
	else {
		return 'N';
	}
}

void print_tree(int i, int k) {

	int li, ri;
	if (l[i] == -1){
		li = 0;
	}
	else {
		li = k;
	}
	if (r[i] == -1){
		ri = 0;
	}
	else {
		ri = k + numleft[i];
	}
	out << t[i] << " " << li << " " << ri << "\n";
	if (li) print_tree(l[i], li + 1);
	if (ri) print_tree(r[i], ri + 1);


}


int main()
{
	in.open("input.txt");
	out.open("output.txt");
	in >> n;
	l.resize(n + 1);
	r.resize(n + 1);
	t.resize(n + 1);
	h.resize(n + 1);
	b.resize(n + 1);
	p.resize(n + 1);
	num.resize(n + 1);
	numleft.resize(n + 1);

	int elem;
	int k = n;
	char o;
	n = 0;
	s = 0;
	root = 0;
	for (int i = 0; i < k; i++) {
		in >> o >> elem;
		if (o == 'A') {
			add_elem(root, elem);
			out << b[root] << "\n";
		}
		else if (o == 'D') {
			if (s == 0) out << "0\n";
			else {
				del_elem(root, elem);
				if (s == 0) out << "0\n";
				else out << b[root] << "\n";
			}
		}
		else {
			if (s == 0) out << "N\n";
			else out << find_elem(root, elem) << "\n";
		}


	}
	in.close();
	out.close();
	return 0;
}