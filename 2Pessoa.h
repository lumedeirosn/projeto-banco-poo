#ifndef PESSOA_H
#define	PESSOA_H

#include <string>

class Pessoa{
	public:
		Pessoa(string nome, int ident): ident(ident){
			this->setNome(nome);
		}
		virtual ~Pessoa(){}

		virtual Pessoa & setNome(string nome){
			this->nome = nome;
			return *this;
		}

		inline string getNome() const {return this->nome;}
		inline int getIdent() const {return this->ident;}

		virtual void print() = 0;
		
	private:
		string nome;
		int ident;
};
#endif