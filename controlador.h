#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <iostream>


#include "lista.h"
//Clases

#include "profesor.h"
#include "tema.h"
#include "corte.h"
#include "contenedor.h"
#include "nota.h"
#include "evaluacion.h"
#include "llenarlistas.h"
#include "lecturaarchivos.h"
#include "escribirarchivos.h"



using namespace std;
class Controlador{
	lista<Profesor> profesores;
	lista<Tema> temas;
	LecturaArchivos lecArchivos;
	EscribirArchivos escArchivos;
	LlenarListas insertar;
	//Param�tros necesarios para manejo de listas
	Profesor p;
	Corte cor;
	Nota nt;
	Contenedor ct;
	Evaluacion eva;
	string ap;
	string nom;
	Tema t;
	public:	
		Controlador(){
			//Inicializar lista profesores
			p.setCedula(999999);
			ap="Apellido1 Apellido2";
			nom="Nombre1 Nombre 2";
			for(int i = 0; i<ap.length(); i++){
				p.setApellidos(i,ap[i]);
			}
			for(int i = 0; i<nom.length(); i++){
				p.setNombres(i,nom[i]);
			}
			p.setNumClases(1000);
			profesores = lista<Profesor>(p);
			
			//Inicializar lista temas
			t.setCodigo(1000);
			t.setNombre("temaEjemplo");
			temas = lista<Tema>(t);
		};
		void iniciar();
		//M�todos para manejar listas
		void mostrarListaProfes();
		void mostrarListaCortes(Profesor p);
		void mostrarListaNotas(Corte cor);
		void mostrarListaContenedores(Nota nt);
		void mostrarListaEvaluaciones(Contenedor cont);
		
		void insertarProfes();
		
		
		
		//M�todos profesores
		lista<Profesor> getProfes();
		void leerProfes();
		void setProfes(lista<Profesor> ps);
		
		//M�todos temas
		lista<Tema> getTemas();
		void leerTemas();
		void setTemas(lista<Tema> ts);
		
		//M�todos de escritura
		void escribirArchivos();
		
};

void Controlador::escribirArchivos(){
	escArchivos.escribir(profesores,temas);
}

lista<Profesor> Controlador::getProfes(){
	return profesores;
}

void Controlador::leerProfes(){
	profesores=lecArchivos.lecturaProfesores(profesores);
}

void Controlador::setProfes(lista<Profesor> ps){
	profesores=ps;
}


lista<Tema> Controlador::getTemas(){
	return temas;
}

void Controlador::leerTemas(){
	temas=lecArchivos.lecturaTemas(temas);
}

void Controlador::setTemas(lista<Tema> ts){
	temas=ts;
}

void Controlador::mostrarListaProfes(){
	cout<<"Profes:"<<endl;
	if(profesores.get_tam()==0){
		cout<<"Lista vacia";
	}
	for(int pos=1;pos<=profesores.get_tam();pos++){
		profesores.recorrer(pos,&p);
		cout<<"Profesor:"<<endl;	
		cout<<"Cedula: "<<p.getCedula()<<endl;
		cout<<"Apellidos: "<<p.getApellidos()<<endl;
		cout<<"Nombres: "<<p.getNombres()<<endl;
		cout<<"Numero de clases: "<<p.getNumClases()<<endl;
		mostrarListaCortes(p);
	}
}

void Controlador::mostrarListaCortes(Profesor p){
	cout<<"Cortes:"<<endl;
	for(int c=1;c<=(p.getListaCorte().get_tam());c++){
		p.getListaCorte().recorrer(c,&cor);
		cout<<cor.getNombre()<<": "<<endl;
		mostrarListaNotas(cor);
	}
}

void Controlador::mostrarListaNotas(Corte cor){
	cout<<"Tipos de evaluaciones:"<<endl;
	for(int n=1;n<=(cor.getListaNotas().get_tam());n++){
		cor.getListaNotas().recorrer(n,&nt);
		cout<<"Tipo: "<<nt.getTipo()<<". Porcentaje: "<<nt.getPorcentaje()<<"%"<<endl;
		mostrarListaContenedores(nt);
	}
}
		
void Controlador::mostrarListaContenedores(Nota nt){
	cout<<"Evaluaciones: "<<endl;
	for(int cont=1;cont<=(nt.getListaContenedor().get_tam());cont++){
		nt.getListaContenedor().recorrer(cont,&ct);
		cout<<"evaluacion #"<<ct.getI()<<endl;
		mostrarListaEvaluaciones(ct);
	}	
}

void Controlador::mostrarListaEvaluaciones(Contenedor ct){
	for(int e=1;e<=(ct.getListaEvaluacion().get_tam());e++){
		ct.getListaEvaluacion().recorrer(e,&eva);
		cout<<"Porcentaje: "<<eva.getPorcentaje()<<". Tema: "<<eva.getTema()<<endl;
	}
}

void Controlador::insertarProfes(){
	profesores=insertar.llenaProfes(profesores);
	
}


#endif
