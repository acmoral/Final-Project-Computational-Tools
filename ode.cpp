#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<random>
#include<cmath>
//constantes del problema//
const double C= 1.0;
const double g_k= 36.0;
const double g_Na=120.0;
const double g_l=0.3;
const double v_k=-77;
const double v_Na=50;
const double v_l=54.387;

void euler(double ta, double tb, double h, std::vector<double> &y,std::vector<double> &x);//metodo de euler para hallar a v,m,n y h
double f(double t, const std::vector<double> & y, int id,const std::vector<double> &x);//las derivadas
void init_x(std::vector<double> &x,const std::vector<double> &y );//asigna condiciones iniciales a x(alpha_n,beta_n...) con base en V(0)
void init_y( std::vector<double> &y);//asigna condiciones iniciales aleatorias a y(V,n,m,h,I)
int main (void)
{ 
  const double t=0.0;/*tiempo inicial*/
  const double tf= 50.0;/*tiempo final*/
  const double time_step =0.001;//delta de tiempo
  std::vector<double> y(5);
  std::vector<double> x(6);
  init_y(y);
  init_x(x,y);/*parametros alpha y beta*/
  
  euler(t,tf,time_step,y,x);
  return 0;
}
void euler(double ta, double tb, double h, std::vector<double>&y, std::vector<double> & x)
{
  const int N=(tb-ta)/h;//cantidad de pasos
  std::vector<double> yaux(y.size());//un vector auxiliar para que no se usen componentes nuevas de y para calcular otras componentes
  for(int nt=0;nt<N;nt++)
    {
      double ti=ta+h*nt;//paso de timpo
      std::copy(y.begin(),y.end(),yaux.begin());//se inicializa el vector inicial
      for(int id=0;id<y.size()-1;++id)//hasta y.size()-1 ya que tenemos a I(corriente) en la ultima componente
	{
	   
	  y[id]+=h*f(ti,yaux,id,x);//metodo de euler
	  if (id==3)
	    {
	      init_x(x,y);//ya que los parametros dependen de v cambian cuando v cambia.se modifica al final
	    }
	  std::cout<<ti<<"\t"<<y[0]<<"\t"<<y[1]<<"\t"<<y[2]<<"\t"<<y[3]<<std::endl;
	}
     
    }
}
double f(double t, const std::vector<double> & y,int id,const std::vector<double> &x)
{
  if(0==id)
    {
      return ((-g_k*(std::pow(y[1],4))*(y[0]-v_k))-(g_Na*(std::pow(y[2],3))*y[3]*(y[0]-v_Na))-(g_l*(y[0]-v_l))+y[4])/C;
    }
  else if (1==id)
    {
      return x[0]-(y[1]*(x[1]+x[0]));
    }
  else if (2==id)
    {
      return x[2]-(y[2]*(x[2]+x[3]));
    }
  else if (3==id)
    {
      return x[4]-(y[3]*(x[4]+x[5]));
    }
  else{
    std::cerr<<"Error!Id does not exist->"<<id<<std::endl;
    exit(1);
  }
}

void init_y(std::vector<double> &y)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0,1 );
  for(int id; id<y.size();id++)
    {
      if(id==0)
	{
	  y[id]=30.0;
	}
      else if (id>0)
	{
	  y[id]=dis(gen);
	  if(id==4)
	    {
	      y[id]=7.0;
	    }
	}
    }
}
void init_x(std::vector<double> & x,const std::vector<double> &y)
{
  for (int ii=0; ii<x.size();ii++)
    {
      if(ii==0 )
	{
	  x[ii]=0.01*(y[0]+10.0)/((std::exp(1+(y[0]/10.0)))-1);
	}
      else if(ii==1)
	{
	  x[ii]=0.125*(std::exp(y[0]/80.0));
	}
      else if(ii==2)
	{
	  x[ii]=0.01*(y[0]+25)/((std::exp(2.5+(y[0]/10.0)))-1);
	}
      else if(ii==3)
	{
	  x[ii]=4*(std::exp(y[0]/18.0));
	}
      else if(ii==4)
	{
	  x[ii]=0.07*(std::exp(y[0]/20.0));
	}
      else if(ii=5)
	{
	  x[ii]=1/((std::exp(3+(y[0]/10.0)))+1);
	}

    }
}
