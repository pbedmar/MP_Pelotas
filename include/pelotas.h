// Alumno1: Pedro Bedmar Lopez
// Alumno2: Alejandro Escalona Garcia


#include"pelota.h"

#ifndef PELOTAS_H
#define PELOTAS_H


class Pelotas{
private:
    Pelota *v;
    int capacidad;
    int util;
    
    
public:

    Pelotas();
    
    Pelotas(const Pelota &pelota1);
    
    Pelotas(int numero);
    
    Pelotas(const Pelotas &P);
    
    int get_capacidad() const;
    
    int get_util() const;
    
    Pelota get_pelota(int posicion) const;
    
    Pelota & get_pelota(int posicion);
    
    void set_util(int util2);
    
    void aniadir(const Pelota &pelota2);
    
    void borrar_pelota(int posicion);
    
    ~Pelotas();
    
    
    
    Pelota & operator[]( int numero);

    const Pelota & operator[]( int numero) const;
     
    Pelotas & operator=(const Pelotas &p1);
    
};

#endif /* PELOTAS_H */

