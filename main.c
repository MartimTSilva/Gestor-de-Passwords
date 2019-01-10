#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#define MAX_UTILIZADORES 21
#define MAX_RECURSOS 100
#define MAX_ACESSOS 200
#define MAX_CARACTERES 50

typedef struct  ///REGISTER
{
    char nome[MAX_CARACTERES];
    char username_login;
    int ID_Utilizador;
    int NIC_register;
    char username_register[20];
    char password_register[20];
} t_register;

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
    int identificador;
    char nome[MAX_CARACTERES];
    int tipo_recurso;
    int grau_seguranca;
    char designacao[MAX_CARACTERES];
} t_recursos;


///Declarações para o menu gerador
void gerador_num(void);
void gerador_letras(int quant4);
void gerador_razovel(int quant);
void gerador_dificil(int quant2);
int le_num(void);
int gerador_nume[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
char gerador_ltr[52] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char gerador_espec[18] = { '_', '.', '-', '$', '/', '&', '(', ')', '[', ']', '?', '!', '@', '=', '+', '*' };


int menu_opcao(void);
int login (t_register user_registo[MAX_UTILIZADORES],int contador_registo);
int registar (t_register user_registo[MAX_UTILIZADORES], int contador_registo, int *seq_ID_Utlizador);
char menuPrincipal(void);
char MenuGestor(void);
void MenuSobre(void);
char MenuGerador(void);
char MenuGestorRecursos(void);
char ConfirmarSaida(void);
char MenuExtras(void);
char MenuGestorAcessos(void);
void VerificadorPassword(t_recursos array_recursos[], int contador_r, char *password[]);


int InserirRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r, int *seq_ID_Recursos);
void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r);


int InserirAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_ACESSOS], int contador_a, int contador_r, int id_utilizador);
void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador, char mostrar[MAX_CARACTERES]);


void VerUtilizadores(t_register user_register[MAX_UTILIZADORES],int contador_registo, int ID_Utilizador);
int InserirAdmin(t_register user_registo[MAX_UTILIZADORES], int contador_registo);
void ler_ficheiro(t_register user_register[], int *contador_registo);
void guardar_ficheiro(t_register user_register[], int contador_registo);


void AlterarUtilizadoresNome(t_register user_registo[MAX_UTILIZADORES], int contador_registo);
void AlterarUtilizadoresLogin(t_register user_registo[MAX_UTILIZADORES], int contador_registo);
void AlterarUtilizadoresPasswords(t_register user_registo[MAX_UTILIZADORES], int contador_registo);
void AlterarUtilizadoresNIC(t_register user_registo[MAX_UTILIZADORES], int contador_registo);
char MenuMinhaConta();
char MenuAlterarUtilizadores();
void AlterarUtilizadores(t_register user_register[MAX_UTILIZADORES], int contador_registo);

void AlterarRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r);
void AlterarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador);
void EliminarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int contador_r, int id_utilizador);
void EliminarRecursos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int *contador_r, int id_utilizador);
void EliminarUtilizadores(t_register user_registo[MAX_UTILIZADORES], t_acessos array_acessos[MAX_ACESSOS], int *contador_registo, int id_utilizador);

t_data getdate();
t_hour gethour();

int main()
{
    system("chcp 65001"); //Para usar caracteres especiais.
    system("cls"); //Limpa o ecrã
    char opcao, opcao2, opcao3, opcao4, opcao5, opcao6, opcao7, opcao8, sair, string[MAX_CARACTERES];
    t_data array_data[MAX_ACESSOS];
    t_acessos arr_acessos[MAX_ACESSOS] = {"", "", ""};
    t_recursos arr_recursos[MAX_RECURSOS] = {"", "", "", "", ""};
    int contador_acessos = 0, pwd, contador_recursos = 0, confirmarLogin = -1, contador_registar=0, seq_ID_Utlizador=0, seq_ID_Recursos=0;

    int opc_register;
    t_register user_register[MAX_UTILIZADORES];
    contador_registar = InserirAdmin(user_register, contador_registar);

    ler_ficheiro(user_register, &contador_registar);
    VerUtilizadores(user_register, contador_registar, &seq_ID_Utlizador);
    do
    {
        do
        {
            opc_register=menu_opcao();
            switch(opc_register)
            {
            case 1:
                confirmarLogin = -1;
                confirmarLogin = login(user_register, contador_registar);
                break;
            case 2:
                if (contador_registar < MAX_UTILIZADORES)
                {
                    confirmarLogin=-1;
                    contador_registar=registar(user_register, contador_registar, &seq_ID_Utlizador);
                }
                else
                {
                    printf("\n\tNúmero máximo de utilizadores excedido.\n");
                    getch();
                }
                break;
            case 3:
                sair = ConfirmarSaida();
                if(sair=='S')
                    return 0;
                else
                    break;
            default:
                printf("\n\tOpção Inválida!\n");
                getch();
            }
        }
        while(confirmarLogin == -1);

        do
        {
            opcao=menuPrincipal();
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
                                if (contador_acessos < MAX_ACESSOS) ///Para não deixar exceder o número máximo de acessos permitidos
                                {
                                    contador_acessos = InserirAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, user_register[confirmarLogin].ID_Utilizador);
                                }
                                else
                                {
                                    printf("\nNúmero máximo de acessos excedido!\n");
                                    getch();
                                }
                                break;
                            case 'B':
                                VerAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, confirmarLogin, string);
                                break;
                            case 'C':
                                AlterarAcessos(arr_acessos, arr_recursos, contador_acessos, contador_recursos, confirmarLogin);
                                break;
                            case 'D':
                                EliminarAcessos(arr_acessos, arr_recursos, &contador_acessos, contador_recursos, confirmarLogin);
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
                                if (contador_recursos < MAX_RECURSOS) ///Para não deixar exceder o número máximo de recursos permitidos
                                {
                                    contador_recursos = InserirRecursos(arr_recursos, contador_recursos, &seq_ID_Recursos);

                                }
                                else
                                {
                                    printf("\nNúmero máximo de recursos excedido!\n");
                                    getch();
                                }
                                break;
                            case 'B':
                                VerRecursos(arr_recursos, contador_recursos, contador_recursos);
                                break;
                            case 'C':
                                AlterarRecursos(arr_recursos, contador_recursos);
                                break;
                            case 'D':
<<<<<<< HEAD
                                EliminarRecursos(arr_acessos, arr_recursos, &contador_acessos, &contador_recursos, confirmarLogin);
=======
                                EliminarRecursos(arr_acessos, arr_recursos, &contador_acessos, contador_recursos, confirmarLogin);
>>>>>>> 127e4363338c71e25780a681fd32e90c9a6358df
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
                        if(user_register[confirmarLogin].ID_Utilizador == 0)
                        {
                            VerUtilizadores(user_register, contador_registar, &seq_ID_Utlizador);
                            getch();
                        }
                        else
                        {
                            printf("\n\tNão tem premissões para esse comando (Apenas como administrador)\n");
                            getch();
                        }
                        break;
                    case 'D':
                        printf("\nA funcionalidade das estatisticas ainda não está feito\n");
                        getch();
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
                ler_ficheiro(user_register, &contador_registar);
                break;
            case 'D':
                guardar_ficheiro(user_register, contador_registar);
                break;
            case 'E':
                do
                {
                    opcao7 = MenuMinhaConta();
                    switch (opcao7)
                    {
                    case 'A':
                        printf("\n\tNome: %s\n", user_register[confirmarLogin].nome);
                        printf("\tUsername: %s\n", user_register[confirmarLogin].username_register);
                        printf("\tPalavra-Passe: %s\n", user_register[confirmarLogin].password_register);
                        printf("\tNumero de identificação civil: %i\n", user_register[confirmarLogin].NIC_register);
                        getch();
                        break;
                    case 'B':
                        do
                        {
                            opcao8 = MenuAlterarUtilizadores();
                            switch (opcao8)
                            {
                            case 'A':
                                AlterarUtilizadoresNome(user_register, confirmarLogin);
                                break;
                            case 'B':
                                AlterarUtilizadoresLogin(user_register, confirmarLogin);
                                break;
                            case 'C':
                                AlterarUtilizadoresPasswords(user_register, confirmarLogin);
                                break;
                            case 'D':
                                AlterarUtilizadoresNIC(user_register, confirmarLogin);
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
                    case 'C':
                        EliminarUtilizadores(user_register, arr_acessos, &contador_registar, confirmarLogin);
                        confirmarLogin = -1;
                        menu_opcao();
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
                sair = ConfirmarSaida();
                if(sair == 'S')
                    return 0;
                else
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
char menuPrincipal(void)
{
    char opcao;
    system("cls");

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
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao);

    opcao = toupper(opcao);

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
    printf("\t\\  C - Gerir Utilizadores                     /\n");
    printf("\t/  D - Estatisticas (Incompleto)              \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao2);
    opcao2 = toupper(opcao2);

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
    printf("\t/  D - Eliminar Acessos (Incompleto)           \\\n");
    printf("\t\\  V - Voltar                                  /\n");
    printf("\t/______________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao3);
    opcao3 = toupper(opcao3);

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
    printf("\t/  D - Eliminar Recursos (Incompleto)            \\\n");
    printf("\t\\  V - Voltar                                    /\n");
    printf("\t/________________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao4);
    opcao4 = toupper(opcao4);

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
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao5);
    opcao5 = toupper(opcao5);

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
    printf("\t/          Gabriel Marques nº2180637           \\\n");
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
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao6);
    opcao6 = toupper(opcao6);

    return opcao6;
}


char ConfirmarSaida(void)
{
    char sair;

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


void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r)
{
    char mostrar[MAX_CARACTERES];
    int i = 0, contador_recursos=0,comparar_recursos;

    if (contador_a != 0)
    {
        printf("______________________________________________________________________\n\n");
        printf("Todos os os recursos guardados:\n\n");

        for(int i = 0; i < contador_r; i++ )  ///Ver a lista de contas
        {
            printf("%i - %s\n", i+1, array_recursos[i].nome); ///i+1 para a lista dos recursos não começar em 0
        }
        printf("\n______________________________________________________________________\n\n");
    }
    else
    {
        printf("\nNão tem recursos guardados.\n");
    }

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

    printf("______________________________________________________________________\n\n");
    getch();
}


void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador_a, int contador_r, int id_utilizador, char mostrar[MAX_CARACTERES])
{
    int i = 0, encontrado=99, contador_acessos=0, contador_recursos=0,comparar_recursos, posicao_acesso;

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

    for(i = 0; i < contador_a; i++)
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


int menu_opcao(void)
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


int login(t_register user_registo[MAX_UTILIZADORES],int contador_registo)
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

    for(i = 0; i < contador_registo ; i++)
    {
        if((strcmp(user_registo[i].username_register,username_login)==0) && (strcmp(user_registo[i].password_register,password_login)==0))
        {
            confirmar=i;
            break;
        }
    }

    if(strcmp(user_registo[i].password_register,password_login)!=0)
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


int registar(t_register user_registo[MAX_UTILIZADORES], int contador_registo, int *seq_ID_Utlizador)
{
    int i, NIC, existe = 0;
    char utilizador[MAX_CARACTERES];
    system("cls");
    printf("\n\t|========================| REGISTAR |========================|\n");
    do
    {
        do
        {
            printf("\n\t  Username: ");
            fflush(stdin);
            gets(utilizador);

            for(i = 0; i < contador_registo ; i++)

            {
                if (strcmp(user_registo[i].username_register, utilizador)==0)
                {
                    printf("\n\t  Esse nome de utilizador já existe.\n");
                    getch();
                    break;
                }

            }
        }
        while (utilizador != "admin" && strcmp(user_registo[i].username_register, utilizador)==0);

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
            for(i=0; i< contador_registo; i++)
            {
                if (user_registo[i].NIC_register==NIC)
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
    while(strcmp(user_registo[i].username_register, utilizador)==0 && user_registo[contador_registo].NIC_register==NIC);

    printf("\n\t  Password: ");
    fflush(stdin);
    scanf("%s", user_registo[contador_registo].password_register);
    printf("\n\t  Introduza o seu nome pessoal: ");
    fflush(stdin);
    gets(user_registo[contador_registo].nome);
    strcpy(user_registo[contador_registo].username_register, utilizador);
    user_registo[contador_registo].NIC_register = NIC;
    printf("\n\t  Registo efetuado com sucesso.\n\n");
    printf("\t|============================================================|\n");
    (*seq_ID_Utlizador)++;
    user_registo[contador_registo].ID_Utilizador = *seq_ID_Utlizador;
    getch();

    return contador_registo+1;
}

void VerUtilizadores(t_register user_register[MAX_UTILIZADORES],int contador_registo, int ID_Utilizador)
{
    int i;
    system("cls");
    for (i = 0; i < contador_registo; i++)
    {
        printf("\n\tNome: %s\n", user_register[i].nome);
        printf("\tUsername: %s\n", user_register[i].username_register);
        printf("\tPalavra-Passe: %s\n", user_register[i].password_register);
        printf("\tNumero de identificação civil: %i\n", user_register[i].NIC_register);
        printf("\tID: %i\n\n", user_register[i].ID_Utilizador);
        printf("\t-----------------------------------------\n");
    }
    printf("\n\tPressione uma tecla para continuar...");
    getch();
}

int InserirAdmin(t_register user_register[MAX_UTILIZADORES], int contador_registo)
{
    user_register[contador_registo].ID_Utilizador=0;
    user_register[contador_registo].NIC_register=999999999;
    strcpy(user_register[contador_registo].username_register, "admin");
    strcpy(user_register[contador_registo].password_register, "admin");
    return contador_registo+1;
}

void ler_ficheiro(t_register user_register[], int *contador_registo)
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
        fread(&n_elementos, sizeof(int), 1, ficheiro);
        n_elementos_lidos = fread(user_register, sizeof(t_register), n_elementos, ficheiro);
        if (n_elementos_lidos != n_elementos)
        {
            printf("Impossivel ler o ficheiro\n\n");
            n_elementos = 0;
        }
        else
        {
            printf("\nA LER...\n\n");
            (*contador_registo) = n_elementos;
        }
    }
}

void guardar_ficheiro(t_register user_register[], int contador_registo)
{
    FILE *ficheiro;
    ficheiro = fopen("dados.dat", "wb");
    if (ficheiro == NULL)
    {
        printf("Ficheiro Inexistente\n\n");
    }
    else
    {
        fwrite(&contador_registo, sizeof(int), 1, ficheiro);
        fwrite(user_register, sizeof(t_register), contador_registo, ficheiro);
        fclose(ficheiro);
    }
}

void AlterarRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador_r)
{
    char mostrar[MAX_CARACTERES];
    int comparar_recursos, i;

    printf("Indique o nome do recurso que pretende alterar: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for (i = 0; i < contador_r; i++)
    {
        comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
        if (comparar_recursos == 0)
        {
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
    char login[MAX_CARACTERES], mostrar[MAX_CARACTERES], password[MAX_CARACTERES];
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

char MenuMinhaConta()
{
    char opcao7;
    system("cls");
    printf("\n\tA - Ver dados\n");
    printf("\tB - Alterar dados\n");
    printf("\tC - Apagar conta\n");
    printf("\tV - Voltar\n");
    printf("\tOpção -> ");
    fflush(stdin);
    scanf("%c", &opcao7);
    opcao7 = toupper(opcao7);
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
    printf("\tOpção -> ");
    fflush(stdin);
    scanf("%c", &opcao8);
    opcao8 = toupper(opcao8);
    return opcao8;
}

void AlterarUtilizadoresNome(t_register user_registo[MAX_UTILIZADORES], int contador_registo)
{
    printf("\n\tInsira o novo nome: ");
    fflush(stdin);
    gets(user_registo[contador_registo].nome);
    printf("\tNome guardado com sucesso!");
    getch();
}

void AlterarUtilizadoresLogin(t_register user_registo[MAX_UTILIZADORES], int contador_registo)
{
    int i;
    char utilizador[MAX_CARACTERES];
    do
    {
        printf("\n\tInsira o seu novo login: ");
        fflush(stdin);
        gets(utilizador);

        for( i = 0; i < contador_registo ; i++)

        {
            if (strcmp(user_registo[i].username_register, utilizador)==0)
            {
                printf("\n\t  Esse nome de utilizador já existe.\n");
                getch();
                break;
            }

        }
    }
    while (utilizador != "admin" && strcmp(user_registo[i].username_register, utilizador)==0);
    strcpy(user_registo[contador_registo].username_register, utilizador);
}

void AlterarUtilizadoresPasswords(t_register user_registo[MAX_UTILIZADORES], int contador_registo)
{
    printf("\n\tInsira a nova password: ");
    fflush(stdin);
    scanf("%s", user_registo[contador_registo].password_register);
    printf("\tPassword guardada com sucesso!");
    getch();
}

void AlterarUtilizadoresNIC(t_register user_registo[MAX_UTILIZADORES], int contador_registo)
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
        for(i=0; i< contador_registo; i++)
        {
            if (user_registo[i].NIC_register==NIC)
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
    user_registo[contador_registo].NIC_register = NIC;
}

void EliminarAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int contador_r, int id_utilizador)
{
    char login[MAX_CARACTERES], mostrar[MAX_CARACTERES], password[MAX_CARACTERES], confirm;
    int encontrado, encontrado2;

    VerAcessos(array_acessos, array_recursos, *contador_a, contador_r, id_utilizador, mostrar);
    printf("Indique o LOGIN DO ACESSO que pretende eliminar: ");
    gets(login);

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, mostrar);
        if (encontrado == 0)
        {
            for (int y = 0; y < *contador_a; y++)
            {
                encontrado2 = strcasecmp(array_acessos[y].login, login);
                if (encontrado2 == 0 && array_acessos[y].id_utilizador == id_utilizador)
                {
                    for(int x = y; x < *contador_a-1; x++)
                    {
                        strcpy(array_acessos[x].login, array_acessos[x+1].login);
                        strcpy(array_acessos[x].nome, array_acessos[x+1].nome);
                        strcpy(array_acessos[x].password, array_acessos[x+1].password);
                        array_acessos[x].id_recurso=array_acessos[x+1].id_recurso;
                        array_acessos[x].id_utilizador=array_acessos[x+1].id_utilizador;
                        array_acessos[x].data=array_acessos[x+1].data;
                        array_acessos[x].hora=array_acessos[x+1].hora;
                    }
                    (*contador_a)--;
                }
            }
        }
    }
    getch();
}

void EliminarRecursos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int *contador_a, int *contador_r, int id_utilizador)
{
    char recurso[MAX_CARACTERES], mostrar[MAX_CARACTERES], password[MAX_CARACTERES], confirm;
    int encontrado;

    printf("Indique o nome do recurso que pretende eliminar: ");
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
                    array_recursos[x].identificador = array_recursos[x+1].identificador;
                    array_recursos[x].grau_seguranca = array_recursos[x+1].grau_seguranca;
                }
                (*contador_r)--;
            }
            else
                printf("Impossivel eliminar porque você ou outro utilizador tem acessos guardados no recurso\n");
        }
    }
    getch();
}

void EliminarUtilizadores(t_register user_registo[MAX_UTILIZADORES], t_acessos array_acessos[MAX_ACESSOS], int *contador_registo, int id_utilizador)
{
    for(int i = 0; i < *contador_registo; i++)
    {
        if (array_acessos[i].id_utilizador != id_utilizador) ///Procurar se há algum id_recurso que é guardado no acesso com o numero de recurso que se está a apagar (i)
        {
            for(int x = i; x < *contador_registo-1; x++)
            {
                user_registo[x].ID_Utilizador = user_registo[x+1].ID_Utilizador;
                strcpy(user_registo[x].nome, user_registo[x+1].nome);
                strcpy(user_registo[x].password_register, user_registo[x+1].password_register);
                strcpy(user_registo[x].username_login, user_registo[x+1].username_login);
                strcpy(user_registo[x].username_register, user_registo[x+1].username_register);
                user_registo[x].NIC_register = user_registo[x+1].NIC_register;
            }
            (*contador_registo)--;
        }
        else
            printf("Impossivel eliminar porque você tem acessos guardados\n");
    }
}
