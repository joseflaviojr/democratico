
/*
 *  Copyright (C) 2015 José Flávio de Souza Dias Júnior
 *  
 *  This file is part of Código Democrático - <http://www.joseflavio.com/democratico/>.
 *  
 *  Código Democrático is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  Código Democrático is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Código Democrático. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *  Direitos Autorais Reservados (C) 2015 José Flávio de Souza Dias Júnior
 * 
 *  Este arquivo é parte de Código Democrático - <http://www.joseflavio.com/democratico/>.
 * 
 *  Código Democrático é software livre: você pode redistribuí-lo e/ou modificá-lo
 *  sob os termos da Licença Pública Menos Geral GNU conforme publicada pela
 *  Free Software Foundation, tanto a versão 3 da Licença, como
 *  (a seu critério) qualquer versão posterior.
 * 
 *  Código Democrático é distribuído na expectativa de que seja útil,
 *  porém, SEM NENHUMA GARANTIA; nem mesmo a garantia implícita de
 *  COMERCIABILIDADE ou ADEQUAÇÃO A UMA FINALIDADE ESPECÍFICA. Consulte a
 *  Licença Pública Menos Geral do GNU para mais detalhes.
 * 
 *  Você deve ter recebido uma cópia da Licença Pública Menos Geral do GNU
 *  junto com Código Democrático. Se não, veja <http://www.gnu.org/licenses/>.
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
