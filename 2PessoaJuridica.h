#ifndef PESSOAJURIDICA_H
#define PESSOAJURIDICA_H

#include <iostream>
#include <string>
using namespace std;

#include "2Pessoa.h"

class PessoaJuridica: public Pessoa{
	friend ofstream & operator<<(ofstream &fout, const PessoaJuridica &p){
		if (!fout) throw runtime_error("/!\\ Erro!, não consegui acessar o arquivo de dados!");
		fout << 2 << " " << p.getNome() << " " << p.getCnpj() << endl;
		return fout;
	}
	public:
		PessoaJuridica(string nome , string cnpj): Pessoa(nome, 2){
			this->setCnpj(cnpj);
		}
		virtual ~PessoaJuridica(){}
		
		virtual PessoaJuridica & setCnpj(string cnpj){
			this->cnpj = cnpj;
			return *this;
		}

		inline string getCnpj() const {return this->cnpj;}

		virtual void print(){
			cout << "Nome-> " << getNome() << endl
			<< "Cnpj-> " << getCnpj() << endl
			<< "------------------------------" << endl;
		}

	private:
		string cnpj;
};
#endif