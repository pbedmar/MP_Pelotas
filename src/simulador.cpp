

#include "simulador.h"

Simulador::Simulador()
{
    alto=ancho=0;
    vredimensiona(alto, ancho);

}

Simulador::Simulador(const std::string &cadena)
{
    std::ifstream fentrada;
    int numero_pelotas;
    char c[100];
    Pelota aux;
    
    fentrada.open(cadena);
    fentrada>>c;
    
    if(fentrada){
        if(strcmp(c, "MP−PELOTAS−T−1.0"))
        {
            fentrada >> alto;
            fentrada >> ancho;
        
            fentrada >> original;
          
            actual = original;
            fentrada.close();
            vredimensiona(alto,ancho);
        }else{
            std::cerr << "No se encontro la cabecera magica.";
        }
    } else {
        std::cerr << "Error en la apertura del fichero.";
    }
}


Simulador:: ~Simulador()
{
    original.~Pelotas();
    actual.~Pelotas();
    vcierra();
}


Pelotas & Simulador::getActual()
{
    return actual;
}

Pelotas Simulador::getActual() const
{
    return actual;
}

Pelotas & Simulador:: getOriginal()
{
    return original;
}

Pelotas Simulador:: getOriginal() const
{
    return original;
}

void Simulador:: step(int n)
{
    for(int i=0; i < n ; i++)
    {
        mover(actual);
        colisionar(actual);
    }
}   

bool Simulador::salvar(std::string cadena) const
{
    std::ofstream fsalida;
    
    fsalida.open(cadena);
    
    fsalida << "MP−PELOTAS−T−1.0" << std::endl;
    fsalida << alto << std::endl;
    fsalida << ancho << std::endl;
    fsalida << actual.get_util() << std::endl;
    fsalida << actual;
    
    fsalida.close();  

    if(fsalida)
        return true;
    else
        return false;
}


void pintar(const Simulador &partida,int espera2)
{
    
    borra();
    pintar(partida.getActual() );
    refresca();
    espera(espera2);

}