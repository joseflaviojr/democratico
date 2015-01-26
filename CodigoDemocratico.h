
/*
 *  Copyright (C) 2015 Jos� Fl�vio de Souza Dias J�nior
 *  
 *  This file is part of C�digo Democr�tico - <http://www.joseflavio.com/democratico/>.
 *  
 *  C�digo Democr�tico is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  C�digo Democr�tico is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with C�digo Democr�tico. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *  Direitos Autorais Reservados (C) 2015 Jos� Fl�vio de Souza Dias J�nior
 * 
 *  Este arquivo � parte de C�digo Democr�tico - <http://www.joseflavio.com/democratico/>.
 * 
 *  C�digo Democr�tico � software livre: voc� pode redistribu�-lo e/ou modific�-lo
 *  sob os termos da Licen�a P�blica Menos Geral GNU conforme publicada pela
 *  Free Software Foundation, tanto a vers�o 3 da Licen�a, como
 *  (a seu crit�rio) qualquer vers�o posterior.
 * 
 *  C�digo Democr�tico � distribu�do na expectativa de que seja �til,
 *  por�m, SEM NENHUMA GARANTIA; nem mesmo a garantia impl�cita de
 *  COMERCIABILIDADE ou ADEQUA��O A UMA FINALIDADE ESPEC�FICA. Consulte a
 *  Licen�a P�blica Menos Geral do GNU para mais detalhes.
 * 
 *  Voc� deve ter recebido uma c�pia da Licen�a P�blica Menos Geral do GNU
 *  junto com C�digo Democr�tico. Se n�o, veja <http://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <cstdio>
#include <fstream>

using namespace std;

#define DESCONEXO 0

int  CodigoDemocratico( int** populacao, int total, ofstream* saida );
void Eleicao( int** populacao, int total, float* insatisfacao, int* eleito, int* candidatonorte, int* candidatosul );
void InteressePopulacional( int** populacao, int total );
void Permutar( int** populacao, int* organizacao, int total, int a, int b );
void ImprimirResultado( int* organizacao, int total, ostream* saida );
inline int Sortear( int maximo );
