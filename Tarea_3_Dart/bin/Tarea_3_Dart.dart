import 'dart:ffi';
import 'dart:io';
import 'dart:convert';
import 'dart:math';
import 'package:extended_math/extended_math.dart';



void main(){
  File puntajes = new File("puntajes.csv");
  print("Procesando información");
  leeGuarda(puntajes);
  participantes();

}

void leeGuarda(File puntajes){
  puntajes.readAsLines().then(leerGuardar);
}

void leerGuardar(List<String> lines){
  List<double> nem = new List();
  List<double> rkn = new List();
  List<double> mat = new List();
  List<double> len = new List();
  List<double> cie = new List();
  List<double> his = new List();
  for(var line in lines){
    List<int> puntajes = ObtenerPuntajes(line);
    if(puntajes.length>=6){
      nem.add(puntajes[1].toDouble());
      rkn.add(puntajes[2].toDouble());
      mat.add(puntajes[3].toDouble());
      len.add(puntajes[4].toDouble());
      cie.add(puntajes[5].toDouble());
      his.add(puntajes[6].toDouble());
    }
    puntajes = new List();
  }

  print("=== NEM === \n");
  double promnem = prom(nem);
  moda(nem);
  mediana(nem);
  desviacionEstandar(nem, promnem);


  print("=== RANKING === \n");
  double promrnk = prom(rkn);
  moda(rkn);
  mediana(rkn);
  desviacionEstandar(rkn, promrnk);

  print("=== MATEMÁTICAS === \n");
  double prommat = prom(mat);
  moda(mat);
  mediana(mat);
  desviacionEstandar(mat, prommat);

  print("=== LENGUAJE === \n");
  double promlen = prom(len);
  moda(len);
  mediana(len);
  desviacionEstandar(len, promlen);

  print("=== CIENCIAS === \n");
  double promcie = prom(cie);
  moda(cie);
  mediana(cie);
  desviacionEstandar(cie, promcie);

  print("=== HISTORIA === \n");
  double promhis = prom(his);
  moda(his);
  mediana(his);
  desviacionEstandar(his, promhis);
}

double prom(List<double> valor){
  double valorprom = 0;
  for(double punt in valor){
    valorprom += punt;
  }
  valorprom=(valorprom/valor.length);
  print(" Promedio: ${valorprom}");
  return valorprom;
}


void ordenar(List<dynamic> list){
  list.sort();
  print(list);
}

void mediana(List<dynamic> a) {
  a.sort();
  int middle = a.length ~/ 2;
  if (a.length % 2 == 1) {
    print(" Mediana: ${a[middle]}");
  } else {
    print(" Mediana: ${(a[middle - 1] + a[middle]) / 2.0}");
  }
}

double moda(List<dynamic> x){
  x.sort();
  int cont=0;
  int contmoda=0;
  int xmoda=0;
  double aux=0;
  double moda;
  for (int i=0;i<x.length;i++){
    if(x[i]!=aux || i+1==x.length){
      if(i+1==x.length){
        cont++;
      }
      if(cont>contmoda){
        contmoda=cont;
        xmoda=i-1;
      }
      aux=x[i];
      cont=0;
    }
    cont=cont+1;
  }
  moda=x[xmoda];
  print(" Moda: ${moda}");
}


double varianza(List<dynamic> a, double prom) {
  double meanA = prom;
  double temp = 0;
  for (double el in a) {
    temp += (el - meanA) * (el - meanA);
  }
  return temp / (a.length - 1);
}

void desviacionEstandar(List<dynamic> a, double prom){
  print(" Desviación Estandar: ${sqrt(varianza(a,prom))}") ;
}


List<int> ObtenerPuntajes(String line){
  List<int> arreglo = [];
  arreglo.add(int.parse(line.substring(0,8)));
  //print(arreglo[0]);
  arreglo.add(int.parse(line.substring(9,12)));
  //print(arreglo[1]);
  arreglo.add(int.parse(line.substring(13,16)));
  //print(arreglo[2]);
  arreglo.add(int.parse(line.substring(17,20)));
  //print(arreglo[3]);
  arreglo.add(int.parse(line.substring(21,24)));
  //print(arreglo[4]);
  arreglo.add(int.parse(line.substring(25,28)));
  //print(arreglo[5]);
  arreglo.add(int.parse(line.substring(29,32)));
  //print(arreglo[6]);
  
  return arreglo;
}

void participantes(){
  print("=== Taller 3 ===");
  print(" Omar Gutiérrez");
  print(" Gina Garrido");
  print(" Abraham Aguilera");
}