#include <iostream>
#include <windows.h>

HANDLE cor;


struct peca
{
	int lado;
	int tipo;
	int posy;
	int posx;
	int selecionado = 0;
};

enum tipo
{
	VAZIO = 0, PEAO = 1, TORRE = 2, BISPO = 3, CAVALO = 4, RAINHA = 5, REI = 6,
	PRETO = 7, BRANCO = 8
};
std::string get_name(int tipo)
{
	switch (tipo)
	{
	case PEAO:
		return "peao";
	case TORRE:
		return "torre";
	case BISPO:
		return "bispo";
	case CAVALO:
		return "cavalo";
	case RAINHA:
		return "rainha";
	case REI:
		return "rei";
	}
	return "invalido";
}
peca a[8][8];
peca vazio{ VAZIO,VAZIO,4,4 };

void desenhar()
{
	std::cout << "#|abcdefgh" << std::endl;
	std::cout << "-|--------" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << i + 1<< "|";
		for (int j = 0; j < 8; j++)
		{
			if (a[i][j].selecionado == 1)
			{
				SetConsoleTextAttribute(cor, 6);
				a[i][j].selecionado = 0;
			}
			
			switch (a[i][j].tipo)
			{
			case VAZIO:
				std::cout << ".";
				break;
			case PEAO:
				if(a[i][j].lado == BRANCO)
					std::cout << "P";
				else
					std::cout << "p";
				break;
			case TORRE:
				if (a[i][j].lado == BRANCO)
					std::cout << "T";
				else
					std::cout << "t";
				break;
			case CAVALO:
				if (a[i][j].lado == BRANCO)
					std::cout << "C";
				else
					std::cout << "c";
				break;
			case BISPO:
				if (a[i][j].lado == BRANCO)
					std::cout << "B";
				else
					std::cout << "b";
				break;
			case REI:
				if (a[i][j].lado == BRANCO)
					std::cout << "K";
				else
					std::cout << "k";
				break;
			case RAINHA:
				if (a[i][j].lado == BRANCO)
					std::cout << "Q";
				else
					std::cout << "q";
				break;
			}
			SetConsoleTextAttribute(cor, 7);
		}
		std::cout << std::endl;

	}
	std::wcout << std::endl;
}

int selecionar(int turno)
{
	if (turno == BRANCO)
		std::cout << "turno do Branco ";
	else if (turno == PRETO)
		std::cout << "turno do preto ";

	std::cout << "selecione uma peca \n";
	int pos = 99;
	bool pos_valida = false;
	while (pos_valida == false)
	{
		std::cin >> pos;
		pos = pos - 11;

		if (pos < 00 || pos>77)
			std::cout << "posicao invalida\n";
		else if (a[pos / 10][pos % 10].tipo == VAZIO)
			std::cout << "espaco vazio\n";
		else if (a[pos / 10][pos % 10].lado != turno)
			std::cout << " essa nao e sua peca\n";
		else
			pos_valida=true;
	}
	
	std::cout << get_name(a[pos / 10][pos % 10].tipo) << " selecionado " << " posicao y=" << (pos / 10)+1 << " posicao x=" << (pos % 10) +1 << ".\n";
	
	a[pos / 10][pos % 10].selecionado = 1;

	return pos;
}

void mover(int pos, int lado)
{
	int nova_pos;
	
	
	bool pos_valida = false;
	while (pos_valida == false)
	{
		std::cout << "mover para: ";


		desenhar();

		std::cin >> nova_pos;
		nova_pos = nova_pos - 11;
		switch (a[pos / 10][pos % 10].tipo)
		{
		case PEAO:
			if (a[pos / 10][pos % 10].lado == PRETO && nova_pos == pos + 10)
				pos_valida = true;
			else if (a[pos / 10][pos % 10].lado == BRANCO && nova_pos == pos - 10)
				pos_valida = true;
			break;
		case TORRE:
			std::cout << "T";
			break;
		case CAVALO:
			std::cout << "C";
			break;
		case BISPO:
			std::cout << "B";
			break;
		case REI:
			std::cout << "K";
			break;
		case RAINHA:
			std::cout << "Q";
			break;
		}
		if (pos_valida == false)
			std::cout << "posicao invalida \n";

	}
	a[nova_pos / 10][nova_pos % 10] = a[pos / 10][pos % 10];
	a[pos / 10][pos % 10] = vazio;
}

int main()
{
	cor = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	a[4][4] = vazio;
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			a[i][j]= vazio;
		}
	}

	peca torrep1{ PRETO,TORRE,0,0 }; a[0][0] = torrep1;
	peca cavalop1 { PRETO,CAVALO,0,1 }; a[0][1] = cavalop1;
	peca bispop1 { PRETO,BISPO,0,2}; a[0][2] = bispop1;
	peca rainhap { PRETO,RAINHA,0,3 }; a[0][3] = rainhap;
	peca reip{ PRETO,REI,0,4 }; a[0][4] = reip;
	peca bispop2{ PRETO,BISPO,0,5 }; a[0][5] = bispop2;
	peca cavalop2 { PRETO,CAVALO,0,6 }; a[0][6] = cavalop2;
	peca torrep2{ PRETO,TORRE,0,7 }; a[0][7] = torrep2;

	peca peaop1{ PRETO,PEAO,1,0 }; a[1][0] = peaop1;
	peca peaop2{ PRETO,PEAO,1,1 }; a[1][1] = peaop2;
	peca peaop3{ PRETO,PEAO,1,2 }; a[1][2] = peaop3;
	peca peaop4{ PRETO,PEAO,1,3 }; a[1][3] = peaop4;
	peca peaop5{ PRETO,PEAO,1,4 }; a[1][4] = peaop5;
	peca peaop6{ PRETO,PEAO,1,5 }; a[1][5] = peaop6;
	peca peaop7{ PRETO,PEAO,1,6 }; a[1][6] = peaop7;
	peca peaop8{ PRETO,PEAO,1,7 }; a[1][7] = peaop8;
	

	peca torreb1{ BRANCO,TORRE,7,0 }; a[7][0] = torreb1;
	peca cavalob1{ BRANCO,CAVALO,7,1 }; a[7][1] = cavalob1;
	peca bispob1{ BRANCO,BISPO,7,2 }; a[7][2] = bispob1;
	peca rainhab{ BRANCO,RAINHA,7,3 }; a[7][3] = rainhab;
	peca reib{ BRANCO,REI,7,4 }; a[7][4] = reib;
	peca bispob2{ BRANCO,BISPO,7,5 }; a[7][5] = bispob2;
	peca cavalob2{ BRANCO,CAVALO,7,6 }; a[7][6] = cavalob2;
	peca torreb2{ BRANCO,TORRE,7,7 }; a[7][7] = torreb2;



	peca peaob1{ BRANCO,PEAO,6,0 }; a[6][0] = peaob1;
	peca peaob2{ BRANCO,PEAO,6,1 }; a[6][1] = peaob2;
	peca peaob3{ BRANCO,PEAO,6,2 }; a[6][2] = peaob3;
	peca peaob4{ BRANCO,PEAO,6,3 }; a[6][3] = peaob4;
	peca peaob5{ BRANCO,PEAO,6,4 }; a[6][4] = peaob5;
	peca peaob6{ BRANCO,PEAO,6,5 }; a[6][5] = peaob6;
	peca peaob7{ BRANCO,PEAO,6,6 }; a[6][6] = peaob7;
	peca peaob8{ BRANCO,PEAO,6,7 }; a[6][7] = peaob8;

	int vencedor = VAZIO;
	int turno = PRETO;
	while (vencedor == VAZIO)
	{
		desenhar();
		mover(selecionar(turno),turno);

		if (turno == PRETO)
			turno = BRANCO;
		else
			turno = PRETO;
	}

	return 0;
}