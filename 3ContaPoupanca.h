#ifndef	CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "3Conta.h"

class ContaPoupanca: public Conta{
	friend ofstream & operator<<(ofstream &fout, const ContaPoupanca &c);
	public:
		ContaPoupanca(Pessoa *cliente, double nmr, double saldo, int diaAniversario): Conta(cliente , nmr, saldo, "ContaPoupança."), diaAniversario(diaAniversario){}
		virtual ~ContaPoupanca(){}

		virtual Conta & extrato();
		virtual Conta & info();

	private:
		int diaAniversario;
};

#endif