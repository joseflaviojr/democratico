
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

#include "CodigoDemocratico.h"

/*
 *  C�digo Democr�tico
 *  <http://www.joseflavio.com/democratico/>
 *
 *  Implementa��o de Refer�ncia
 *  Reference Implementation
 */
int CodigoDemocratico( int** populacao, int total, ofstream* saida ) {

	// Pr�-Governo

	InteressePopulacional( populacao, total );

	// Governo

	int organizacao[total];
	int organizacao_melhor[total];
	for( int i = 0; i < total; i++ ) organizacao[i] = organizacao_melhor[i] = i;

	float insatisfacao, insatisfacao_nova, insatisfacao_melhor;
	
	int candidatonorte[total], candidatosul[total];
	int eleito, eleito_novo, eleito_melhor;
	int votado, sorteado;

	Eleicao( populacao, total, &insatisfacao, &eleito, candidatonorte, candidatosul );
	insatisfacao_melhor = insatisfacao;
	eleito_melhor = eleito;

	int mandatos = 0;
	int mandatos_tolerancia = ( eleito<0 ? -eleito : total-eleito ) * 0.8;

	while( insatisfacao_melhor > 0 ){

		votado = abs(eleito);
		sorteado = eleito<0 ? Sortear(votado-1) : eleito+1+Sortear(total-eleito-2);

		Permutar( populacao, organizacao, total, votado, sorteado );

		Eleicao( populacao, total, &insatisfacao_nova, &eleito_novo, candidatonorte, candidatosul );

		if( insatisfacao_nova < insatisfacao || mandatos >= mandatos_tolerancia ){
			
			insatisfacao = insatisfacao_nova;
			eleito = eleito_novo;
			mandatos = 0;
			mandatos_tolerancia = ( eleito<0 ? -eleito : total-eleito ) * 0.8;

			if( insatisfacao < insatisfacao_melhor ){
				
				insatisfacao_melhor = insatisfacao;
				eleito_melhor = eleito;
				memcpy( organizacao_melhor, organizacao, total * sizeof(int) );

				saida->seekp( 0, saida->beg );
				ImprimirResultado( organizacao_melhor, total, saida );
				saida->flush();

			}

		}else{
			mandatos++;
			Permutar( populacao, organizacao, total, votado, sorteado );
		}

	}

	return 0;

}

/* Processo Eleitoral */
void Eleicao( int** populacao, int total, float* insatisfacao, int* eleito, int* candidatonorte, int* candidatosul ) {

	*insatisfacao = 0;

	float apuracao, media;
	int interesse, cand1, cand2, i, j;

	for( i = 0; i < total; i++ ) candidatonorte[i] = candidatosul[i] = 0;
	int candidatonorte_maior = 0;
	int candidatosul_maior = 0;

	const float relevancia = 0.6 * total;

	for( j = 0; j < total; j++ ){
		
		apuracao = 0;

		for( i = 0; i < total; i++ ){
			
			if( i == j ) continue;
			interesse = populacao[i][j];

			if( i < j ){ // Norte
				media = i <= (j-3) ? (populacao[i+1][j]+populacao[i+2][j])/2 : populacao[i+1][j];
				if( interesse < media ){
					apuracao += (media-interesse) / log(relevancia*(j-i));
					cand1 = ++candidatonorte[i];
					cand2 = candidatonorte[candidatonorte_maior];
					if( ( cand1 > cand2 ) || ( cand1 == cand2 && Sortear(100) <= 80 ) ) candidatonorte_maior = i;
				}
			}else{ // Sul
				media = i >= (j+3) ? (populacao[i-1][j]+populacao[i-2][j])/2 : populacao[i-1][j];
				if( interesse < media ){
					apuracao += (media-interesse) / log(relevancia*(i-j));
					cand1 = ++candidatosul[i];
					cand2 = candidatosul[candidatosul_maior];
					if( ( cand1 > cand2 ) || ( cand1 == cand2 && Sortear(100) <= 80 ) ) candidatosul_maior = i;
				}
			}

		}

		*insatisfacao += apuracao;

	}

	*eleito = candidatonorte[candidatonorte_maior] >= candidatosul[candidatosul_maior] ? candidatonorte_maior : -candidatosul_maior;

}

/*
 *  Matriz de Interesse Populacional
 *  Adapta��o do algoritmo Floyd-Warshall
 *  Floyd, R. W. (1962). Algorithm 97: Shortest path. Communications of the ACM, 5(6):345�.
 */
void InteressePopulacional( int** populacao, int total ) {

	int i, j, k, a, b;
	int interesse, periferia = 0;

	for( i = 0; i < total; i++ ){
		for( j = 0; j < total; j++ ){
			interesse = populacao[i][j];
			for( k = 0; k < total; k++ ){
				a = populacao[i][k];
				b = populacao[k][j];
				b = a == DESCONEXO || b == DESCONEXO ? DESCONEXO : a + b;
				if( b != DESCONEXO && ( interesse == DESCONEXO || b < interesse ) ) interesse = b;
			}
			populacao[i][j] = interesse;
			if( interesse != DESCONEXO && interesse > periferia ) periferia = interesse;
		}
	}

	periferia *= 2;

	for( i = 0; i < total; i++ ){
		populacao[i][i] = 1;
		for( j = 0; j < total; j++ ){
			if( populacao[i][j] == DESCONEXO ) populacao[i][j] = periferia;
		}
	}

}

/* Permuta��o */
void Permutar( int** populacao, int* organizacao, int total, int a, int b ) {

	int i, x;

	for( i = 0; i < total; i++ ){
		x = populacao[a][i];
		populacao[a][i] = populacao[b][i];
		populacao[b][i] = x;
	}

	for( i = 0; i < total; i++ ){
		x = populacao[i][a];
		populacao[i][a] = populacao[i][b];
		populacao[i][b] = x;
	}

	x = organizacao[a];
	organizacao[a] = organizacao[b];
	organizacao[b] = x;

}

/* Impress�o de Resultado */
void ImprimirResultado( int* organizacao, int total, ostream* saida ) {
	*saida << organizacao[0] + 1;
	for( int i = 1; i < total; i++ ) *saida << ',' << organizacao[i] + 1;
}

/* Sorteio */
inline int Sortear( int maximo ) {
	return rand() % ( maximo + 1 );
}
