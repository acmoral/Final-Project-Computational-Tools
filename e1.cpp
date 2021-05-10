#include<iostream>
#include<math.h>

//Parámetros constantes del modelo
const double c = 1.0;
const double gk = 36.0;
const double gna = 120.0;
const double gl = 0.3; 
const double vk= -12.0;
const double vna= 115.0;
const double vl= 10.613;

//Constantes temporales y de tamaño del vector
const int N = 4;                                //Tamaño del vector
const double TF = 6000;                           //Tiempo final
const double dt = 0.01;                         //Tamaño de paso

double ci(double *y1, double v);
double fd(double *y2, double *y1);
double fd2(double *y2, double *y1, double corr);
double sp( double *y2, double *y1);
double an(double *y1);
double am(double *y1);
double ah(double *y1);
double bn(double *y1);
double bm(double *y1);
double bh(double *y1);

int main(){
  double v = 0;
  double y1[N]={0.0};
  ci(y1,v);
  double y2[N]={0.0};
  double time = 0.0;
  double corr;
  double dcorr;
  std::cin>>corr;
  std::cin>>dcorr;
  double ccorr= corr+dcorr;
  for(int i=0;i<=TF;i++){
    
    if (i>2000){
      
      fd2(y2,y1,ccorr);
      sp(y2,y1);
      time = time + dt;   
      std::cout<<time<<'\t'<<y1[0]<<std::endl;
    }
    else
      {
	fd2(y2,y1,corr);
	sp(y2,y1);
	time = time + dt;   
	//	std::cout<<time<<'\t'<<y1[0]<<std::endl;
	  }
  }
  
  return 0;
}

double ci(double *y1, double v){
  
   y1[0]= v;
   y1[1]= an(y1)/(an(y1)+bn(y1));
   y1[2]= am(y1)/(am(y1)+bm(y1));
   y1[3]= ah(y1)/(ah(y1)+bh(y1));

  //   std::cout<<y[0]<<'\t'<<y[1]<<'\t'<<y[2]<<'\t'<<y[3]<<std::endl;
}

double fd(double *y2, double *y1){
  y2[0]= -gk*pow(y1[1],4)*(y1[0]-vk)-gna*pow(y1[2],3)*y1[3]*(y1[0]-vna)-gl*(y1[0]-vl);
  y2[1]= an(y1)*(1.0-y1[1])-bn(y1)*y1[1];
  y2[2]= am(y1)*(1.0-y1[2])-bm(y1)*y1[2];
  y2[3]= ah(y1)*(1.0-y1[3])-bh(y1)*y1[3];
  }

double fd2(double *y2, double *y1,double corr){
  y2[0]= -gk*pow(y1[1],4)*(y1[0]-vk)-gna*pow(y1[2],3)*y1[3]*(y1[0]-vna)-gl*(y1[0]-vl) + corr;
  y2[1]= an(y1)*(1.0-y1[1])-bn(y1)*y1[1];
  y2[2]= am(y1)*(1.0-y1[2])-bm(y1)*y1[2];
  y2[3]= ah(y1)*(1.0-y1[3])-bh(y1)*y1[3];
  }

double sp( double *y2, double *y1){
  for(int i=0; i<N; ++i){
    double a = 0;
    a = y2[i];
     y1[i] = y1[i]+dt*a; 
  } 
}


double an(double *y1){
  return 0.01*(-y1[0]+10.0)/(exp(1.0-(y1[0]/10.0))-1.0);
}
double am(double *y1){
  return 0.1*(-y1[0]+25.0)/(exp(2.5-(y1[0]/10.0))-1.0);
}
double ah(double *y1){
  return 0.07*exp(-y1[0]/20.0);
}
double bn(double *y1){
  return 0.125*exp(-y1[0]/80.0);
}
double bm(double *y1){
  return 4.0*exp(-y1[0]/18.0);
}
double bh(double *y1){
  return 1.0/(exp(3.0-(y1[0]/10.0))+1.0);
}
