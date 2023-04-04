#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H

#include <iostream>
#include <string>
#include <fstream>
using std::ofstream, std::ifstream;
using namespace std;

#include "2Pessoa.h"

class PessoaFisica: public Pessoa{

	friend ofstream & operator<<(ofstream &fout, const PessoaFisica &p){
		if (!fout) throw runtime_error("/!\\ Erro!, não consegui acessar o arquivo de dados!");
		fout << 1 << " " << p.getNome() << " " << p.getCpf() << endl;
		return fout;
	}

	public:
		PessoaFisica(string nome, string cpf):Pessoa(nome, 1){
			this->setCpf(cpf);
		}
		virtual ~PessoaFisica(){}
		
		virtual PessoaFisica & setCpf(string cpf){
			this->cpf = cpf;
			return *this;
		}

		inline string getCpf() const {return this->cpf;}
	

		virtual void print(){
			cout << "Nome-> " << getNome() << endl
			<< "Cpf-> " << getCpf() << endl
			<< "------------------------------" << endl;
		}

	private:
		string cpf;
};
#endif