#include<cmath>
#include<cstring>

class Distance{
	private:
		double Dis[4];
		
	public:
		Distance(){ std::memset(Dis,0,sizeof(Dis)); }
		
		inline double Get(int x){ return Dis[x]; }
		
		inline void Set(int x,double y){ Dis[x]=y; }
};

class Vector{
	private:
		double x,y,z;
	
	public:
		Vector(double X,double Y,double Z){ x=X,y=Y,z=Z; }
		
		Vector operator + (const Vector &r) const{
			return Vector(x+r.x,y+r.y,z+r.y);
		}
		
		vector operator - (const Vector &r) const{
			return Vector(x-r.x,y-r.y,z-r.y);
		}
};

class Calculator{
	private:
		double C,L;
		Vector FixPoint[4];
		
	public:
		Calculator(){ C=0,L=0; }
		
		Calculator(double c,double l){	
			C=c,L=l;
			//double TempR=2*std::sqrt(6)*C/3;
			FixPoint[0]=Vector(0,0,C);
			FixPoint[1]=Vector(std::sqrt(2)*C/3,-(std::sqrt(6)*C/3),-(C/3));
			FixPoint[2]=Vector(std::sqrt(2)*C/3,std::sqrt(6)*C/3,-(C/3));
			FixPoint[3]=Vector(-(2*std::sqrt(2)*C/3),0,-(C/3));
		}
		
		inline void solve(int x,int y){
			
		}//??????
};
