#include <iostream>
#include <string>
using namespace std;

#include "3Conta.h"


Conta & Conta::operator<<(double valor){
	this->deposito(valor);
	return *this;
}

Conta & Conta::operator>>(double valor){
	this->retirada(valor);
	return *this;
}

Conta::~Conta(){
	this->transacoes.clear();
}

Conta &Conta::deposito(double valor){
	st_transacao *transacao = new st_transacao;
	transacao->data = "21/05/2021";
	transacao->descricao = "depósito";
	transacao->tipo = "crédito";
	transacao->valor = valor;

	this->transacoes.push_back(*transacao);
	this->saldo += valor;
	cout << "	/!\\ Operação realizada com sucesso!" << endl;
	return *this;
}

Conta &Conta::retirada(double valor){
	if(valor >= this->saldo || valor <= 0) throw runtime_error("	/!\\ Valor para saque está fora do |LIMITE DISPONÍVEL| ou é |NULO|.");	
	else{
		st_transacao *transacao = new st_transacao;
		transacao->data = "21/05/2021";
		transacao->descricao = "saque";
		transacao->tipo = "débito";
		transacao->valor = valor;

		this->transacoes.push_back(*transacao);
		this->saldo -= valor;
		cout << "	/!\\ Operação realizada com sucesso!" << endl;
	}
	return *this;
}

Conta & Conta::transferencia(double valor, Conta &c){
	*this >> valor;
	c << valor;
	return *this;
}