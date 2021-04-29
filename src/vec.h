#ifndef VEC
#define VEC

struct Vec {
  double v[3];
  Vec(){
    v[0] = v[1] = v[2] = 0.;
  }
  Vec(int x, int y, int z) {
    v[0] = x; v[1] = y; v[2] = z;
  }
  double& operator[](int i) {
    return v[i];
  }
  const double& operator[](int i) const {
    return v[i];
  }
  Vec operator+(const Vec& a) const {
    return Vec(a[0]+v[0], a[1]+v[1], a[2]+v[2]);
  }
  Vec operator-() const {
    return Vec(-v[0], -v[1], -v[2]);
  }
  Vec operator-(const Vec& a) const {
    return Vec(a[0]-v[0], a[1]-v[1], a[2]-v[2]);
  }
  Vec operator*(const double& a) const {
    return Vec(a*v[0], a*v[1], a*v[2]);
  }
  Vec operator/(const double& a) const {
    return Vec(v[0]/a, v[1]/a, v[2]/a);
  }
  double operator*(const Vec& a) const {
    return a[0]*v[0] + a[1]*v[1] + a[2]*v[2];
  }
};

#endif
