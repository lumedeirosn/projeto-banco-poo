#ifndef CONTACORRENTE_H
#define CONTACORRENTE_H

#include "3Conta.h"

class ContaCorrente: public Conta{
	friend ofstream & operator<<(ofstream &fout, const ContaCorrente &c);
	public:
		ContaCorrente(Pessoa *cliente, double nmr, double saldo): Conta(cliente , nmr, saldo, "ContaCorrente."){}
		virtual ~ContaCorrente(){}
		
		virtual Conta & extrato();
		virtual Conta & info();
		
};
#endif