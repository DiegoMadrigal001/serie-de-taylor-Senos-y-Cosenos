#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

double r32 = sqrt(3) / 2; // Raiz de 3 sobre dos 0.866
double r22 = sqrt(2) / 2; // Riz de dos sobre dos 0.707

// Tabla de valores conocidos de la funcion seno
double d[5][2] = {{0,0},{30,0.5},{45,r22},{60,r32},{90,1}}; // datos de seno
// Tabla de de derivadas de los valores de seno
double derivadas[4][5] = {{0,0.5,r22, r32 ,1},{1,r32,r22,0.5,0},{-0,-0.5,-r22,-r32,-1},{-1,-r32,-r22,-0.5,-0}}; //derivadas de seno

double CGR(double grados) //Función para Convertir Grados a Radianes
{
  return grados * (M_PI / 180);
}

double factorial(double n) //Función para Realizar la operacion factorial
{
   if(n == 0 or n==1) return 1;
   else if(n > 1) return n*factorial(n-1);
   return 1;
}

double derivada(int m, int a) // devuelve la derivada en funcion del grado
{
    m = m - 4 * trunc(m/4);
    double res = derivadas[m][a];
    return res;
    
}

double senoCoseno(double x) // Funcion seno o coseno
{
    if(x<0) x = x + 360;
    
    int y = abs(x - 360 * trunc(x/360));

    int signo = 1;
    
    //Determinamos en que cuadrante estamos trabajando
    if( y > 180 && d[0][1] == 1) signo = -1;
    if( y > 90 && y < 270 && d[0][1] == 0) signo = -1;
    int eva2 = trunc(y/90);
    
    //ahora X -> es el angulo reducido al primer cuadrante
    switch(eva2)
    {
        case 0:
            x=y;
        break;
        case 1:
            x=180-y;
        break;
        case 2:
            x=y-180;
        break;
        case 3:
            x=360-y;
        break;
        default: cout << "ERROR";
    }
    
    int a = 0;//angulo mar cercano
    
    //encontramos el angulo mas cercano a evaluar;
    int indice;
    for(int i=0 ; i < 5 ; i = i+1)
    {
        if( d[i][0] - x >= 0){
            a = d[i][0];
            indice = i ;
            break;
        }
    }
    
    if( d[indice][0] - x > x - d[indice - 1][0])
    {
        indice=indice-1;
        a = d[indice][0];
    }
    
    double termino = 1;
    double suma = 0 ;
    int m = 0 ;
    double operacion = CGR(x - a);
    cout << endl <<"-----------------------------------------------" << endl <<endl;
    while (abs(termino) > 0.000001)
    {
       termino = (( derivada(m,indice) * pow(operacion,m)) / factorial(m));
       suma = suma + termino;
       cout <<"Aprox"<< " #" << m + 1<< " : "<< suma << endl;
       m = m + 1;
    }
    cout << endl <<"-----------------------------------------------" << endl << endl;
    cout << "  >>>    Respuesta aproximada: ";
    suma = suma * signo;
    return suma;
}

void menu() // Muestra el menu de opciones
{  // Pinta el menu de opciones
    system("clear"); // unix: system("clear") -- DOS : system("cls");
    cout<< endl <<"Seleccione la funcion a emplear" << endl;
    cout<<">> 1) sen(x)"<<endl;
    cout<<">> 2) cos(x)"<<endl;
    int entrada = -1;
    cin>>entrada;
    cout<<endl;
    if(entrada<0 || entrada > 2){
        menu();
    }else if(entrada == 2){

     // Valores del coseno conocidos y sus derivadas
     double d2[5][2] = {{0,1},{30,r32},{45,r22},{60,0.5},{90,0}}; // datos
     double derivadas2[4][5] = {{1,r32,r22,0.5,0},{0,-0.5,-r22,-r32,-1},{-1,-r32,-r22,0.5,0},{0,0.5,r22,r32,1}};
     
     //La funcion coseno es la inversa del seno , por eso solamente invertimos los valores
     for(int c = 0 ; c < 5 ; c= c + 1 ){
       d[1][c] =  d2[1][c];
       for(int f =0 ; f<4 ; f= f + 1){
         derivadas[f][c] = derivadas2[f][c];
       }
     }
     
       
       system("clear"); // unix: system("clear") -- DOS : system("cls");
    cout << endl<< ">> cos(x)"<<endl;
       
    }else{
        
        system("clear"); // unix: system("clear") -- DOS : system("cls");
        cout << endl<< ">> sen(x)"<<endl;
    }
    
}

int main () // funcion principal
{
  menu();
  double x;
  cout << "x = ";
  cin >> x ;
  cout << fixed << senoCoseno(x) << "   <<<"  << endl;
  return 0;
}
