#ifndef	CONTACORRENTELIMITADA_H
#define CONTACORRENTELIMITADA_H

#include "3Conta.h"

class ContaCorrenteLimitada: public Conta{
	friend ofstream & operator<<(ofstream &fout, const ContaCorrenteLimitada &c);
	public:
		ContaCorrenteLimitada(Pessoa *cliente, double nmr, double saldo, double limite): Conta(cliente , nmr, saldo, "ContaCorrenteComLimite."), limite(limite){}
		virtual ~ContaCorrenteLimitada(){}

		virtual Conta &retirada(double valor);
		virtual Conta & extrato();
		virtual Conta & info();

	private:
		double limite;
};

#endif