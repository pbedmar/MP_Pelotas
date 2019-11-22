#include "utilidades.h"

using namespace std;
using namespace miniwin;

//Generales:

string formato_color(PColor color)
{
    string color_final;
    
    PColor color2=PColor::ROJO;
    if(color2 == color)
        color_final="ROJO";
    else 
        color_final="VERDE";
    
    return color_final;

}

PColor formato_color(std::string color1)
{
    PColor color;
    if(color1 == "ROJO")
        color=PColor::ROJO;
    else
        color=PColor::VERDE;
    
    return color;
}


//Pelota:

void pintar(const Pelota &P) {
    color((int) P.get_color());
    circulo_lleno( P.get_x() , P.get_y() , P.get_radio() );
}

void mover(Pelota &P){
    
   const float factor = 0.97;
   
   P.set_x(P.get_dx()+P.get_x());
   P.set_y(P.get_dy()+P.get_y());
   
   if (P.get_x() > vancho() - P.get_radio()) {
      P.set_dx(-P.get_dx() * factor);
      P.set_x(vancho() - P.get_radio());
   } 
   else if (P.get_x() < P.get_radio()) {
      P.set_dx(-P.get_dx() * factor);
      P.set_x(P.get_radio());
   } 
   else if (P.get_y() > valto() - P.get_radio()) {
      P.set_dy(-P.get_dy() * factor);
      P.set_y(valto() - P.get_radio());
   } 
   else if (P.get_y() < P.get_radio()) {
      P.set_dy(-P.get_dy() * factor);
      P.set_y(P.get_radio());
   }
   
   P.set_dy(0.05+P.get_dy());
}

void colisionar(Pelota &P, Pelota &T) {
    
    float auxiliary,auxiliarx;
    
    if(P.colisionado(T))
    {
        auxiliarx = (P.get_dx());
        auxiliary = (P.get_dy());
        P.set_dx(T.get_dx()*1.00);
        P.set_dy(T.get_dy()*1.00);
        T.set_dx(auxiliarx*1.00);
        T.set_dy(auxiliary*1.00);
    }
}

std::ostream& operator<<(std::ostream &os,const Pelota &p1 )
{
    os << p1.get_x() << " ";
    os << p1.get_y() << " ";
    os << p1.get_dx() << " ";
    os << p1.get_dy() << " " ;
    os << p1.get_radio() << " " ;
    os << formato_color(p1.get_color());
    return os;
}


std::istream& operator>>(std::istream &is, Pelota &p1)
{
    std::string auxcolor;
    float x,y,dx,dy,radio;
    
    is >> x;
    p1.set_x(x);
    is >> y;
    p1.set_y(y);
    is >> dx;
    p1.set_dx(dx);
    is >> dy;
    p1.set_dy(dy);
    is >> radio;
    p1.set_radio(radio);
    is >> auxcolor;
    PColor color2 =formato_color(auxcolor);
    p1.set_color(color2);
    
    return is;
}

//Pelotas:

void pintar(const Pelotas &P) {
    
    for(int i=0; i < P.get_util(); i++){
        color((int) P.get_pelota(i).get_color());
        circulo_lleno( P.get_pelota(i).get_x() , P.get_pelota(i).get_y() , P.get_pelota(i).get_radio() );
    }
}



void mover(Pelotas &P){
   const float factor = 1;
   
   for(int i=0; i < P.get_util(); i++)
   {
      mover(P.get_pelota(i));
   }
}

void colisionar(Pelotas &P) {
    bool chocado=false;
    
    for(int i=0; i < P.get_util(); i++){
        chocado=false;
        for(int k=i; k < P.get_util() && !chocado; k++)
        {
            if(P.get_pelota(i).colisionado(P.get_pelota(k)))
            {
                if(i != k && P.get_pelota(i).get_color() == PColor::VERDE && P.get_pelota(k).get_color() == PColor::VERDE)
                { 
                    colisionar( P.get_pelota(i), P.get_pelota(k) );
                    Pelota pelota1=P.get_pelota(i);
                    pelota1.set_x(10+rand()%(MIN_X-10));
                    pelota1.set_y(10+rand()%(MIN_Y-10));
                    if(P.get_util() <15)
                    {
                        P.aniadir(pelota1);
                        chocado=true;
                    }
                }
                
                if(i != k && P.get_pelota(i).get_color() == PColor::ROJO && P.get_pelota(k).get_color() == PColor::ROJO)
                {
                    colisionar( P.get_pelota(i), P.get_pelota(k) );
                }
                
                if(i != k && P.get_pelota(i).get_color() == PColor::ROJO && P.get_pelota(k).get_color() == PColor::VERDE)
                {
                    P.borrar_pelota(k);
                }
                
                if(i != k && P.get_pelota(i).get_color() == PColor::VERDE && P.get_pelota(k).get_color() == PColor::ROJO)
                {
                    P.borrar_pelota(i);
                }
            }
        }
    }
}

Pelotas & operator+=(Pelotas &P, const Pelota &pelota1)
{
    P.aniadir(pelota1);   
    return P;
}

bool operator==(const Pelota &p1,const  Pelota &p2)
{
    if( p1.get_radio() == p2.get_radio() && p1.get_color() == p2.get_color() )
        return true;
    
    else
        return false;
}


std::ostream& operator<<(std::ostream &os,const Pelotas &p1 )
{
    for(int i=0; i < p1.get_util(); i++){
        os << p1[i] << endl;
    }
    return os;
}



std::istream& operator>>(std::istream &is, Pelotas &p1)
{  
    Pelota aux;
    int n;
    is >> n;
    
    for(int i=0; i < n; i++)
    {
        is >> aux;
        p1.aniadir(aux);
    }
    
    return is;
}


