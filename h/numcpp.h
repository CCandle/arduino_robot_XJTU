#ifndef NUMCPP
#define NUMCPP

template<typename T>
class Matrix {
private:
	T** val;
	int x_length, y_length;
public:
	inline void CopyMatrix(const Matrix& x) {
		if (this->val != NULL) {
			for (int i = 0; i < this->x_length; ++i) delete[] this->val[i];
			delete[] this->val;
		}
		this->x_length = x.x_length, this->y_length = x.y_length;
		val = new T* [this->x_length];
		for (int i = 0; i < this->x_length; ++i) this->val[i] = new T[this->y_length];
	}
	Matrix() { val = NULL, x_length = 0, y_length = 0; }
	Matrix(int X, int Y) {
		this->val = new T* [X];
		for (int i = 0; i < X; ++i) this->val[i] = new T[Y];
		this->x_length = X, this->y_length = Y;
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) this->val[i][j] = 0.0;
		}
	}
	Matrix(int X, int Y, const char type) {
		this->val = new T* [X];
		for (int i = 0; i < X; ++i) this->val[i] = new T[Y];
		this->x_length = X, this->y_length = Y;
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) this->val[i][j] = 0.0;
		}
		switch (type) {
		case 'I':
			for (int i = 0; i < min(X, Y); ++i) this->val[i][i] = (T) 1.0;
			break;
		}//To be continued...
	}
	Matrix(const Matrix& x) {
		this->x_length = x.x_length, this->y_length = x.y_length;
		val = new T* [this->x_length];
		for (int i = 0; i < this->x_length; ++i) this->val[i] = new T[this->y_length];
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) this->val[i][j] = x.val[i][j];
		}
	}
	Matrix& operator = (const Matrix& x) {
		if (&x == this) return *this;
		if ((this->x_length != x.x_length) || (this->y_length != x.y_length)) CopyMatrix(x);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) this->val[i][j] = x.val[i][j];
		}
		return *this;
	}
	~Matrix() {
		if (this->val == NULL) return;
		for (int i = 0; i < this->x_length; ++i) delete[] this->val[i];
		delete[] this->val;
	}
	inline int GetX() { return this->x_length; }
	inline int GetY() { return this->y_length; }
	inline bool IsNULL() { return (this->x_length | this->y_length) == 0; }
	inline bool IsSquare() { return (this->x_length ^ this->y_length) == 0; }
	inline void Show() {
		if ((!this->x_length) && (!this->y_length)) {
			std::puts("The matrix is empty.");
			return;
		}
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) {
				std::cout << std::fixed << std::setprecision(6) << this->val[i][j] << " ";
			}
			std::puts("");
		}
	}
	inline void Init() {
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) std::cin >> this->val[i][j];
		}
	}
	inline void Init(int X, int Y, T Value) { this->val[X][Y] = Value; }
	Matrix Inverse() {
		Matrix X0 = Matrix(*this);
		Matrix X1 = Matrix(this->x_length, this->y_length, 'I');
		for (int i = 0; i < this->x_length; ++i) {
			if (std::fabs(X0.val[i][i]) < EPS) {
				int pos = 0;
				for (int j = i + 1; j < this->x_length; ++j) {
					if (fabs(this->val[j][i]) > EPS) { pos = j; break; }
				}
				for (int j = 0; j < this->x_length; ++j) {
					std::swap(X0.val[i][j], X0.val[pos][j]);
					std::swap(X1.val[i][j], X1.val[pos][j]);
				}
			}
			T tmp = X0.val[i][i];
			for (int j = 0; j < this->y_length; ++j) X0.val[i][j] /= tmp, X1.val[i][j] /= tmp;
			for (int j = i + 1; j < this->x_length; ++j) {
				tmp = X0.val[j][i];
				for (int k = 0; k < this->y_length; ++k) {
					X0.val[j][k] = X0.val[j][k] - X0.val[i][k] * tmp;
					X1.val[j][k] = X1.val[j][k] - X1.val[i][k] * tmp;
				}
			}
		}
		for (int i = this->x_length - 1; i; --i) {
			for (int j = i - 1; ~j; --j) {
				for (int k = 0; k < this->x_length; ++k) X1.val[j][k] -= X1.val[i][k] * X0.val[j][i];
			}
		}
		return X1;
	}
	Matrix T() {
		Matrix X0 = Matrix(this->y_length, this->x_length);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) X0.val[j][i] = this->val[i][j];
		}
		return X0;
	}
	int Rank() {
		int res = 0, pre = -1;
		Matrix X0 = Matrix(*this);
		for (int i = 0; i < X0.x_length; ++i) {
			int pos = -1;
			while ((!(~pos)) && (pre < X0.y_length)) {
				++pre;
				for (int j = i; j < X0.x_length; ++j) {
					if (fabs(X0.val[j][pre]) > EPS) { pos = j; break; }
				}
			}
			if (!(~pos)) return res;
			++res;
			if (i != pos) {
				for (int j = 0; j < X0.y_length; ++j) std::swap(X0.val[i][j], X0.val[pos][j]);
			}
			for (int j = X0.y_length - 1; j >= pre; --j) X0.val[i][j] /= X0.val[i][pre];
			for (int j = i + 1; j < X0.x_length; ++j) {
				T tmp = X0.val[j][pre];
				for (int k = pre; k < X0.y_length; ++k) X0.val[j][k] -= tmp * X0.val[i][k];
			}
		}
		return res;
	}
	T Det() {
		T res = 1.0;
		Matrix X0 = Matrix(*this);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = i + 1; j < this->y_length; ++j) {
				if (std::fabs(X0.val[i][i]) < EPS) {
					int pos = -1;
					for (int k = i + 1; k < this->x_length; ++k) {
						if (std::fabs(X0.val[k][i]) > EPS) { pos = k; break; }
					}
					if (~pos) {
						for (int k = 0; k < this->x_length; ++k) std::swap(X0.val[i][k], X0.val[pos][k]);
						res *= -1.0;
					}
					else return (res = 0);
				}
				T f = X0.val[j][i] / X0.val[i][i];
				for (int k = i; k < this->x_length; ++k) X0.val[j][k] -= X0.val[i][k] * f;
			}
		}
		for (int i = 0; i < x_length; ++i) res *= X0.val[i][i];
		return res;
	}
	Matrix operator + (const Matrix& x) const {
		Matrix res = Matrix(this->x_length, this->y_length);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) {
				res.val[i][j] = this->val[i][j] + x.val[i][j];
			}
		}
		return res;
	}
	Matrix operator - (const Matrix& x) const {
		Matrix res = Matrix(this->x_length, this->y_length);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) {
				res.val[i][j] = this->val[i][j] - x.val[i][j];
			}
		}
		return res;
	}
	Matrix operator * (const Matrix& x) const {
		Matrix res = Matrix(this->x_length, x.y_length);
		for (int i = 0; i < this->x_length; ++i) {
			for (int j = 0; j < this->y_length; ++j) {
				res.val[i][j] = 0;
				for (int k = 0; k < this->y_length; ++k) {
					res.val[i][j] += this->val[i][k] * x.val[k][j];
				}
			}
		}
		return res;
	}
};

#endif
