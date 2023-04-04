#include "1Banco.h"

Banco::Banco(string nome, string cnpj, string nomeBanco)
	: PessoaJuridica(nome, cnpj), nome(nomeBanco) {
	ifstream fin("01dados.dat", ios::in);
	if (!fin)
		throw runtime_error(
			"/!\\ Erro!, não consegui acessar o arquivo de dados!");

	int qtdPessoas, qtdContas;
	fin >> qtdPessoas >> qtdContas;

	// lendo as pessoas;
	stLinePessoa linhaPessoa;
	for (int i = 0; i < qtdPessoas; i++) {
		fin >> linhaPessoa.ident >> linhaPessoa.nome >> linhaPessoa.dado;

		if (linhaPessoa.ident == 1)
			cadastrarPessoa(linhaPessoa.nome, linhaPessoa.dado, "fisica");
		else
			cadastrarPessoa(linhaPessoa.nome, linhaPessoa.dado, "juridica");
	}

	// lendo as contas;
	stLineConta linhaConta;
	st_transacao linhaTransacoes;
	for (int i = 0; i < qtdContas; i++) {
		fin >> linhaConta.tipo >> linhaConta.propietario >>
			linhaConta.nmrConta >> linhaConta.saldo >> linhaConta.limite >>
			linhaConta.dia >> linhaConta.qtdTransacoes;

		if (linhaConta.tipo == "ContaCorrente.") {
			cadastrarConta(
				getPessoa(linhaConta.propietario),
				linhaConta.nmrConta,
				linhaConta.saldo);
			for (int i = 0; i < linhaConta.qtdTransacoes; i++) {
				fin >> linhaTransacoes.tipo >> linhaTransacoes.data >>
					linhaTransacoes.descricao >> linhaTransacoes.valor;

				st_transacao *transacao = new st_transacao;
				transacao->data = linhaTransacoes.data;
				transacao->descricao = linhaTransacoes.descricao;
				transacao->tipo = linhaTransacoes.tipo;
				transacao->valor = linhaTransacoes.valor;
				getConta(linhaConta.nmrConta)->cadastrarTransacao(*transacao);
			}
		} else if (linhaConta.tipo == "ContaCorrenteComLimite.") {
			cadastrarConta(
				getPessoa(linhaConta.propietario),
				linhaConta.nmrConta,
				linhaConta.saldo,
				linhaConta.limite);
			for (int i = 0; i < linhaConta.qtdTransacoes; i++) {
				fin >> linhaTransacoes.tipo >> linhaTransacoes.data >>
					linhaTransacoes.descricao >> linhaTransacoes.valor;

				st_transacao *transacao = new st_transacao;
				transacao->data = linhaTransacoes.data;
				transacao->descricao = linhaTransacoes.descricao;
				transacao->tipo = linhaTransacoes.tipo;
				transacao->valor = linhaTransacoes.valor;
				getConta(linhaConta.nmrConta)->cadastrarTransacao(*transacao);
			}
		} else {
			cadastrarConta(
				getPessoa(linhaConta.propietario),
				linhaConta.nmrConta,
				linhaConta.saldo,
				linhaConta.dia);
			for (int i = 0; i < linhaConta.qtdTransacoes; i++) {
				fin >> linhaTransacoes.tipo >> linhaTransacoes.data >>
					linhaTransacoes.descricao >> linhaTransacoes.valor;

				st_transacao *transacao = new st_transacao;
				transacao->data = linhaTransacoes.data;
				transacao->descricao = linhaTransacoes.descricao;
				transacao->tipo = linhaTransacoes.tipo;
				transacao->valor = linhaTransacoes.valor;
				getConta(linhaConta.nmrConta)->cadastrarTransacao(*transacao);
			}
		}
	}
	fin.close();
}

Banco::~Banco() {
	// gravação das pessoas
	ofstream fout("01dados.dat", ios::out);
fout << this->pessoas.size() << " " << this->contas.size()<< endl;

for(int i = 0 ; i < this->pessoas.size() ; i++){
	if(this->pessoas[i]->getIdent() == 1){
		PessoaFisica *p = dynamic_cast<PessoaFisica*>(this->pessoas[i]);
		fout << *p;
	}
	else{
		PessoaJuridica *p = dynamic_cast<PessoaJuridica*>(this->pessoas[i]);
		fout << *p;
	}
}
this->pessoas.clear();

//gravação das contas
for(int i = 0 ; i < this->contas.size() ; i++){
	if(this->contas[i]->getTipo() == "ContaCorrente."){
		ContaCorrente *c = dynamic_cast<ContaCorrente*>(this->contas[i]);
		fout << *c;
	}
	else if(this->contas[i]->getTipo() == "ContaCorrenteComLimite."){
		ContaCorrenteLimitada *c =
dynamic_cast<ContaCorrenteLimitada*>(this->contas[i]); fout << *c;
	}
	else{
		ContaPoupanca *c = dynamic_cast<ContaPoupanca*>(this->contas[i]);
		fout << *c;
	}
}
this->contas.clear();
	fout.close();
}

Banco &Banco::cadastrarPessoa(string nome, string nmr, string tipo) {
	for (auto &n : this->pessoas) {
		if (n->getNome() == nome)
			throw runtime_error("	/!\\ Essa pessoa já |EXISTE NO SISTEMA|!");
	}
	Pessoa *p;
	if (tipo == "fisica") {
		p = new PessoaFisica(nome, nmr);
		this->pessoas.push_back(p);
	} else {
		p = new PessoaJuridica(nome, nmr);
		this->pessoas.push_back(p);
	}
	cout << "	/!\\ Pessoa cadastrada com sucesso!" << endl;
	return *this;
}

Banco &Banco::cadastrarConta(Pessoa *pessoa, int nmr, double saldo) {
	for (auto &n : this->contas) {
		if (n->getNmr() == nmr)
			throw runtime_error("	/!\\ Esse número já |EXISTE NO SISTEMA|!");
	}
	Conta *c = new ContaCorrente(pessoa, nmr, saldo);
	this->contas.push_back(c);
	cout << "	/!\\ Conta |CORRENTE| cadastrada com sucesso!" << endl;
	return *this;
}

Banco &
Banco::cadastrarConta(Pessoa *pessoa, int nmr, double saldo, double limite) {
	for (auto &n : this->contas) {
		if (n->getNmr() == nmr)
			throw runtime_error("	/!\\ Esse número já |EXISTE NO SISTEMA|!");
	}
	Conta *c = new ContaCorrenteLimitada(pessoa, nmr, saldo, limite);
	this->contas.push_back(c);
	cout << "	/!\\ Conta |CORRENTE LIMITADA| cadastrada com sucesso!" << endl;
	return *this;
}

Banco &Banco::cadastrarConta(Pessoa *pessoa, int nmr, double saldo, int dia) {
	for (auto &n : this->contas) {
		if (n->getNmr() == nmr)
			throw runtime_error("	/!\\ Esse número já |EXISTE NO SISTEMA|!");
	}
	Conta *c = new ContaPoupanca(pessoa, nmr, saldo, dia);
	this->contas.push_back(c);
	cout << "	/!\\ Conta |CORRENTE POUPANÇA| cadastrada com sucesso!" << endl;
	return *this;
}

Banco &Banco::removerConta(int num) {
	int cont = 0;
	for (int i = this->contas.size() - 1; i >= 0; i--) {
		cont++;
		if (this->contas[i]->getNmr() == num) {
			this->contas.erase(this->contas.end() - cont);
			cout << "	/!\\ Conta |REMOVIDA| com sucesso!" << endl;
			return *this;
		}
	}
	throw runtime_error("/!\\		|CONTA| não encontrada!, insira "
						"informações |VÁLIDAS| na próxima vez.");
}

Banco &Banco::consultarConta(int num) {
	for (int i = 0; i < this->contas.size(); i++)
		if (this->contas[i]->getNmr() == num) {
			this->contas[i]->info();
			return *this;
		}
	throw runtime_error("/!\\		|CONTA| não encontrada!, insira "
						"informações |VÁLIDAS| na próxima vez.");
	return *this;
}

Banco &
Banco::atualizarConta(Pessoa *novaPessoa, double novoSaldo, int numConta) {
	for (int i = 0; i < this->contas.size(); i++)
		if (this->contas[i]->getNmr() == numConta) {
			this->contas[i]->setPessoa(novaPessoa);
			this->contas[i]->setSaldo(novoSaldo);
			cout << "	/!\\ Conta |ATUALIZADA| com sucesso!" << endl;
			return *this;
		}
	throw("/!\\		|CONTA| não encontrada!, insira informações |VÁLIDAS| na "
		  "próxima vez.");
	return *this;
}

Banco &Banco::listarContasCorrentista(string correntista) {
	bool aux = true;
	for (int i = 0; i < this->contas.size(); i++)
		if (this->contas[i]->getCliente()->getNome() == correntista) {
			this->contas[i]->info();
			aux = false;
		}
	if (aux)
		throw runtime_error("/!\\		|CORRENTISTA| não encontrado!, insira "
							"informações |VÁLIDAS| na próxima vez.");
	return *this;
}

Banco &Banco::listarContasBanco() {
	for (auto &n : this->contas) {
		n->info();
	}
	return *this;
}

Banco &Banco::listarPessoasCadastradas() {
	cout << "\nPessoas |CADASTRADAS NO SISTEMA|:" << endl
		 << "------------------------------" << endl;
	for (auto &n : this->pessoas)
		n->print();
	return *this;
}

Conta *Banco::getConta(int num) {
	for (int i = 0; i < this->contas.size(); i++)
		if (this->contas[i]->getNmr() == num)
			return this->contas[i];
	throw runtime_error("/!\\		|CONTA| não encontrada!, insira "
						"informações |VÀLIDAS| na próxima vez.");
}

Pessoa *Banco::getPessoa(string nome) {
	for (int i = 0; i < this->pessoas.size(); i++)
		if (this->pessoas[i]->getNome() == nome)
			return this->pessoas[i];
	throw runtime_error("/!\\		|PESSOA| não encontrada!, insira "
						"informações |VÀLIDAS| na próxima vez.");
}
