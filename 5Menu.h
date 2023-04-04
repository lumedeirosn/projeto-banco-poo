#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

#include "2PessoaFisica.h"
#include "2PessoaJuridica.h"
#include "3ContaCorrente.h"
#include "3ContaCorrenteLimitada.h"
#include "3ContaPoupanca.h"
#include "1Banco.h"

int verifyNum(string s){
	for(auto &a : s)
		if(!isdigit(a) && a != '.') throw runtime_error("		/!\\ Informe um |NÚMERO VÁLIDO| na próxima vez.");
	return 1;
}

void MENU(Banco &meuBanco) {
    	string opc = "1";
	char continuar = 's';
	while(stoi(opc) >= 1){
		try{
			system("cls");
			cout << endl
			<< "------------------------------------------------------" << endl
			<< "                  " 
			<< "|Bem vindo ao MENU|" << endl
			<< "------------------------------------------------------" << endl
			<< "	1-) Operações |GERENTE|." << endl
			<< "	2-) Operações |CORRENTISTA|." << endl
			<< "	-1 Para SAIR." << endl;
			cout << "Opção-> ";
			cin >> opc;
			
			if(opc != "-1" && opc != "1" && opc != "2") throw runtime_error("		/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");

			if(stoi(opc) == 1){
				string nome, dado, tipo, nmrConta, novoNome;
				continuar = 's';
				while(continuar == 's' || continuar == 'S'){
					cout << endl
					<< "		1- Cadastrar Pessoa." << endl
					<< "		2- Abrir Conta." << endl
					<< "		3- Consultar Conta." << endl
					<< "		4- Atualizar Conta." <<endl
					<< "		5- Excluir Conta." << endl
					<< "		6- Atualizar dados de uma |PESSOA|." << endl
					<< "		7- Listar |CONTAS DE UM CORRENTISTA|." << endl
					<< "		8- Listas as |CONTAS DO BANCO|." << endl
					<< "		9- Listar as |PESSOAS CADASTRADAS|." << endl;
					cout << "Opção-> ";
					cin >> opc;

					if(!isdigit(opc[0]) || opc.size() > 1 || stoi(opc) <= 0 || stoi(opc) > 9) throw runtime_error("		/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");

					switch(stoi(opc)){
						case 1:
							cout << endl <<"	Cadastrando novo |CLIENTE|..." << endl << "	Informe o nome: ";
							cin >> nome;
							cout << " 	Insira o CPF ou o CNPJ: ";
							cin >> dado;
							cout << "	Diga-me se a pessoa é  [fisica/juridica]: ";
							cin >> tipo;
							if(tipo != "fisica" && tipo != "juridica") throw runtime_error("	/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");
							meuBanco.cadastrarPessoa(nome, dado, tipo);
							break;
						
						case 2:
							if(meuBanco.getSizePessoas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |PESSOAS| cadastradas. Cadastre uma nova |PESSOA|.");
							cout << endl << "	Cadastando nova |CONTA|..." <<
							endl << "	1- Para conta |CORRENTE|.\n 	2- Para conta |LIMITADA|.\n 	3- Para conta |POUPANÇA|." << endl;
							cout << "Opção-> ";
							cin >> opc;
							if(opc != "1" && opc != "2" && opc != "3") throw runtime_error("		/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");

							//Colhendo dados
							if(opc == "1"){
								string nome, nmr, saldo;
								cout << "\n	Cadastrando conta |CORRENTE|..." << endl
								<< "	Insira as seguintes |INFORMAÇÔES|..." << endl << "	|NOME DO PROPIETÁRIO|: ";
								cin >> nome;
								cout << "	|NÚMERO DA CONTA|: ";
								cin >> nmr;
								verifyNum(nmr);
								cout << "	|SALDO DA CONTA|: ";
								cin >> saldo;
								verifyNum(saldo);
								meuBanco.cadastrarConta(meuBanco.getPessoa(nome), stoi(nmr), stof(saldo));
							}
							else if(opc == "2"){
								string nome, nmr, saldo, limite;
								cout << "\n	Cadastrando conta |LIMITADA|..." << endl
								<< "	Insira as seguintes |INFORMAÇÔES|..." << endl << "	|NOME DO PROPIETÁRIO|: ";
								cin >> nome;
								cout << "	|NÚMERO DA CONTA|: ";
								cin >> nmr;
								verifyNum(nmr);
								cout << "	|SALDO DA CONTA|: ";
								cin >> saldo;
								verifyNum(saldo);
								cout << "	|LIMITE DA CONTA|: ";
								cin >> limite;
								verifyNum(limite);
								meuBanco.cadastrarConta(meuBanco.getPessoa(nome), stoi(nmr), stof(saldo), stof(limite));
							}
							else{
								string nome, nmr, saldo, dia;
								cout << "\n	Cadastrando conta |POUPANÇA|..." << endl
								<< "	Insira as seguintes |INFORMAÇÔES|..." << endl << "	|NOME DO PROPIETÁRIO|: ";
								cin >> nome;
								cout << "	|NÚMERO DA CONTA|: ";
								cin >> nmr;
								verifyNum(nmr);
								cout << "	|SALDO DA CONTA|: ";
								cin >> saldo;
								verifyNum(saldo);
								cout << "	|DIA DO ANIVERSÁRIO|: ";
								cin >> dia;
								verifyNum(dia);
								meuBanco.cadastrarConta(meuBanco.getPessoa(nome), stoi(nmr), stof(saldo), stoi(dia));
							}
							break;
						
						case 3:
							if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |PESSOAS| no sistema. Cadastre uma nova |CONTA|.");
							cout << "\n	Insira o |NÚMERO DA CONTA|: ";
							cin >> nmrConta;
							verifyNum(nmrConta);
							meuBanco.getConta(stoi(nmrConta))->info();
							break;
						
						case 4:
							if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |CONTAS| para operações. Cadastre uma nova |CONTA|.");
							cout << "\n	Insira o |NÚMERO DA CONTA|: ";
							cin >> nmrConta;
							verifyNum(nmrConta);
							cout << "\n	Atualizando dados..." << endl
							<< "	Insira as seguintes |INFORMAÇÔES|..." << endl << "	|NOME DO |NOVO| PROPIETÁRIO|: ";
							cin >> nome;
							cout << "	| |NOVO| SALDO DA CONTA|: ";
							cin >> dado;
							verifyNum(dado);
							meuBanco.atualizarConta(meuBanco.getPessoa(nome),stof(dado),stoi(nmrConta));
							break;
						
						case 5:
							if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |CONTAS| para operações. Cadastre uma nova |CONTA|.");
							cout << "\n	Insira o |NÚMERO DA CONTA|: ";
							cin >> nmrConta;
							verifyNum(nmrConta);
							meuBanco.removerConta(stoi(nmrConta));
							break;
						
						case 6:
							if(meuBanco.getSizePessoas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |PESSOAS| cadastradas. Cadastre uma nova |PESSOA|.");
							cout << "Informe o nome do |CORRENTISTA A SER |ATUALIZADO| |: ";
							cin >> nome;
							cout << "Digite o |NOVO NOME|: ";
							cin >> novoNome;
							meuBanco.getPessoa(nome)->setNome(novoNome);
							cout << "Diga-me o que vai atualizar |CPF/CNPJ|: ";
							cin >> dado;
							if(dado != "CPF" && dado != "cpf" && dado != "cnpj" && dado != "CNPJ") throw runtime_error("	/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");

							if(dado == "cpf" || dado == "CPF"){
								cout << "Insira o novo CPF: ";
								cin >> dado;
								PessoaFisica *p = dynamic_cast<PessoaFisica*>(meuBanco.getPessoa(novoNome));
								p->setCpf(dado);
								cout << "/!\\ Alterações realizadas com sucesso." << endl;
							}
							else{
								cout << "Insira o novo CNPJ: ";
								cin >> dado;
								PessoaJuridica *p = dynamic_cast<PessoaJuridica*>(meuBanco.getPessoa(novoNome));
								p->setCnpj(dado);
								cout << "/!\\ Alterações realizadas com sucesso." << endl;
							}
							break;
						
						case 7:
							if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |CONTAS| para operações. Cadastre uma nova |CONTA|.");
							cout << "Informe o nome do |CORRENTISTA| : ";
							cin >> nome;
							meuBanco.listarContasCorrentista(nome);
							break;
						
						case 8:
							if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |CONTAS| para operações. Cadastre uma nova |CONTA|.");
							meuBanco.listarContasBanco();
							break;

						case 9:
							if(meuBanco.getSizePessoas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |PESSOAS| cadastradas. Cadastre uma nova |PESSOA|.");
							meuBanco.listarPessoasCadastradas();
					}

					cout << endl << "	Continuar como |GERENTE| ? [S/N] ";
					cin >> continuar;
				}
			}
			else if(stoi(opc) == 2){
				if(meuBanco.getSizeContas() == 0) throw runtime_error("	/!\\ No momento o |BANCO| não possui |CONTAS| para operações. Cadastre uma nova |CONTA|.");
				string nmrConta , valor;
				string nmrConta2; //conta destino para transferencias
				continuar = 's';
				while(continuar == 's' || continuar == 'S'){
					cout << "\n	Insira o |NÚMERO DA CONTA|: ";
					cin >> nmrConta;
					verifyNum(nmrConta);
					cout
					<< "		1- Depósito." << endl
					<< "		2- Saque." << endl
					<< "		3- Transferência." <<endl
					<< "		4- Saldo." << endl
					<< "		5- Extrato." << endl;
					cout << "Opção-> ";
					cin >> opc;

					if(!isdigit(opc[0]) || opc.size() > 1 || stoi(opc) <= 0 || stoi(opc) > 5) throw runtime_error("		/!\\ Informe uma |OPÇÃO VÁLIDA| na próxima vez.");

					switch(stoi(opc)){
						case 1: //
							cout << "\n	Informe o |VALOR|: ";
							cin >> valor;
							verifyNum(valor);
							*meuBanco.getConta(stoi(nmrConta)) << stof(valor);
							break;
						
						case 2: //
							cout << "\n	Informe o |VALOR|: ";
							cin >> valor;
							verifyNum(valor);
							*meuBanco.getConta(stoi(nmrConta)) >> stof(valor);
							break;
						
						case 3: //
							cout << "\n	Informe o |VALOR|: ";
							cin >> valor; //valor
							verifyNum(valor);
							cout << "	Insira o |NÚMERO DA CONTA| para |TRANSFERÊNCIA|: ";
							cin >> nmrConta2;
							if(!isdigit(nmrConta[0])) throw runtime_error("		/!\\ Informe uma |CONTA VÁLIDA| na próxima vez.");
							meuBanco.getConta(stoi(nmrConta))->transferencia(stof(valor), *meuBanco.getConta(stoi(nmrConta2)));
							break;
						
						case 4: //
							cout << "	|SALDO| da conta-> " <<
							meuBanco.getConta(stoi(nmrConta))->getSaldo() << endl;
							break;
						
						case 5: //
							meuBanco.getConta(stoi(nmrConta))->extrato();
							break;
					}

					cout << endl << "	Continuar como |CORRENTISTA| ? [S/N] ";
					cin >> continuar;
				}
			}
		}
		catch(runtime_error &e){
			cerr << e.what() << endl;
			cout << "\n/!\\ Digite |OK| para continuar." << endl;
			cin >> opc;
			opc = "1";
		}
	}
}

#endif