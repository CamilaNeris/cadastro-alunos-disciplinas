#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

#define TFA 50
#define TFD 10
#define TFN 100

struct TpAlunos{
	char RA[12], Nome[50];
};

struct TpDisciplinas{
	int CodDisc;
	char Disciplina[20];
};

struct TpNota{
	char RANota[12];
	int CodDiscNota;
	float Nota;
};

int BuscaAlunos(TpAlunos alunos[TFA], int TL, char Aux[12]){
	int i = 0;
	while(i < TL && strcmp(Aux,alunos[i].RA)!=0)
		i++;
	if(i < TL)
		return i;
	else
		return -1;
}

int BuscaCodDisc(TpDisciplinas disc[TFD], int TL, int Aux){
	int i = 0;
	while(i < TL && Aux != disc[i].CodDisc)
		i++;
	if(i < TL)
		return i;
	else
		return -1;
}

void OrdenaAluno(TpAlunos alunos[TFA], int TL){
	int i, j;
	TpAlunos aux;
	
	for(i = 0; i < TL-1; i++)
		for(j = i+1; j < TL; j++)
			if(stricmp(alunos[i].Nome,alunos[j].Nome)>0){
				aux = alunos[i];
				alunos[i] = alunos[j];
				alunos[j] = aux;
			}
			
	printf("\nAlunos Ordenados!\n");
}

void CadastroAlunos(TpAlunos alunos[TFA], int &TL){
	char Aux[12];
	int pos;
	printf("\n### C A D A S T R O  D E  A L U N O S ###\n");
	printf("RA:\n");
	fflush(stdin);
	gets(Aux);
	while(TL < TFA && strcmp(Aux,"\0")!=0){
		pos = BuscaAlunos(alunos,TL,Aux);
		if(pos == -1){
			printf("Aluno nao cadastrado!\n");
			strcpy(alunos[TL].RA,Aux);
			printf("Nome do aluno:\n");
			fflush(stdin);
			gets(alunos[TL].Nome);
			TL++;
			OrdenaAluno(alunos,TL);
		}
		else{
			printf("Aluno ja cadastrado!\n");
			printf("RA: %s \t NOME: %s\n", alunos[pos].RA, alunos[pos].Nome);
		}
		printf("RA:\n");
		fflush(stdin);
		gets(Aux);
	}
}

void ExcluiAluno(TpAlunos alunos[TFA], int &TL){
	char AuxRA[13]; int pos, i;
	if(TL == 0)
		printf("\nNao ha alunos cadastrados!\n");
	else{
		printf("Digite o RA do aluno:\n");
		fflush(stdin);
		gets(AuxRA);
		while(stricmp(AuxRA,"\0")!=0){
			pos = BuscaAlunos(alunos,TL,AuxRA);
			if(pos == -1)
				printf("Aluno nao cadastrado!\n");
			else{
				for(i = pos; i < TL - 1; i++)
					alunos[pos] = alunos[pos + 1];
				TL--;
				printf("\nAluno excluido!\n");
			}
			printf("Digite o RA do aluno:\n");
			fflush(stdin);
			gets(AuxRA);
		}
	}
}

void CadastroDisc(TpDisciplinas disc[TFD], int &TL){
	int Aux, pos;
	printf("\n### C A D A S T R O  D E  D I S C I P L I N A ###\n");
	printf("Codigo da disciplina:\n");
	scanf("%d", &Aux);
	while(TL < TFD && Aux > 0){
		pos = BuscaCodDisc(disc,TL,Aux);
		if(pos == -1){
			printf("Disciplina nao cadastrada!\n");
			disc[TL].CodDisc = Aux;
			printf("Nome da disciplina:\n");
			fflush(stdin);
			gets(disc[TL].Disciplina);
			TL++;
		}
		else{
			printf("Disciplina ja cadastrada!\n");
			printf("CODIGO: %d \t DISCIPLINA: %s\n", disc[pos].CodDisc, disc[pos].Disciplina);
		}
		printf("Codigo da disciplina:\n");
		scanf("%d", &Aux);
	}
}

void AlteraDisc(TpDisciplinas disc[TFD], int TL){
	int auxCod, pos;
	if(TL == 0)
		printf("\nNao ha disciplinas cadastradas!\n");
	else{
		printf("\nDigite o codigo da disciplina que deseja alterar:\n");
		scanf("%d", &auxCod);
		while(auxCod != 0){
			pos = BuscaCodDisc(disc,TL,auxCod);
			if(pos == -1)
				printf("\nDisciplina nao encontrada!\n");
			else{
				printf("Digite o novo codigo da disciplina:\n");
				scanf("%d", &disc[pos].CodDisc);
				printf("Digite o novo nome da disciplina:\n");
				fflush(stdin);
				gets(disc[pos].Disciplina);
				printf("\nDiciplina ALTERADA!\n");
			}
			printf("\nDigite o codigo da disciplina que deseja alterar:\n");
			scanf("%d", &auxCod);
		}
	}
}

void CadastroNotas(TpNota notas[TFN], TpAlunos alunos[TFA], TpDisciplinas disc[TFD], int TLA, int TLD, int &TLN){
	char Aux[12];
	int i, pos, AuxCod;
	printf("\n### C A D A S T R O  D E  N O T A S ###\n");
	printf("RA:\n");
	fflush(stdin);
	gets(Aux);
	while(TLN < TFN && strcmp(Aux,"\0")!=0){
		pos = BuscaAlunos(alunos,TLA,Aux);
		if(pos == -1)
			printf("RA nao cadastrado!\n");
		else{
			strcpy(notas[TLN].RANota,Aux);
			printf("Codigo da disciplina:\n");
			scanf("%d",&AuxCod);
			pos = BuscaCodDisc(disc,TLD,AuxCod);
			if(pos == -1)
				printf("Codigo nao cadastrado!\n");
			else{
				notas[TLN].CodDiscNota = AuxCod; 
				printf("Nota:\n");
				scanf("%f", &notas[TLN].Nota);
				TLN++;
			}
		}
		printf("RA:\n");
		fflush(stdin);
		gets(Aux);
	}
	for(i = 0; i < TLN; i++)
		printf("CodDisc: %d\t Nota: %.2f\n", notas[i].CodDiscNota, notas[i].Nota);
	
}


void Relatorio(TpNota notas[TFN], TpAlunos alunos[TFA], TpDisciplinas disc[TFD], int TLA, int TLD, int TLN){
	int i, j, pos;
	printf("\n### R E L A T O R I O  D E  A L U N O S ###\n");
	if(TLA == 0)
		printf("Nao ha alunos cadastrados!\n");
	else
		for(i = 0; i < TLA; i++){
				printf("RA: %s\t NOME: %s\t\n", alunos[i].RA, alunos[i].Nome);
				for(j = 0; j < TLN; j++){
					if(strcmp(alunos[i].RA,notas[j].RANota)==0)
						printf("Disciplina: %d\t Nota: %.2f\n", notas[j].CodDiscNota, notas[j].Nota);
				}
				
		}
}

void AlteraAluno(TpAlunos alunos[TFA], int TL){
	int pos;
	char Aux[14];
	if(TL == 0)
		printf("Nao existem alunos cadastrados!\n");
	else{
		printf("### A L T E R A R  A L U N O ###\n");
		printf("RA:\n");
		fflush(stdin);
		gets(Aux);
		while(strcmp(Aux,"\0")!=0){
			pos = BuscaAlunos(alunos,TL,Aux);
			if(pos == -1)
				printf("Aluno nao cadastrado!\n");
			else{
				printf("NOVO nome:\n");
				fflush(stdin);
				gets(alunos[pos].Nome);
			}
		}
	}
}

char Menu(void){
	printf("=========  M E N U  =========\n");
	printf("[A]   - CADASTRAR ALUNO\n");
	printf("[B]   - CADASTRAR DISCIPLINA\n");
	printf("[C]   - CADASTRAR NOTAS\n");
	printf("[D]   - RELATORIO\n");
	printf("[E]   - ALTERAR ALUNO\n");
	printf("[F]   - EXCLUIR ALUNO\n");
	printf("[G]   - ALTERAR DISCIPLINA\n");
	printf("[ESC] - SAIR\n");
	
	return toupper(getche());
}

int main(void){
	char op;
	TpAlunos alunos[TFA];
	TpDisciplinas disc[TFD];
	TpNota notas[TFN];
	int TLA = 0, TLD = 0, TLN = 0;
	
	do{
		op = Menu();
		switch(op){
			case 'A':CadastroAlunos(alunos,TLA);
				break;
			case 'B':CadastroDisc(disc,TLD);
				break;
			case 'C':CadastroNotas(notas,alunos,disc,TLA,TLD,TLN);
				break;
			case 'D':Relatorio(notas,alunos,disc,TLA,TLD,TLN);
				break;
			case 'E':AlteraAluno(alunos,TLA);
				break;
			case 'F':ExcluiAluno(alunos,TLA);
				break;
			case 'G':AlteraDisc(disc,TLD);
				break;
		}	
	}while(op != 27);
	
	return 0;
}
