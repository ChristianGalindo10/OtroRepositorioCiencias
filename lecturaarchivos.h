#ifndef LECTURAARCHIVOS_H
#define LECTURAARCHIVOS_H
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "lista.h"
#include "corte.h"
#include "nota.h"
#include "Cola.h"
#include "contenedor.h"
#include "profesor.h"
#include "tema.h"
class LecturaArchivos{
	public:
		lista<Profesor> lecturaProfesores(lista<Profesor> ps);
		lista<Corte> lecturaCortes(Profesor p);
		lista<Nota> lecturaNotas(Profesor p, Corte cor);
		lista<Contenedor> lecturaContenedores(Profesor p, Corte cor, Nota nt);
		lista<Evaluacion> lecturaEvaluaciones(Profesor p, Corte cor, Nota nt, Contenedor cont);
		lista<Tema> lecturaTemas(lista<Tema> ts);
};
lista<Profesor> LecturaArchivos::lecturaProfesores(lista<Profesor> ps){
	ifstream archivo;
	int numLines = 0;
	ifstream in("archivos//Profesores//profesores.txt");
	string unused;
	//Contar lineas de archivo
	while (getline(in, unused) )
   		++numLines; 
	cola<string> Cola;
	archivo.open("archivos//Profesores//profesores.txt",ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	string aux;
	//while(!archivo.eof()){
	for(int i=0;i<numLines;i++){
		Profesor p;
		string puntero="";
		getline(archivo,aux);
		stringstream ss(aux);
		while(ss.good()){
			string substr;
			getline(ss,substr,',');
			Cola.InsCola(substr);
		}
		Cola.AtenderCola(&puntero);
		istringstream cedula(puntero);
		if ( !(cedula >> p.getCedula()) ) //give the value to 'Result' using the characters in the stream
    		p.setCedula(0);
    	Cola.AtenderCola(&puntero);
		for(int i = 0; i<puntero.length(); i++){
			p.setApellidos(i,puntero[i]);
		}
		for(int i = puntero.length(); i<50; i++){
			p.setApellidos(i,0);
		}
		Cola.AtenderCola(&puntero);
		for(int i = 0; i<puntero.length(); i++){
			p.setNombres(i,puntero[i]);
		}
		for(int i = puntero.length(); i<50; i++){
			p.setNombres(i,0);
		}
		Cola.AtenderCola(&puntero);
		istringstream numClases(puntero);
		if ( !(numClases >> p.getNumClases()) ) //give the value to 'Result' using the characters in the stream
    		p.setNumClases(0);
		p.setListaCorte(lecturaCortes(p));	
    	ps.insertarOrd(p,p.getCedula());
	}
	archivo.close();
	return ps;
}
lista<Corte> LecturaArchivos::lecturaCortes(Profesor p){
	ifstream archivo;
	ostringstream ss;
	ss << p.getCedula();
	string ruta;
	ruta="archivos//Cortes//"+ss.str()+"cortes.txt";
	//Contar lineas de archivo
	int numLines = 0;
	ifstream in(ruta.c_str());
	string unused;
	while (getline(in, unused))
   		++numLines; 
	archivo.open(ruta.c_str(),ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		//exit(1);
	}
	Corte c;
	c.setNombre("CorteEjemplo");
	lista<Corte> cs= lista<Corte>(c);
	for(int i=0;i<numLines;i++){
		string nombre;
		getline(archivo,nombre);
		c.setNombre(nombre);
		
		c.setEvaluaciones(lecturaNotas(p,c));
		cs.insertarOrd(c,cs.get_tam()+1);
	}
	archivo.close();
	return cs;
}
lista<Nota> LecturaArchivos::lecturaNotas(Profesor p, Corte cor){
	ifstream archivo;
	ostringstream ss;
	ss << p.getCedula();
	string ruta;
	ruta="archivos//TiposEvaluacion//"+ss.str()+cor.getNombre()+"tiposEval.txt";
	//cout<<ruta;
	//Contar lineas de archivo
	int numLines = 0;
	ifstream in(ruta.c_str());
	string unused;
	while (getline(in, unused))
   		++numLines; 
	archivo.open(ruta.c_str(),ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		//exit(1);
	}
	Nota nt;
	nt.setPorcentaje(1000);
	nt.setTipo("TipoCualquiera");
	lista<Nota> ns= lista<Nota>(nt);
	
	string aux;
	cola<string> Cola2;
	for(int i=0;i<numLines;i++){
		string puntero="";
		getline(archivo,aux);
		stringstream ss(aux);
		while(ss.good()){
			string substr;
			getline(ss,substr,',');
			Cola2.InsCola(substr);
		}
		Cola2.AtenderCola(&puntero);
		nt.setTipo(puntero);
		Cola2.AtenderCola(&puntero);
		istringstream porcentaje(puntero);
		if ( !(porcentaje >> nt.getPorcentaje()) ) //give the value to 'Result' using the characters in the stream
    		nt.setPorcentaje(0);
    		nt.setListaContenedor(lecturaContenedores(p,cor,nt));
    	ns.insertarOrd(nt,ns.get_tam()+1);	
	}
	archivo.close();
	return ns;
}
lista<Contenedor> LecturaArchivos::lecturaContenedores(Profesor p, Corte cor, Nota nt){
	ifstream archivo;
	ostringstream ss;
	ss << p.getCedula();
	string ruta;
	ruta="archivos//Contenedores//"+ss.str()+cor.getNombre()+nt.getTipo()+".txt";
	//Contar lineas de archivo
	int numLines = 0;
	ifstream in(ruta.c_str());
	string unused;
	while (getline(in, unused))
   		++numLines; 
	archivo.open(ruta.c_str(),ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		//exit(1);
	}
	Contenedor cont;
	cont.setI(1000);
	lista<Contenedor> cs= lista<Contenedor>(cont);
	string aux;
	for(int i=0;i<numLines;i++){
		getline(archivo,aux);
		istringstream contador(aux);
		if ( !(contador >> cont.getI()) ) //give the value to 'Result' using the characters in the stream
    		cont.setI(0);
    	cont.setListaEvaluacion(lecturaEvaluaciones(p,cor,nt,cont));
    	cs.insertarOrd(cont,cs.get_tam()+1);
	}
    return cs;
}
lista<Evaluacion> LecturaArchivos::lecturaEvaluaciones(Profesor p, Corte cor, Nota nt, Contenedor cont){
	ifstream archivo;
	ostringstream ss;
	ss << p.getCedula();
	ostringstream ss2;
	ss2 << cont.getI();
	string ruta;
	ruta="archivos//Evaluaciones//"+ss.str()+cor.getNombre()+nt.getTipo()+ss2.str()+"preguntas.txt";
	//Contar lineas de archivo
	int numLines = 0;
	ifstream in(ruta.c_str());
	string unused;
	while (getline(in, unused))
   		++numLines; 
	archivo.open(ruta.c_str(),ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		//exit(1);
	}
	Evaluacion eva;
	eva.setPorcentaje(1000);
	eva.setTema(1000);
	lista<Evaluacion> vs = lista<Evaluacion>(eva);
	string aux;
	cola<string> Cola3;
	for(int i=0;i<numLines;i++){
		string puntero="";
		getline(archivo,aux);
		stringstream ss(aux);
		while(ss.good()){
			string substr;
			getline(ss,substr,',');
			Cola3.InsCola(substr);
		}
		Cola3.AtenderCola(&puntero);
		istringstream tema(puntero);
		if ( !(tema >> eva.getTema()) ) //E
    		eva.setTema(0);
		Cola3.AtenderCola(&puntero);
		istringstream porcentaje(puntero);
		if ( !(porcentaje >> eva.getPorcentaje()) ) //give the value to 'Result' using the characters in the stream
    		eva.setPorcentaje(0);
    	vs.insertarOrd(eva,vs.get_tam()+1);
	}
    return vs;
}

lista<Tema> LecturaArchivos::lecturaTemas(lista<Tema> ts){
	ifstream archivo;
	string ruta;
	ruta="archivos//Temas//temas.txt";
	//Contar lineas de archivo
	int numLines = 0;
	ifstream in(ruta.c_str());
	string unused;
	while (getline(in, unused))
   		++numLines; 
	archivo.open(ruta.c_str(),ios::in);
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		//exit(1);
	}
	Tema t;
	string aux;
	cola<string> Cola4;
	for(int i=0;i<numLines;i++){
		string puntero="";
		getline(archivo,aux);
		stringstream ss(aux);
		while(ss.good()){
			string substr;
			getline(ss,substr,',');
			Cola4.InsCola(substr);
		}
		Cola4.AtenderCola(&puntero);
		istringstream numt(puntero);
		if ( !(numt >> t.getCodigo()) ) //give the value to 'Result' using the characters in the stream
    		t.setCodigo(0);
		Cola4.AtenderCola(&puntero);
		t.setNombre(puntero);
    	ts.insertarOrd(t,t.getCodigo());
	}
    return ts;
}



#endif
