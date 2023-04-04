#include <iostream>
#include <ctime>
using namespace std;

#include "3ContaCorrenteLimitada.h"

ofstream & operator<<(ofstream &fout, const ContaCorrenteLimitada &c){
	if(!fout) throw runtime_error("/!\\ Erro!, não consegui acessar o arquivo de dados para contas!");

	fout << c.getTipo() << " " << c.cliente->getNome() << " " << c.getNmr() << " " << c.getSaldo() << " " << c.limite << " " << 0 << " " << c.transacoes.size();
	
	for(auto &n : c.transacoes){
		fout << " " << n.tipo << " " << n.data << " " << n.descricao << " " << n.valor;
	}
	fout << endl;
	return fout;
}

Conta & ContaCorrenteLimitada::info(){
	cout << "----------------------" << endl;
	cout << "TipoDaConta-> " << this->tipoDaConta;
	cout << "\nNmrDaConta-> " << this->nmr << "\nNomeDoCliente-> " << this->cliente->getNome() << "\nValorDoLimite-> " << this->limite << "\nSaldoDaConta-> " << this->saldo << endl;
	cout << "----------------------" << endl;
	return *this;
}
Conta & ContaCorrenteLimitada::retirada(double valor){
	if(saldo - valor >= limite && valor > 0){
		st_transacao *transacao = new st_transacao;
		transacao->data = "21/05/2021";
		transacao->descricao = "saque";
		transacao->tipo = "débito";
		transacao->valor = valor;

		transacoes.push_back(*transacao);
		saldo -= valor;
	}
	else throw runtime_error("/!\\ 	Valor para saque está fora do |LIMITE DISPONÍVEL| ou é |NULO|.");

	cout << "	/!\\ Operação realizada com sucesso!" << endl;
	return *this;
}

Conta & ContaCorrenteLimitada::extrato(){
	cout << "\nTipoDaConta-> " << this->tipoDaConta;
	cout << "\nNmrDaConta-> " << this->nmr << "\nNomeDoCliente-> " << this->cliente->getNome() << "\nValorDoLimite-> " << this->limite << "\nSaldoDaConta-> " << this->saldo << endl;
			
	cout << "\nExtrato:" << endl;
	for(int i = 0 ; i < this->transacoes.size() && i < 30 ; i++){
		cout << "----------------------" <<endl;
		cout << "Tipo-> " << this->transacoes[i].tipo << "\nData-> " << this->transacoes[i].data << "\nValor-> " << this->transacoes[i].valor << "\nDescrição-> " << this->transacoes[i].descricao << endl;
	}
	cout << endl;
	return *this;
}