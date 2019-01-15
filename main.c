#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_UTILIZADORES 21
#define MAX_RECURSOS 100
#define MAX_ACESSOS 200
#define MAX_CARACTERES 50

typedef struct
{
    char nome[MAX_CARACTERES];
    int ID_Utilizador;
    int NIC;
    char login_utilizador[MAX_CARACTERES];
    char password_utilizador[MAX_CARACTERES];
} t_utilizadores;

typedef struct
{
    int dia;
    int mes;
    int ano;
} t_data;

typedef struct
{
    int hora;
    int minutos;
} t_hour;

typedef struct
{
    int id_recurso;
    int id_utilizador;
    char nome[MAX_CARACTERES];
    char login[MAX_CARACTERES];
    char password[MAX_CARACTERES];
    t_data data;
    t_hour hora;
} t_acessos;

typedef struct
{
    int ID_Recurso;
    char nome[MAX_CARACTERES];
    int tipo_recurso;
    int grau_seguranca;
    char designacao[MAX_CARACTERES];
} t_recursos;


///Funções Gerador de Passwords (EXTRA)/////////////////
void gerador_num(void);
void gerador_letras(int quant4);
void gerador_razovel(int quant);
void gerador_dificil(int quant2);
int le_num(void);
int gerador_nume[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
char gerador_ltr[52] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char gerador_espec[18] = { '_', '.', '-', '$', '/', '&', '(', ')', '[', ']', '?', '!', '@', '=', '+', '*' };
///Funções Gerador de Passwords (EXTRA)/////////////////


///Funções Menus/////////////////
int MenuInicial(void);
int MenuRegistar(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores, int *seq_ID_Utlizador);
int MenuLogin (t_utilizadores user_registo[MAX_UTILIZADORES],int contador_utilizadores);
char MenuPrincipal(t_utilizadores user_registo[MAX_UTILIZADORES], int utilizador_logado);
char MenuGestor(void);
void MenuSobre(void);
char MenuGerador(void);
char MenuGestorRecursos(void);
char ConfirmarSaida(int ficheiro_guardado);
char MenuExtras(void);
char MenuGestorAcessos(void);
char MenuMinhaConta();
char MenuAlterarUtilizadores();
char MenuUtilizadores();
///Funções Menus/////////////////


///Funções Acessos/////////////////
int InserirAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_ACESSOS], int contador_a, int contador_r, int id_utilizador);
void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador, char mostrar[MAX_CARACTERES]);
void AlterarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador);
void EliminarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int contador_r, int id_utilizador);
///Funções Acessos/////////////////


///Funções Recursos/////////////////
int InserirRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r, int *seq_ID_Recursos);
void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r);
void AlterarRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r);
void EliminarRecursos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int *contador_r, int id_utilizador);
///Funções Recursos/////////////////


///Funções Utilizadores/////////////////
void VerUtilizadores(t_utilizadores user_registo[MAX_UTILIZADORES],int contador_utilizadores, int utilizador_logado);
int InserirAdmin(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void AlterarUtilizadoresNome(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void AlterarUtilizadoresLogin(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void AlterarUtilizadoresPasswords(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void AlterarUtilizadoresNIC(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void AlterarUtilizadores(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
void EliminarUtilizadores(t_utilizadores user_registo[MAX_UTILIZADORES], t_acessos array_acessos[MAX_ACESSOS], int *contador_utilizadores, int id_utilizador, int contador_a);
void VerDadosUtilizador(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores);
///Funções Utilizadores/////////////////


///Outras Funções/////////////////
void VerificadorPassword(t_recursos array_recursos[], int contador_r, char *password[]);
void ler_ficheiro(t_utilizadores user_registo[MAX_UTILIZADORES], t_recursos array_recursos[MAX_ACESSOS], t_acessos array_acessos[MAX_RECURSOS], int *contador_utilizadores, int *contador_r, int *contador_a);
int guardar_ficheiro(t_utilizadores user_registo[MAX_UTILIZADORES], t_recursos array_recursos[MAX_ACESSOS], t_acessos array_acessos[MAX_RECURSOS], int contador_utilizadores, int contador_r, int contador_a);
t_data getdate();
t_hour gethour();
///Outras Funções/////////////////


///Funções das estatisticas///////////////
char MenuEstatisticas(t_utilizadores user_registo[MAX_UTILIZADORES], int utilizador_logado);
void  ListagemRecursosPorTipo(t_recursos array_recursos[], int *contador_r);
void  ListagemAcessos(t_utilizadores user_registo[], t_acessos array_acessos[], int contador_utilizadores, int *contador_a);
void RecursoComMaisAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r);
void UtilizadorComMaisAcessos(t_acessos array_acessos[], t_utilizadores user_registo[], int contador_a, int contador_r, int contador_registar);
void DiasDesdeUltimoAcesso(t_recursos array_recursos[], t_acessos array_acessos[], int contador_r, int contador_a);
///Funções das estatisticas///////////////

int main()
{
    system("chcp 65001");
    system("cls");
    char opcao, opcao2, opcao3, opcao4, opcao5, opcao6, opcao7, opcao8, opcao9, opcao10, sair, string[MAX_CARACTERES];
    int contador_acessos = 0, contador_recursos = 0, contador_registar=0, seq_ID_Utlizador=0, seq_ID_Recursos=0, utilizador_logado = -1, opc_register, pwd, ficheiro_guardado=0;
    t_acessos arr_acessos[MAX_ACESSOS];
    t_recursos arr_recursos[MAX_RECURSOS];
    t_utilizadores user_registo[MAX_UTILIZADORES];

    contador_registar = InserirAdmin(user_registo, contador_registar);
    ler_ficheiro(user_registo, arr_recursos, arr_acessos, &contador_registar, &contador_recursos, &contador_acessos);

    do
    {
        do
        {
            opc_register=MenuInicial();
            switch(opc_register)
            {
            case 1:
                utilizador_logado = -1;
                utilizador_logado = MenuLogin(user_registo, contador_registar);
                break;
            case 2:
                utilizador_logado = -1;
                contador_registar = MenuRegistar(user_registo, contador_registar, &seq_ID_Utlizador);
                break;
            case 3:
                sair = ConfirmarSaida(ficheiro_guardado);
                if(sair=='S')
                    return 0;
                else
                    break;
            default:
                printf("\n\tOpção Inválida!\n");
                getch();
            }
        }
        while(utilizador_logado == -1);

        do
        {
            opcao=MenuPrincipal(user_registo, utilizador_logado);
            switch (opcao)
            {
            case 'A':
                do
                {
                    opcao2=MenuGestor();
                    switch(opcao2)
                    {
                    case 'A':
                        do
                        {
                            opcao3 = MenuGestorAcessos();
                            switch (opcao3)
                            {
                            case 'A':
                                contador_acessos = InserirAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, user_registo[utilizador_logado].ID_Utilizador);
                                break;
                            case 'B':
                                VerAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, utilizador_logado, string);
                                break;
                            case 'C':
                                AlterarAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, utilizador_logado);
                                break;
                            case 'D':
                                EliminarAcessos(arr_acessos, arr_recursos, &contador_acessos, contador_recursos, utilizador_logado);
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while (opcao3 != 'V');
                        break;
                    case 'B':
                        do
                        {
                            opcao4 = MenuGestorRecursos();
                            switch(opcao4)
                            {
                            case 'A':
                                contador_recursos = InserirRecursos(arr_recursos, contador_recursos, &seq_ID_Recursos);
                                break;
                            case 'B':
                                VerRecursos(arr_recursos, contador_recursos, contador_recursos);
                                break;
                            case 'C':
                                AlterarRecursos(arr_recursos, contador_recursos);
                                break;
                            case 'D':
                                EliminarRecursos(arr_acessos, arr_recursos, &contador_acessos, &contador_recursos, utilizador_logado);
                                break;
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while (opcao4 != 'V');
                        break;
                    case 'C':
                        do
                        {
                            opcao10 = MenuUtilizadores();
                            switch (opcao10)
                            {
                            case 'A':
                                VerUtilizadores(user_registo, contador_registar, utilizador_logado);
                                break;
                            case 'B':
                                EliminarUtilizadores(user_registo, arr_acessos, &contador_registar, utilizador_logado, contador_acessos);
                                break;
                            case 'V':
                                break;
                            }
                        }
                        while (opcao10 != 'V');
                        break;
                    case 'D':
                        do
                        {
                            opcao9 = MenuEstatisticas(user_registo, utilizador_logado);
                            switch (opcao9)
                            {
                            case 'A':
                                ListagemRecursosPorTipo(arr_recursos, &contador_recursos);
                                break;
                            case 'B':
                                ListagemAcessos(user_registo, arr_acessos, contador_registar, contador_acessos);
                                break;
                            case 'C':
                                RecursoComMaisAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos);
                                break;
                            case 'D':
                                UtilizadorComMaisAcessos(arr_acessos, user_registo, contador_acessos, contador_recursos, contador_registar);
                                break;
                            case 'E':
                                DiasDesdeUltimoAcesso(arr_recursos, arr_acessos, contador_recursos, contador_acessos);
                                break;
                            case 'V':
                                break;
                            }
                        }
                        while (opcao9 != 'V');
                        break;
                    case 'V':
                        break;
                    default:
                        printf("\n\tOpção Inválida!\n");
                        getch();
                    }
                }
                while(opcao2 != 'V');
                break;
            case 'B':
                do
                {
                    opcao5 = MenuExtras();
                    switch(opcao5)
                    {
                    case 'A':
                        do
                        {
                            opcao6=MenuGerador();
                            switch(opcao6)
                            {
                            case 'A':
                                gerador_num();
                                break;
                            case 'B':
                                pwd=le_num();
                                gerador_letras(pwd);
                                break;
                            case 'C':
                                pwd=le_num();
                                gerador_razovel(pwd);
                                break;
                            case 'D':
                                pwd=le_num();
                                gerador_dificil(pwd);
                                break;
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while(opcao6 != 'V');
                        break;
                    case 'B':
                        MenuSobre();
                        break;
                    case 'V':
                        break;
                    default:
                        printf("\n\tOpção Inválida!\n");
                        getch();
                    }
                }
                while(opcao5 != 'V');
                break;
            case 'C':
                ler_ficheiro(user_registo, arr_recursos, arr_acessos, &contador_registar, &contador_recursos, &contador_acessos);
                break;
            case 'D':
                ficheiro_guardado = guardar_ficheiro(user_registo, arr_recursos, arr_acessos,contador_registar, contador_recursos, contador_acessos);
                break;
            case 'E':
                do
                {
                    opcao7 = MenuMinhaConta();
                    switch (opcao7)
                    {
                    case 'A':
                        VerDadosUtilizador(user_registo, utilizador_logado);
                        break;
                    case 'B':
                        do
                        {
                            opcao8 = MenuAlterarUtilizadores();
                            switch (opcao8)
                            {
                            case 'A':
                                AlterarUtilizadoresNome(user_registo, utilizador_logado);
                                break;
                            case 'B':
                                AlterarUtilizadoresLogin(user_registo, utilizador_logado);
                                break;
                            case 'C':
                                AlterarUtilizadoresPasswords(user_registo, utilizador_logado);
                                break;
                            case 'D':
                                AlterarUtilizadoresNIC(user_registo, utilizador_logado);
                                break;
                            case 'V':
                                break;
                            default:
                                printf("Opção inválida\n");
                                getch();
                            }
                        }
                        while (opcao8 != 'V');
                        break;
                    case 'V':
                        break;
                    default:
                        printf("Opção inválida\n");
                        getch();
                    }
                }
                while (opcao7 != 'V');
                break;
            case 'F':
                break;
            case 'S':
                sair = ConfirmarSaida(ficheiro_guardado);
                if(sair == 'S')
                    return 0;
                break;
            default:
                printf("\n\tOpção Inválida!\n");
            }
        }
        while (opcao != 'F');
    }
    while(sair != 'S');

    return 0;
}

char LerCaracter()
{
    char opcao;
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao);
    opcao = toupper(opcao);
    return opcao;
}

char MenuPrincipal(t_utilizadores user_registo[MAX_UTILIZADORES], int utilizador_logado)
{
    char opcao;
    system("cls");
    printf(" Utilizador logado: %s\n", user_registo[utilizador_logado].login_utilizador);
    printf("\n");
    printf("\t                ________________              \n");
    printf("\t               | MENU PRINCIPAL |             \n");
    printf("\t ______________|________________|_____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gestor de Passwords                    /\n");
    printf("\t/  B - EXTRAS                                 \\\n");
    printf("\t/  C - Ler dados do ficheiro                  \\\n");
    printf("\t\\  D - Guardar dados no ficheiro              /\n");
    printf("\t/  E - A minha conta                          \\\n");
    printf("\t\\  F - Trocar de conta                        /\n");
    printf("\t/  S - Sair                                   \\\n");
    printf("\t\\_____________________________________________/\n");
    printf("\n");
    opcao = LerCaracter();

    return opcao;
}

char MenuGestor(void)
{
    char opcao2;
    system("cls");

    printf("\n");
    printf("\t                _________________             \n");
    printf("\t               |   MENU GESTOR   |            \n");
    printf("\t ______________|_________________|____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerir Acessos                          /\n");
    printf("\t/  B - Gerir Recursos                         \\\n");
    printf("\t\\  C - Gerir Utilizadores (Administrador)     /\n");
    printf("\t/  D - Estatisticas                           \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    opcao2 = LerCaracter();

    return opcao2;
}

char MenuGestorAcessos(void)
{
    char opcao3;
    system("cls");

    printf("\n");
    printf("\t                __________________              \n");
    printf("\t               |  GESTOR ACESSOS  |             \n");
    printf("\t ______________|__________________|_____________\n");
    printf("\t/                                              \\\n");
    printf("\t\\  A - Inserir Acessos                         /\n");
    printf("\t/  B - Consultar Acessos                       \\\n");
    printf("\t\\  C - Alterar Acessos                         /\n");
    printf("\t/  D - Eliminar Acessos                        \\\n");
    printf("\t\\  V - Voltar                                  /\n");
    printf("\t/______________________________________________\\\n");
    printf("\n");
    opcao3 = LerCaracter();

    return opcao3;
}

char MenuGestorRecursos(void)
{
    char opcao4;
    system("cls");

    printf("\n");
    printf("\t                ___________________              \n");
    printf("\t               |  GESTOR RECURSOS  |             \n");
    printf("\t ______________|___________________|_____________\n");
    printf("\t/                                                \\\n");
    printf("\t\\  A - Inserir Recursos                          /\n");
    printf("\t/  B - Consultar Recursos                        \\\n");
    printf("\t\\  C - Alterar Recursos                          /\n");
    printf("\t/  D - Eliminar Recursos                         \\\n");
    printf("\t\\  V - Voltar                                    /\n");
    printf("\t/________________________________________________\\\n");
    printf("\n");
    opcao4 = LerCaracter();

    return opcao4;
}

char MenuExtras(void)
{
    char opcao5;
    system("cls");

    printf("\n");
    printf("\t                _________________             \n");
    printf("\t               |   MENU EXTRAS   |            \n");
    printf("\t ______________|_________________|____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerador de Passwords                   /\n");
    printf("\t/  B - Sobre                                  \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    opcao5 = LerCaracter();

    return opcao5;
}


void MenuSobre(void)
{
    system("cls");
    printf("\t                 _________________             \n");
    printf("\t                |      SOBRE      |            \n");
    printf("\t _______________|_________________|____________\n");
    printf("\t/                                              \\\n");
    printf("\t\\     Projeto de Fundamento de Porgramação     /\n");
    printf("\t/                 Elaborado por:               \\\n");
    printf("\t\\            Martim Silva nº2180686            /\n");
    printf("\t/            Gabriel Marques nº2180637         \\\n");
    printf("\t\\                                              /\n");
    printf("\t/                            TeSP PSI - PL4    \\\n");
    printf("\t\\______________________________________________/\n");
    printf("\t Pressione qualquer tecla para voltar\n");
    getch();
}


char MenuGerador(void)
{
    char opcao6;
    system("cls");

    printf("\n");
    printf("\t                ________________              \n");
    printf("\t               |  MENU GERADOR  |             \n");
    printf("\t ______________|________________|_____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerar password só com números          /\n");
    printf("\t/  B - Gerar password só com letras           \\\n");
    printf("\t\\  C - Gerar password com numeros e letras    /\n");
    printf("\t/  D - Gerar password com todos os caracteres \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    opcao6 = LerCaracter();

    return opcao6;
}


char ConfirmarSaida(int ficheiro_guardado)
{
    char sair;
    if (ficheiro_guardado == 0)
        printf("\n\tFicheiro não foi guardado, tem a certeza que quer sair?\n");
    printf("______________________________________________________________________\n");
    printf("\tQuer mesmo sair? [S/N]: ");
    fflush(stdin);
    sair = getchar();
    sair = toupper(sair);
    return sair;
}


int InserirRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r, int *seq_ID_Recursos)
{
    char nome_recurso[MAX_CARACTERES];
    int encontrado, i;

    if (contador_r < MAX_RECURSOS) ///Para não deixar exceder o número máximo de recursos permitidos
    {

        printf("______________________________________________________________________\n");
        printf("\nIndique o nome do novo recurso: ");
        scanf(" %s", nome_recurso);

        for(i = 0; i < contador_r; i++)
        {

            encontrado = strcasecmp(array_recursos[i].nome, nome_recurso);
            if (encontrado == 0)
            {
                printf("Já tem um recurso criado com esse nome.");
                getch();
                return contador_r;
            }
        }

        if (i == contador_r && encontrado != 0)
        {
            strcpy(array_recursos[contador_r].nome, nome_recurso);
            printf("\nInsira os dados\n");
            do
            {
                printf("Tipo de recurso (1 - Site | 2 - Aplicação | 3 - Dispositivo): ");
                fflush(stdin);
                scanf("%d", &array_recursos[i].tipo_recurso);
                if (array_recursos[i].tipo_recurso > 3)
                {
                    printf("\nValor inválido\n");
                }
            }
            while (array_recursos[i].tipo_recurso > 3);
            printf("Designação única (ex. www.google.pt): ");
            fflush(stdin);
            gets(array_recursos[i].designacao);
            do
            {
                printf("Grau de segurança (1 - Baixo | 2 - Médio | 3 - Elevado): ");
                fflush(stdin);
                scanf("%d", &array_recursos[i].grau_seguranca);
                if (array_recursos[i].grau_seguranca > 3)
                {
                    printf("\nValor inválido\n");
                }
            }
            while (array_recursos[i].grau_seguranca <1 || array_recursos[i].grau_seguranca > 3);
            printf("\nRecurso criado com sucesso!");
            contador_r+=1;
        }
        printf("\n______________________________________________________________________\n\n");

        array_recursos[i].ID_Recurso = *seq_ID_Recursos;
        (*seq_ID_Recursos)++;
        getch();
        return contador_r;
    }
    else
    {
        printf("\nNúmero máximo de recursos excedido!\n");
        getch();
    }
}


void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r)
{
    char mostrar[MAX_CARACTERES];
    int i = 0, contador_recursos=0,comparar_recursos;
    system("cls");
    if (contador_a != 0)
    {
        printf("______________________________________________________________________\n\n");
        printf("Todos os os recursos guardados:\n\n");

        for(int i = 0; i < contador_r; i++ )  ///Ver a lista de contas
        {
            printf("%i - %s\n", i+1, array_recursos[i].nome); ///i+1 para a lista dos recursos não começar em 0
        }
        printf("\n______________________________________________________________________\n\n");
        printf("Indique o nome do recurso que pretende consultar: ");
        fflush(stdin);
        gets(mostrar);
        printf("\n");
        for (i = 0; i < contador_r; i++)
        {
            comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
            if (comparar_recursos == 0)
            {
                printf("Tipo de recurso (1 - Site | 2 - Aplicação | 3 - Dispositivo): %i\n", array_recursos[i].tipo_recurso);
                printf("Designação única: %s\n", array_recursos[i].designacao);
                printf("Grau de segurança (1 - Baixo | 2 - Médio | 3 - Elevado): %i\n", array_recursos[i].grau_seguranca);
                printf("ID: %i\n", array_recursos[i].ID_Recurso);
                contador_recursos++;
            }
        }
        if (contador_recursos == 0 && comparar_recursos != 0)
        {
            printf("O recurso que introduziu não existe.\n");
            printf("______________________________________________________________________\n\n");
            getch();
            return;
        }
    }
    else
    {
        printf("\nNão tem recursos guardados.\n");
    }
    printf("______________________________________________________________________\n\n");
    getch();
}


void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador, char mostrar[MAX_CARACTERES])
{
    int i = 0, encontrado=99, contador_acessos=0, contador_recursos=0, comparar_recursos, posicao_acesso;

    printf("______________________________________________________________________\n\n");
    printf("Indique o nome do recurso que pretende consultar: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for (i = 0; i < contador_r; i++)
    {
        comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
        if (comparar_recursos == 0)
        {
            posicao_acesso = i;
            break;
        }
    }

    if (contador_recursos == 0 && comparar_recursos != 0)
    {
        printf("O recurso que introduziu não existe.\n");
        printf("______________________________________________________________________\n\n");
        getch();
        return;
    }

    for(i = 0; i <= contador_a; i++)
    {
        encontrado = strcasecmp(array_acessos[i].nome, mostrar);
        if (encontrado == 0 && array_acessos[i].id_utilizador == id_utilizador)
        {
            printf("-----------------");
            printf("\nLogin: %s\nPassword: %s\n", array_acessos[i].login, array_acessos[i].password);
            printf("\nHora: %i:%i\n", array_acessos[i].hora.hora, array_acessos[i].hora.minutos);
            printf("Data: %i/%i/%i\n", array_acessos[i].data.dia, array_acessos[i].data.mes, array_acessos[i].data.ano);
            printf("-----------------\n");
            contador_acessos++; ///Contador necessário para verificar se não existe nenhum acesso com esse recurso.
        }
    }

    if(contador_acessos == 0)
        printf("O recurso que introduziu não tem acessos.\n");

    printf("______________________________________________________________________\n\n");
    getch();
}


int InserirAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_ACESSOS], int contador_a, int contador_r, int id_utilizador)
{
    char mostrar[MAX_CARACTERES], password[MAX_CARACTERES];
    int encontrado=1;

    printf("______________________________________________________________________\n\n");
    printf("Indique o nome do recurso em que pretende guardar os acessos: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, mostrar);
        if (encontrado == 0)
        {
            strcpy(array_acessos[contador_a].nome, mostrar);
            printf("\nInsira os seus dados\n\n");
            printf("Login: ");
            scanf(" %s", array_acessos[contador_a].login);
            array_acessos[contador_a].id_utilizador=id_utilizador;
            array_acessos[contador_a].id_recurso=array_recursos[i].ID_Recurso;


            VerificadorPassword(array_recursos, i, &password);
            strcpy(array_acessos[contador_a].password, password);


            array_acessos[contador_a].hora = gethour();
            array_acessos[contador_a].data = getdate();

            contador_a += 1;
            printf("\nAcesso adicionado com sucesso!");
            break;
        }
    }

    if (encontrado != 0)
    {
        printf("Recurso não encontrado. Crie um recurso antes de guardar os acessos.");
    }
    printf("\n______________________________________________________________________\n\n");
    getch();
    return contador_a;
}


void VerificadorPassword(t_recursos array_recursos[], int contador_r, char *password[])
{
    int espec=0,maiusc=0,minusc=0, num=0,i=0, tamanho;
    char verificar_password[25];
    if (array_recursos[contador_r].grau_seguranca == 3)
    {
        printf("\nEscolheu o grau de segurança máximo para este recurso, por isso a sua password tem que ter:\n");
        printf("Pelo menos 8 caracteres, um número, um caracter especial, uma letra maiúscula e minúscula.\n\n");
        do
        {
            espec=0, maiusc=0, minusc=0, num=0;
            printf("\nPassword: ");
            scanf(" %s", verificar_password);
            tamanho=strlen(verificar_password);
            for(i=0; i<tamanho; i++)
            {
                if(ispunct(verificar_password[i]))
                {
                    espec++;

                }
                if(isupper(verificar_password[i]))
                {
                    maiusc++;
                }
                if(islower(verificar_password[i]))
                {
                    minusc++;
                }
                if(isdigit(verificar_password[i]))
                {
                    num++;
                }
            }

            if (espec == 0)
            {
                printf("Falta um caracter especial\n");
            }
            if (maiusc == 0)
            {
                printf("Falta uma letra maiúscula\n");
            }
            if (minusc == 0)
            {
                printf("Falta uma letra minúscula\n");
            }
            if (num == 0 )
            {
                printf("Falta um número\n");
            }
            if(tamanho<8)
                printf("Password demasiado pequena\n");
        }
        while (espec == 0 || maiusc == 0 || minusc == 0 || num == 0 || tamanho < 8);
        strcpy(password, verificar_password);
    }


    if (array_recursos[contador_r].grau_seguranca == 2)
    {
        printf("\nEscolheu o grau de segurança médio para este recurso, por isso a sua password tem que ter:\n");
        printf("Pelo menos 8 caracteres, um número, uma letra maiúscula e minúscula.\n\n");
        do
        {
            espec=0, maiusc=0, minusc=0, num=0;
            printf("\nPassword: ");
            scanf("%s", verificar_password);
            tamanho=strlen(verificar_password);
            for(i=0; i<tamanho; i++)
            {
                if(isupper(verificar_password[i]))
                    maiusc++;
                if(islower(verificar_password[i]))
                    minusc++;
                if(isdigit(verificar_password[i]))
                    num++;
            }
            if (maiusc == 0)
                printf("Falta uma letra maiúscula\n");
            if (minusc == 0)
                printf("Falta uma letra minúscula\n");
            if (num == 0)
                printf("Falta um número\n");
            if(tamanho<8)
                printf("Password demasiado pequena\n");

        }
        while (maiusc == 0 || minusc == 0 || num == 0 || tamanho < 8);
        strcpy(password, verificar_password);
    }

    if (array_recursos[contador_r].grau_seguranca == 1)
    {
        printf("\nEscolheu o grau de segurança baixo para este recurso, por isso pode ser o que quiser:\n");
        printf("\nPassword: ");
        scanf("%s", verificar_password);
        strcpy(password, verificar_password);
    }
}


int le_num(void)
{
    int num;
    printf("\n______________________________________________________________________\n\n");
    printf("Introduza a quantidade de caracteres que deseja [8-16]: ");
    fflush(stdin);
    scanf("%d", &num);
    return num;
}


void gerador_num(void)
{
    int numeros, n;

    printf("\n______________________________________________________________________\n\n");
    printf("Introduza a quantidade de número que deseja [4-16]: ");
    fflush(stdin);
    scanf("%d", &numeros);
    if (numeros > 3 && numeros < 17)
    {
        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <= numeros; n++)
        {
            printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_letras(int quant4)
{
    int n;

    if (quant4 > 7 && quant4 < 17)
    {
        srand(time(0));
        printf("\nA password gerada foi: ");
        for(n = 1; n <= quant4; n++)

        {
            printf("%c", gerador_ltr[rand()%57]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_razovel(int quant)
{
    int qtn;
    int n;

    if (quant > 7 && quant < 17)
    {
        qtn = quant / 2;
        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <= qtn; n++)
        {
            printf("%c", gerador_ltr[rand()%57]);
            printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_dificil(int quant2)
{
    int qtn;
    int n=0;

    if (quant2 > 7 && quant2 < 17)
    {
        qtn = quant2 / 2;

        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <=qtn; n++)
        {
            printf("%c", gerador_ltr[rand()%57]);

            if(n % 2 == 0)
            {
                if((rand()%11) % 2 == 0)
                    printf("%c", gerador_espec[rand()%21]);

                else
                    printf("%d", gerador_nume[rand()%11]);
            }

            else

                printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    getch();
}


int MenuInicial(void)
{
    int opcao;
    system("cls");
    printf("\n");
    printf("\t                _________________________             \n");
    printf("\t               |   GESTOR DE PASSWORDS   |            \n");
    printf("\t ______________|_________________________|____________\n");
    printf("\t/                                                    \\\n");
    printf("\t\\  1 - Login                                         /\n");
    printf("\t/  2 - Registar                                      \\\n");
    printf("\t\\  3 - Sair                                          /\n");
    printf("\t/____________________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    scanf("%i", &opcao);
    return opcao;
}


int MenuLogin(t_utilizadores user_registo[MAX_UTILIZADORES],int contador_utilizadores)
{
    char username_login[MAX_CARACTERES];
    char password_login[MAX_CARACTERES];
    int confirmar=99, i;

    system("cls");

    printf("\n\t|========================| LOGIN |========================|\n\n");
    printf("\t  Username: ");
    fflush(stdin);
    scanf("%s",username_login);
    printf("\n\t  Password: ");
    fflush(stdin);
    scanf("%s",password_login);

    for(i = 0; i < contador_utilizadores ; i++)
    {
        if((strcmp(user_registo[i].login_utilizador,username_login)==0) && (strcmp(user_registo[i].password_utilizador,password_login)==0))
        {
            confirmar=i;
            break;
        }
    }

    if(strcmp(user_registo[i].password_utilizador,password_login)!=0)
    {
        printf("\n\t  Credenciais erradas!\n\n");
        getch();
        confirmar=-1;
    }
    else
    {
        printf("\nUsername invalido");
    }
    return confirmar;
}


int MenuRegistar(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores, int *seq_ID_Utlizador)
{
    int i, NIC, existe = 0, utilizador_existe=0;
    char utilizador[MAX_CARACTERES];

    if (contador_utilizadores < MAX_UTILIZADORES)
    {
        system("cls");
        printf("\n\t|========================| REGISTAR |========================|\n");
        do
        {
            do
            {
                utilizador_existe = 0;
                printf("\n\t  Username: ");
                scanf(" %s", utilizador);
                for(i = 0; i < contador_utilizadores ; i++)
                {
                    if (strcmp(user_registo[i].login_utilizador, utilizador)==0)
                    {
                        printf("\n\t  Esse nome de utilizador já existe.\n");
                        utilizador_existe = 1;
                        getch();
                        break;
                    }
                }
            }
            while (utilizador != "admin" && utilizador_existe != 0);

            do
            {
                do
                {
                    printf("\n\t  Numero de identificação civil: ");

                    fflush(stdin);
                    scanf("%i", &NIC);
                    if(NIC < 11111111 || NIC > 99999999)
                    {
                        printf("\n\t  O NIC necissita de ter 8 numeros. \n");
                    }
                }
                while(NIC < 11111111 || NIC > 99999999);
                for(i=0; i< contador_utilizadores; i++)
                {
                    if (user_registo[i].NIC==NIC)
                    {
                        existe = 1;
                        printf("\n\t  Esse NIC já existe.\n");
                    }
                    else
                    {
                        existe = 0;
                    }
                }
            }
            while(NIC > 11111111 && NIC < 99999999 && existe==1);

        }
        while(strcmp(user_registo[i].login_utilizador, utilizador)==0 && user_registo[contador_utilizadores].NIC==NIC);

        printf("\n\t  Password: ");
        fflush(stdin);
        scanf("%s", user_registo[contador_utilizadores].password_utilizador);
        printf("\n\t  Introduza o seu nome pessoal: ");
        fflush(stdin);
        gets(user_registo[contador_utilizadores].nome);
        strcpy(user_registo[contador_utilizadores].login_utilizador, utilizador);
        user_registo[contador_utilizadores].NIC = NIC;
        printf("\n\t  Registo efetuado com sucesso.\n\n");
        printf("\t|============================================================|\n");
        (*seq_ID_Utlizador)++;
        user_registo[contador_utilizadores].ID_Utilizador = *seq_ID_Utlizador;
        getch();
        return contador_utilizadores+1;
    }
    else
    {
        printf("\n\tNúmero máximo de utilizadores excedido.\n");
        getch();
    }
}

void VerUtilizadores(t_utilizadores user_registo[MAX_UTILIZADORES],int contador_utilizadores, int utilizador_logado)
{
    int i;
    if(user_registo[utilizador_logado].ID_Utilizador == 0)
    {
        system("cls");
        for (i = 0; i < contador_utilizadores; i++)
        {
            printf("\n\tNome: %s\n", user_registo[i].nome);
            printf("\tUsername: %s\n", user_registo[i].login_utilizador);
            printf("\tPalavra-Passe: %s\n", user_registo[i].password_utilizador);
            printf("\tNumero de identificação civil: %i\n", user_registo[i].NIC);
            printf("\tID: %i\n\n", user_registo[i].ID_Utilizador);
            printf("\t-----------------------------------------\n");
        }
        printf("\n\tPressione uma tecla para continuar...");
        getch();
    }
    else
    {
        printf("\n\tNão tem premissões para este comando. \n");
        getch();
    }
}

int InserirAdmin(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    strcpy(user_registo[contador_utilizadores].nome, "Admin");
    user_registo[contador_utilizadores].ID_Utilizador=0;
    user_registo[contador_utilizadores].NIC=999999999;
    strcpy(user_registo[contador_utilizadores].login_utilizador, "admin");
    strcpy(user_registo[contador_utilizadores].password_utilizador, "admin");
    return contador_utilizadores+1;
}

void ler_ficheiro(t_utilizadores user_registo[MAX_UTILIZADORES], t_recursos array_recursos[MAX_ACESSOS], t_acessos array_acessos[MAX_RECURSOS], int *contador_utilizadores, int *contador_r, int *contador_a)
{
    int n_elementos, n_elementos_lidos;
    FILE *ficheiro;
    ficheiro = fopen("dados.dat", "rb");

    if (ficheiro == NULL)
    {
        printf("Ficheiro Inexistente\n\n");
    }
    else
    {
        fread(&(*contador_utilizadores), sizeof(int), 1, ficheiro);
        fread(&(*contador_r), sizeof(int), 1, ficheiro);
        fread(&(*contador_a), sizeof(int), 1, ficheiro);

        fread(user_registo, sizeof(t_utilizadores), *contador_utilizadores, ficheiro);
        fread(array_recursos, sizeof(t_recursos), *contador_r, ficheiro);
        fread(array_acessos, sizeof(t_acessos), *contador_a, ficheiro);

        /*if (n_elementos_lidos != n_elementos)
        {
            printf("Impossivel ler o ficheiro\n\n");
            n_elementos = 0;
        }
        else
        {
            printf("\nA LER...\n\n");
            (*contador_utilizadores) = n_elementos;
        }*/
        fclose(ficheiro);
    }
}

int guardar_ficheiro(t_utilizadores user_registo[MAX_UTILIZADORES], t_recursos array_recursos[MAX_ACESSOS], t_acessos array_acessos[MAX_RECURSOS], int contador_utilizadores, int contador_r, int contador_a)
{
    int ficheiro_guardado=0;
    FILE *ficheiro;
    ficheiro = fopen("dados.dat", "wb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro Inexistente\n\n");
    }
    else
    {
        fwrite(&contador_utilizadores, sizeof(int), 1, ficheiro);
        fwrite(&contador_r, sizeof(int), 1, ficheiro);
        fwrite(&contador_a, sizeof(int), 1, ficheiro);

        fwrite(user_registo, sizeof(t_utilizadores), contador_utilizadores, ficheiro);
        fwrite(array_recursos, sizeof(t_recursos), contador_r, ficheiro);
        fwrite(array_acessos, sizeof(t_acessos), contador_a, ficheiro);

        fclose(ficheiro);
        ficheiro_guardado = 1;
        return ficheiro_guardado;
    }
}


void AlterarRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r)
{
    char mostrar[MAX_CARACTERES], novo_nome[MAX_CARACTERES];
    int comparar_recursos, i, encontrado=0;

    printf("Indique o nome do recurso que pretende alterar: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for (i = 0; i < contador_r; i++)
    {
        comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
        if (comparar_recursos == 0)
        {
            do
            {
                printf("Novo nome do recurso: ");
                scanf("%s", novo_nome);
                for(int x = 0; x < contador_r; x++)
                {
                    encontrado = strcasecmp(array_recursos[x].nome, novo_nome);
                    if (encontrado == 0)
                    {
                        printf("\nJá tem um recurso criado com esse nome.\n");
                        getch();
                    }
                }
            }
            while (encontrado == 0);
            strcpy(array_recursos[i].nome, novo_nome);
            printf("Tipo de recurso atual: %i\n", array_recursos[i].tipo_recurso);
            do
            {
                printf("Novo tipo de recurso (1 - Site | 2 - Aplicação | 3 - Dispositivo): ");
                fflush(stdin);
                scanf("%d", &array_recursos[i].tipo_recurso);
                if (array_recursos[i].tipo_recurso > 3)
                {
                    printf("\nValor inválido\n");
                }
            }
            while (array_recursos[i].tipo_recurso > 3);

            printf("Designação única atual: %s\n", array_recursos[i].designacao);
            printf("Nova designação única: ");
            fflush(stdin);
            gets(array_recursos[i].designacao);

            printf("Grau de segurança atual: %i\n", array_recursos[i].grau_seguranca);
            do
            {
                printf("Novo grau de segurança (1 - Baixo | 2 - Médio | 3 - Elevado): ");
                fflush(stdin);
                scanf("%d", &array_recursos[i].grau_seguranca);
                if (array_recursos[i].grau_seguranca > 3)
                {
                    printf("\nValor inválido\n");
                }
            }
            while (array_recursos[i].grau_seguranca < 1 || array_recursos[i].grau_seguranca > 3);
            printf("\nRecurso criado com sucesso!");
        }
    }
}

void AlterarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador)
{
    char login[MAX_CARACTERES], mostrar[MAX_CARACTERES];
    int encontrado, encontrado2;

    VerAcessos(array_acessos, array_recursos, contador_a, contador_r, id_utilizador, mostrar);
    printf("Indique o LOGIN ATUAL do acesso que pretende alterar ou eleminar: ");
    gets(login);

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, mostrar);
        if (encontrado == 0)
        {
            for (int i = 0; i < contador_a; i++)
            {
                encontrado2 = strcasecmp(array_acessos[i].login, login);
                if (encontrado2 == 0 && array_acessos[i].id_utilizador == id_utilizador)
                {
                    printf("\nInsira os seus novos dados\n\n");
                    printf("Login: ");
                    scanf(" %s", array_acessos[i].login);

                    VerificadorPassword(array_recursos, array_acessos[i].id_recurso, array_acessos[i].password);

                    array_acessos[i].hora = gethour();
                    array_acessos[i].data = getdate();
                }
            }
        }
    }
    getch();
}

t_data getdate()
{
    t_data date;

    do
    {
        printf("Dia: ");
        fflush(stdin);
        scanf("%i", &date.dia);
        if (date.dia > 31)
            printf("Dia inválido.\n");
    }
    while (date.dia > 31);

    do
    {
        printf("Mês: ");
        fflush(stdin);
        scanf("%i", &date.mes);
        if (date.mes > 12)
            printf("Mês inválido.\n");
    }
    while (date.mes > 12);

    do
    {
        printf("Ano: ");
        fflush(stdin);
        scanf("%i", &date.ano);
        if (date.ano > 2019 || date.ano < 1920)
            printf("Ano inválido.\n");
    }
    while (date.ano > 2019 || date.ano < 1920);
    return date;
}

t_hour gethour()
{
    t_hour hour;
    do
    {
        printf("Hora: ");
        fflush(stdin);
        scanf("%i", &hour.hora);
        if (hour.hora > 23)
            printf("Hora inválida.\n");
    }
    while (hour.hora > 23);

    do
    {
        printf("Minutos: ");
        fflush(stdin);
        scanf("%i", &hour.minutos);
        if (hour.minutos > 59)
            printf("Minutos inválidos.\n");
    }
    while (hour.minutos > 59);
    return hour;
}

char MenuUtilizadores()
{
    char opcao10;
    system("cls");

    printf("\n");
    printf("\t               _________________                \n");
    printf("\t              | MENU UTILIZADOR | (Administrador)\n");
    printf("\t _____________|_________________|______________ \n");
    printf("\t/                                              \\\n");
    printf("\t\\  A - Ver dados de todos os utilizadores      /\n");
    printf("\t/  B - Eliminar utilizadores                   \\\n");
    printf("\t\\  V - Voltar                                  /\n");
    printf("\t/______________________________________________\\\n");
    printf("\n");
    opcao10 = LerCaracter();
    return opcao10;
}

char MenuMinhaConta()
{
    char opcao7;
    system("cls");

    printf("\n");
    printf("\t               __________________                \n");
    printf("\t              | MENU MINHA CONTA |               \n");
    printf("\t _____________|__________________|______________ \n");
    printf("\t/                                               \\\n");
    printf("\t\\  A - Ver dados                                /\n");
    printf("\t/  B - Alterar dados                            \\\n");
    printf("\t\\  V - Voltar                                   /\n");
    printf("\t/_______________________________________________\\\n");
    printf("\n");
    opcao7 = LerCaracter();
    return opcao7;
}

char MenuAlterarUtilizadores()
{
    char opcao8;
    system("cls");
    printf("\n\tO que quer alterar?\n\n");
    printf("\tA - Nome\n");
    printf("\tB - Login\n");
    printf("\tC - Password\n");
    printf("\tD - NIC\n");
    printf("\tV - Voltar\n");
    opcao8 = LerCaracter();
    return opcao8;
}

void VerDadosUtilizador(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    printf("\n\tNome: %s\n", user_registo[contador_utilizadores].nome);
    printf("\tUsername: %s\n", user_registo[contador_utilizadores].login_utilizador);
    printf("\tPalavra-Passe: %s\n", user_registo[contador_utilizadores].password_utilizador);
    printf("\tNumero de identificação civil: %i\n", user_registo[contador_utilizadores].NIC);
    getch();
}

void AlterarUtilizadoresNome(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    printf("\n\tInsira o novo nome: ");
    fflush(stdin);
    gets(user_registo[contador_utilizadores].nome);
    printf("\tNome guardado com sucesso!");
    getch();
}

void AlterarUtilizadoresLogin(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    int i;
    char utilizador[MAX_CARACTERES];
    do
    {
        printf("\n\tInsira o seu novo login: ");
        fflush(stdin);
        gets(utilizador);

        for( i = 0; i < contador_utilizadores ; i++)

        {
            if (strcmp(user_registo[i].login_utilizador, utilizador)==0)
            {
                printf("\n\t  Esse nome de utilizador já existe.\n");
                getch();
                break;
            }
        }
    }
    while (utilizador != "admin" && strcmp(user_registo[i].login_utilizador, utilizador)==0);
    strcpy(user_registo[contador_utilizadores].login_utilizador, utilizador);
}

void AlterarUtilizadoresPasswords(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    printf("\n\tInsira a nova password: ");
    fflush(stdin);
    scanf("%s", user_registo[contador_utilizadores].password_utilizador);
    printf("\tPassword guardada com sucesso!");
    getch();
}

void AlterarUtilizadoresNIC(t_utilizadores user_registo[MAX_UTILIZADORES], int contador_utilizadores)
{
    int i, NIC, existe;
    do
    {
        do
        {
            printf("\n\t  Numero de identificação civil: ");
            fflush(stdin);
            scanf("%i", &NIC);
            if(NIC < 11111111 || NIC > 99999999)
            {
                printf("\n\t  O NIC necissita de ter 8 numeros. \n");
            }
        }
        while(NIC < 11111111 || NIC > 99999999);
        for(i=0; i< contador_utilizadores; i++)
        {
            if (user_registo[i].NIC==NIC)
            {
                existe = 1;
                printf("\n\t  Esse NIC já existe.\n");
            }
            else
            {
                existe = 0;
            }
        }
    }
    while(NIC > 11111111 && NIC < 99999999 && existe==1);
    user_registo[contador_utilizadores].NIC = NIC;
}

void EliminarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int contador_r, int id_utilizador)
{
    char login[MAX_CARACTERES], mostrar[MAX_CARACTERES];
    int encontrado, encontrado2;

    VerAcessos(array_acessos, array_recursos, *contador_a, contador_r, id_utilizador, mostrar);
    printf("\tIndique o LOGIN DO ACESSO que pretende eliminar: ");
    gets(login);

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, mostrar);
        if (encontrado == 0)
        {
            for (int y = 0; y < *contador_a; y++)
            {
                encontrado2 = strcasecmp(array_acessos[y].login, login);
                if (encontrado2 == 0)
                {
                    for(int x = y; x < *contador_a; x++)
                    {
                        strcpy(array_acessos[x].login, array_acessos[x+1].login);
                        strcpy(array_acessos[x].nome, array_acessos[x+1].nome);
                        strcpy(array_acessos[x].password, array_acessos[x+1].password);
                        array_acessos[x].id_recurso=array_acessos[x+1].id_recurso;
                        array_acessos[x].id_utilizador=array_acessos[x+1].id_utilizador;
                        array_acessos[x].data=array_acessos[x+1].data;
                        array_acessos[x].hora=array_acessos[x+1].hora;
                    }
                    printf("\n\tAcesso eliminado com sucesso!\n");
                    (*contador_a)--;
                }
            }
        }
        break;
    }
    if (encontrado != 0)
    {
        printf("\n\tO login de acesso que introduziu não corresponde.\n");
    }
    getch();
}

void EliminarRecursos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int *contador_r, int id_utilizador)
{
    char recurso[MAX_CARACTERES];
    int encontrado;

    printf("\n\tIndique o nome do recurso que pretende eliminar: ");
    scanf("%s", recurso);

    for(int i = 0; i < *contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, recurso);
        if (encontrado == 0)
        {
            if (array_acessos[i].id_recurso != i) ///Procurar se há algum id_recurso que é guardado no acesso com o numero de recurso que se está a apagar (i)
            {
                for(int x = i; x < *contador_r-1; x++)
                {
                    strcpy(array_recursos[x].designacao, array_recursos[x+1].designacao);
                    strcpy(array_recursos[x].nome, array_recursos[x+1].nome);
                    array_recursos[x].tipo_recurso = array_recursos[x+1].tipo_recurso;
                    array_recursos[x].ID_Recurso = array_recursos[x+1].ID_Recurso;
                    array_recursos[x].grau_seguranca = array_recursos[x+1].grau_seguranca;
                }
                printf("\n\tRecurso eliminado com sucesso!\n");
                (*contador_r)--;
            }
            else
                printf("Impossivel eliminar porque você ou outro utilizador tem acessos guardados no recurso\n");
        }
        break;
    }
    if (encontrado != 0)
    {
        printf("\n\tO recurso que introduziu não corresponde.\n");
    }
    getch();
}

void EliminarUtilizadores(t_utilizadores user_registo[MAX_UTILIZADORES], t_acessos array_acessos[MAX_ACESSOS], int *contador_utilizadores, int id_utilizador, int contador_a)
{
    char utilizador_a_eliminar[MAX_CARACTERES];
    int encontrado = -1, i, eliminar=1;

    if(user_registo[id_utilizador].ID_Utilizador == 0) ///Vê se é administrador
    {
        printf("\n\tIntroduza o nome do utilizador que pretende eliminar: ");
        scanf("%s", utilizador_a_eliminar);
        for(i = 0; i < *contador_utilizadores; i++)
        {
            getch();
            if(strcasecmp(user_registo[i].login_utilizador, utilizador_a_eliminar)==0)
            {
                encontrado=i;
                i=(*contador_utilizadores);
                getch();
            }
        }

        if (encontrado != -1)
        {
            for (int y = 0 ; y < contador_a ; y++)
            {
                if (array_acessos[y].id_utilizador == user_registo[i].ID_Utilizador) ///Procurar se há algum id_recurso que é guardado no acesso com o numero de recurso que se está a apagar (i)
                {
                    printf("\n\tImpossivel eliminar porque você tem acessos guardados\n");
                    eliminar = 0;
                    getch();
                }
            }

            if(eliminar = 1)
            {
                for(int x = i; x < *contador_utilizadores-1; x++)
                {
                    user_registo[x].ID_Utilizador = user_registo[x+1].ID_Utilizador;
                    strcpy(user_registo[x].nome, user_registo[x+1].nome);
                    strcpy(user_registo[x].password_utilizador, user_registo[x+1].password_utilizador);
                    strcpy(user_registo[x].login_utilizador, user_registo[x+1].login_utilizador);
                    user_registo[x].NIC = user_registo[x+1].NIC;
                }
                (*contador_utilizadores)--;
            }
        }
        else
        {
            printf("\n\tUtilizador não encontrado\n");
            getch();
        }
    }
    else
    {
        printf("\n\tFuncionalidade apenas para o administrador. Se pretender eliminar a sua conta, peça ao administrador.\n");
        getch();
    }
}

char MenuEstatisticas(t_utilizadores user_registo[MAX_UTILIZADORES],int utilizador_logado)
{
    char opcao;
    if(user_registo[utilizador_logado].ID_Utilizador == 0)
    {
        system("cls");
        printf("\n");
        printf("\t                ________________              \n");
        printf("\t               |  ESTATÍSTICAS  |             \n");
        printf("\t ______________|________________|_____________ \n");
        printf("\t/                                             \\\n");
        printf("\t\\  A - Listagem de recursos por tipo          /\n");
        printf("\t/  B - Listagem de acessos dos utilizadores   \\\n");
        printf("\t\\  C - Recurso com mais acessos               /\n");
        printf("\t/  D - Utilizador com mais acessos            \\\n");
        printf("\t\\  E - Dias desde o último acesso             /\n");
        printf("\t/  V - Voltar                                 \\\n");
        printf("\t\\_____________________________________________/\n");
        printf("\n");
        opcao = LerCaracter();
        return opcao;
    }
    else
    {
        printf("\n\tNão tem premissões para este menu (Apenas como administrador)\n");
    }
}

void ListagemRecursosPorTipo(t_recursos array_recursos[], int *contador_r)
{
    int tipo;
    if (*contador_r == 0)
    {
        printf("\n\tNão têm quaisquer recursos criados.\n");
    }
    else
    {
        system("cls");
        printf("Tipo de recurso (1 - Site | 2 - Aplicação | 3 - Dispositivo): ");
        fflush(stdin);
        scanf("%d", &tipo);
        for (int i = 0; i < *contador_r; i++)
        {
            if (array_recursos[i].tipo_recurso == tipo)
            {
                printf("____________________________________\n\n");
                printf("Nome: %s\n", array_recursos[i].nome);
                printf("Designação: %s\n", array_recursos[i].designacao);
                printf("Grau de segurança: %i\n", array_recursos[i].grau_seguranca);
                printf("____________________________________\n");
            }
        }
    }
    getch();
}

void ListagemAcessos(t_utilizadores user_registo[MAX_UTILIZADORES], t_acessos array_acessos[MAX_ACESSOS], int contador_utilizadores, int *contador_a)
{
    int utilizador;
    if (contador_a == 0)
    {
        printf("\n\tNenhum utilizador tem acessos.\n");
    }
    else
    {
        system("cls");
        for (int i = 1 ; i < contador_utilizadores ; i++)
        {
            printf("%d - %s\n", i, user_registo[i].login_utilizador);
        }
        printf("\nIntroduza o número do utilizador: ");
        fflush(stdin);
        scanf("%d", &utilizador);
        for (int x = 0 ; x < contador_a ; x++)
        {
            if (array_acessos[x+1].id_utilizador == utilizador)
            {
                printf("____________________________________\n\n");
                printf("Nome do acesso: %s\n", array_acessos[x].nome);
                printf("Login: %s\n", array_acessos[x].login);
                printf("Password: %s\n", array_acessos[x].password);
                printf("____________________________________\n");
            }
        }
    }
    getch();
}

void RecursoComMaisAcessos(t_acessos array_acessos[], t_recursos array_recursos[], int contador_a, int contador_r)
{
    int numero_acessos=0, contador=0, id_recurso=-1, i, j;

    if (contador_a == 0)
    {
        printf("\n\tNenhum utilizador tem acessos guardados\n");
    }
    else
    {
        for (i=0; i < contador_r; i++)
        {
            contador = 0;
            for (j=0; j < contador_a; j++)
            {
                if (array_recursos[i].ID_Recurso == array_acessos[j].id_recurso)
                {
                    contador++;
                }

            }
            if (contador > numero_acessos)
            {
                numero_acessos = contador;
                id_recurso = array_acessos[i].id_recurso;
                contador = i;
            }
        }
        printf("\t________________________\n");
        printf("\n\tO recurso com mais acessos é o: %s, com %d acessos.\n", array_recursos[contador].nome, numero_acessos);
    }
    getch();
}

void UtilizadorComMaisAcessos(t_acessos array_acessos[], t_utilizadores user_registo[], int contador_a, int contador_r, int contador_registar)
{
    int numero_acessos=0, contador=0, id_utilizador=-1, i, j;

    for (i=1; i < contador_registar; i++)
    {
        contador = 0;
        for (j=0; j < contador_a; j++)
        {
            if (user_registo[i].ID_Utilizador == array_acessos[j].id_utilizador)
            {
                contador++;
            }
        }
        if (contador > numero_acessos)
        {
            numero_acessos = contador;
            id_utilizador = array_acessos[i].id_recurso;
            contador = i;
        }
    }
    printf("\t________________________\n");
    printf("\n\tO utilizador com mais acessos é o: %s, com %d acessos.\n", user_registo[contador].nome, numero_acessos);
    getch();
}

void DiasDesdeUltimoAcesso(t_recursos array_recursos[], t_acessos array_acessos[], int contador_r, int contador_a)
{
    int soma_data_atual = 0, acesso_mais_velho = 0;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
    soma_data_atual = tm.tm_year + 1900 + tm.tm_mon + 1 + tm.tm_mday + tm.tm_hour + tm.tm_min;
    printf("%d + %d + %d + %d + %d\n", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);

    char recurso[MAX_CARACTERES];
    int encontrado, hora, dia, mes, ano;

    printf("\n\tIndique o nome do recurso que pretende eliminar: ");
    scanf("%s", recurso);

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, recurso);
        if (encontrado == 0)
        {
            /*printf("Introduza a data e hora atual");
            printf("Dia: ");
            printf("Mês: ");
            printf("Ano: ");*/
            for (int j=1; j < contador_a; j++)
            {
                if (array_recursos[i].ID_Recurso == array_acessos[j].id_recurso)
                {

                }
                else
                {
                    printf("O recurso não tem acessos\n");
                }

            }
        }
    }
    if (encontrado != 0)
    {
        printf("\n\tO recurso que introduziu não corresponde.\n");
    }
    printf("O acesso mais velho: %s", array_acessos[acesso_mais_velho].nome);
    getch();
}
