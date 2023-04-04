#ifndef CONTA_H
#define CONTA_H 

#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "2Pessoa.h"

typedef struct transacao{
	string tipo, data, descricao;
	double valor;
}st_transacao;

class Conta{
	public:
		Conta(Pessoa *cliente, double nmr, double saldo, string tipoDaConta): cliente(cliente), nmr(nmr), saldo(saldo), tipoDaConta(tipoDaConta){}
		
		virtual ~Conta();

		virtual Conta & deposito(double);
		virtual Conta & retirada(double);
		virtual Conta & transferencia(double, Conta &);
		virtual Conta & info() = 0;
		virtual Conta & extrato() = 0;

		virtual Conta & setSaldo(double saldo){
			this->saldo = saldo;
			return *this;
		}

		virtual Conta & setPessoa(Pessoa* p){
			this->cliente = p;
			return * this;
		}

		inline string getTipo()const{return this->tipoDaConta;}
		inline double getSaldo()const{return this->saldo;}
		inline double getNmr()const{return this->nmr;}
		inline Pessoa* getCliente()const{return this->cliente;}

		Conta & operator<<(double);
		Conta & operator>>(double);

		Conta & cadastrarTransacao(st_transacao t){
			this->transacoes.push_back(t);
			return *this;
		}

	protected:
		Pessoa *cliente;
		string tipoDaConta;
		double nmr, saldo;
		vector<st_transacao> transacoes;
};
#endif