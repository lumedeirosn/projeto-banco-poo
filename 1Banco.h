#ifndef BANCO_H
#define	BANCO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "2PessoaFisica.h"
#include "2PessoaJuridica.h"
#include "3ContaCorrente.h"
#include "3ContaCorrenteLimitada.h"
#include "3ContaPoupanca.h"

typedef struct linePessoa{
	int ident;
	string nome, dado;
}stLinePessoa;

typedef struct lineConta{
	string tipo, propietario;
	int nmrConta, dia, qtdTransacoes;
	double saldo, limite;
}stLineConta;

class Banco: public PessoaJuridica{
	public:
		Banco(string nome = "Banco", string cnpj = "NãoInformado", string nomeBanco = "NãoInformado");
		~Banco();

		Banco & cadastrarPessoa(string, string, string);

		//conta corrente
		Banco & cadastrarConta(Pessoa*, int, double);
		//conta corrente com limite
		Banco & cadastrarConta(Pessoa*, int, double, double);
		//conta poupanca
		Banco & cadastrarConta(Pessoa*, int, double, int);

		Banco & removerConta(int);
		Banco & consultarConta(int);
		Banco & atualizarConta(Pessoa*, double, int);

		Banco & listarContasCorrentista(string);
		Banco & listarContasBanco();
		Banco & listarPessoasCadastradas();

		Conta* getConta(int);
		Pessoa* getPessoa(string);
		int getSizePessoas(){return this->pessoas.size();}
		int getSizeContas(){return this->contas.size();}

	private:
		string nome;
		vector<Pessoa*> pessoas;
		vector<Conta*> contas;
};
#endif
