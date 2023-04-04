#include <iostream>
using namespace std;

#include "3ContaPoupanca.h"

ofstream & operator<<(ofstream &fout, const ContaPoupanca &c){
	if(!fout) throw runtime_error("/!\\ Erro!, não consegui acessar o arquivo de dados para contas!");

	fout << c.getTipo() << " " << c.cliente->getNome() << " " << c.getNmr() << " " << c.getSaldo() << " " << 0 << " " << c.diaAniversario << " " << c.transacoes.size();
	
	for(auto &n : c.transacoes){
		fout << " " << n.tipo << " " << n.data << " " << n.descricao << " " << n.valor;
	}
	fout << endl;
	return fout;
}

Conta & ContaPoupanca::info(){
	cout << "----------------------" << endl;
	cout << "TipoDaConta-> " << this->tipoDaConta;
	cout << "\nNmrDaConta-> " << this->nmr << "\nNomeDoCliente-> " << this->cliente->getNome() << "\nDiaDoAniversário-> " << this->diaAniversario << "\nSaldoDaConta-> " << this->saldo << endl;
	cout << "----------------------" << endl;
	return *this;
}

Conta & ContaPoupanca::extrato(){
	cout << "\nTipoDaConta-> " << this->tipoDaConta;
	cout << "\nNmrDaConta-> " << this->nmr << "\nNomeDoCliente-> " << this->cliente->getNome() << "\nDiaDoAniversário-> " << this->diaAniversario << "\nSaldoDaConta-> " << this->saldo << endl;
			
	cout << "\nExtrato:" << endl;
	for(int i = 0 ; i < this->transacoes.size() && i < 30 ; i++){
		cout << "----------------------" <<endl;
		cout << "Tipo-> " << this->transacoes[i].tipo << "\nData-> " << this->transacoes[i].data << "\nValor-> " <<this-> transacoes[i].valor << "\nDescrição-> " << this->transacoes[i].descricao << endl;
	}
	cout << endl;
	return *this;
}